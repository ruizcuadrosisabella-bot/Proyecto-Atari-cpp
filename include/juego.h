#ifndef JUEGO_H
#define JUEGO_H

struct Posicion {
    int x;
    int y;
};

struct Jugador {
    Posicion pos;
    char inventario; 
    int vida;
};

struct Enemigo {
    Posicion pos;
    bool activo;
    int tipo; 
};

struct Portal {
    Posicion entrada;
    Posicion salida;
    bool activo;
};

struct Habitacion {
    int id;
    char mapa[10][20]; 
    Portal portalEspecial; 
};

void inicializarJuego(Jugador* jugador, Enemigo* enemigos, Habitacion* habitaciones, int* habitacionActual);
void dibujarMapa(const Jugador* jugador, const Enemigo* enemigos, const Habitacion* habActual);
void procesarEntrada(Jugador* jugador, Habitacion* habActual, int* habitacionActual);
void actualizarEnemigos(Enemigo* enemigos, const Jugador* jugador, const Habitacion* habActual);

#endif
