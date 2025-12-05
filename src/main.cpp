#include <iostream>
#include <limits>
#include <algorithm>
#include "hpp/utils.hpp"
#include "hpp/lista.hpp"
#include <random>

using namespace std;
string Metodo_Ordenacao = "Nenhum";
int Dado_Final = 0;

void LimparInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Pausar()
{
    cout << "Pressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void ExibirMenu()
{
    cout << endl;
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║            RPG v1.0                  ║" << endl;
    cout << "║      Estrutura de Dados I - UFG      ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;
}

void MenuPrincipal()
{
    cout << endl;
    cout << "============ MENU PRINCIPAL ============" << endl;
    cout << " 1. Definir tipo de dado do jogo" << endl;
    cout << " 2. Adicionar personagem manualmente" << endl;
    cout << " 3. Remover personagem" << endl;
    cout << " 4. Exibir lista de personagens" << endl;
    cout << " 5. Rolar iniciativa para todos" << endl;
    cout << " 6. Ordenar lista (QuickSort)" << endl;
    cout << " 7. Ordenar lista (MergeSort)" << endl;
    cout << " 8. Iniciar combate" << endl;
    cout << " 9. Carregar personagens de arquivo" << endl;
    cout << " 0. Sair" << endl;
    cout << "========================================" << endl;
    cout << " Metodo de ordenacao atual: " << Metodo_Ordenacao << endl;
    cout << " Escolha uma opcao: ";
}

void ExibirMenuDeCombate()
{
    cout << endl;
    cout << "============== MENU DE COMBATE ==============" << endl;
    cout << " P - Proximo turno (Rola e Reordena TUDO)" << endl;
    cout << " R - Remover personagem por ID" << endl;
    cout << " A - Adicionar novo personagem (e Reordena)" << endl;
    cout << " L - Listar todos os personagens" << endl;
    cout << " S - Sair do combate" << endl;
    cout << "----------------------------------------" << endl;
    cout << " Metodo de ordenacao: " << Metodo_Ordenacao << endl;
    cout << " Acao: ";
}

void AddPersonagem(Lista *lista, int *proximoID)
{
    if (!lista || !proximoID)
        return;

    Personagem p;
    p.id = (*proximoID)++;

    cout << "Nome: ";
    getline(cin, p.nome);

    if (p.nome.empty())
    {
        cout << "Nome invalido!" << endl;
        (*proximoID)--;
        return;
    }

    int nivelInput;
    cout << "Nivel (1-20): ";
    cin >> nivelInput;

    p.nivel = nivelInput;
    if (p.nivel < 1) p.nivel = 1;
    if (p.nivel > 20) p.nivel = 20;

    p.dadoBase = Dado_Final;

    char tipo;
    cout << "Tipo (P = Player, N = NPC): ";
    cin >> tipo;

    while (tipo != 'P' && tipo != 'N' && tipo != 'p' && tipo != 'n')
    {
        cout << "Tipo invalido! Insira P para Player ou N para NPC: ";
        cin >> tipo;
    }

    p.isPlayer = (tipo == 'P' || tipo == 'p');
    p.iniciativaAtual = 0;

    lista->inFim(p);

    cout << "Personagem adicionado com sucesso! ID: " << p.id << endl;
}

int addPersonagemArquivo(Lista* lista, int* proximoID) {
    string nomeArquivo;
    
    cout << endl << "Digite o caminho do arquivo ou pressione ENTER para usar o padrao: ";
    getline(cin, nomeArquivo);
    
    if (nomeArquivo.empty()) {
        nomeArquivo = "data/personagens.txt";
        cout << "Usando arquivo padrao: " << nomeArquivo << endl;
    }
    
    int carregados = carregarArquivo(nomeArquivo, lista);
    
    if (carregados > 0) {
        *proximoID += carregados;
        cout << "Carregados " << carregados << " personagem(ns)!" << endl;
    }
    
    return carregados;
}

void RemoverPersonagem(Lista *lista)
{
    if (!lista || lista->estaVazia())
    {
        cout << "Nenhum personagem para remover!" << endl;
        return;
    }

    int id;
    cout << "Digite o ID do personagem a ser removido: ";
    cin >> id;

    if (lista->remover(id))
        cout << "Personagem removido com sucesso!" << endl;
    else
        cout << "Personagem com ID " << id << " nao encontrado!" << endl;
}

void IniciarCombate(Lista *lista, int *proximoID)
{

    if (!lista || lista->estaVazia())
    {
        cout << "Nenhum personagem na lista para iniciar o combate!" << endl;
        return;
    }
    
    if (Metodo_Ordenacao == "Nenhum")
    {
        cout << "Metodo de ordenacao nao selecionado. Usando QuickSort por padrao." << endl;
        Metodo_Ordenacao = "QuickSort";
    }

    cout << "Iniciando combate com " << Metodo_Ordenacao << "..." << endl;

    rolarIniciativaTodos(lista);
    
    if(Metodo_Ordenacao == "QuickSort"){
        lista->ordenarQS();
    } else if(Metodo_Ordenacao == "MergeSort"){
        lista->ordenarMerge();
    }

    int rodadaAtual = 1;
    int turnosTotal = 0;

    bool combateAtv = true;

    while (combateAtv)
    {

        if (lista->estaVazia()){
            cout << "Todos os personagens foram removidos. Combate encerrado." << endl;
            break;
        }

        lista->exibirOrdemCombate();

        char acao;
        ExibirMenuDeCombate();
        cin >> acao;
        LimparInputBuffer();

        switch (acao){
        case 'P':
        case 'p':
            cout << "\n--- Processando Proximo Turno ---" << endl;
            {
                No *primeiro = lista->getInicio();
                if (primeiro != nullptr) {
                    Personagem p = primeiro->dados;

                    lista->remover(p.id);
                    lista->inFim(p);

                    cout << "Turno de " << p.nome << " encerrado." << endl;

                    turnosTotal++;

                    if (turnosTotal >= lista->getTamanho()) {
                        
                        cout << "\n>>> FIM DA RODADA " << rodadaAtual << " <<<" << endl;
                        cout << ">>> Rerolando Iniciativas para a proxima rodada... <<<" << endl;

                        rolarIniciativaTodos(lista);
                        
                        if(Metodo_Ordenacao == "QuickSort"){
                            lista->ordenarQS();
                        } else {
                            lista->ordenarMerge(); 
                        }

                        rodadaAtual++;
                        turnosTotal = 0;
                        
                        cout << ">>> INICIANDO RODADA " << rodadaAtual << " (Nova Ordem Definida) <<<" << endl;
                        Pausar();
                    }
                }
            }
            break;
        case 'R':
        case 'r':
            if (lista->estaVazia())
            {
                cout << "Nenhum personagem para remover!" << endl;
                break;
            }
            // Chama a função global para remoção por ID
            RemoverPersonagem(lista);
            Pausar();
            break;
          case 'A':
        case 'a':
            AddPersonagem(lista, proximoID);
            
            rolarIniciativaTodos(lista);
            
            if(Metodo_Ordenacao == "MergeSort"){
                cout << "Reordenando com MergeSort..." << endl;
                lista->ordenarMerge();
            } else {
                cout << "Reordenando com QuickSort..." << endl;
                lista->ordenarQS();
            }
            Pausar();
            break;

        case 'L':
        case 'l':
            lista->exibir();
            Pausar();
            break;
        case 'S':
        case 's':
            cout << "Saindo do combate..." << endl;
            combateAtv = false;
            break;
        default:
            cout << "Acao invalida! Tente novamente." << endl;
            break;
        }       
    }
}

int main()
{
    // inicializarRNG(); 

    Lista lista;
    int proximoID = 1;
    int opcao;

    ExibirMenu();

    do
    {
        MenuPrincipal();
        cin >> opcao;
        LimparInputBuffer();

        if (Dado_Final == 0 && opcao != 0 && opcao != 1)
        {
            cout << "Voce precisa escolher o tipo de dado primeiro! (Opcao 1)" << endl;
            Pausar();
            continue;
        }

        switch (opcao)
        {
        case 1:
            cout << "Escolha o tipo de dado base (d4, d6, d8, d10, d12, d20): ";
            cin >> Dado_Final;

            while (Dado_Final != 4 && Dado_Final != 6 && Dado_Final != 8 &&
                   Dado_Final != 10 && Dado_Final != 12 && Dado_Final != 20)
            {
                cout << "Valor invalido! Escolha entre 4, 6, 8, 10, 12 ou 20: ";
                cin >> Dado_Final;
            }

            cout << "Dado definido como d" << Dado_Final << endl;
            Pausar();
            break;

        case 2:
            LimparInputBuffer();
            AddPersonagem(&lista, &proximoID);
            Pausar();
            break;

        case 3:
            RemoverPersonagem(&lista);
            Pausar();
            break;

        case 4:
            lista.exibir();
            Pausar();
            break;

        case 5:
            rolarIniciativaTodos(&lista);

            cout << "\n===== Rolagem de Iniciativa =====\n";
            {
                No *it = lista.getInicio();
                while (it != nullptr)
                {
                    cout << it->dados.nome << ": " << it->dados.iniciativaAtual
                              << " (d" << Dado_Final << " + nivel " << it->dados.nivel << ")\n";
                    it = it->proximo;
                }
            }
            cout << "=================================\n";

            cout << "Iniciativa rolada para todos os personagens." << endl;
            Pausar();
            break;

        case 6:
            cout << "Ordenar lista (QuickSort) selecionado. Lista sera ordenada apos rolar iniciativa ou ao iniciar combate." << endl;
            Metodo_Ordenacao = "QuickSort";

            if (!lista.estaVazia()) {
                rolarIniciativaTodos(&lista);
                lista.ordenarQS();
                cout << "\nLista ordenada (apos QuickSort):" << endl;
                lista.exibirOrdemCombate();
            }

            Pausar();
            break;

        case 7:
            cout << "Ordenar lista (MergeSort) selecionado. Lista sera ordenada apos rolar iniciativa ou ao iniciar combate." << endl;
            Metodo_Ordenacao = "MergeSort";

            if (!lista.estaVazia()) {
                rolarIniciativaTodos(&lista);
                lista.ordenarMerge();
                cout << "\nLista ordenada (apos MergeSort):" << endl;
                lista.exibirOrdemCombate();
            }

            Pausar();
            break;

        case 8:
            IniciarCombate(&lista, &proximoID);
            Pausar();
            break;

        case 9:
            addPersonagemArquivo(&lista, &proximoID);
            break;

        case 0:
            cout << "Saindo do programa. Ate mais!" << endl;
            break;

        default:
            cout << "Opcao invalida! Tente novamente." << endl;
            Pausar();
            break;
        }
    } while (opcao != 0);

    return 0;
}