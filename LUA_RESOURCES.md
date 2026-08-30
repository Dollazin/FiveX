# Guia de resources Lua do FiveX

Este documento descreve a API realmente implementada pelo FiveX. A camada de
compatibilidade facilita portar scripts client-side, mas não representa o
runtime completo do FiveM.

## 1. Pastas reconhecidas

O refresh procura subpastas, nesta ordem:

```text
Hdd:\FiveX\Resources
Usb0:\FiveX\Resources
Usb1:\FiveX\Resources
```

Cada subpasta válida vira uma resource. O HDD é montado e sua estrutura é
criada pelo FiveX. Um USB ausente ou sem a pasta esperada é simplesmente
ignorado.

Nomes de resources:

- precisam ter de 1 a 63 caracteres;
- aceitam letras, números, `_`, `-` e `.`;
- não podem conter espaços, barras ou `:`;
- devem ser únicos entre HDD e USBs.

Ao executar **Refresh Resouces**, resources novas entram no catálogo. Se uma
pasta foi removida, a resource é parada primeiro, seus objetos são limpos e a
entrada desaparece do menu. Não existe estado `MISSING`.

No menu, pressione `X` sobre uma resource para alternar seu auto-start. A
marcação `AUTO-START` aparece em amarelo e é persistida em
`Hdd:\FiveX\FiveX.ini`. As resources marcadas são iniciadas uma única vez por
carregamento do FiveX, somente depois de `COMBINED_READY`; um refresh manual
não dispara o auto-start.

## 2. Estrutura mínima

```text
my_resource\
├── fxmanifest.lua
└── client.lua
```

O manifest deve existir, ser Lua válido e registrar ao menos um script.

```lua
fx_version 'cerulean'
game 'gta5'

client_script 'client.lua'
```

As chaves `fx_version` e `game` são aceitas como metadados, mas não alteram o
comportamento do runtime.

### Vários scripts

```lua
client_scripts {
    'config.lua',
    'client/main.lua'
}

shared_script 'shared.lua'
```

São implementadas:

- `client_script` e `client_scripts`;
- `shared_script` e `shared_scripts`;
- `dependency` e `dependencies`.

Os scripts são carregados na ordem em que aparecem no manifest. Caminhos com
`/` ou `\` são normalizados para o separador do Xbox, inclusive em subpastas.
Caminhos relativos não podem conter `..` nem `:`. Wildcards como
`client/*.lua` ainda não são suportados: liste cada arquivo explicitamente.

As seguintes entradas são reconhecidas e ignoradas para facilitar o uso de
manifests existentes:

```text
fx_version, game, games, lua54, author, description, version, repository,
server_script, server_scripts, file, files, ui_page, data_file,
escrow_ignore, provide, use_experimental_fxv2_oal
```

`server_script` e `server_scripts` não são executados.

## 3. Dependências e arquivos compartilhados

Uma resource pode declarar outra como dependência:

```lua
dependency 'common'

dependencies {
    'common',
    'vehicles'
}
```

As dependências são iniciadas automaticamente antes da resource. Se uma
dependência estiver ausente ou falhar, a resource fica em `FAILED`. Ao parar
uma dependência, as resources ativas que dependem dela também são paradas.

Também é possível carregar um script de outra resource já catalogada:

```lua
shared_script '@common/shared/config.lua'
client_script 'client.lua'
```

## 4. Estados e ciclo de vida

Estados exibidos no menu:

- `STOPPED`: detectada, mas sem VM Lua ativa;
- `STARTED`: scripts carregados e em execução;
- `FAILED`: manifest, dependência, memória ou script apresentou erro ao iniciar.

Quando uma resource inicia, o FiveX:

1. lê o manifest e resolve dependências;
2. cria uma VM Lua isolada com limite de memória;
3. registra a API e carrega os scripts;
4. executa as declarações de topo;
5. dispara `onResourceStart`.

Quando ela para, o FiveX:

1. para primeiro as dependentes;
2. dispara `onResourceStop`;
3. encerra threads, handlers e exports;
4. remove entidades criadas pelo binding controlado de `CreateVehicle`;
5. fecha a VM Lua.

Exemplo:

```lua
local current = GetCurrentResourceName()

AddEventHandler('onResourceStart', function(name)
    if name == current then
        print(current .. ' started')
    end
end)

AddEventHandler('onResourceStop', function(name)
    if name == current then
        print(current .. ' stopped')
    end
end)
```

## 5. Threads, espera e timers

```lua
CreateThread(function()
    while true do
        Wait(1000)
        print('tick')
    end
end)

SetTimeout(5000, function()
    print('five seconds later')
end)
```

Aliases disponíveis:

```lua
Citizen.CreateThread(...)
Citizen.Wait(...)
Citizen.SetTimeout(...)
Citizen.Trace(...)
```

`Wait` somente pode ser usado em uma coroutine criada pelo scheduler. Não use
`Wait` em uma função síncrona como um export.

## 6. Eventos

```lua
AddEventHandler('my_event', function(message, value)
    print(message, value)
end)

TriggerEvent('my_event', 'hello', 360)
```

`TriggerEvent` distribui o evento localmente para as resources iniciadas. São
copiados valores `nil`, booleanos, números, strings, `vector3` e tabelas com
profundidade limitada.

`RegisterNetEvent` existe apenas como no-op de compatibilidade. O FiveX não tem
transporte de rede nem servidor.

## 7. Exports entre resources

Na resource `math_resource`:

```lua
exports('sum', function(a, b)
    return a + b
end)
```

Em outra resource:

```lua
local result = exports['math_resource']:sum(10, 20)
print('result:', result)
```

O destino precisa estar em `STARTED`. As chamadas são síncronas, retornam no
máximo oito valores e não devem usar `Wait`.

## 8. Biblioteca Lua disponível

Cada VM oferece:

- biblioteca base;
- `table`;
- `string`;
- `math`;
- `coroutine`;
- `utf8`.

Bibliotecas de sistema de arquivos, sistema operacional, pacotes dinâmicos e
debug não são abertas. `dofile` e `loadfile` também são removidos. Isso reduz o
acesso da resource ao ambiente do console, mas não deve ser tratado como uma
garantia absoluta de segurança contra código Lua não confiável.

`print(...)` concatena os argumentos e mostra uma notificação in-game. Ele não
escreve o texto do script no `DbgPrint`.

## 9. Vector3

```lua
local a = vector3(1.0, 2.0, 3.0)
local b = vec3(4.0, 5.0, 6.0)
local c = a + b

print(c.x, c.y, c.z)
print(#c)
```

`vector3` oferece `.x`, `.y`, `.z`, conversão para string, comprimento e
operações de soma, subtração, multiplicação e divisão.

## 10. Natives do GTA V

O catálogo é gerado com as assinaturas oficiais do FiveM em
`Tools/NativeMetadata/natives_fivem.json` e usa somente os `jhash` legados de
32 bits. Cada resource recebe um resolvedor leve; o wrapper Lua de uma native
só é criado e armazenado quando o script acessa aquele nome pela primeira vez.
Nesse momento o FiveX também confirma que existe um handler na build do Xbox.

O catálogo gerado contém 4.905 nomes candidatos, incluindo aliases. Entradas
sem handler Xbox não são expostas à resource. Como os wrappers são resolvidos
sob demanda, várias resources não duplicam milhares de closures na memória.

```lua
local player = PlayerId()
local ped = PlayerPedId()
local coords = GetEntityCoords(ped, true)

SetPlayerInvincible(player, true)
print(coords.x, coords.y, coords.z)
```

Natives com parâmetros de saída seguros retornam os valores adicionais para
Lua:

```lua
local width, height = GetScreenResolution()
local parsed, number = StringToInt('360')
local primary, secondary = GetVehicleColours(vehicle)
```

Natives de ponteiro/handle suportadas recebem o handle normal, nunca um
endereço bruto:

```lua
DeleteVehicle(vehicle)
RemoveBlip(blip)
```

Arrays, estruturas arbitrárias e ponteiros sem conversão segura não são
expostos.

### Chamada direta por hash

Para uma native sem binding por nome:

```lua
local exists = Citizen.InvokeNative(0x3AC90869, 'bool', ped)
Citizen.InvokeNative(0xC1213A21, 'void', ped, true)
```

Tipos de retorno aceitos:

```text
void
int / integer / hash / entity
float
bool / boolean
string
vector3
```

Argumentos diretos aceitam `nil`, boolean, inteiro de 32 bits, float, string e
`vector3`. Use `1.0` quando a native espera float; `1` é tratado como inteiro.
Use hashes de 32 bits do Xbox 360, não hashes de 64 bits da versão PC. Resources
que chamam natives por nome usam as assinaturas Lua do FiveM sempre que existe
um `jhash` correspondente.

Se o hash já estiver no catálogo seguro, o número de argumentos e o retorno
precisam corresponder à assinatura registrada. Natives conhecidas que exigem
ponteiros devem ser chamadas pelo nome para que o runtime prepare o armazenamento
corretamente.

## 11. API de gerenciamento

```lua
GetCurrentResourceName()
GetResourceState('resource_name')
StartResource('resource_name')
StopResource('resource_name')
RestartResource('resource_name')
```

`GetResourceState` retorna `starting`, `started`, `failed`, `stopped` ou
`missing`. Start, stop e restart solicitados por Lua entram em uma fila e são
processados pelo runtime fora da chamada atual.

Outros helpers expostos diretamente incluem:

```text
GetGameTimer, PlayerId, PlayerPedId, DoesEntityExist, GetEntityCoords,
GetFirstBlipInfoId, DoesBlipExist, GetBlipInfoIdCoord,
GetGroundZFor_3dCoord, GetGroundZFor3dCoord, SetEntityCoords,
GetEntityHeading, GetHashKey, RequestModel, HasModelLoaded,
SetModelAsNoLongerNeeded, CreateVehicle, DeleteEntity,
SetVehicleEngineOn, IsControlJustPressed
```

Os bindings manuais também aceitam as formas usuais do FiveM. Por exemplo,
`SetEntityCoords` aceita os quatro argumentos básicos ou os oito argumentos
com flags; `GetGroundZFor3dCoord` aceita o `includeWater` do FiveM; e
`SetVehicleEngineOn` aceita o quarto argumento `disableAutoStart`, ignorado no
Xbox porque essa build não possui flag equivalente.

Além deles, use os nomes disponíveis em
`Runtime/Lua/LuaNativeCatalog.inl`.

Esse catálogo é gerado diretamente de
`Tools/NativeMetadata/natives_fivem.json`. O gerador usa apenas definições que
possuem `jhash` legado de 32 bits e não lê os wrappers C++ do núcleo. Ao usar
uma native pela primeira vez, a runtime valida seu hash na tabela nativa do
GTA V do Xbox e mantém o wrapper em cache naquela resource.

### Corda física

O catálogo também expõe as natives Xbox de rope usadas por resources de
mangueira, reboque e cabo:

```lua
RopeLoadTextures()
local rope = AddRope(
    x, y, z,
    0.0, 0.0, 0.0,
    initialLength, 4, maxLength, 0.5, 0.5,
    false, false, false, 1.0, false
)

AttachEntitiesToRope(
    rope, entity1, entity2,
    point1.x, point1.y, point1.z,
    point2.x, point2.y, point2.z,
    initialLength, false, false, '', ''
)
```

O ponteiro interno opcional de `ADD_ROPE` é preenchido com `NULL` pelo binding
seguro e não aparece como argumento Lua. Os dois últimos argumentos de
`AttachEntitiesToRope` são os nomes opcionais dos bones e podem usar strings
vazias. `DeleteRope(rope)` recebe o handle normal; o runtime cria o ponteiro
temporário exigido pela native Xbox.

## 12. Exemplo: carregar e criar um veículo

```lua
CreateThread(function()
    local model = GetHashKey('adder')
    RequestModel(model)

    while not HasModelLoaded(model) do
        Wait(0)
    end

    local ped = PlayerPedId()
    local position = GetEntityCoords(ped, true)
    local heading = GetEntityHeading(ped)
    local vehicle = CreateVehicle(
        model,
        position.x + 3.0,
        position.y,
        position.z,
        heading,
        true,
        false
    )

    SetModelAsNoLongerNeeded(model)
    print('Vehicle created:', vehicle)
end)
```

Entidades criadas por `CreateVehicle` são registradas como pertencentes à
resource e são removidas quando ela para. Natives genéricas podem criar objetos
que o runtime não consegue rastrear; a própria resource deve limpá-los em
`onResourceStop`.

## 13. Limites atuais

| Item | Limite |
| --- | ---: |
| Resources catalogadas | 64 |
| Scripts por resource | 32 |
| Dependências por resource | 12 |
| Threads por resource | 64 |
| Event handlers por resource | 64 |
| Exports por resource | 32 |
| Entidades rastreadas por resource | 128 |
| Ações pendentes globais | 16 |
| Tamanho de cada arquivo Lua/manifest | 2 MiB |
| Memória Lua por resource | 8 MiB |
| Budget inicial por thread | 2.000.000 instruções |

Uma thread que ultrapassa seu budget é interrompida para não monopolizar o
game thread. Loops contínuos devem sempre chamar `Wait`.

## 14. Diferenças importantes para FiveM

- somente scripts client-side;
- sem sintaxe exclusiva de CfxLua/GLM;
- sem rede, servidor, NUI, OneSync ou state bags;
- sem wildcards no manifest;
- exports síncronos e sem `Wait`;
- sem APIs de arquivo ou sistema operacional;
- hashes de natives são os hashes Xbox 360 de 32 bits.

Ao manter uma resource compatível com PC e Xbox 360, coloque chamadas
específicas de cada plataforma em pequenos arquivos adaptadores e mantenha a
lógica principal em Lua portátil.

## 15. Diagnóstico rápido

### A resource não aparece

- confirme a pasta `FiveX\Resources` no dispositivo;
- confirme que a resource é uma subpasta, não um `.lua` solto;
- remova espaços e caracteres inválidos do nome;
- use **Refresh Resouces**.

### A resource aparece como `FAILED`

- valide a sintaxe de `fxmanifest.lua` e dos scripts;
- confirme que há ao menos um `client_script` ou `shared_script`;
- liste arquivos explicitamente, sem wildcards;
- confirme que dependências existem;
- verifique limites de arquivo e memória.

### Alterei o script, mas nada mudou

Parar e iniciar a resource fecha a VM e relê os arquivos. O refresh atualiza o
catálogo de pastas, mas não reinicia automaticamente uma resource que continua
ativa.

### O console travou ao chamar uma native

Revise a assinatura, os tipos, a versão do GTA/Title Update e o hash usado. Uma
native pode aceitar valores sintaticamente válidos e ainda assim ser insegura
no estado atual do jogo. Teste primeiro em uma resource mínima e limpe objetos
criados no evento `onResourceStop`.
