#include "operationHelper.h"

void ShowAllOperations(fstream &operationsFile){
    operationsFile.open("operacje.txt", ios::in);
    if(operationsFile.is_open()){
        string line;
        while (getline(operationsFile, line))
        {
            cout<<line<<endl;
        }
        operationsFile.close();
        
    }
    
}