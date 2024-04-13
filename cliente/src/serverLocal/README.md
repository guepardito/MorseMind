# Como copmpilar el cliente y servidor

## Observaciones Previas
Para compilar debes ir a la carpeta serverLocal en la terminal
``` bash
cd ./cliente/src/serverLocal/
```

## Cliente
``` bash
gcc .\cliente.c .\clientUtils.c -o cliente.exe -lws2_32
```
Solo funciona si el servidor ya esta activo, en caso contrario dara error

## Servidor
``` bash
gcc .\servidor.c .\serverUtils.c -o server.exe -lws2_32
```
Al ejecutarlo estará en escucha hasta que se mate el proceso en terminal (ctrl + c)

<br>
<br>

Es para ver que funciona, no hace absolutamente nada
Lo he hecho a parte para que luego solo sea copiar y pegar (espero)