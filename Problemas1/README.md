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

### Problema 2 - Problema de Pizza Nocturna

Un grupo de estudiantes está desarrollando una actividad integradoras de la materia
TC2037. Los estudiantes solo pueden programar mientras comen pizza. Cada alumno ejecuta
el siguiente código para obtener una rebanada de pizza:

```{cpp}
while (true)
{
    recoger un trozo de pizza;
    estudiar mientras come pizza;
}
```

Si un estudiante descubre que la pizza se ha acabado, el estudiante se va a dormir
hasta que llegue otra pizza. El primer estudiante que descubre que el grupo no tiene
pizza llama a la pizzerias "All night long" para pedir otra pizza antes de irse a
dormir. Cada pizza tiene S rebanadas. Escribe un codigo para sincronizar los hilos de
los estudiantes y el hilo de entrega de pizza. Tu solución debe evitar interbloqueos
y la atención del cliente de la pizerría (es decir, reactivar el hilo de la pizzeria)
exactamente una vez cada vez que se agota una pizza. Ningún pedazo de pizza puede
ser consumido por más de un estudiante.
