#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Nodo
{
private:
    bool marca;
    string padre; 
    vector<pair<string, int>> list; 

public:
    Nodo();
    ~Nodo();

    bool getMarca();
    string getPadre();
    vector<pair<string, int>>& getList();
    void setMarca(bool marc);
    void setPadre(string pad);
    void addAdyacente(string nodo, int peso);
    pair<string, int> sacarSiguienteAdyacente(size_t iesimo);
};


Nodo::Nodo() : marca(false), padre("") {}

Nodo::~Nodo() {}

bool Nodo::getMarca()
{
    return marca;
}

string Nodo::getPadre()
{
    return padre;
}

vector<pair<string, int>>& Nodo::getList() 
{
    return list;
}

void Nodo::setMarca(bool marc)
{
    marca = marc;
}

void Nodo::setPadre(string pad)
{
    padre = pad;
}

void Nodo::addAdyacente(string nodo, int peso) 
{
    list.emplace_back(nodo, peso);
}


pair<string, int> Nodo::sacarSiguienteAdyacente(size_t iesimo) 
{
    if (iesimo < list.size()) 
    {
        return list[iesimo];
    }
    return {"", -1}; 
}
