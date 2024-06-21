#include "voo.h"
#include "cemiterio.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Voo::Voo(int codigo, const string& destinoNovo) : codigoVoo(codigo), destino(destinoNovo) {}

int Voo::getCodigo() const {
    return codigoVoo;
}

vooStatus Voo::getStatus() const {
    return status;
}

bool Voo::getDispo() const {
    return dispo;
}

string Voo::getDestino() const {
    return destino;
}

void Voo::setStatus(vooStatus novoStatus) {
    status = novoStatus;
}

void Voo::setDestino(string novoDestino) {
    destino = novoDestino;
}

void Voo::adicionarPassageiro(const Astronauta& astronauta) {
    passageiros.push_back(astronauta);
}

void Voo::lancarVoo() {
    srand(time(nullptr));
    int numAleatorio = rand() % 2; // Número entre 1 e 0 para que seja aleatória a destruição do voo ou seu sucesso

    if (numAleatorio == 0) {
        status = DESTRUIDO;
        cout << "O Voo de codigo " << codigoVoo << " foi explodido." << endl;
        for (auto& astronauta : passageiros) {
            astronauta.mataAstro();
            cout << "O astronauta " << astronauta.getNome() << " morreu..." << endl;
            Cemiterio::adicionarMorto(astronauta);
        }
    } else {
        status = EMVOO;
        cout << "O Voo de codigo " << codigoVoo << " esta a caminho de " << destino << endl;
    }

    dispo = false;
}

void Voo::visualizarPassageiros(const list<Astronauta>& astronautas) const {
    cout << "   Astronautas cadastrados para o voo [" << codigoVoo << "]:" << endl;

    for (const auto& astronauta : passageiros) {
        if (passageiros.empty()) {
            cout << "   Nao ha astronautas cadastrados..." << endl;
            break;
        } else {
            cout << "   CPF: " << astronauta.getCPF() << ", Nome: " << astronauta.getNome() << ", Idade: " << astronauta.getIdade() << endl;
        }
    }
}

void Voo::removerPassageiro(const string& cpf) {
    for (auto it = passageiros.begin(); it != passageiros.end(); ++it) {
        if (it->getCPF() == cpf) {
            passageiros.erase(it);
            return;
        }
    }
}

void Voo::finalizarVoo() {
    status = PLANEJANDO; // definir o status do voo como planejando novamente
    dispo = true; // tornar o voo disponível novamente

    cout << "O voo pousou de " << destino << endl;

    // Marcar todos os passageiros como disponíveis novamente
    for (auto& passageiro : passageiros) {
        passageiro.setDisponivel();
    }
    
    // Limpar a lista de passageiros, já que o voo foi finalizado
    passageiros.clear();
}
