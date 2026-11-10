#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "MinHeap.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "MaxHeap.h"
#include "Graph.h"
using namespace std;
using namespace std::chrono;
// κλάσεις των δομών δεδομένων που θα χρησιμοποιηθούν στο πρόγραμμα 
// κλάση AVLTree με συναρτήσεις insert, deleteKey, search, findMin, getSize, buildFromFile 
// κλάση MinHeap με συναρτήσεις insert, deleteMin, findMin, getSize, buildFromFile 
//κλάση HashTable με συναρτήσεις insert, search, getSize, buildFromFile 
//κλάση MaxHeap με συναρτήσεις insert,deleteTop,top,getSize,buildFromFile
//κλάση Graph με συναρτήσεις insertEdge,deleteEdge,getSize,computeShortestPath,computeSpanningTreeCost,findConnectedComponents,buildFromFile
int main() {
    ifstream commandFile("commands.txt");//διαβάζουμε τις εντολές από το αρχείο commands.txt
    ofstream outputFile("output.txt");//τα αποτελέσματα των εντολών θα γραφτούν στο αρχείο output.txt
    string line;

    AVLTree avltree;
    MinHeap minheap;
    HashTable hashtable;
    MaxHeap maxheap;
    Graph graph;
    while (getline(commandFile, line)) {
        istringstream iss(line);
        string command;
        iss >> command;
        auto start = high_resolution_clock::now();
        if (command == "BUILD") { //αν η εντολή είναι build τότε διαβάζουμε το όνομα της δομής δεδομένων και το όνομα του αρχείου 
            string structure, filename;
            iss >> structure >> filename;
            if (structure == "AVLTREE") { 
                avltree.buildFromFile(filename);
            } else if (structure == "MINHEAP") {
                minheap.buildFromFile(filename);
            } else if (structure == "HASHTABLE") {
                hashtable.buildFromFile(filename);
            }else if(structure=="MAXHEAP"){
                maxheap.buildFromFile(filename);
            }else if(structure=="GRAPH"){
                graph.buildFromFile(filename);
            }
            auto end = high_resolution_clock::now();

            duration<double, std::milli> exec_time = end - start;
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";
        } else if (command == "INSERT") {// αν η εντολή είναι  INSERT τότε διαβάζουμε το όνομα της δομής δεδομένων και την τιμή που θα εισαχθει
            string structure;
            
            iss >> structure ;
            
            auto start = high_resolution_clock::now();
            
            if (structure == "AVLTREE") {
                int value;
                iss>>value;
                avltree.insert(value);
            } else if (structure == "MINHEAP") {
                int value;
                iss>>value;
                minheap.insert(value);
            } else if (structure == "HASHTABLE") {
                int value;
                iss>>value;
                hashtable.insert(value);
            }else if(structure=="MAXHEAP"){
                int value;
                iss>>value;
                maxheap.insert(value);
            }else if(structure=="GRAPH"){
                int node1,node2,weight;
                iss>>node1>>node2>>weight;
                graph.insertEdge(node1,node2,weight);  
            }
            auto end = high_resolution_clock::now();
            duration<double, std::milli> exec_time = end - start;
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";
            outputFile<<"\n";

        } else if (command == "SEARCH") {// αν η εντολή είναι SEARCH τότε διαβάζουμε το όνομα της δομής δεδομένων και την τιμή που θα αναζητήσουμε
            string structure;
            int value;
            iss >> structure >> value;

            auto start = high_resolution_clock::now();
            bool result = false;

            if (structure == "AVLTREE") {
                result = avltree.search(value);
            } else if (structure == "HASHTABLE") {
                result = hashtable.search(value);
            }
            

            auto end = high_resolution_clock::now();
          
            duration<double, std::milli> exec_time = end - start;// υπολογισμός του χρόνου εκτέλεσης της εντολής
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";// γραφή της εντολής ,του αποτελέσματος και του χρόνου εκτέλεσης στο αρχείο output.txt
            outputFile << "ΑΠΟΤΕΛΕΣΜΑ: " << (result ? "SUCCESS" : "FAILURE") << "\n";
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";

        } else if (command == "DELETE") {// αν η εντολή είναι DELETE τότε διαβάζουμε το όνομα της δομήσ δεδομένων και την τιμή που θα διαγραφεί
            string structure;
            
            iss >> structure;
            auto start = high_resolution_clock::now();
            if (structure == "AVLTREE") {
                int value;
                iss>>value;
                avltree.deleteKey(value);
            }else if(structure == "GRAPH") {
                int node1,node2;
                iss>>node1>>node2;
                graph.deleteEdge(node1,node2);
            }
            auto end = high_resolution_clock::now();
            duration<double, std::milli> exec_time = end - start;
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";

        } else if (command == "DELETEMIN") {// αν η εντολή είναι DELETEMIN τότε διαβάζουμε το όνομα της δομής δεδομένων και διαγράφουμε το ελάχιστο 
            string structure;
            iss >> structure;
            if (structure == "MINHEAP") {
                minheap.deleteMin();
            }

        } else if (command == "FINDMIN") {// αν η εντολή είναι FINDMIN τότε διαβάζουμε το όνομα της δομής δεδομένων και βρίσκουμε το ελάχιστο
            string structure;
            iss >> structure;

            auto start = high_resolution_clock::now();
            int result = -1;

            if (structure == "AVLTREE") {
                if (avltree.getSize()>0) //αν το δέντρο δεν είναι άδειο τότε βρίσκουμε το ελάχιστο
                   result = avltree.findMin();
                else 
                   outputFile <<"TO AVLTREE ΕΙΝΑΙ ΑΔΕΙΟ ΚΑΙ ΔΕΝ ΒΡΕΘΗΚΕ ΕΛΑΧΙΣΤΟ\n";//αν το δέντρο είναι άδειο τότε γράφουμε στο αρχείο ότι το δέντρο είναι άδειο, δεν βρέθηκε ελάχιστο και το ΑΠΟΤΕΛΕΣΜΑ παίρνει την τιμή  -1
            } else if (structure == "MINHEAP") {
               if (minheap.getSize()>0)
                result = minheap.findMin();
               else 
                outputFile << "TO MINHEAP ΕΙΝΑΙ ΑΔΕΙΟ ΚΑΙ ΔΕΝ ΒΡΕΘΗΚΕ ΕΛΑΧΙΣΤΟ\n";
            }
            auto end = high_resolution_clock::now();
         
            duration<double, std::milli> exec_time = end - start;
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";
            outputFile << "ΑΠΟΤΕΛΕΣΜΑ: " << result << "\n";
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";

        } else if (command == "GETSIZE") {// αν η εντολή είναι GETSIZE τότε διαβάζουμε το όνομα τησ δομής δεδομένων και βρίσκουμε το μέγεθος της δομής δεδομένων
            string structure;
            iss >> structure;

            auto start = high_resolution_clock::now();
           
            int result=-1;//false
            if (structure == "AVLTREE") {
                result = avltree.getSize();
            } else if (structure == "MINHEAP") {
                result = minheap.getSize();
            } else if (structure == "HASHTABLE") {
                result = hashtable.getSize();
            }else if(structure=="MAXHEAP"){
                result=maxheap.getSize();
            }else if (structure=="GRAPH"){
                result=graph.getSize().first;
            }
                

            auto end = high_resolution_clock::now();
            duration<double, std::milli> exec_time = end - start;
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";
            outputFile << "ΑΠΟΤΕΛΕΣΜΑ: " << result << "\n";
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";
        
        }else if(command=="FINDMAX"){
            string structure;
            iss >> structure;

            auto start = high_resolution_clock::now();
            int result = -1;
            if (structure=="MAXHEAP")
            {
                if (maxheap.getSize()>0) //αν το maxheap δεν είναι άδειο τότε βρίσκουμε το μέγιστο
                       result=maxheap.top();
                    else 
                       outputFile <<"TO MAXHEAP ΕΙΝΑΙ ΑΔΕΙΟ ΚΑΙ ΔΕΝ ΒΡΕΘΗΚΕ ΜΕΓΙΣΤΟ\n";//αν το  maxheap είναι άδειο τότε γράφουμε στο αρχείο ότι το maxheap είναι άδειο, δεν βρέθηκε μέγιστο και το ΑΠΟΤΕΛΕΣΜΑ παίρνει την τιμή  -1
            }
            auto end = high_resolution_clock::now();
            duration<double, std::milli> exec_time = end - start;
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";
            outputFile << "ΑΠΟΤΕΛΕΣΜΑ: " << result << "\n";
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";
        }
        else if(command=="DELETEMAX"){
            string structure;
            iss >> structure;
            auto start = high_resolution_clock::now();
          
            if (structure == "MAXHEAP") {
                maxheap.deleteTop();
            }
            auto end = high_resolution_clock::now();
            duration<double, std::milli> exec_time = end - start;
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";
           
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";
            
        }
        else if(command=="COMPUTESHORTESTPATH"){
            string structure;
            iss>>structure;
            auto start=high_resolution_clock::now();
            int result=-1;//false
            if (structure=="GRAPH"){
                int node1,node2;
                iss>>node1>>node2;
                result=graph.computeShortestPath(node1,node2);
            }
            auto end = high_resolution_clock::now();
            duration<double, std::milli> exec_time = end - start;
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";
            outputFile << "ΑΠΟΤΕΛΕΣΜΑ: " << result << "\n";
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";

        }else if(command=="COMPUTESPANNINGTREE"){
            string structure;
            iss>>structure;
            auto start=high_resolution_clock::now();
            int result=-1;//false
            if (structure=="GRAPH"){
               
                result=graph.computeSpanningTreeCost();
            }
            auto end = high_resolution_clock::now();
            duration<double, std::milli> exec_time = end - start;
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";
            outputFile << "ΑΠΟΤΕΛΕΣΜΑ: " << result << "\n";
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";

            
        }else if(command=="FINDCONNECTEDCOMPONENTS")
        {
            string structure;
            iss>>structure;
            auto start=high_resolution_clock::now();
            int result=-1;
            if (structure=="GRAPH"){
                result=graph.findConnectedComponents();
            }
            auto end = high_resolution_clock::now();
            duration<double, std::milli> exec_time = end - start;
            outputFile << "ΕΝΤΟΛΗ: " << line << "\n";
            outputFile << "ΑΠΟΤΕΛΕΣΜΑ: " << result << "\n";
            outputFile << "ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ: " << exec_time.count() << " msec\n\n";
        }
    }

    commandFile.close();
    outputFile.close();
    return 0;
}
