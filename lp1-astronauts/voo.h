#include <iostream>
#include <string>
#include <list>
#include <astronauta.h>

using namespace std;

class Voo {
private:
    int codigoVoo;
    list<string> astronautas;

public:
    Voo(int codigo) : codigoVoo(codigo) {}

    void adicionarPassageiro(const Astronauta& astronauta) {
        astronautas.push_back(astronauta.getCPF());
    }
};