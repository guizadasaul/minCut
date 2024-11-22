#pragma once
#include "Nodo.h"
#include <fstream>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Grafo
{
private:
    unordered_map<string, Nodo*> grafo;
    priority_queue<pair<int, pair<string, string>>, vector<pair<int, pair<string, string>>>, greater<>> monticuloMin;
    int Vertices;

public:
    Grafo();
    ~Grafo();
    bool insertarAristaConPeso(string origen, string destino, int peso);
    bool leerArchivo(string& filename);
    void mostrarGrafo(Grafo* g);
    void kruskal(Grafo& AE, int& sum);
    string buscarCiclo(unordered_map<string, string>& hash, string nodo);

    int contarAristas();
};

Grafo::Grafo() : Vertices(0)
{

} 

Grafo::~Grafo()
{
    for (auto& pair : grafo) 
    {
        delete pair.second;
    }
    grafo.clear();
}

bool Grafo::insertarAristaConPeso(string origen, string destino, int peso)
{
    if (grafo.find(origen) == grafo.end()) 
    {
        grafo[origen] = new Nodo(); 
        Vertices++;
    }
    if (grafo.find(destino) == grafo.end()) 
    {
        grafo[destino] = new Nodo();
        Vertices++;
    }

    grafo[origen]->addAdyacente(destino, peso);
    grafo[destino]->addAdyacente(origen, peso);


    monticuloMin.push({peso, {origen, destino}});
    return true;
}

bool Grafo::leerArchivo(string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cout << "Error al abrir el archivo." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string origen, destino;
        int peso;
        ss >> origen >> destino >> peso;

        if (!insertarAristaConPeso(origen, destino, peso)) 
        {
            cout << "Error al insertar arista: " << origen << "-" << destino << " con peso " << peso << endl;
        }
    }

    file.close();
    return true;
}

void Grafo::mostrarGrafo(Grafo* g)
{
    cout << "Contenido del grafo:" << endl;
    for (const auto& pair : g->grafo) 
    {
        const string& nodo = pair.first;
        Nodo* nodoPtr = pair.second;
        
        cout << nodo << " -> ";

        for (const auto& adyacente : nodoPtr->getList()) 
        {
            cout << "(" << adyacente.first << ", peso: " << adyacente.second << ") ";
        }
        for (const auto& adyacente : nodoPtr->getList()) 
        {
            cout << "(" << adyacente.first << ", peso: " << adyacente.second << ") ";
        }
 
        cout << endl;
    }
}

void Grafo::kruskal(Grafo& arbolExpansion, int& total)
{
    total = 0;

    unordered_map<string, string> hash;
    for (auto& pair : grafo) 
    {
        hash[pair.first] = pair.first; // inicializa cada nodo como su propio padre
    }

    int addAristas = 0; // contador de aristas añadidas al arbol de expancion

    while (addAristas < this->Vertices - 1) // ajuste para evitar problemas
    {
        auto trio = monticuloMin.top(); // obtener la arista con menor peso
        monticuloMin.pop();

        string vo = buscarCiclo(hash, trio.second.first);
        string vd = buscarCiclo(hash, trio.second.second);

        if (vo != vd) // solo se aniade si no forma un ciclo
        {
            arbolExpansion.insertarAristaConPeso(trio.second.first, trio.second.second, trio.first);
            total += trio.first; // acumula el peso de las aristas en el arbol de expancion
            hash[vo] = vd; // unionn de conjuntos

        }
        addAristas++; // incrementa el numero de aristas aniadidas
    }
}

inline string Grafo::buscarCiclo(unordered_map<string, string>& hash, string nodo)
{
    if (hash[nodo] == nodo)
    {
        return nodo;
    }
    return hash[nodo] = buscarCiclo(hash, hash[nodo]); // Compresión de camino
}

int Grafo::contarAristas() 
{
    unordered_map<string, bool> visitados;
    int contador = 0;
    unordered_map<string, Nodo*>::iterator grafoIterador = grafo.begin();
    vector<pair<string, int>>::iterator adyIterador;
    Nodo* nodoActual;
    string nodo;

    while (grafoIterador != grafo.end()) 
    {
        nodo = grafoIterador->first;
        nodoActual = grafoIterador->second;
        adyIterador = nodoActual->getList().begin();

        while (adyIterador != nodoActual->getList().end()) 
        {
            string destino = adyIterador->first;

            if (visitados.find(destino) == visitados.end()) 
            {
                contador++;
            }
            ++adyIterador;
        }
        visitados[nodo] = true;
        ++grafoIterador; 
    }

    return contador;
}
