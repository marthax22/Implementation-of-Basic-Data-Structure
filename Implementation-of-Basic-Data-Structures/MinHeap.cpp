#include "MinHeap.h"

void MinHeap:: resize() {
    int newCapacity = capacity * 2;
    int* newArray = new int[newCapacity];

    for (int i = 0; i < heapSize; i++) {
        newArray[i] = heapArray[i];
    }

    delete[] heapArray;
    heapArray = newArray;
    capacity = newCapacity;
}
void MinHeap::heapifyUp(int index) {// ελέγχουμε αν το στοιχείο που εισάγουμε είναι μικρότερο από το στοιχείο γονέα του και αν ναι τότε ανταλλάσουμε τα στοιχεία και συνεχίζουμε να ελέγχουμε το στοιχείο που εισάγουμε μέχρι να βρούμε την σωστή θέση στο δέντρο
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heapArray[index] < heapArray[parent]) {
            std::swap(heapArray[index], heapArray[parent]);
            index = parent;
        } else {
            break;
        }
    }
}
void MinHeap:: heapifyDown(int index) {
    while (true) { //ελέγχουμε αν το στοιχείο που εισάγουμε είναι μεγαλύτερο από το στοιχείο γονέα του και αν ναι τότε ανταλλάσουμε τα στοιχεία και συνεχίζουμε να ελέγχουμε το στοιχείο που εισάγουμε μέχρι να βρούμε την σωστή θέστη στο δέντρο  
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heapSize && heapArray[left] < heapArray[smallest]) {
            smallest = left;
        }

        if (right < heapSize && heapArray[right] < heapArray[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            std::swap(heapArray[index], heapArray[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}
void MinHeap::insert(int value) {//εισάγουμε το στοιχείο στο δέντρο και ελέγχουμε αν το δέντρο είναι γεμάτο και αν ναι τότε αυξάνουμε το μέγεθος του δέντρου
    if (heapSize == capacity) {
        resize();
    }
    heapArray[heapSize] = value;
    heapifyUp(heapSize);
    heapSize++;
}
int MinHeap:: extractMin() {//διαγράφουμε το ελάχιστο στοιχείο από το δέντρο και ελέγχουμε αν το δέντρο είναι άδειο και αν ναι τότε επιστρέφουμε το ελάχιστο στοιχείο
    if (heapSize == 0) {
        return -1;//άδειο heap
    }
    int min = heapArray[0];
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;
    if (heapSize > 0) {
        heapifyDown(0);
    }
    return min;
}
int MinHeap::findMin() {
    if (heapSize == 0) {

    }
    return heapArray[0];
}
bool MinHeap::isEmpty() {
    return heapSize == 0;
}
int MinHeap:: getSize(){
    return heapSize;
}
void MinHeap:: buildFromFile(string& filename) {//διαβάζουμε τα στοιχεία από το αρχείο και τα εισάγουμε στο δέντρο
     ifstream file(filename);
     int number;
     while (file >> number) {
         insert(number);
     }
     file.close();
 }
void MinHeap::deleteMin() {//διαγράφουμε το ελάχιστο στοιχείο
     if (heapSize == 0) return;
     heapArray[0] = heapArray[heapSize - 1];
     heapSize--;
     heapifyDown(0);
 }
