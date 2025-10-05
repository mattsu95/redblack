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
private:

};