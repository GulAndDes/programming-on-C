#include <iostream>
#include <fstream>
#include <cstring> // Для strlen и memcpy
using namespace std;

struct Computer {
    char brand[50];
    char model[50];
    char processor[50];
    char hd[50];
    char gpu[50];
};

int main() {
    ifstream inputFile("Textfile.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Input file not found." << endl;
        return 1;
    }

    Computer computers[10];

    for (int i = 0; i < 10; i++) {
        inputFile >> computers[i].brand >> computers[i].model >> computers[i].processor >> computers[i].hd >> computers[i].gpu;
    }

    ofstream outputFile("BinaryFile.bin", ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error: Output file not created." << endl;
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        if (strcmp(computers[i].processor, "-") == 0 || strcmp(computers[i].hd, "-") == 0 || strcmp(computers[i].gpu, "-") == 0) {
            Computer incompleteComputer;
            strcpy(incompleteComputer.brand, computers[i].brand);
            strcpy(incompleteComputer.model, computers[i].model);
            strcpy(incompleteComputer.processor, "");
            strcpy(incompleteComputer.hd, "");
            strcpy(incompleteComputer.gpu, "");
            outputFile.write(reinterpret_cast<char*>(&incompleteComputer), sizeof(Computer));
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}