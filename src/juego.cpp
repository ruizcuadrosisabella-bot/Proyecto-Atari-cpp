#include "../include/juego.h"
#include <iostream>
#include <cstdlib>

#define RESET   "\033[0m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

void inicializarJuego(Jugador* jugador, Enemigo* enemigos, Habitacion* habitaciones, int* habitacionActual) {
    *habitacionActual = 0;

    jugador->pos.x = 2;
    jugador->pos.y = 2;
    jugador->vida = 3;
    jugador->inventario = ' ';

    enemigos[0].pos.x = 5; enemigos[0].pos.y = 12; enemigos[0].activo = true; enemigos[0].tipo = 1;
    enemigos[1].pos.x = 8; enemigos[1].pos.y = 8;  enemigos[1].activo = true; enemigos[1].tipo = 2;

    for (int s = 0; s < 6; s++) {
        habitaciones[s].id = s;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 20; j++) {
                if (i == 0 || i == 9 || j == 0 || j == 19) {
                    habitaciones[s].mapa[i][j] = '#';
                } else {
                    habitaciones[s].mapa[i][j] = ' ';
                }
            }
        }

        habitaciones[s].portalEspecial.entrada.x = 3;
        habitaciones[s].portalEspecial.entrada.y = 5;
        habitaciones[s].portalEspecial.salida.x = 7;
        habitaciones[s].portalEspecial.salida.y = 15;
        habitaciones[s].portalEspecial.activo = true;

        habitaciones[s].mapa[3][5] = '@';
        habitaciones[s].mapa[7][15] = 'O';
    }

    habitaciones[0].mapa[4][4] = 'K';  
    habitaciones[5].mapa[5][10] = 'C'; 
}

void dibujarMapa(const Jugador* jugador, const Enemigo* enemigos, const Habitacion* habActual) {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif

    std::cout << CYAN << "=========================================\n" << RESET;
    std::cout << CYAN << "   ATARI ADVENTURE: C++ VISUAL EDITION   \n" << RESET;
    std::cout << CYAN << "=========================================\n" << RESET;
    
    std::cout << " Habitacion: " << habActual->id + 1 << "/6 | Vidas: " << ROJO;
    for(int v = 0; v < jugador->vida; v++) std::cout << "♥ ";
    std::cout << RESET << " | Item: [" << AMARILLO << jugador->inventario << RESET << "]\n\n";

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            if (jugador->pos.x == i && jugador->pos.y == j) {
                std::cout << VERDE << 'P' << RESET;
            } else if (enemigos[0].activo && enemigos[0].pos.x == i && enemigos[0].pos.y == j) {
                std::cout << ROJO << 'E' << RESET;
            } else if (enemigos[1].activo && enemigos[1].pos.x == i && enemigos[1].pos.y == j) {
                std::cout << ROJO << 'X' << RESET;
            } else if (habActual->mapa[i][j] == '#') {
                std::cout << MAGENTA << '#' << RESET; 
            } else if (habActual->mapa[i][j] == '@' || habActual->mapa[i][j] == 'O') {
                std::cout << AZUL << habActual->mapa[i][j] << RESET; 
            } else if (habActual->mapa[i][j] == 'K' || habActual->mapa[i][j] == 'C') {
                std::cout << AMARILLO << habActual->mapa[i][j] << RESET; 
            } else {
                std::cout << habActual->mapa[i][j];
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n[W/A/S/D] Moverse | [Q] Salir\n";
    std::cout << AZUL << "Mecánica: Entra al '@' para salir por el portal 'O'.\n" << RESET;
    
    std::cout << CYAN << "-----------------------------------------\n" << RESET;
    if (habActual->id == 0) std::cout << "📜 LORE: Despertaste en las celdas oscuras. Busca la llave 'K'.\n";
    else if (habActual->id == 1 || habActual->id == 2) std::cout << "📜 LORE: Los pasillos se vuelven estrechos. Siento pasos cerca...\n";
    else if (habActual->id == 3 || habActual->id == 4) std::cout << "📜 LORE: ¡Los portales de energía te ayudan a esquivar monstruos!\n";
    else if (habActual->id == 5) std::cout << "📜 LORE: ¡Ahí está! El cofre sagrado. Usa la llave para abrirlo.\n";
    std::cout << CYAN << "-----------------------------------------\n" << RESET;
}

void procesarEntrada(Jugador* jugador, Habitacion* habActual, int* habitacionActual) {
    char tecla;
    std::cin >> tecla;
    tecla = tolower(tecla);

    if (tecla == 'q') {
        std::exit(0);
    }

    int sigX = jugador->pos.x;
    int sigY = jugador->pos.y;

    if (tecla == 'w') sigX--;
    if (tecla == 's') sigX++;
    if (tecla == 'a') sigY--;
    if (tecla == 'd') sigY++;

    if (habActual->mapa[sigX][sigY] != '#') {
        jugador->pos.x = sigX;
        jugador->pos.y = sigY;

        if (habActual->mapa[jugador->pos.x][jugador->pos.y] == 'K') {
            jugador->inventario = 'K';
            habActual->mapa[jugador->pos.x][jugador->pos.y] = ' ';
        }

        if (habActual->portalEspecial.activo && 
            jugador->pos.x == habActual->portalEspecial.entrada.x && 
            jugador->pos.y == habActual->portalEspecial.entrada.y) {
            
            jugador->pos.x = habActual->portalEspecial.salida.x;
            jugador->pos.y = habActual->portalEspecial.salida.y;
        }

        if (habActual->mapa[jugador->pos.x][jugador->pos.y] == 'C') {
            if (jugador->inventario == 'K') {
                std::cout << VERDE << "\n¡FELICIDADES GANASTE! Abriste el cofre sagrado con éxito.\n" << RESET;
                std::exit(0);
            } else {
                std::cout << ROJO << "\n[!] El cofre necesita la llave 'K' de la habitacion 1.\n" << RESET;
                std::cout << "Presiona Enter para continuar...";
                std::cin.get(); std::cin.get();
            }
        }
    }

    if (jugador->pos.y >= 19 && *habitacionActual < 5) {
        (*habitacionActual)++;
        jugador->pos.y = 1;
    } else if (jugador->pos.y <= 0 && *habitacionActual > 0) {
        (*habitacionActual)--;
        jugador->pos.y = 18;
    }
}

void actualizarEnemigos(Enemigo* enemigos, const Jugador* jugador, const Habitacion* habActual) {
    for (int i = 0; i < 2; i++) {
        if (!enemigos[i].activo) continue;

        if (enemigos[i].tipo == 1) {
            if (enemigos[i].pos.x < jugador->pos.x) enemigos[i].pos.x++;
            else if (enemigos[i].pos.x > jugador->pos.x) enemigos[i].pos.x--;
        } else {
            if (enemigos[i].pos.y < jugador->pos.y) enemigos[i].pos.y++;
            else if (enemigos[i].pos.y > jugador->pos.y) enemigos[i].pos.y--;
        }

        if (enemigos[i].pos.x == jugador->pos.x && enemigos[i].pos.y == jugador->pos.y) {
            const_cast<Jugador*>(jugador)->vida--;
            std::cout << ROJO << "\n¡Un enemigo te ha atrapado!\n" << RESET;
            std::cout << "Presiona Enter para reaparecer...";
            std::cin.get(); std::cin.get();
            const_cast<Jugador*>(jugador)->pos.x = 2;
            const_cast<Jugador*>(jugador)->pos.y = 2;
        }
    }
}
