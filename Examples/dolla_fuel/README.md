# dolla_fuel

Versao do sistema de combustivel adaptada ao FiveX no Xbox 360.

## Uso

1. Compile o FiveX com os novos bindings de rope.
2. Copie as pastas `drawhud` e `dolla_fuel` para
   `Hdd:\FiveX\Resources` ou para a pasta equivalente em `Usb0`/`Usb1`.
3. Abra o menu do FiveX com `RB + X`.
4. Use `Refresh Resouces` e inicie `dolla_fuel`. A dependência `drawhud` será
   iniciada automaticamente.
5. Use o direcional direito para pegar, conectar, retirar e devolver o bico.

## Diferencas da versao FiveM

- hashes sao obtidos com `GetHashKey`, sem sintaxe CfxLua;
- bombas e veiculos usam natives originais do GTA V, sem `GetGamePool`;
- o combustivel fica em uma tabela local da resource porque a versao Xbox 360
  nao expoe `GET/SET_VEHICLE_FUEL_LEVEL`;
- o consumo usa velocidade e acelerador como carga do motor, pois a versao
  Xbox 360 nao expoe `GET_VEHICLE_CURRENT_RPM`;
- nao usa servidor, rede, NUI, state bags ou framework.
- usa a interface compartilhada da resource `drawhud` sem HTML.
