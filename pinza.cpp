#include <iostream>
#include <fstream> //Necesario para lectura/escritura archivos

using namespace std;

int main() {
    float datos[22000][3];   // Matriz general
    int ids[22000];          // Identificadores
    float galga[22000];      // Sensor galga
    float fuerza_izq[22000]; // Fuerza izquierda
    float fuerza_der[22000]; // Fuerza derecha

    int n = 0;    // contador de muestras

    // Abrir archivo de entrada
    ifstream archivo("datos_pinza.txt");

    // Comprobar si se abre correctamente
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir datos_pinza.txt" << endl;
        return 1;
    }

    // Lectura de datos desde el archivo
    while (n < 22000 && archivo >> ids[n] >> galga[n] >> fuerza_izq[n] >> fuerza_der[n]) {
        // Lo guardmaos en la matriz
        datos[n][0] = galga[n];
        datos[n][1] = fuerza_izq[n];
        datos[n][2] = fuerza_der[n];
        n++;
    }
    archivo.close(); // cerramos el archivo

    if (n == 0) {
        cout << "Archivo vacío." << endl;
        return 1;
    }

    // Ordenar por ID
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ids[j] > ids[j + 1]) {

                int tmp_id = ids[j];
                ids[j] = ids[j + 1];
                ids[j + 1] = tmp_id;

                float tmp_g = galga[j];
                galga[j] = galga[j + 1];
                galga[j + 1] = tmp_g;

                float tmp_i = fuerza_izq[j];
                fuerza_izq[j] = fuerza_izq[j + 1];
                fuerza_izq[j + 1] = tmp_i;

                float tmp_d = fuerza_der[j];
                fuerza_der[j] = fuerza_der[j + 1];
                fuerza_der[j + 1] = tmp_d;

                for (int k = 0; k < 3; k++) {
                    float temp = datos[j][k];
                    datos[j][k] = datos[j + 1][k];
                    datos[j + 1][k] = temp;
                }
            }
        }
    }

    // Cálculos
    double suma_g = 0, suma_i = 0, suma_d = 0;
    double fuerza_total = 0;

    float max_g = galga[0], min_g = galga[0];
    float max_i = fuerza_izq[0], min_i = fuerza_izq[0];
    float max_d = fuerza_der[0], min_d = fuerza_der[0];

    for (int i = 0; i < n; i++) {
        suma_g += galga[i];
        suma_i += fuerza_izq[i];
        suma_d += fuerza_der[i];

        fuerza_total += (fuerza_izq[i] + fuerza_der[i]);

        // max/min galga
        if (galga[i] > max_g) max_g = galga[i];
        if (galga[i] < min_g) min_g = galga[i];

        // max/min izq
        if (fuerza_izq[i] > max_i) max_i = fuerza_izq[i];
        if (fuerza_izq[i] < min_i) min_i = fuerza_izq[i];

        // max/min der
        if (fuerza_der[i] > max_d) max_d = fuerza_der[i];
        if (fuerza_der[i] < min_d) min_d = fuerza_der[i];
    }

    float m_g = suma_g / n;
    float m_i = suma_i / n;
    float m_d = suma_d / n;

    // Mostrar primeros 100 datos ordenados por terminal
    cout << "\n--- 100 PRIMERAS MUESTRAS ORDENADAS POR ID ---\n";

    int contador = 0;
    for (int i = 0; i < n && contador < 100; i++) {

        float diff;
        if (fuerza_izq[i] > fuerza_der[i]) {
            diff = fuerza_izq[i] - fuerza_der[i];
        } else {
            diff = fuerza_der[i] - fuerza_izq[i];
        }

        cout << "ID: " << ids[i]
             << " Galga: " << galga[i]
             << " Izq: " << fuerza_izq[i]
             << " Der: " << fuerza_der[i];

        // Clasificacion estables/inestable     
        if (diff > 0.15) {
            cout << " INESTABLE";
        } else {
            cout << " ESTABLE";
        }

        cout << endl;
        contador++;
    }

    // Mostrar todos los calculos
    cout << "\n--- MEDIAS ---\n";
    cout << "Media Galga: " << m_g << endl;
    cout << "Media Izquierda: " << m_i << endl;
    cout << "Media Derecha: " << m_d << endl;

    cout << "\n--- FUERZA TOTAL GLOBAL ---\n";
    cout << fuerza_total << endl;

    cout << "\n--- MAXIMOS Y MINIMOS ---\n";
    cout << "Galga -> Max: " << max_g << " Min: " << min_g << endl;
    cout << "Izquierda -> Max: " << max_i << " Min: " << min_i << endl;
    cout << "Derecha -> Max: " << max_d << " Min: " << min_d << endl;

    // Creacion del archivo de resultados
    ofstream salida("resultado_pinza.txt");

    // Comprobamos si se ha abierto bien, si es asi lo rellanamos con todos los datos
    if (salida.is_open()) {

        salida << "DATOS ORDENADOS POR ID\n\n";

        for (int i = 0; i < n; i++) {

            float diff;
            if (fuerza_izq[i] > fuerza_der[i]) {
                diff = fuerza_izq[i] - fuerza_der[i];
            } else {
                diff = fuerza_der[i] - fuerza_izq[i];
            }

            salida << ids[i] << " "
                   << galga[i] << " "
                   << fuerza_izq[i] << " "
                   << fuerza_der[i];

            if (diff > 0.15) {
                salida << " INESTABLE\n";
            } else {
                salida << " ESTABLE\n";
            }
        }

        // Mostramos los mismos calculos que por terminal al final del archivo
        salida << "\n--- RESUMEN FINAL ---\n";
        salida << "Media Galga: " << m_g << "\n";
        salida << "Media Izquierda: " << m_i << "\n";
        salida << "Media Derecha: " << m_d << "\n";
        salida << "Fuerza Total Global: " << fuerza_total << "\n";

        salida << "\n--- MAXIMOS Y MINIMOS ---\n";
        salida << "Galga -> Max: " << max_g << " Min: " << min_g << "\n";
        salida << "Izquierda -> Max: " << max_i << " Min: " << min_i << "\n";
        salida << "Derecha -> Max: " << max_d << " Min: " << min_d << "\n";

        salida.close(); // cerramos el archivo
    }

    return 0;
}
