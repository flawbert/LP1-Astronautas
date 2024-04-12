#include <iostream>
#include <list>
#include <cstdlib> // Para gerar o número aleatório para o voo ser explodido ou não
#include <ctime>   // Para usar srand()

using namespace std;

enum vooStatus {
    PLANEJANDO,
    LANCADO,
    DESTRUIDO,
    EMVOO,
};

class Astronauta{
    private:
    string cpf;
    string nome;
    int idade;
    bool dispo = true;

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
    bool dispo = true;
    list<string> astronautas;
    vooStatus status = PLANEJANDO;

public:
    Voo(int codigo) : codigoVoo(codigo) {}

    int getCodigo() {
        return codigoVoo;
    }

    void adicionarPassageiro(const Astronauta& astronauta) {
        astronautas.push_back(astronauta.getCPF());
    }

    // Criar método lancarVoo()
    void lancarVoo() {
        srand(time(nullptr));
        int numAleatorio = rand() % 2; // Número entre 1 e 0 para que seja aleatória a destruição do voo, e não voluntária

        if (numAleatorio == 0) {
            status = DESTRUIDO; // Status do Voo ao ser distruido
            dispo = false; // Voo indisponivel 
            cout << "O Voo de codigo " << codigoVoo << " foi explodido." << endl; 
            // ~Voo
        }
        else {
            status = EMVOO; // Status do Voo ao ser lançado com sucesso
            dispo = false; // Voo indisponivel por esta no ar
            cout << "O Voo de codigo " << codigoVoo << " esta em andamento." << endl;
        }
    }
};



int main(void){
    cout << "Bem vindo ao controle de Voo." << endl;

    int controle = 0;

    list<Astronauta> astronautas;
    list<Voo> voos;

    while (controle != 1) {
        cout << "Escolha uma opcao:" << endl;

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
            cout << astronauta.getCPF() << " " << astronauta.getNome() << " " << astronauta.getIdade() << "." << endl;

            astronautas.push_back(astronauta); // Armazenando o objeto em uma lista
        
            break;
            }
            
            case 2: {
                // Cadastrar Voo
            int numVoo;
            cout << "Codigo do voo: ";
            cin >> numVoo;

            // Criar um objeto Voo
            Voo novoVoo(numVoo);

            cout << "O voo com codigo " << novoVoo.getCodigo() << " ja esta em planejamento." << endl;

            voos.push_back(novoVoo); // Armazenando o objeto em uma lista.

            break;
            }

            case 3: {
                int cod;
                cout << "Digite o codigo do voo a ser lancado: " << endl;
                cin >> cod;

                bool encontrado = false;

                // Percorrer a lista de voos
                for (const auto& voo : voos) {
                    if (voo.getCodigo() == cod) {
                        // Voo encontrado, chamar a função lancarVoo() neste voo
                        voo.lancarVoo();
                        encontrado = true;
                        break; // Não é necessário continuar procurando
                    }
                }

                if (!encontrado) {
                    cout << "Voo nao encontrado!" << endl;
                }

                break;
            }

            default:
                cout << "Saindo..." << endl;
                break;
        }
    }
    

    return 0;
}