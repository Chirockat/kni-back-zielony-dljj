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

void NewAccountEntry(fstream &account_file, int account_amount, tm t){
    account_file.open("account.txt", ios::app);
    if(account_file.is_open()){
        cout << "MAKING NEW ACCOUNT ENTRY"<<endl;
        // first line - Date
        account_file <<endl<<"-"<<t.tm_mday<<"."<<t.tm_mon+1<<"."<<t.tm_year+1900<<endl;
       
        //third line - account_amount
        account_file <<"-"<<account_amount<<endl;

        account_file.close();
    }

    
}


void FindAccountBalance(fstream &account_file, string date){
    account_file.open("account.txt", ios::in);
    if(account_file.is_open()){
        cout <<"FINDING ACCOUNT BALANCE FROM "<<date<<":"<<endl;
        string line;
        int counter=0;

        // adding '-' at the beginning of given date, so we can compare easier
        date.insert (0, 1, '-');

        while (getline(account_file, line)){
            if(date.compare(line)==0){
                cout<<line<<endl;
                for(int i=0;i<=0;i++){
                    getline(account_file, line);
                    cout<<line<<endl;
                }
                cout<<endl;
                counter++;

            }
        }
        if(counter==0){
            cout<<"NO ENTRIES FOUND"<<endl;
        }
        account_file.close();
    }
}
