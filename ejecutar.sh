#!/bin/bash

# Ejecutar en segundo plano
echo "Lanzando programa en segundo plano..."
./programa_pinza &

# Guardamos el PID
PID=$!
echo "Proceso iniciado con PID: $PID"

# Esperamos finalizacion
echo "Procesando datos, por favor espere..."
wait $PID

# Controlamos cierre de proceso
if ps -p $PID > /dev/null
then
    echo "El proceso no responde. Forzando cierre..."
    kill -9 $PID
else
    echo "Ejecucion finalizada correctamente."
fi

echo "Consulta 'resultado_pinza.txt' para ver el analisis completo."
