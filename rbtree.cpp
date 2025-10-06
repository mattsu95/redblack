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

    Node* Insert(const string &w, const string &m, Node *n) {
        if(!n) {//node == NULL
            Node *aux = new Node(w, m);
            //return new Node(w, m); //n sei se ta certo isso
            aux->color = false; //leaf node always black
            return aux; //faz sentido?
        }

        if(w > n->word) {
            n->right = Insert(w, m, n->right);
        }
        else if(w < n->word) 
            n->left = Insert(w, m, n->right);
        else
            return n;  
        
    }
};