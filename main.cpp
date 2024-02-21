#include<iostream>
#include<fstream>
#include<string>

#include"helpers/operationHelper.h"
#include"helpers/accountHelper.h"
// To make everything work, we attach 3 cpp files instead of 1, for example:
// g++ helpers//operationHelper.cpp helpers//accountHelper.cpp  main.cpp -o main .\main

using namespace std;


int main(){
    fstream operations_file;
    fstream account_file;
    tm t = CurrentDate();
    NewOperationEntry(operations_file, '+', 1000, t);
    ShowAllOperations(operations_file);
    //ShowAccount(account_file);
    return 0;
}