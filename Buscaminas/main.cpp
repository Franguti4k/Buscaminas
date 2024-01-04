//FRANCISCO JAVIER GUTIERREZ GALLEGO Y GINA ANDREA RAMIREZ GUERRERO
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"
using namespace std;
int menu();
Board jPersonalizado();
Board jFacil();
Board jExperto();
void juego(Board& b);
int main() {
    int opc{ 0 };
    Board bType;
    do
    {
        opc = menu();
        switch (opc)
        {
        case 1:
            cout << endl;
            bType = jFacil();
            juego(bType);
            break;
        case 2:
            cout << endl;
            bType = jExperto();
            juego(bType);
            break;
        case 3:
            cout << endl;
            bType = jPersonalizado();
            juego(bType);
            break;
        case 0:
            cout << "\n\t FIN DEL JUEGO" << endl;
            break;
        default:
            cout << "\n\t POR FAVOR SELECCIONE UNA OPCION VALIDA" << endl;
            break;
        }
    } while (opc != 0);
    return 0;
}
