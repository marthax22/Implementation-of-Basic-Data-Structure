#include "MaxHeap.h"

MaxHeap::MaxHeap(int size) {
    maxSize = size;
    currentSize = 0;
    heap = new int[maxSize];  //Δεσμευση μνημης για τον πινακα
}

MaxHeap::~MaxHeap() {
    delete[] heap;   // Αποδεσμευση μνημης
}

void MaxHeap::insert(int val) {
    if (currentSize == maxSize) {
        return;  
    }

    heap[currentSize] = val;   // Τοποθετηση στοιχειου στο τελος
    goUp(currentSize);         // Ανυψωση για διατηρηση ιδιοητας σωρου
    currentSize++;             
}

int MaxHeap::top() const {
    if (currentSize == 0) {
        return -1;  // Ο σωρος είναι κενος
    }
    return heap[0];   //Το μεγιστο στοιχειο ειναι στη ριζα
}

void MaxHeap::deleteTop() {
    if (currentSize == 0) {
        return;   //Δεν υπαρχει τιποτα για διαγραφη
    }

    heap[0] = heap[currentSize - 1];   // Αντικατασταση της ριζας με το τελευταιο στοιχειο
    currentSize--;
    goDown(0);  // Καθοδικη εξισοροπηση
}

int MaxHeap::getSize() const {
    return currentSize;
}

void MaxHeap::goUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[i] > heap[parent]) {
            std::swap(heap[i], heap[parent]);   // Ανταλλαγη με τον γονεα αν ειναι μεγαλυτερο
            i = parent;
        } else {
            return; 
        }
    }
}

void MaxHeap::goDown(int i) {
    while (2 * i + 1 < currentSize) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < currentSize && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            std::swap(heap[i], heap[largest]);   // Ανταλλαγη με το μεγαλυτερο παιδι
            i = largest;
        } else {
            break;
        }
    }
}

void MaxHeap::buildFromFile(string& filename) {
    std::ifstream file(filename);
    int number;
    while (file >> number) {
        insert(number);   // Εισαγωγη καθε αριθμου στον σωρο
    }
    file.close(); 
}
