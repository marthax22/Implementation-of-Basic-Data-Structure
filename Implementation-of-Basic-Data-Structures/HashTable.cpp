#include "HashTable.h"

int HashTable:: hash(int key) {
    return key % TABLE_SIZE;//υπολογισμός του hash κλειδιού
}
HashTable::HashTable() {
    table = new int[TABLE_SIZE];
    occupied = new bool[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {//δείχνει αν η θέση είναι κατειλημένη ή όχι
        occupied[i] = false;
    }
    size = 0;
}
HashTable::~HashTable() {
    delete[] table;
    delete[] occupied;
}
void HashTable::insert(int key) {
  int idx = hash(key);
  int startIdx = idx;

  do {//αν η θέση είναι άδεια τότε εισάγουμε το στοιχείο και αυξάνουμε το μέγεθος του πίνακα
      if (!occupied[idx]) {
          table[idx] = key;
          occupied[idx] = true;
          size++;
          return;
      }
      if (occupied[idx] && table[idx] == key) {//αν η θέση είναι κατειλημένη και το στοιχείο που εισάγουμε είναι ίσο με το στοιχείο που υπάρχει τότε το επιστρέφουμε
          return; // key υπάρχει ήδη 
      }
      idx = (idx + 1) % TABLE_SIZE;
  } while (idx != startIdx);
}

bool HashTable::search(int key) {
  int idx = hash(key);
  int startIdx = idx;

  do {//αν η θέση είναι άδεια τότε επιστρέφουμε false αλλιώς ελέγχουμε αν το στοιχείο που εισάγουμε είναι ίσο με το στοιχείο που υπάρχει και αν ναι τότε επιστρέφουμε true αλλιώς συνεχίζουμε να ελέγχουμε το επόμενο στοιχείο
      if (!occupied[idx])
          return false;
      if (table[idx] == key)
          return true;
      idx = (idx + 1) % TABLE_SIZE;
  } while (idx != startIdx);

  return false;
}

int HashTable:: getSize() {
  return size;
}

void HashTable::buildFromFile(string& filename) {
  ifstream infile(filename);
  int number;
  while (infile >> number) {
      insert(number);
  }
  infile.close();
}




