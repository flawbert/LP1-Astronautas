#include <iostream>
#include <list>

using namespace std;

class Astronauta{
    private:
    string cpf;
    string nome;
    int idade;

    public:
    Astronauta(const string& cpf, const string& nome, int idade)
        : cpf(cpf), nome(nome), idade(idade) {}

    string getCPF() const {
        return cpf;
    }
    string getNome() const {
        return nome;
    }
    int getIdade() const {
        return idade;
    }
};

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



int main(void){
    cout << "Bem vindo ao controle de Voo." << endl;

    cout << "Escolha uma opção:" << endl;

    list<string> opcoes;
    opcoes.push_back("1 - Cadastrar Astronauta");
    opcoes.push_back("2 - Cadastrar Voo");
    opcoes.push_back("3 - Lançar Voo");
    opcoes.push_back("0 - Sair");

    for (const auto& frase : opcoes) {
        cout << frase << endl;
    }

    int op;

    cin >> op;

    switch (op) {
        case 1: {
        // Cadastrar Astronauta
        string cpf, nome;
        int idade;
        cout << "CPF do astronauta: ";
        cin >> cpf;
        cout << "Nome do astronauta: ";
        cin >> nome;
        cout << "Idade do astronauta: ";
        cin >> idade;

        // Criar um objeto Astronauta
        Astronauta astronauta(cpf, nome, idade);

        // Armazenar o astronauta em algum lugar, como em uma lista
        // ou realizar outras operações com o objeto astronauta

        break;
        }
        
        case 2: {
            // Cadastrar Voo
        int codigoVoo;
        cout << "Código do voo: ";
        cin >> codigoVoo;

        // Criar um objeto Voo
        Voo novoVoo(codigoVoo);

        // Armazenar o voo em algum lugar, como em uma lista
        // ou realizar outras operações com o objeto voo

        break;
        }

        default:
            cout << "Saindo..." << endl;
            break;
    }

    return 0;
}