Alumna: Katya Pérez Rodríguez.
Carné: B45269.

**Simulador de un cache parametizado.**
Este programa simula una memoria cache que permite obtener métricas de rendimiento utilizando un trace. Como política de reemplazo utiliza SRRIP. Para implementarlo, se leen las direcciones del trace y se trabaja a partir del index y el tag. Se generó la clase "Cache", que posee además una estructura llamada "Bloque". Dicha clase posee métodos que son para revisar la dirección y verificar si hay un hit o miss, almacenar esos parámetros en contadores, además de métodos para el reemplazo y victimización, entre otros.

**Para compilarlo**
Se debe entrar al directorio del proyecto y correr el comando *make* en terminal. El Makefile lo compilará con el nombre "cache_katya". Después se corre el comando *PATH=$PATH:.* en la terminal. Este agregará al path el repositorio.

**Para ejecutarse**
Se utiliza el comando dado en el enunciado de la tarea:
  gunzip -c  *El trace a utilizar* | cache_katya -t # -l # -a #

    donde, -t es el tamaño del cache en *bytes*, -l el tamaño de líneas en *bytes* y -a la asociatividad. En # los valores deseados.
