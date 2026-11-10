#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 1009; //μέγεθος του πίνακα 
    int* table;//δυναμικός πίνακας που αποθηκεύει τα στοιχεία του πίνακα
    bool* occupied;//δυναμικός πίνακας που αποθηκεύει αν το στοιχείο του πίνακα είναι κενό ή όχι
    int size;//μέγεθος του πίνακα

    int hash(int key);//επιστροφή του hash κλειδιού key
public:
    HashTable();//constructor
    ~HashTable();//destructor
    void insert(int key);//εισαγωγή στοιχείου στον πίνακα 
    bool search(int key);//αναζήτηση στοιχείου στον πίνακα
    int getSize();//επιστροφή του μεγέθους του πίνακα
    void buildFromFile(string& filename);//δημιουργία του πίνακα από το αρχείο με όνομα filename
};
#endif