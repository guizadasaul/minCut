#include <iostream>
#include <random>
#include <string>
#include "Grafo.h"

using namespace std;

void mostrarMenu() 
{
    cout << "\n---- Menu de Opciones ----" << endl;
    cout << "1. Insertar arista con peso" << endl;
    cout << "2. Leer de archivo VALORADO BOLIVIA" << endl;
    cout << "3. Mostrar Grafo" << endl;
    cout << "4. KRUSKAL" << endl;
    cout << "5. Mostrar el AE (llamando al 3)" << endl;
    cout << "6. Defensa" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main()
{
    Grafo grafo;      
    Grafo arbolExpansion;
    int opcion;
    string elemento1, elemento2;
    int peso;
    string filename = "VALORADO_BOLIVIA.txt";
    int total = 0;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout<<"Dame el origen" <<endl;
                cin>>elemento1;
                cout<<"Dame el destino" <<endl;
                cin>>elemento2;
                cout<<"Dame el peso" <<endl;
                cin>>peso;
                if (grafo.insertarAristaConPeso(elemento1, elemento2, peso))
                {
                    cout<<"Insertado correctamente" <<endl;
                }
                else
                {
                    cout<<"error al insertar" <<endl;
                }
                break;
            case 2:
                if (grafo.leerArchivo(filename)) 
                {
                    cout << "Archivo leído correctamente." << endl;
                } else {
                    cout << "Error al leer el archivo." << endl;
                }
                break;
            case 3:
                cout << "Mostrando el grafo:" << endl;
                grafo.mostrarGrafo(&grafo);
                break;
            case 4:
                cout << "Ejecutando algoritmo de Kruskal..." << endl;
                grafo.kruskal(arbolExpansion, total);
                cout << "Árbol de expansión mínima calculado." << endl;
                cout << "Peso total del árbol de expansión mínima: " << total << endl;
                break;
            case 5:
                cout << "Mostrando el Árbol de Expansión Mínima:" << endl;
                arbolExpansion.mostrarGrafo(&arbolExpansion);
                break;
            case 6:
                cout << "El numero de aristas en el arbol de expancion minima es:" <<arbolExpansion.contarAristas();
                break;
            default:
                break;
        }
    } while (opcion != 0);

    return 0;
}
