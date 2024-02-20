#include "operationHelper.h"

void ShowAllOperations(fstream &operationsFile){
    operationsFile.open("operation.txt", ios::in);
    cout << "SHOW ALL OPERATIONS:"<<endl;
    if(operationsFile.is_open()){
        string line;
        while (getline(operationsFile, line))
        {
            cout<<line<<endl;
        }
        operationsFile.close();
        
    }
    
}