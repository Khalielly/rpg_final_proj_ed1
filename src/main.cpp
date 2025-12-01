#include <iostream>
#include <limits>
#include "hpp/utils.hpp"
#include "hpp/lista.hpp"

using namespace std;

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
    cout << " N - Nova rodada (rolar iniciativa)" << endl;
    cout << " L - Listar todos os personagens" << endl;
    cout << " S - Sair do combate" << endl;
    cout << "----------------------------------------" << endl;
    cout << " Acao: ";
}

void AddPersonagem(Lista *lista, int *proximoID)
{
    if (!lista || !proximoID) return;

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

    cout << "Tipo de dado para iniciativa: ";
    cin >> p.dadoBase;
    while (p.dadoBase < 4)
    {
        cout << "Tipo de dado invalido! Insira um valor igual ou maior que 4: ";
        cin >> p.dadoBase;
    }

    cout << "Modificador de iniciativa: ";
    cin >> p.modificador;

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

void IniciarCombate(Lista* lista, int* proximoID)
{
    // implementação da ordenacao
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

        switch (opcao)
        {
        case 1:
            cout << "Definir tipo de dado ainda nao implementado." << endl;
            Pausar();
            break;

        case 2:
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
            cout << "Iniciativa rolada para todos os personagens." << endl;
            Pausar();
            break;

        case 6:
            cout << "Ordenar lista (QuickSort) selecionado." << endl;
            Pausar();
            break;

        case 7:
            cout << "Ordenar lista (MergeSort) selecionado." << endl;
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
