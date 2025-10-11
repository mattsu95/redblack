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
        
        //InsertFixup(n);                           
        root->color = black;
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
        
        if(!y || g) return; //se for a raiz ou um filho direto da raiz ta tudo certo, pq aparentemente a regra de nó folha ser sempre preto serve pra nada

        while(y && y->color) {
            uncle = (g->left == y)? g->right: g->left;
            if(uncle && uncle->color) { //1st case - z's uncle red
                uncle->color = black;   //o tio e o pai pegam a negritude do avô
                y->color = black;
                g->color = red;
            }


            //aqui, implementar o resto dos casos


            z = y->parent;
            y = z->parent;
            g = y->parent;
        }
        
    }
};