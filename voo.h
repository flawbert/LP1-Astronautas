#ifndef VOO_H
#define VOO_H

#include "astronauta.h"
#include <list>
#include <string>

using namespace std;

enum vooStatus {
    PLANEJANDO,
    DESTRUIDO,
    EMVOO,
};

class Voo {
private:
    int codigoVoo;
    bool dispo = true;
    list<Astronauta> passageiros;
    vooStatus status = PLANEJANDO;
    string destino;

public:
    Voo(int codigo, const string& destinoNovo);

    int getCodigo() const;
    vooStatus getStatus() const;
    bool getDispo() const;
    string getDestino() const;
    void setStatus(vooStatus novoStatus);
    void setDestino(string novoDestino);
    void adicionarPassageiro(const Astronauta& astronauta);
    void lancarVoo();
    void visualizarPassageiros(const list<Astronauta>& astronautas) const;
    void removerPassageiro(const string& cpf);
    void finalizarVoo();
};

#endif
