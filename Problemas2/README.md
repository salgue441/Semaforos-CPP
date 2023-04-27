# Cruzando un Puente

La Comisión Estatal de Infraestructura de Querétaro te ha contratado para sincronizar
el tráfico en un puente angosto de servicio ligero en una via pública. El tráfico solo
puede cruzar el puente en una dirección a la vez (de Norte a Sur o de Sur a Norte), y si
alguna vez hay más de 3 vehículos en el puento al mismo tiempo, colapsará bajo su peso.
En este sistema, cada automóvil está representado por un hilo, que ejecuta la tarea
OneVehicle cuando llega al puente:

```c

OneVehicle (direction) {
    ArreiveBridge (direction)
    CrossBridge (direction)
    ExitBridge (direction)
}

```

En el código anterior, direction indica la dirección en la que el vehículo
cruzará el puente. Escribe los procedimientos, ArreiveBridge, CrossBridge y ExitBridge
(el procedimiento CrossBridge solo desplegar informacion). ArriveBridge no debe
regresar hasta que sea seguro para el automovil cruzar el puente en la direccion
para indicar que el hilo que lo invica ha terminado de cruzar el puente; ExitBridge
debe tomar medidas para permitir que otros autos crucen el puente. Este es un puente
rural poco transitado, por lo que no es necesario garantizar la equidad o la muerte
por inanición.
