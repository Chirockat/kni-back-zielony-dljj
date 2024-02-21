#include "operationHelper.h"

void ShowAccount(fstream &account_file){
    account_file.open("account.txt", ios::in);
    cout << "SHOW ACCOUNT:"<<endl;
    if(account_file.is_open()){
        string line;
        while (getline(account_file, line))
        {
            cout<<line<<endl;
        }
        account_file.close();
        
    }
    
}