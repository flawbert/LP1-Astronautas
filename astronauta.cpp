#include "astronauta.h"

Astronauta::Astronauta(const string& cpf, const string& nome, int idade)
    : cpf(cpf), nome(nome), idade(idade) {}

string Astronauta::getCPF() const {
    return cpf;
}

string Astronauta::getNome() const {
    return nome;
}

int Astronauta::getIdade() const {
    return idade;
}

astroStatus Astronauta::getStatus() {
    return status;
}

bool Astronauta::getDisponibilidade() {
    return dispo;
}

void Astronauta::mataAstro() {
    status = MORTO;
}

void Astronauta::setDisponivel() {
    dispo = true;
}

void Astronauta::setIndisponivel() {
    dispo = false;
}

void Astronauta::adicionarVoo(int codigoVoo) {
    historicoVoos.push_back(codigoVoo);
}

const list<int>& Astronauta::getHistoricoVoos() const {
    return historicoVoos;
}

void Astronauta::setHistoricoVoos(const list<int>& novoHistorico) {
    historicoVoos = novoHistorico;
}
