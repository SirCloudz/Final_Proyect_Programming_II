
#include "ux.h"

#include "ux.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <random>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::this_thread::sleep_for;

void LimpiarPantalla()
{
    system("clear");
    system("cls");

}

string center(const string &s, int width)
{
    int pad = (width - s.size()) / 2;
    if (pad < 0)
        pad = 0;
    return string(pad, ' ') + s;
}

void mostrarASCII()
{
    const char *G = "\033[38;5;46m";
    const char *R = "\033[0m";

    cout << G << center("██████  ██ ██    ██  █████  ██         ") << R << "\n";
    cout << G << center("██   ██ ██ ██    ██ ██   ██ ██       ") << R << "\n";
    cout << G << center("██████  ██ ██    ██ ███████ ██       ") << R << "\n";
    cout << G << center("██   ██ ██  ██  ██  ██   ██ ██        ") << R << "\n";
    cout << G << center("██   ██ ██   ████   ██   ██ ███████      ") << R << "\n\n";

    cout << G << center("███████ ██████   ██████  ███    ██ ████████ ██ ███████ ██████  ███████ ") << R << "\n";
    cout << G << center("██      ██   ██ ██    ██ ████   ██    ██    ██ ██      ██   ██ ██      ") << R << "\n";
    cout << G << center("█████   ██████  ██    ██ ██ ██  ██    ██    ██ █████   ██████  ███████ ") << R << "\n";
    cout << G << center("██      ██   ██ ██    ██ ██  ██ ██    ██    ██ ██      ██   ██      ██ ") << R << "\n";
    cout << G << center("██      ██   ██  ██████  ██   ████    ██    ██ ███████ ██   ██ ███████ ") << R << "\n\n";
}

int interfaz()
{
    int elec = 0;

    do
    {
        LimpiarPantalla();
        mostrarASCII();

        cout << "\033[35m";
        cout << center("============================================\n");
        cout << center("                MENU              \n");
        cout << center("============================================\n\n");
        cout << "\033[0m";

        cout << "\033[33m";
        cout << center("[1] Jugar\n");
        cout << center("[2] Bromitas?\n");
        cout << center("[3] Salir\n\n");
        cout << "\033[0m";

        cout << center("⚠ Seleccione una opción: ");

        // --- INICIO DE CORRECCIÓN ---
        if (!(cin >> elec)) {
            // Manejar error de entrada (no es un número)
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            elec = 0; // Forzar a que el bucle se repita
        }
    } while (elec < 1 || elec > 3);

    return elec;
}

void loadingBarSalida()
{
    vector<string> mensajes{
        "Guardando tus avances... (si es que hiciste alguno)",
        "Desconectando la IA principal... ¡AY NO, ME ESTOY APAG-",
        "Cerrando procesos ocultos... (no preguntes cuáles)",
        "Liberando memoria RAM... (esa que te faltó todo el juego)",
        "Apagando servidores... adiós a los trabajadores explotados",
        "Desactivando modo gamer... vuelve a ser civil ahora",
        "Calculando si realmente te quieres ir... confirmado",
        "Cerrando shaders... estaban ocupados haciendo nada",
        "Desinstalando bugs del sistema... (no se puede)",
        "Cerrando sesión... ojalá no vuelvas por un crash"};

    int progreso = 0;

    while (progreso <= 100)
    {
        LimpiarPantalla();
        mostrarASCII();

        cout << center(mensajes[progreso / 10]) << "\n\n";

        cout << center("[");
        for (int i = 0; i < 49; i++)
        {
            if (i < progreso / 2)
                cout << "#";
            else
                cout << " ";
        }
        cout << "]\n";

        cout << center(std::to_string(progreso) + "%") << endl;

        sleep_for(milliseconds(300 + (rand() % 200)));

        progreso += 5;
    }

    LimpiarPantalla();
}

void loadingBarEntrada()
{
    vector<string> mensajes{
        "Despertando al servidor...",
        "Cargando texturas HD...",
        "Compilando shaders...",
        "Buscando bugs...",
        "Optimizando el juego...",
        "Aumentando FPS artificialmente...",
        "Poniendo música épica...",
        "Cargando físicas realistas...",
        "Cargando UI...",
        "A punto de terminar..."};

    int progreso = 0;

    while (progreso <= 100)
    {
        LimpiarPantalla();
        mostrarASCII();

        cout << center(mensajes[progreso / 10]) << "\n\n";

        cout << center("[");
        for (int i = 0; i < 49; i++)
        {
            if (i < progreso / 2)
                cout << "#";
            else
                cout << " ";
        }
        cout << "]\n";

        cout << center(std::to_string(progreso) + "%") << endl;

        sleep_for(milliseconds(300 + (rand() % 200)));

        progreso += 5;
    }

    LimpiarPantalla();
}

void entrada()
{
    LimpiarPantalla();
    sleep_for(milliseconds(100));
    loadingBarEntrada();
}

void salida()
{
    LimpiarPantalla();
    cout << "\n\n";
    cout << "\033[1;32m" << center("Gracias por jugar.") << "\033[0m\n\n";
    sleep_for(milliseconds(100));
    loadingBarSalida();
}

int runUXMenu()
{
    int elec = interfaz();

    switch (elec)
    {
    case 1:
        entrada();
        break;

    case 2:
        // Bromas
        break;

    case 3:
        salida();
        break;
    default:
        break;
    }

    return elec;
}