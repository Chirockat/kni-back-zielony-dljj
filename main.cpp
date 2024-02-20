#include<iostream>
#include<fstream>
#include<string>

#include"helpers/operationHelper.h"
#include"helpers/accountHelper.h"
// By wszystko dzialalo, podczas uruchamiania zalaczamy 2 pliki cpp zamiast 1, przykladowo:
// g++ helpers//operationHelper.cpp  main.cpp -o main .\main

using namespace std;



int main(){
    fstream operationsFile;
    fstream accountFile;
    ShowAllOperations(operationsFile);
    ShowAccount(accountFile);
    return 0;
}