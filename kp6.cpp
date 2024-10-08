#include <iostream> 
#include <fstream> 
using namespace std;

struct Computer { 
    string brand; 
    string model; 
    string processor; 
    string hd; 
    string gpu; 
}; 
 
int main() { 
    ifstream file("TextFile.txt"); 
    if (!file.is_open()) { 
        cerr << "Error: File not found." << endl; 
        return 1; 
    } 
 
    Computer computers[10]; 
 
    for (int i = 0; i < 10; i++) { 
        file >> computers[i].brand >> computers[i].model >> computers[i].processor >> computers[i].hd >> computers[i].gpu; 
    } 
 
    for (int i = 0; i < 10; i++) { 
        if (computers[i].processor == "-" || computers[i].hd == "-" || computers[i].gpu == "-") {  
            cout << "Incomplete Computer: " << computers[i].brand << " " << computers[i].model << endl; 
        } 
    } 
 
    file.close(); 
 
    return 0; 
}
