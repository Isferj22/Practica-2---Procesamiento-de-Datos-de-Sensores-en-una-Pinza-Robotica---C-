# Práctica 2 – Procesamiento de Datos de Sensores en una Pinza Robótica
## 1. Introducción 
En esta práctica se realiza la captura de datos de sensores de una pinza robótica industrial, su almacenamiento en ficheros y posteriormente su analisis mediante C++ y un script de Bash

## 2. Descripción del problema y de lo que se hace 
El objetivo de la práctica es construir un sistema que: 

- Lea datos de sensores desde un archivo de texto (datos_pinza.txt). 
- Almacene los datos en arrays y matrices para su procesamiento. 
- Ordene las muestras por ID. 
- Calcule medias, máximos, mínimos y fuerza total aplicada. 
- Evalúe la estabilidad del agarre de la pinza comparando la fuerza del dedo izquierdo y derecho. 
- Genere un archivo de resultados (resultado_pinza.txt) con toda la información procesada. 
- Automatice la ejecución del programa mediante un script de Bash (ejecutar.sh) lanzando el programa en segundo plano y controlando su finalizacion. 

## 3. Estructura del proyecto 
El proyecto tiene la siguiente estructura de archivos: 
trabajo_2/ 
│ 
├── pinza.cpp # Código fuente en C++ 
├── datos_pinza.txt # Archivo de datos de entrada 
├── resultado_pinza.txt # Archivo generado 
├── ejecutar.sh # Script de Bash 
└── README.md 

### Descripción de los archivos 
- **pinza.cpp**: Programa principal que procesa los datos de los sensores y genera los resultados. 
- **datos_pinza.txt**: Archivo que contiene los datos sin procesar de los sensores (ID, galga, fuerza izquierda y derecha).
- **resultado_pinza.txt**: Archivo donde se guardan los datos procesados, estadísticas y clasificación de estabilidad. 
- **ejecutar.sh**: Script de Bash que ejecuta el programa pinza en segundo plano, espera su finalización y controla el proceso

## 4. Requisitos del sistema y cómo instalarlo 
Para ejecutar esta práctica se necesita: 

- Sistema operativo: Linux o entorno Linux (WSL en Windows). 
- Software necesario: 
	- Bash 
	- Compilador de C++ (g++) 

### Instalación de dependencias Instalar g++ si no está disponible:
sudo apt update
sudo apt install g++

### Permisos necesarios
- Dar permisos de ejecución al binario:
        chmod +x ejecutar.sh

## 5. Ejecucion del programa
- Compilar el programa de C++:
        g++ -o pinza pinza.cpp

- Ejecutar el programa (2 formas):
        - Mediante bash:
                ./ejecutar.sh
        - Directamente el binario:
                ./pinza

## 6. Funcionamiento

El funcionamiento del sistema se divide en dos fases principales:

Lectura y procesamiento de datos (C++)
Lee el archivo datos_pinza.txt.
Almacena los datos en matrices y arrays.
Ordena los datos por ID.
Calcula medias, máximos, mínimos y fuerza total global.
Evalúa la estabilidad del agarre según la diferencia de fuerzas entre dedos.
Genera resultado_pinza.txt con toda la información.
Automatización y control del proceso (Bash)
Lanza el programa pinza en segundo plano.
Espera a que finalice o, si se cuelga, lo finaliza tras un timeout.
Permite ejecutar la práctica completa de manera automática y reproducible.


## 7. Salida esperada
Por pantalla y en el archivo resultado_pinza.txt se obtienen:

- Datos de cada muestra ordenados por ID.
- Medias de galga, fuerza izquierda y derecha.
- Máximos y mínimos de cada sensor.
- Fuerza total global aplicada.
- Clasificación de cada muestra: ESTABLE o INESTABLE

## 8. Autor
Ismael Fernandez Jorreto
