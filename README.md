# proy-buscaminas-raylib


## Para correr en Windows

Descargar MSYS2 e instalar en la terminal de MSYS2 ucrt los paquetes
`mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja mingw-w64-x86_64-make`
junto con los paquetes por defecto que te indica la pagina oficial.

Se debe asegurar que el PATH de windows tenga la direccion correcta
a la carpeta de MSYS2 ucrt.

## Para correr en Linux

Solo sal de la casa a correr o si lo prefieres instala los paquetes
`cmake gcc g++ make` con tu administrador de paquetes de confianza.

### Comandos para construir
```
cmake -S . -B build
cd build
make -j
```
O su equivalente en windows y MSYS2, se recomienda usar la extension
cmake-tools para Visual Studio Code para una experiencia más simplificada
e integrada a la hora de correr el juego.
