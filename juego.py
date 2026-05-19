import os
import sys

# Códigos de color ANSI (Le dan el toque aesthetic sin librerías raras)
VERDE = "\033[92m"
ROJO = "\033[91m"
AMARILLO = "\033[93m"
AZUL = "\033[94m"
MAGENTA = "\033[95m"
CYAN = "\033[96m"
RESET = "\033[0m"

class Jugador:
    def __init__(self):
        self.x = 2
        self.y = 2
        self.vida = 3
        self.inventario = ' '

class Enemigo:
    def __init__(self, x, y, tipo):
        self.x = x
        self.y = y
        self.activo = True
        self.tipo = tipo

class Habitacion:
    def __init__(self, id_sala):
        self.id = id_sala
        self.mapa = []
        
        for i in range(10):
            if i == 0 or i == 9:
                self.mapa.append(['#'] * 20)
            else:
                self.mapa.append(['#'] + [' '] * 18 + ['#'])
        
        if id_sala == 0: self.mapa[4][4] = 'K' 
        if id_sala == 5: self.mapa[5][10] = 'C' 
        
        # Portales mágicos innovadores
        self.mapa[3][5] = '@' 
        self.mapa[7][15] = 'O' 

def dibujar_mapa(jugador, enemigos, sala):
    os.system('cls' if os.name == 'nt' else 'clear')
    print(CYAN + "=========================================" + RESET)
    print(CYAN + "   ATARI ADVENTURE: VISUAL EDITION       " + RESET)
    print(CYAN + "=========================================" + RESET)
    print(f" Habitacion: {sala.id + 1}/6 | Vidas: {ROJO}{'♥ ' * jugador.vida}{RESET} | Item: [{AMARILLO}{jugador.inventario}{RESET}]\n")

    for i in range(10):
        linea = ""
        for j in range(20):
            if jugador.x == i and jugador.y == j:
                linea += VERDE + 'P' + RESET # Jugador en Verde
            elif enemigos[0].activo and enemigos[0].x == i and enemigos[0].y == j:
                linea += ROJO + 'E' + RESET # Enemigo 1 en Rojo
            elif enemigos[1].activo and enemigos[1].x == i and enemigos[1].y == j:
                linea += ROJO + 'X' + RESET # Enemigo 2 en Rojo
            elif sala.mapa[i][j] == '#':
                linea += MAGENTA + '#' + RESET # Paredes en Magenta retro
            elif sala.mapa[i][j] == '@' or sala.mapa[i][j] == 'O':
                linea += AZUL + sala.mapa[i][j] + RESET # Portales en Azul místico
            elif sala.mapa[i][j] == 'K':
                linea += AMARILLO + 'K' + RESET # Llave dorada
            elif sala.mapa[i][j] == 'C':
                linea += AMARILLO + 'C' + RESET # Cofre dorado
            else:
                linea += sala.mapa[i][j]
        print(linea)
    
    print("\n[W/A/S/D] Moverse | [Q] Salir")
    print(AZUL + "Mecánica: El '@' te teletransporta al 'O' para escapar rápido." + RESET)
    
    # SISTEMA DE LORE / HISTORIA (Varía según la habitación donde vayas)
    print(CYAN + "-----------------------------------------" + RESET)
    if sala.id == 0:
        print("📜 LORE: Despertaste en las celdas oscuras. Busca la llave 'K'.")
    elif sala.id == 1 or sala.id == 2:
        print("📜 LORE: Los pasillos se vuelven estrechos. Siento pasos cerca...")
    elif sala.id == 3 or sala.id == 4:
        print("📜 LORE: ¡Los portales de energía te ayudan a esquivar monstruos!")
    elif sala.id == 5:
        print("📜 LORE: ¡Ahí está! El cofre sagrado. Usa la llave para abrirlo.")
    print(CYAN + "-----------------------------------------" + RESET)

def main():
    jugador = Jugador()
    enemigos = [Enemigo(5, 12, 1), Enemigo(8, 8, 2)]
    habitaciones = [Habitacion(i) for i in range(6)]
    sala_actual = 0

    while jugador.vida > 0:
        sala = habitaciones[sala_actual]
        dibujar_mapa(jugador, enemigos, sala)
        
        tecla = input().lower()
        if tecla == 'q': sys.exit()
        
        sigX, sigY = jugador.x, jugador.y
        if tecla == 'w': sigX -= 1
        if tecla == 's': sigX += 1
        if tecla == 'a': sigY -= 1
        if tecla == 'd': sigY += 1

        if sala.mapa[sigX][sigY] != '#':
            jugador.x, jugador.y = sigX, sigY
            
            if sala.mapa[sigX][sigY] == 'K':
                jugador.inventario = 'K'
                sala.mapa[sigX][sigY] = ' '
            
            if jugador.x == 3 and jugador.y == 5:
                jugador.x, jugador.y = 7, 15
                
            if sala.mapa[sigX][sigY] == 'C':
                if jugador.inventario == 'K':
                    print(VERDE + "\n¡FELICIDADES GANASTE! Abriste el cofre sagrado." + RESET)
                    sys.exit()
                else:
                    print(ROJO + "\n[!] Necesitas la llave 'K' para abrir este cofre." + RESET)
                    input("Presiona Enter para continuar...")

        if jugador.y >= 19 and sala_actual < 5:
            sala_actual += 1
            jugador.y = 1
        elif jugador.y <= 0 and sala_actual > 0:
            sala_actual -= 1
            jugador.y = 18

        for e in enemigos:
            if e.tipo == 1:
                if e.x < jugador.x: e.x += 1
                elif e.x > jugador.x: e.x -= 1
            else:
                if e.y < jugador.y: e.y += 1
                elif e.y > jugador.y: e.y -= 1
                
            if e.x == jugador.x and e.y == jugador.y:
                jugador.vida -= 1
                print(ROJO + "¡Te ha atrapado un enemigo!" + RESET)
                input("Presiona Enter...")
                jugador.x, jugador.y = 2, 2

    print(ROJO + "\n=========================================")
    print("   ¡GAME OVER! Caíste en combate. ")
    print("=========================================" + RESET)

if __name__ == "__main__":
    main()