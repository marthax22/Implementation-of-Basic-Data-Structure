#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <limits.h>
using namespace std;
struct Node {
       int key;//στοιχείο του κόμβου
       Node* left;//αριστερός κόμβος
       Node* right;//δεξιός κόμβος
       int height;//ύψος του κόμβου
       Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
   };
class AVLTree {
private:
   
    Node* root;//ρίζα του δέντρου
    int size;//μέγεθος του δέντρου (αριθμός κόμβων)

    int height(Node* n) ;//επιστροφή του ύψους του κόμβου n
    int getBalance(Node* n);//επιστροφή της διαφοράς ύψους μεταξύ των δύο υποδέντρων του κόμβου n
    int max(int a, int b);//επιστροφή του μεγαλύτεερου μεταξύ των a και b 
    Node* rightRotate(Node* y);//δεξιά περιστροφή του κόμβου y
    Node* leftRotate(Node* x);//αριστερή περιστροφή του κόμβου x
    Node* insert(Node* node, int key) ;//εισαγωγή στοιχείου στο δέντρο
    Node* minValueNode(Node* node);//επιστροφή του κόμβου με το ελάχιστο στοιχείο του δέντρου με ρίζα τον κόμβο node
    Node* deleteNode(Node* root, int key);//διαγραφή στοιχείου από το δέντρο
    bool search(Node* node, int key);//αναζήτηση στοιχείου στο δέντρο
    int findMin(Node* node);//επιστροφή του ελάχιστου στοιχείου του δέντρου με ρίζα τον κόμβο node
public:
    AVLTree() : root(nullptr), size(0) {}//constructor

    void insert(int key) ;//εισαγωγή στοιχείου στο δέντρο
    void deleteKey(int key) ;//διαγραφή στοιχείου από το δέντρο
    bool search(int key);//αναζήτηση στοιχείου στο δέντρο
    int findMin() ;//επιστροφή του ελάχιστου στοιχείου
    int getSize();//επιστροφή του μεγέθους του πίνακα
    void buildFromFile( string& filename);//δημιουργία του δέντρου από το αρχείπο με όνομα με filename
};
#endif