// Falta para fazer:
// Fazer o case 9 de Menção Honrosa (menciona na tela todos os Astronautas que morreram: nome, histórico de Voos e Voo em que morreu)
// Refazer a interface gráfica de listar voos, e listar passageiros, igual a verificação de registro de voo e de astronautas


#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>

using namespace std;

enum vooStatus {
    PLANEJANDO,
    DESTRUIDO,
    EMVOO,
};

enum astroStatus{
    VIVO,
    MORTO,
};

class Astronauta {
private:
    string cpf;
    string nome;
    int idade;
    bool dispo = true;
    astroStatus status = VIVO;
    list<int> historicoVoos;

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

    astroStatus getStatus() {
        return status;
    }

    bool getDisponibilidade() {
        return dispo;
    }

    void setStatus(astroStatus novoStatus) {
        status = novoStatus;
    }

    void setDisponibilidade(bool disponivel) {
        dispo = disponivel;
    }

    void adicionarVoo(int codigoVoo) {
        historicoVoos.push_back(codigoVoo);
    }

    const list<int>& getHistoricoVoos() const {
        return historicoVoos;
    }

    void setHistoricoVoos(const list<int>& novoHistorico) {
        historicoVoos = novoHistorico;
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

    void setStatus(vooStatus novoStatus) {
        status = novoStatus;
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
            cout << "O Voo de codigo " << codigoVoo << " foi explodido." << endl; 
            for (auto& astronauta : passageiros) {
                astronauta.setStatus(MORTO);
                cout << "O astronauta " << astronauta.getNome() << " morreu..." << endl;
            } 
        }
        else {
            status = EMVOO;
            cout << "O Voo de codigo " << codigoVoo << " esta em andamento." << endl;
        }

        dispo = false;
    }

    void visualizarPassageiros(const list<Astronauta>& astronautas) const {
        cout << "   Astronautas cadastrados para o voo [" << codigoVoo << "]:" << endl;
        for (const auto& astronauta : passageiros) {
            cout << "   CPF: " << astronauta.getCPF() << ", Nome: " << astronauta.getNome() << ", Idade: " << astronauta.getIdade() << endl;
        }
    }

    void removerPassageiro(const string& cpf) {
        for (auto it = passageiros.begin(); it != passageiros.end(); ++it) {
            if (it->getCPF() == cpf) {
                passageiros.erase(it);
                return;
            }
        }
    }


    void finalizarVoo() {
        status = PLANEJANDO; // definir o status do voo como planejando novamente
        dispo = true; // tornar o voo disponível novamente

        // Percorrer a lista de passageiros e tornar a disponibilidade de cada astronauta como true novamente
        for (auto& astronauta : passageiros) {
            astronauta.setDisponibilidade(true);
        }

        // Limpar a lista de passageiros, já que o voo foi finalizado
        passageiros.clear();
    }

};

int main(void) {
    cout << "Bem vindo ao controle de Voo." << endl;

    int controle = 0;
    list<Astronauta> astronautas;
    list<Voo> voos;

    while (controle != 1) {
        cout << endl;
        cout << "Escolha uma opcao:" << endl;

        list<string> opcoes;
        opcoes.push_back("///////////////////////////////////////////////");
        opcoes.push_back("//       1 - Cadastrar Astronauta            //");
        opcoes.push_back("//       2 - Cadastrar Voo                   //");
        opcoes.push_back("//       3 - Registrar Passageiros em um Voo //");
        opcoes.push_back("//       4 - Remover passageiros de um Voo   //");
        opcoes.push_back("//       5 - Listar Voos                     //");
        opcoes.push_back("//       6 - Lancar Voo                      //");
        opcoes.push_back("//       7 - Finalizar Voo                   //");
        opcoes.push_back("//       8 - Listar astronautas              //");
        opcoes.push_back("//       9 - Mencoes honrosas                //");
        opcoes.push_back("//       0 - Sair                            //");
        opcoes.push_back("///////////////////////////////////////////////");

        for (const auto& frase : opcoes) {
            cout << frase << endl;
        }
        cout << endl;
        cout << endl;
        cout << endl;

        int op;
        cout << "Digite uma opcao: ";
        cin >> op;

        cout << endl;

        switch (op) {
            case 1: {
                string cpf, nome;
                int idade;
                cout << "CPF do astronauta: ";
                cin >> cpf;
                cout << "Nome do astronauta: ";
                cin.ignore(); // Ignora o caractere de nova linha pendente do cin >> op
                getline(cin, nome);
                cout << "Idade do astronauta: ";
                cin >> idade;

                Astronauta astronauta(cpf, nome, idade);
                cout << endl << "Astronauta cadastrado: " << endl;
                cout << "   CPF: " << astronauta.getCPF() << endl;
                cout << "   Nome: " <<  astronauta.getNome() << endl;
                cout << "   Idade: " << astronauta.getIdade() << endl;

                astronautas.push_back(astronauta); // Armazenando astronauta em uma lista
                break;
            }
            
            case 2: {
                int numVoo;
                cout << "Codigo do voo: ";
                cin >> numVoo;
                
                Voo novoVoo(numVoo);
                cout << "O voo com codigo " << novoVoo.getCodigo() << " esta em planejamento." << endl;

                voos.push_back(novoVoo); // Armazenando Voo em lista

                break;
            }

            case 3: {
                cout << "Voos disponiveis (em planejamento): " << endl;

                for (const auto& voo : voos) {
                    if (voo.getStatus() == PLANEJANDO) {
                        cout << "   Voo Cod: " << voo.getCodigo() << endl;
                    }
                }

                cout << endl;

                int cod;
                cout << "Digite o codigo do Voo a ser adicionado Passageiros: ";
                cin >> cod;

                // Procurar Voo na lista de voos
                bool encontrado = false;
                for (auto it = voos.begin(); it != voos.end(); ++it) {
                    if (it->getCodigo() == cod && it->getStatus() == PLANEJANDO) {
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
                            for (auto& astronauta : astronautas) {
                                if (astronauta.getCPF() == cpfAstronauta && astronauta.getStatus() == VIVO && astronauta.getDisponibilidade()) {
                                    it->adicionarPassageiro(astronauta); // Adicionar passageiro ao voo encontrado
                                    astronauta.adicionarVoo(it->getCodigo());
                                    astronauta.setDisponibilidade(false);
                                    astroFind = true; // Atualizar astroFind
                                    break;
                                }
                                else if (astronauta.getCPF() == cpfAstronauta && astronauta.getStatus() == MORTO){
                                    cout << "Este astronauta esta morto." << endl; // Verifica se o astronauta está morto
                                }
                                else if (astronauta.getCPF() == cpfAstronauta && !astronauta.getDisponibilidade()) {
                                    cout << "Este astronauta nao esta disponivel." << endl; // Verifica se o astronauta está indisponivel
                                }
                            }
                            if (astroFind) {
                                cout << endl << "Astronauta adicionado ao voo com sucesso!" << endl << endl;
                            }
                        }
                        break; // Sair do loop de voos
                        }
                        else if (it->getCodigo() == cod && it->getStatus() == EMVOO) {
                            cout << endl << "O voo nao esta disponivel para se adicionar passageiros." << endl << endl;
                            break;
                        }
                }

                if (!encontrado) {
                    cout << "Voo nao encontrado!" << endl;
                }

                break;
            }

            case 4: {
                cout << "Voos disponiveis (em planejamento): " << endl;

                for (const auto& voo : voos) {
                    if (voo.getStatus() == PLANEJANDO) {
                        cout << "   Voo Cod: " << voo.getCodigo() << endl;
                    }
                }

                cout << endl;

                int cod;
                cout << "Digite o codigo do voo do qual deseja remover passageiros: ";
                cin >> cod;

                // Procurar o voo na lista de voos
                bool encontrado = false;
                for (auto& voo : voos) {
                    if (voo.getCodigo() == cod && voo.getStatus() == PLANEJANDO) {
                        encontrado = true;

                        // Exibir os passageiros do voo
                        cout << "Passageiros do voo [" << cod << "]:" << endl;
                        cout << endl;
                        voo.visualizarPassageiros(astronautas);
                        cout << endl;

                        // Remover passageiros
                        while (true) {
                            string cpfPassageiro;
                            cout << "Digite o CPF do passageiro que deseja remover ( [0] para sair ): ";
                            cin >> cpfPassageiro;

                            if (cpfPassageiro == "0") {
                                break;
                            }

                            // Remover o passageiro do voo
                            voo.removerPassageiro(cpfPassageiro);

                            // Atualizar o histórico de voos do passageiro 
                            for (auto& astronauta : astronautas) {
                                if (astronauta.getCPF() == cpfPassageiro) {
                                    astronauta.setDisponibilidade(true); 
                                    auto& historico = astronauta.getHistoricoVoos(); // Obtém uma referência constante ao histórico de voos
                                    list<int> historicoModificado = historico; // Faz uma cópia do histórico de voos
                                    historicoModificado.remove(cod); // Remove o código do voo da cópia
                                    astronauta.setHistoricoVoos(historicoModificado); // Atualiza o histórico de voos do astronauta com a cópia modificada
                                    break;
                                }
                            }

                            cout << "Passageiro removido com sucesso!" << endl;
                        }

                        break; // Sair do loop de voos
                    }
                    else if (voo.getCodigo() == cod && voo.getStatus() != PLANEJANDO) {
                        cout << "O voo nao esta disponivel para remover passageiros." << endl << endl;
                        break;
                    }
                }

                if (!encontrado) {
                    cout << "Voo nao encontrado!" << endl;
                }

                break;
            }

            case 5: {
                cout << "Voos cadastrados:" << endl;

                for (const auto& voo : voos) {  // O for percorre a lista de voos cadastrados
                    cout << "Codigo do Voo: " << voo.getCodigo() << endl;  // imprime as insformações do voo a partir do seu código (funciona como uma key)
                    cout << "   Status do Voo: ";
                    switch (voo.getStatus()) {
                        case PLANEJANDO:
                            cout << "em planejamento." << endl;
                            break;
                        case DESTRUIDO:
                            cout << "o voo foi explodido." << endl;
                            break;
                        case EMVOO:
                            cout << "Em voo." << endl;
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
                cout << "Voos disponiveis para lancamento: " << endl;

                for (const auto& voo : voos) {
                    if (voo.getStatus() == PLANEJANDO) {
                        cout << "   Voo Cod: " << voo.getCodigo() << endl;
                    }
                }

                cout << endl;


                int cod;
                cout << "Digite o codigo do voo a ser lancado: ";
                cin >> cod;

                bool encontrado = false;

                // Percorrer a lista de voos
                for (auto it = voos.begin(); it != voos.end(); ++it) { // Passagem por refêrencia
                    if (it->getCodigo() == cod && it->getStatus() == PLANEJANDO) {
                        it->lancarVoo(); // Chamar a função lancarVoo() neste voo
                        encontrado = true;
                        break;
                    }
                    else if (it->getCodigo() == cod && it->getStatus() == EMVOO) {
                        cout << "O voo ja foi lancado." << endl;
                        break;
                    }
                    else if (it->getCodigo() == cod && it->getStatus() == DESTRUIDO) {
                        cout << "O voo foi explodido." << endl;
                        break;
                    }
                }

                if (!encontrado) {
                    cout << "Voo nao encontrado!" << endl;
                }

                break;
            }
            
            case 7: {
                cout << "Voos disponiveis para finalizar: " << endl;

                for (const auto& voo : voos) {
                    if (voo.getStatus() == EMVOO) {
                        cout << "   Voo Cod: " << voo.getCodigo() << endl;
                    }
                }

                cout << endl;


                int cod;
                cout << "Digite o codigo do voo a ser finalizado: " << endl;
                cin >> cod;

                bool encontrado = false;

                // Percorrer a lista de voos
                for (auto& voo : voos) {
                    if (voo.getCodigo() == cod && voo.getStatus() == EMVOO) {
                        voo.finalizarVoo(); // Chamar a função finalizarVoo() neste voo
                        encontrado = true;
                        cout << "Voo finalizado com sucesso!" << endl;
                        break;
                    }
                    else if (voo.getCodigo() == cod && voo.getStatus() != EMVOO ) {
                        cout << "O voo não está disponivel para finalizar." << endl;
                        break;
                    }
                }
            

                if (!encontrado) {
                    cout << "Voo nao encontrado!" << endl;
                }

                break;
            }

            case 8: {
                cout << "Astronautas Cadastrados:" << endl << endl;

                if (astronautas.empty()) {
                    cout << "Nao ha astronautas cadastrados." << endl;
                }
                else {
                    for (auto& astronauta : astronautas) {
                        cout << "Nome: " << astronauta.getNome() << endl;
                        cout << "CPF: " << astronauta.getCPF() << endl;
                        cout << "Idade: " << astronauta.getIdade() << endl;
                        if (astronauta.getDisponibilidade()) cout << "Status: Disponivel" << endl;
                        else cout << "Status: Indisponivel" << endl;
                        cout << "Ultimo voo cadastrado: ";
                        if (astronauta.getHistoricoVoos().empty()) {
                            cout << "O astronauta nao esteve cadastrado em nenhum voo" << endl;
                        }
                        else {
                            cout << astronauta.getHistoricoVoos().back() << endl;
                        }
                        
                        cout << endl;
                    }
                }

                cout << endl;

                break;
            }


            case 9: {

                // Menções Honrosas para os astronautas tiveram os status alterados para mortos
                
                cout << "Mencoes Honrosas:" << endl;

                /*
                for (auto& astronauta : astronautas) {
                    if (astronauta.getStatus() == MORTO) {
                        cout << "   Nome: " << astronauta.getNome() << endl;
                        cout << "   CPF: " << astronauta.getCPF() << endl;
                        cout << "   Historico de Voos:" << endl;
                        const auto& historico = astronauta.getHistoricoVoos();
                        if (!historico.empty()) {
                            for (const auto& codigoVoo : historico) {
                                cout << "      Codigo do Voo: " << codigoVoo << endl;
                            }
                        } 
                        else {
                            cout << "      Sem historico de voos." << endl;
                        }
                        cout << endl;
                    }
                }
                */

                break;
            }

            default:
                cout << "Saindo..." << endl;
                controle = 1;
                break;
        }

        cout << endl;
        cout << endl;
    }
    return 0;
}
