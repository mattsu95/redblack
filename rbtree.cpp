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
        
        InsertFixup(n);                           
        if(root) root->color = black;
    }

    Node* rLeft(Node* x) { 
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
                delete z;
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
        Node* y = z->parent;
        Node* g = y->parent;      //g de godfather
        Node* uncle = nullptr;
        
        if(!y || !g) return; //se for a raiz ou um filho>righteto da raiz ta tudo certo
        while(y && y->color) {
            if(!g) break;

            uncle = (g->left == y)? g->right: g->left;

            //case 1 - z's uncle red
            if(uncle && uncle->color) { 
                uncle->color = black;   //o tio e o pai pegam a negritude do avô
                y->color = black;
                g->color = red;
            }

            else{
                //case 2.1 - z is an inner left child (right-left)
                if(z == y->left && y == g->right) {
                    y = rRight(y); //single rotation right
                    z = y->right;
                } //proceed to case 3.1

                //case 2.2 - z is an inner right child (left-right)
                if(z == y->right && y == g->left) {
                    y = rLeft(y); //single rotation left
                    z = y->left;
                } //proceed to case 3.2

                //case 3.1 - z is an outer right child (right-right)
                if(z == y->right && y == g->right) {
                    y->color = black;
                    g->color = red;
                    y = rLeft(g); //single rotation left
                }

                //case 3.2 - z is an outer left child (left-left)
                else if(z == y->left && y == g->left) {
                    y->color = black;
                    g->color = red;
                    y = rRight(g); //single rotation right
                }
            }
            
            z = y->parent;
            y = z->parent;
            g = (y? y->parent: nullptr); //evitar operação com nullptr
        }
        
    }
};


void carregarDeArquivo(Dictionary &dict) {
    string linha, palavra, significado;

    // O loop continua enquanto houver linhas para ler da entrada padrão (cin)
    while (getline(cin, linha)) {
     

        // Encontra a posição do primeiro espaço na linha
        size_t pos = linha.find(' ');


        if (pos == string::npos) { 
            // Se não houver espaço
            palavra = linha;
            significado = ""; // significado fica vazio
        } else {
            // palavra posição 0 até a posição do espaço
            palavra = linha.substr(0, pos);

            // posição depis do espaço até o final da linha
            significado = linha.substr(pos + 1);
        }

        //sem palavras cagadas
        if (palavra.empty()) {
            continue;
        }

        cout << "Lido do arquivo -> chave = " << palavra << ", significado = " << significado << endl;

        // Adiciona a palavra e o significado
        //dict.Insert(palavra, significado);
    }

    cin.clear();
    cin.ignore();
}


void inserirPalavra(Dictionary &dict) { // Recebe o dict por referencia
    string palavra, significado;

    cout << "\nDigite a nova palavra: ";
    getline(cin, palavra);

    cout << "Digite o significado da palavra: ";
    getline(cin, significado);

    if (palavra.empty()) {
        cout << "\nA palavra não pode estar vazia. Operação cancelada.\n";
        return;
    }

    dict.Insert(palavra, significado);

    cout << "\nPalavra '" << palavra << "' inserida com sucesso!\n";
}

void buscarPalavra(){
    return;
}
void listarPalavras(){
    return;
}
void excluirPalavra(){
    return;
}
void salvarEmArquivo(){
    return;
}

int main() {
    Dictionary dict; 
    int opcao;

    cout << "Tentando carregar dados do arquivo...\n";
    carregarDeArquivo(dict);
    cout << "Carregamento finalizado. Iniciando modo interativo.\n";

    do {
        cout << "\n========== DICIONÁRIO DIGITAL ==========\n\n";
        cout << "1. Inserir nova palavra\n";
        cout << "2. Buscar palavra\n";
        cout << "3. Listar todas as palavras (ordem alfabética)\n";
        cout << "4. Excluir palavra\n";
        cout << "5. Salvar e sair\n\n";
        cout << "========================================\n";
        cout << "Selecione uma opção: ";
        cin >> opcao;
        cin.ignore(); // tirar /n do buffer

        switch (opcao) {
            case 1:
                inserirPalavra(dict); 
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