#ifndef ACCOUNT_HELPER
#define ACCOUNT_HELPER

#include<iostream>
#include<fstream>
#include<string>
#include<ctime>

using namespace std;

void ShowAccount(fstream &account_file);
void NewAccountEntry(fstream &account_file, int account_amount, tm t);
tm CurrentDate();
void FindAccountBalance(fstream &account_file, string date);

#endif
