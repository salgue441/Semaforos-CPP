# Problema de Sincronizacion

## Datos de Entrega

Instituto Tecnologico de Estudios Superiores de Monterrey, Campus Queretaro

### Alumno

| Nombre          | Matricula |
| --------------- | --------- |
| Carlos Salguero | A00833341 |

### Profesor

| Nombre                    | Clave Materia | Materia                                   |
| ------------------------- | ------------- | ----------------------------------------- |
| Pedro Oscar Perez Murieta | TC2037        | Implementacion de Metodos Computacionales |

## Problemas

### Problema 1 - Aproximacion de Pi

Una forma interesante de calcular pi es utilizar una técnica conocida como
Monte Carlo, que implica la aleatorizaciónl. Esta técnica funciona de la siguiente
manera: supón que tiene un círculo inscrito dentro de un cuadrado,
como se muestra en la figura

![Monte Carlo technique for calculating pi](/images/aproximacion-pi.png)

Primero, genera una serie de puntos aleatorios como coordenadas simples (x, y).
Estos puntos deben estar dentro de las coordenadas cartesianas que delimitan
el cuadrado. Del número total de puntos aleatorios que se generan, algunos
ocurrirán dentro del círculo y otros no. Luego estima pi realizando el siguiente calculo

```{}
pi = 4 * (puntos dentro del circulo) / (total de puntos)
```

Escribe una versión de múltiples hilos de este algoritmo que cree un hilo separado
para generar una canti-dad de puntos aleatorios. El hilo contará la cantidad de puntos
que ocurren dentro del círculo y almacenará ese resultado en una variable global
compartida. Cuando este hilo haya salido, el hilo principal calculará y generará el
valor estimado de Π. Vale la pena experimentar con la cantidad de puntos aleatorios
generados. Como regla general, cuanto mayor sea el número de puntos, más cercana será
la aproximación a Pi
