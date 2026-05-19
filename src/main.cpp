#include "../include/juego.h"
#include <iostream>

int main() {
    Jugador jugador;
    Enemigo enemigos[2];
    Habitacion habitaciones[6];
    int habitacionActual = 0;

    inicializarJuego(&jugador, enemigos, habitaciones, &habitacionActual);

    while (jugador.vida > 0) {
        dibujarMapa(&jugador, enemigos, &habitaciones[habitacionActual]);
        procesarEntrada(&jugador, &habitaciones[habitacionActual], &habitacionActual);
        actualizarEnemigos(enemigos, &jugador, &habitaciones[habitacionActual]);
    }

    std::cout << "\033[31m\n=========================================\n";
    std::cout << "   ¡GAME OVER! Tus vidas llegaron a 0.   \n";
    std::cout << "=========================================\n\033[0m";

    return 0;
}
