#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {

    // Arrays para almacenar los datos
    float datos[100][3];      // Matriz general
    int ids[100];             // Identificadores
    float galga[100];         // Sensor galga
    float fuerza_izq[100];    // Fuerza izquierda
    float fuerza_der[100];    // Fuerza derecha

    int n = 0; // contador de muestras

    // Abrir archivo de entrada
    ifstream archivo("datos_pinza.txt");

    // Comprobar se si abre correctamente
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de entrada" << endl;
        return 1;
    }

    // Lectura de datos desde el archivo
    while (archivo >> ids[n] >> galga[n] >> fuerza_izq[n] >> fuerza_der[n] && n < 100) {
        // Lo Guardamos tambien en la matriz
        datos[n][0] = galga[n];
        datos[n][1] = fuerza_izq[n];
        datos[n][2] = fuerza_der[n];
        n++;
    }
    archivo.close(); //cerramos el archivo

    // Ponemos un limite de datos a mostrar (100)
    if (n == 100) cout << "Se alcanzó el límite de 100 datos" << endl;

    // Ordenar por ID
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (ids[j] > ids[j+1]) {
                int temp_id = ids[j]; ids[j] = ids[j+1]; ids[j+1] = temp_id;
                float temp_galga = galga[j]; galga[j] = galga[j+1]; galga[j+1] = temp_galga;
                float temp_izq = fuerza_izq[j]; fuerza_izq[j] = fuerza_izq[j+1]; fuerza_izq[j+1] = temp_izq;
                float temp_der = fuerza_der[j]; fuerza_der[j] = fuerza_der[j+1]; fuerza_der[j+1] = temp_der;
                for(int k=0;k<3;k++){
                    float temp = datos[j][k]; datos[j][k] = datos[j+1][k]; datos[j+1][k] = temp;
                }
            }
        }
    }

    // Mostrar datos
    cout << "\nDatos ordenados por ID:\n";
    for (int i = 0; i < n; i++) {
        cout << "ID: " << ids[i] 
             << " Galga: " << galga[i] 
             << " Izq: " << fuerza_izq[i] 
             << " Der: " << fuerza_der[i] << endl;
    }

    // Calculo de medias
    float suma_galga=0, suma_izq=0, suma_der=0;
    for(int i=0;i<n;i++){
        suma_galga += galga[i];
        suma_izq += fuerza_izq[i];
        suma_der += fuerza_der[i];
    }
    float media_galga = suma_galga/n;
    float media_izq = suma_izq/n;
    float media_der = suma_der/n;

    cout << "\nMedias:\nGalga: " << media_galga
         << "\nIzq: " << media_izq
         << "\nDer: " << media_der << endl;

    // Maximos y minimos
    // Inicializamos el maximo y el minimo con el primer valor del array
    float max_galga=galga[0], min_galga=galga[0];
    float max_izq=fuerza_izq[0], min_izq=fuerza_izq[0];
    float max_der=fuerza_der[0], min_der=fuerza_der[0];

    // Recorremos el resto de datos
    for(int i=1;i<n;i++){
        if(galga[i]>max_galga) max_galga=galga[i];
        if(galga[i]<min_galga) min_galga=galga[i];
        if(fuerza_izq[i]>max_izq) max_izq=fuerza_izq[i];
        if(fuerza_izq[i]<min_izq) min_izq=fuerza_izq[i];
        if(fuerza_der[i]>max_der) max_der=fuerza_der[i];
        if(fuerza_der[i]<min_der) min_der=fuerza_der[i];
    }

    // Mostrar resultados
    cout << "\nMaximos y minimos:\n"
         << "Galga -> Max: " << max_galga << " Min: " << min_galga << endl
         << "Izq   -> Max: " << max_izq << " Min: " << min_izq << endl
         << "Der   -> Max: " << max_der << " Min: " << min_der << endl;

    // Fuerza total global
    float fuerza_total=0;
    for(int i=0;i<n;i++){
        fuerza_total += fuerza_izq[i]+fuerza_der[i];
    }
    cout << "\nFuerza total global: " << fuerza_total << "\n";

    // Archivo de salida
    ofstream salida("resultado_pinza.txt");
    // Comprobamos que el archivo se haya creado
    if(!salida.is_open()){
        cerr << "Error al crear el archivo de salida" << endl;
        return 1;
    }

    // Guardamos datos originales
    salida << "RESULTADOS DEL SISTEMA DE PINZA ROBOTICA\n\n";
    salida << "Datos ordenados:\n";
    for(int i=0;i<n;i++){
        salida << ids[i] << " " << galga[i] << " " << fuerza_izq[i] << " " << fuerza_der[i] << endl;
    }

    // Medias, maximos, minimos y fuerza total
    salida << "\nMedias:\nGalga = " << media_galga
           << "\nFuerza izquierda = " << media_izq
           << "\nFuerza derecha = " << media_der << endl;

    salida << "\nMaximos y minimos:\n"
           << "Galga -> Max: " << max_galga << " Min: " << min_galga << endl
           << "Izq   -> Max: " << max_izq << " Min: " << min_izq << endl
           << "Der   -> Max: " << max_der << " Min: " << min_der << endl;

    salida << "\nFuerza total global: " << fuerza_total << "\n";

    // Clasificacion estable/ inestable
    salida << "\nClasificacion:\n";
    for(int i=0;i<n;i++){
        //diferencia entre fuerzas
        float diff = abs(fuerza_izq[i]-fuerza_der[i]);
        // Inestable
        if(diff>0.15){
            cout << "Estado muestra " << ids[i] << ": INESTABLE" << endl;
            salida << ids[i] << " INESTABLE" << endl;
        } else {
            cout << "Estado muestra " << ids[i] << ": ESTABLE" << endl;
            salida << ids[i] << " ESTABLE" << endl;
        }
    }

    salida.close(); //cerrarmos el archivo
    return 0;
}
