#!/bin/bash

echo "1. Ejecutando el binario..."

# Ejecuta el programa en segundo plano y captura su PID
./pinza &
PID=$!

echo "2. Proceso lanzado en segundo plano con PID: $PID"

# Definimos un tiempo máximo de espera en segundos
TIMEOUT=10

echo "3. Esperando finalización (timeout ${TIMEOUT}s)..."

# Bucle para comprobar cada segundo si el proceso sigue activo
for ((i=0; i<TIMEOUT; i++)); do
    # ps -p $PID verifica si el proceso con ese PID sigue existiendo
    if ! ps -p $PID > /dev/null; then
        echo "Proceso finalizó correctamente"
        exit 0  # Salimos del script si ya terminó
    fi
    sleep 1  # Espera 1 segundo antes de volver a comprobar
done

# Si después del timeout el proceso sigue activo
echo "4. El proceso sigue activo después de $TIMEOUT segundos -> se finaliza"

# Kill envía señal de terminación al proceso
kill $PID

# Comprobación de que se ha finalizado correctamente
if ! ps -p $PID > /dev/null; then
    echo "Proceso finalizado exitosamente"
else
    echo "No se pudo finalizar el proceso"
fi
