#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream>
#include <cstring>
#define MAX_COMMAND_LENGTH 256
#define MAX_FILENAME_LENGTH 128
#define MAX_HEAP_SIZE 10000
#include <fstream>
#include <limits.h>
#include <climits>
using namespace std;


class MinHeap {
private:
    int* heapArray;//δυναμικός πίνακας που αποθηκεύει τα στοιχεία του heap
    int capacity;//μέγεθος του πίνακα
    int heapSize;//μέγεθος του heap

    void resize();//μετατροπή του πίνακα σε μεγαλύτερο
    void heapifyUp(int index);//επαναφορά της ιδιότητας του min heap από κάτω προς τα πάνω
    void heapifyDown(int index);//επαναφορά της ιδιότητας του min heap από πάνω προς τα κάτω
public:
    MinHeap(int initialCapacity = 10) : capacity(initialCapacity), heapSize(0) {//constructor
        heapArray = new int[capacity];
    }
    ~MinHeap() {//destructor
        delete[] heapArray;
    }
    void insert(int value) ;//εισαγωγή στοιχείου στο heap
    int extractMin() ;//αφαίρεση του ελάχιστου στοιχείου 
    int findMin() ;//επιστροφή του ελάχιστου στοιχείου
    bool isEmpty();//επιστροφή true αν το heap είναι άδειο
    int getSize();//επιστροφή του μεγέθους του heap
    void buildFromFile(string& filename);//δημιουργία του heap από το αρχείο με όνομα filename
    void deleteMin();//διαγραφή του ελάχιστου στοιχείου
};
#endif