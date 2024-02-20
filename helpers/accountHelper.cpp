#include "operationHelper.h"

void ShowAccount(fstream &AccountFile){
    AccountFile.open("account.txt", ios::in);
    cout << "SHOW ACCOUNT:"<<endl;
    if(AccountFile.is_open()){
        string line;
        while (getline(AccountFile, line))
        {
            cout<<line<<endl;
        }
        AccountFile.close();
        
    }
    
}