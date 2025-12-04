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
    cout << "║               RPG v1.0               ║" << endl;
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
    cout << " 0. Sair" << endl;
    cout << "========================================" << endl;
    cout << " Escolha uma opcao: ";
}

void ExibirMenuDeCombate()
{
    cout << endl;
    cout << "============== MENU DE COMBATE ==============" << endl;
    cout << " P - Proximo turno" << endl;
    cout << " R - Remover personagem atual" << endl;
    cout << " A - Adicionar novo personagem" << endl;
    cout << " L - Listar todos os personagens" << endl;
    cout << " S - Sair do combate" << endl;
    cout << "----------------------------------------" << endl;
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
        return;
    }

    cout << "Nivel (1-20): ";
    cin >> p.nivel;
    while (p.nivel < 1 || p.nivel > 20)
    {
        cout << "Nivel invalido! Insira um valor entre 1 e 20: ";
        cin >> p.nivel;
    }
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

// Funcoes para QuickSort
No *particao(No *low, No *high)
{
    Personagem pivot = high->dados;
    No *i = low->anterior;

    for (No *j = low; j != high; j = j->proximo)
    {
        if (j->dados.iniciativaAtual >= pivot.iniciativaAtual)
        {
            i = (i == nullptr) ? low : i->proximo;
            std::swap(i->dados, j->dados);
        }
    }

    i = (i == nullptr) ? low : i->proximo;
    swap(i->dados, high->dados);

    return i;
}

void quickSort(No *low, No *high)
{
    if (high != nullptr && low != high && low != high->proximo)
    {
        No *p = particao(low, high);
        quickSort(low, p->anterior);
        quickSort(p->proximo, high);
    }
}

// Funcoes para mergeSort
No *split(No *head)
{
    No *fast = head;
    No *slow = head;

    while (fast->proximo && fast->proximo->proximo)
    {
        fast = fast->proximo;
        slow = slow->proximo;
    }

    No *temp = slow->proximo;
    slow->proximo = nullptr;
    if (temp)
        temp->anterior = nullptr;
    return temp;
}

No *merge(No *primeiro, No *segundo)
{
    if (!primeiro)
        return segundo;
    if (!segundo)
        return primeiro;

    if (primeiro->dados.iniciativaAtual >= segundo->dados.iniciativaAtual)
    {
        primeiro->proximo = merge(primeiro->proximo, segundo);
        if (primeiro->proximo)
            primeiro->proximo->anterior = primeiro;
        primeiro->anterior = nullptr;
        return primeiro;
    }
    else
    {
        segundo->proximo = merge(primeiro, segundo->proximo);
        if (segundo->proximo)
            segundo->proximo->anterior = segundo;
        segundo->anterior = nullptr;
        return segundo;
    }
}

No *mergeSort(No *topo)
{
    if (!topo || !topo->proximo)
        return topo;

    No *segundo = split(topo);

    topo = mergeSort(topo);
    segundo = mergeSort(segundo);

    return merge(topo, segundo);
}

// Iniciar combate
void IniciarCombate(Lista *lista, int *proximoID)
{

    if (!lista || lista->estaVazia())
    {
        cout << "Nenhum personagem na lista para iniciar o combate!" << endl;
        return;
    }

    cout << "Iniciando combate..." << endl;

    bool fim = false;

    while (!fim)
    {

        rolarIniciativaTodos(lista);

        if (Metodo_Ordenacao == "QuickSort")
        {
            cout << "Metodo de ordenacao selecionado: QuickSort" << endl;
            quickSort(lista->getInicio(), lista->getFim());
        }

        if (Metodo_Ordenacao == "MergeSort")
        {
            cout << "Metodo de ordenacao selecionado: MergeSort" << endl;
            mergeSort(lista->getInicio());
        }

        lista->exibirOrdemCombate();

        char acao = ' ';

        do
        {
            ExibirMenuDeCombate();
            cin >> acao;
            LimparInputBuffer();
            switch (acao)
            {
            case 'P':
                continue;
                break;

            case 'R':
                if (lista->estaVazia())
                {
                    cout << "Nenhum personagem para remover!" << endl;
                    break;
                }
                {
                    No *atual = lista->getInicio();
                    Personagem p = atual->dados;
                    if (lista->remover(p.id))
                    {
                        cout << "Personagem " << p.nome << " removido com sucesso!" << endl;
                    }
                }
                break;
            case 'A':
                AddPersonagem(lista, proximoID);
                break;
            case 'L':
                lista->exibir();
                break;
            case 'S':
                cout << "Saindo do combate..." << endl;
                fim = true;
                break;
            default:
                cout << "Acao invalida! Tente novamente." << endl;
                break;
            }

        } while (acao != ' ');
    }
}

int main()
{
    inicializarRNG();

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
            cout << "Ordenar lista (QuickSort) selecionado." << endl;
            Metodo_Ordenacao = "QuickSort";

            cout << "\nLista atual (antes da ordenacao):\n";
            {
                No *it = lista.getInicio();
                while (it != nullptr)
                {
                    cout << it->dados.nome << " - iniciativa: " << it->dados.iniciativaAtual << endl;
                    it = it->proximo;
                }
            }
            Pausar();
            break;

        case 7:
            cout << "Ordenar lista (MergeSort) selecionado." << endl;
            Metodo_Ordenacao = "MergeSort";

            cout << "\nLista atual (antes da ordenacao):\n";
            {
                No *it = lista.getInicio();
                while (it != nullptr)
                {
                    cout << it->dados.nome << " - iniciativa: " << it->dados.iniciativaAtual << endl;
                    it = it->proximo;
                }
            }
            Pausar();
            break;

        case 8:
            IniciarCombate(&lista, &proximoID);
            Pausar();
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
