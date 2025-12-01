#include <iostream>
#include <limits>

using namespace std;

int Dado_Final = 0;

void LimparInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Pausar() {
    cout << "Pressione ENTER para continuar";
    LimparInputBuffer();
    cin.get();
}

void ExibirMenu() {
      cout << endl;
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║               RPG v1.0               ║" << endl;
    cout << "║      Estrutura de Dados I - UFG      ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;
}

void MenuPrincipal(){
    cout << endl;
    cout << "============ MENU PRINCIPAL ============" << endl;
    cout << " 1. Definir tipo de dado do jogo" << endl;
    cout << " 2. Carregar personagens de arquivo" << endl;
    cout << " 3. Adicionar personagem manualmente" << endl;
    cout << " 4. Remover personagem" << endl;
    cout << " 5. Exibir lista de personagens" << endl;
    cout << " 6. Rolar iniciativa para todos" << endl;
    cout << " 7. Ordenar lista (QuickSort)" << endl;
    cout << " 8. Ordenar lista (MergeSort)" << endl;
    cout << " 9. Iniciar combate" << endl;
    cout << " 0. Sair" << endl;
    cout << "========================================" << endl;
    cout << " Escolha uma opcao: ";
}