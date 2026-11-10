#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <fstream>
#include <string>
#include <iostream> 
using namespace std;
class MaxHeap {
private:
    int* heap;         // Πινακας με τα στοιχεια
    int maxSize;       // Μεγιστο μεγεθος του πινακα
    int currentSize;   // Πληθος στοιχειων που υπαρχουν τωρα

    void goUp(int i);     // Κινηση προς τα πανω για εξισοροπηση σωρου
    void goDown(int i);   //Κινηση προς τα κατω για διατηρηση σωρου

public:
    MaxHeap(int size=10);  
    ~MaxHeap();

    void insert(int val);   // Εισαγωγη στοιχειου στον σωρο
    int top() const;        // Επιστροφη του μεγαλυτερου στοιχειου
    void deleteTop();       // Διαγραφη του max στοιχειου
    int getSize() const;    // Επιστροφη μεγεθους

    void buildFromFile(string& filename);  
};

#endif
