#include <iostream>
#include <string>

using namespace std;

struct Node {
    string word, meaning;
    Node *left, *right, *parent;
    bool color; //true for red, false for black

    Node(string w, string m) : word(w), meaning(m), left(nullptr), right(nullptr), parent(nullptr), color(true) {}
};

class Dictionary {
public:

    Node *root;
    Dictionary(){root = NULL;}
    Node* Insert(const string &w, const string &m) { //achei legal isso aqui pra garantir raiz sempre preta
        Insertrb(w, m, root);                        //mas não queria usar mais de um ponteiro pra node
        //InsertFixup(n);                            //então fiz essa gambiarra desnecessária aí mesmo
        root->color = false;
    }

private:
    Node* Insertrb(const string& w, const string& m, Node *n) {
        if(!n) {//node == NULL
            return new Node(w, m); //n sei se ta certo isso
        }

        if(w > n->word) {
            n->right = Insertrb(w, m, n->right);
            n->right->parent = n;
        }
        else if(w < n->word) {
            n->left = Insertrb(w, m, n->left);
            n->left->parent = n;
        }

        return n;  
        
    }
};