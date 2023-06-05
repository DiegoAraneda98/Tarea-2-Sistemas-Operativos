# Tarea-2-Sistemas-Operativos
## Carrera de Caballos
### Esta tarea consiste en crear un juego sobre una ***Carrera de caballos***, en la cual deberemos implementar en lenguaje de programación ***C***, junto con la librería de ***ncurses.h*** para ayudarnos con el control de la pantalla del juego, tambien junto a la librería ***pthread.h*** para el manejo de hilos en la carrera y por último el movimiento de los caballos durante la carrera será aleatorio.

## Programas utilizados

* [GitHub Desktop](https://desktop.github.com/) - Herramienta para tener los repositorios en la nube y mantener las versiones.
* [Visual Studio Code](https://visualstudio.microsoft.com/es/) - IDE y editor para la creación del Algoritmo.
* [Remote Viewer]() - Máquina virtual en la cual se compilo y ejecuto el programa.

## Bibliotecas utilizadas

* ***pthread.h***: Biblioteca para el manejo de threads.
* ***unistd.h***: Biblioteca para funciones de sistema Unix.
* ***stdlib.h***: Biblioteca para funciones estándar.
* ***ncurses.h***: Biblioteca para el manejo de la pantalla.

## Instalación 

* Necesitaremos instalar la libreria de ncurses.h con el siguiente comando en la terminal.
```
sudo apte install libncurses5-dev libncursesw5-dev
```

* Para descargar el programa haga click en el siguiente [Link]()

## Ejecución del programa

* Debemos estar en el mismo directorio donde se encuentra el código fuente, para ello se debe escribir el siguiente comando, si es que el archivo se encuentra en el escritorio.
```
cd Desktop/carrera_caballos_2
```
* Luego para poder compilar el programa debemos usar el siguiente comando en la terminal, en el mismo directorio donde se encuentra el código fuente.
```
gcc -o carrera_caballos_2 carrera_caballos_2.c -lpthread -lncurses -DMUTEX
```
## Resultados
```
Caballo A: 2 vueltas - 60 metros
Caballo B: 2 vueltas - 60 metros
Caballo C: 2 vueltas - 60 metros
Caballo D: 2 vueltas - 60 metros
Caballo E: 2 vueltas - 60 metros
Caballo F: 2 vueltas - 60 metros
Caballo G: 2 vueltas - 60 metros

Totales: 14 vueltas - 420 metros

Carril 0|A|A-----------------------|2/2 vueltas
Carril 1|B|B-----------------------|2/2 vueltas
Carril 2|C|C-----------------------|2/2 vueltas
Carril 3|D|D-----------------------|2/2 vueltas
Carril 4|E|E-----------------------|2/2 vueltas
Carril 5|F|F-----------------------|2/2 vueltas
Carril 6|G|G-----------------------|2/2 vueltas

Largo de la pista: 30 metros
Numero de vueltas: 2
El ganador es: D
Carrera Terminada!!!!!!

```
## Autores
* Diego Araneda  - daranedah@ing.ucsc.cl
* Hector Contreras - hcontreras@ing.ucsc.cl
* Ignacio Valdebenito - ivaldebenito@ing.ucsc.cl
