#include <iostream>
#include <string>

using namespace std;

class Astronauta{
    private:
    string cpf;
    string nome;
    int idade;

    public:
    Astronauta(const string& cpf, const string& nome, int idade)
        : cpf(cpf), nome(nome), idade(idade) {}

    std::string getCPF() const {
        return cpf;
    }
    std::string getNome() const {
        return nome;
    }
    int getIdade() const {
        return idade;
    }
};