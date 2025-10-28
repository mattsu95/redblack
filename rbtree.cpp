#include <iostream>
#include <string>

using namespace std;

#define black false
#define red true

struct Node {
    string word, meaning;
    Node *left, *right, *parent;
    bool color; //true == red; false == black

    Node(string w, string m) : word(w), meaning(m), left(nullptr), right(nullptr), parent(nullptr), color(red) {}
};

class Dictionary {
public:

    Node *root;
    Dictionary(){root = NULL;}

    void Insert(const string &w, const string &m) {
        Node* z = new Node(w, m);
        Node* n = Insertrb(z);
        
        if(n != z) {
            delete z;
            return;
        }
        
        InsertFixup(n);                           
        if(root) root->color = black;
    }

    Node* rLeft(Node* x) { 
        if(!x || !x->right) return x;
		Node* y = x->right;
		Node *w = y->left;
		
		y->left = x;
        y->parent = x->parent;

        if(y->parent) {
            if(y->parent->left == x) y->parent->left = y;
            else y->parent->right = y;
        }
        else { //parent == nullptr
            root = y;
        }

        x->parent = y;
		x->right = w;
        if(w) w->parent = x;
		
		return y;
	}

    Node* rRight(Node* x) {
        if(!x || !x->left) return x;
		Node* y = x->left;
		Node *w = y->right;
		
		y->right = x;
        y->parent = x->parent;

        if(y->parent) {
            if(y->parent->left == x) y->parent->left = y;
            else y->parent->right = y;
        }
        else { //parent == nullptr
            root = y;
        }

        x->parent = y;
		x->left = w;
        if(w) w->parent = x;
		
		return y;
	}
    
private:
    Node* Insertrb(Node *z) {
        Node* x = root;         //não teve jeito, tive que fazer isso
        Node* y = nullptr;

        while(x) {
            y = x;
            if(z->word < x->word) x = x->left;
            else if(z->word > x->word) x = x->right;
            else {
                return x;
            }
        }
        z->parent = y;
        if(!y) root = z;
        else if(z->word < y->word) y->left = z;
        else y->right = z;

        return z;  
    }

    void InsertFixup(Node* z) {
        while(z->parent && z->parent->color == red) {
            Node* y = z->parent;
            Node* g = y->parent;    //g de godfather
            if(!g) { // y == root
                y->color = black;
                break;
            }
    
            Node* uncle = (y == g->left) ? g->right : g->left;
    
            // case 1: z's uncle is red
            if(uncle && uncle->color) {
                uncle->color = black;   //o tio e o pai pegam a negritude do avô
                y->color = black;
                g->color = red;
                z = g;
            } 
            else {
                if(y == g->left) {
                    
                    //case 2.1: z is an inner right child (left-right)
                    if(z == y->right) {
                        z = y;
                        rLeft(z);     //single rotation left (do pai do nó atual)
                        y = z->parent;
                        g = y ? y->parent : nullptr;
                    } //segue pro caso 3.1
                    
                    //case 3.1: z is an outer left child (left-left)
                    y = z->parent;
                    g = y ? y->parent : nullptr;
                    
                    //troca as cores do pai e do vô
                    if(y) y->color = black;
                    if(g) {
                        g->color = red;
                        rRight(g);   //single rotation right (do vô do nó atual)
                    }
                    z = y ? y : z;
                }
                else { //y == g->right
                
                    //case 2.2: z is an inner left child (right-left)
                    if(z == y->left) {
                        z = y;
                        rRight(z);    //single rotation right
                        y = z->parent;
                        g = y ? y->parent : nullptr;
                    } //segue pro caso 3.2
                    
                    
                    //case 3.2: z is an outer left child (left-left)
                    y = z->parent;
                    g = y ? y->parent : nullptr;
                    
                    if(y) y->color = black;
                    if(g) {
                        g->color = red;
                        rLeft(g);    //single rotation left
                    }
                    z = y ? y : z;
                }
            }
        }
    
        if(root) root->color = black;
    }

};

// ---- Funções do menu para teste ----
Dictionary dict;

void inserirPalavra(){
    string w, m;
    cout << "Palavra: ";
    getline(cin, w);
    if (w.empty()) {
        cout << "Palavra vazia. Abortando.\n";
        return;
    }
    cout << "Significado (uma linha): ";
    getline(cin, m);
    dict.Insert(w, m);
    cout << "Inserido: " << w << "\n";
}

void inorderPrint(Node* node) {
    if (!node) return;
    inorderPrint(node->left);
    cout << (node->color == red ? "(R) " : "(B) ") << node->word << " : " << node->meaning << "\n";
    inorderPrint(node->right);
}

void listarPalavras(){
    if (!dict.root) {
        cout << "Dicionario vazio.\n";
        return;
    }
    inorderPrint(dict.root);
}

void buscarPalavra(){
    string w;
    cout << "Palavra a buscar: ";
    getline(cin, w);
    Node* cur = dict.root;
    while (cur) {
        if (w == cur->word) {
            cout << cur->word << " : " << cur->meaning << "\n";
            return;
        } else if (w < cur->word) cur = cur->left;
        else cur = cur->right;
    }
    cout << "Palavra nao encontrada.\n";
}

void excluirPalavra(){
    cout << "Funcao de exclusao nao implementada ainda.\n";
}

void salvarEmArquivo(){
    cout << "Funcao de salvar nao implementada (teste local somente).\n";
}


void carregarDeArquivo(Dictionary &dict) {
    string linha, palavra, significado;
    int linhasLidas = 0;
    
    // O loop continua enquanto houver linhas para ler da entrada padrão (cin)
    while (getline(cin, linha)) {
        linhasLidas++;

        // Encontra a posição do primeiro espaço na linha
        size_t pos = linha.find(' ');

        if (pos == string::npos) { 
            // Se não houver espaço, a palavra é a linha inteira, significado vazio
            palavra = linha;
            significado = "";
        } else {
            // palavra posição 0 até a posição do espaço
            palavra = linha.substr(0, pos);

            // Posição depis do espaço até o final da linha
            significado = linha.substr(pos + 1);
        }

        //sem palavras vazias
        if (palavra.empty()) {
            continue;
        }

        dict.Insert(palavra, significado);
    }

    
    // 1. Limpa o estado de falha (EOF) do cin
    cin.clear();
    cin.ignore(); // limpar buffer
    
    cout << "Carregamento finalizado. " << linhasLidas << " linhas processadas.\n";
}

int main() {
    int opcao;

    cout << "Tentando carregar dados do arquivo...\n";
    carregarDeArquivo(dict);

    cin.clear();

    do {
        cout << "\n========== DICIONÁRIO DIGITAL ==========\n\n";
        cout << "1. Inserir nova palavra\n";
        cout << "2. Buscar palavra\n";
        cout << "3. Listar todas as palavras (ordem alfabética)\n";
        cout << "4. Excluir palavra\n";
        cout << "5. Salvar e sair\n\n";
        cout << "========================================\n";
        cout << "Selecione uma opção: ";

        if (!(cin >> opcao)) break;
        cin.ignore(); // limpar buffer

        switch (opcao) {
            case 1:
                inserirPalavra();
                break;
            case 2:
                buscarPalavra();
                break;
            case 3:
                listarPalavras();
                break;
            case 4:
                excluirPalavra();
                break;
            case 5:
                salvarEmArquivo();
                cout << "\nEncerrando o programa e salvando alterações...\n";
                break;
            default:
                cout << "\nOpção inválida. Tente novamente.\n";
        }
    } while (opcao != 5);

    return 0;
}
