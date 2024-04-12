#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>

using namespace std;

enum vooStatus {
    PLANEJANDO,
    LANCADO,
    DESTRUIDO,
    EMVOO,
};

class Astronauta {
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
    list<Astronauta> passageiros;
    vooStatus status = PLANEJANDO;

public:
    Voo(int codigo) : codigoVoo(codigo) {}

    int getCodigo() const {
        return codigoVoo;
    }

    vooStatus getStatus() const {
        return status; // Retorna o status do voo (que é privado)
    }

    bool getDispo() const {
        return dispo; // Retorna a disponibilidade do voo
    }

    void adicionarPassageiro(const Astronauta& astronauta) {
        passageiros.push_back(astronauta); // Adicionar o astronauta á lista de passageiros
    }

    void lancarVoo() {
        srand(time(nullptr));
        int numAleatorio = rand() % 2; // Número entre 1 e 0 para que seja aleatória a destruição do voo ou seu sucesso

        if (numAleatorio == 0) {
            status = DESTRUIDO;
            dispo = false;
            cout << "O Voo de codigo " << codigoVoo << " foi explodido." << endl; 
        }
        else {
            status = EMVOO;
            dispo = false;
            cout << "O Voo de codigo " << codigoVoo << " esta em andamento." << endl;
        }
    }

    void visualizarPassageiros(const list<Astronauta>& astronautas) const {
        cout << "   Astronautas cadastrados para o voo [" << codigoVoo << "]:" << endl;
        for (const auto& astronauta : passageiros) {
            cout << "   CPF: " << astronauta.getCPF() << ", Nome: " << astronauta.getNome() << ", Idade: " << astronauta.getIdade() << endl;
        }
    }
};

int main(void) {
    cout << "Bem vindo ao controle de Voo." << endl;

    int controle = 0;
    list<Astronauta> astronautas;
    list<Voo> voos;

    while (controle != 1) {
        cout << "Escolha uma opcao:" << endl;

        list<string> opcoes;
        opcoes.push_back("///////////////////////////////////////////////");
        opcoes.push_back("//       1 - Cadastrar Astronauta            //");
        opcoes.push_back("//       2 - Cadastrar Voo                   //");
        opcoes.push_back("//       3 - Registrar Passageiros em um Voo //");
        opcoes.push_back("//       4 - Remover passageiros de um Voo   //");
        opcoes.push_back("//       5 - Listar Voos                     //");
        opcoes.push_back("//       6 - Lancar Voo                      //");
        opcoes.push_back("//       0 - Sair                            //");
        opcoes.push_back("///////////////////////////////////////////////");

        for (const auto& frase : opcoes) {
            cout << frase << endl;
        }

        int op;
        cin >> op;

        switch (op) {
            case 1: {
                string cpf, nome;
                int idade;
                cout << "CPF do astronauta: ";
                cin >> cpf;
                cout << "Nome do astronauta: ";
                cin >> nome;
                cout << "Idade do astronauta: ";
                cin >> idade;

                Astronauta astronauta(cpf, nome, idade);
                cout << "Astronauta cadastrado: " << astronauta.getCPF() << " " << astronauta.getNome() << " " << astronauta.getIdade() << "." << endl;
                astronautas.push_back(astronauta);
                break;
            }
            
            case 2: {
                int numVoo;
                cout << "Codigo do voo: ";
                cin >> numVoo;
                
                Voo novoVoo(numVoo);
                cout << "O voo com codigo " << novoVoo.getCodigo() << " está em planejamento." << endl;

                voos.push_back(novoVoo); // Armazenando Voo em lista

                break;
            }

            case 3: {
                int cod;
                cout << "Digite o código do Voo a ser adicionado Passageiros: ";
                cin >> cod;

                // Procurar Voo na lista de voos
                bool encontrado = false;
                for (auto it = voos.begin(); it != voos.end(); ++it) {
                    if (it->getCodigo() == cod) {
                        it->visualizarPassageiros(astronautas); // Passar a lista de astronautas como argumento
                        encontrado = true;
                        // Adicionar astronautas ao voo
                        while (true) {
                            string cpfAstronauta;
                            cout << "Digite o CPF do astronauta a ser adicionado ao voo ( [0] para sair ): ";
                            cin >> cpfAstronauta;
                            if (cpfAstronauta == "0") {
                                break;
                            }

                            bool astroFind = false;
                            for (const auto& astronauta : astronautas) {
                                if (astronauta.getCPF() == cpfAstronauta) {
                                    it->adicionarPassageiro(astronauta); // Adicionar passageiro ao voo encontrado
                                    astroFind = true; // Atualizar astroFind
                                    break;
                                }
                            }
                            if (astroFind) {
                                cout << "Astronauta adicionado ao voo com sucesso!" << endl;
                            } else {
                                cout << "Astronauta não encontrado/CPF inválido!" << endl;
                            }
                        }
                        break; // Sair do loop de voos
                    }
                }

                if (!encontrado) {
                    cout << "Voo não encontrado!" << endl;
                }

                break;
            }

            case 4: {
                cout << "Você tentou remover um passageiro de um Voo" << endl;
                break;
            }

            case 5: {
                cout << "Voos cadastrados:" << endl;

                for (const auto& voo : voos) {
                    cout << "Codigo do Voo: " << voo.getCodigo() << endl;
                    cout << "   Status do Voo: ";
                    switch (voo.getStatus()) {
                        case PLANEJANDO:
                            cout << "em planejamento" << endl;
                            break;
                        case LANCADO:
                            cout << "o voo foi lançado" << endl;
                            break;
                        case DESTRUIDO:
                            cout << "o voo foi explodido" << endl;
                            break;
                        case EMVOO:
                            cout << "Em voo" << endl;
                            break;
                    }

                    if (voo.getDispo()) cout << "   O voo esta disponivel." << endl;
                    else cout << "   O voo está indisponivel." << endl;

                    cout << "   Passageiros do Voo:" << endl;
                    voo.visualizarPassageiros(astronautas);
                    cout << endl;
                }

                break;
            }

            case 6: {
                int cod;
                cout << "Digite o codigo do voo a ser lancado: " << endl;
                cin >> cod;

                bool encontrado = false;

                // Percorrer a lista de voos
                for (auto it = voos.begin(); it != voos.end(); ++it) { // Passagem por refêrencia
                    if (it->getCodigo() == cod) {
                        it->lancarVoo(); // Chamar a função lancarVoo() neste voo
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) {
                    cout << "Voo nao encontrado!" << endl;
                }

                break;
            }

            default:
                cout << "Saindo..." << endl;
                controle = 1;
                break;
        }
    }
    return 0;
}
