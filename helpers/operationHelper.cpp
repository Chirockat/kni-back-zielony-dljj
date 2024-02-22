#include "operationHelper.h"

void ShowAllOperations(fstream &operations_file){
    operations_file.open("operation.txt", ios::in);
    cout << "SHOW ALL OPERATIONS:"<<endl;
    if(operations_file.is_open()){
        string line;
        while (getline(operations_file, line)){
            cout<<line<<endl;
        }
        operations_file.close();
        
    }
    
}
tm CurrentDate(){
    time_t tmNow;
    tmNow = time(NULL);
    struct tm t = *localtime(&tmNow);
    //cout<<"Current Date: "<<t.tm_mday<<"-"<<t.tm_mon+1<<"-"<<t.tm_year+1900;
    cout<<endl;
    return t;
}

void NewOperationEntry(fstream &operations_file, char operation_type, int amount, tm t){
    operations_file.open("operation.txt", ios::app);
    cout << "MAKING NEW ENTRY"<<endl;
    if(operations_file.is_open()){
        // first line - Date
        operations_file <<endl<<"-"<<t.tm_mday<<"."<<t.tm_mon+1<<"."<<t.tm_year+1900<<endl;
        // second line - Operation type
        switch (operation_type){
            case '+':{
                operations_file<<"-addFunds"<<endl;
                break;
            }
            case '-':{
                operations_file<<"-withdrawFunds"<<endl;
                break;
            }
        
            default:{
                operations_file<<"ERROR - WRONG OPERATION TYPE"<<endl;
                break;
            }
        }
        //third line - Amount
        operations_file <<"-"<<amount<<endl;

        operations_file.close();
    }

    
}

void FindOperations(fstream &operations_file, string date){
    operations_file.open("operation.txt", ios::in);
    if(operations_file.is_open()){
        string line;
        int counter=0;

        // adding '-' at the beginning of given date, so we can compare easier
        date.insert (0, 1, '-');

        while (getline(operations_file, line)){
            if(date.compare(line)==0){
                cout<<line<<endl;
                for(int i=0;i<=1;i++){
                    getline(operations_file, line);
                    cout<<line<<endl;
                }
                cout<<endl;
                counter++;

            }
        }
        if(counter==0){
            cout<<"NO ENTRIES FOUND"<<endl;
        }
        operations_file.close();
    }
    
    
}

