#ifndef ACCOUNT_HELPER
#define ACCOUNT_HELPER

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

void ShowAccount(fstream &account_file);
void NewAccountEntry(fstream &account_file, int account_amount, tm t);
void FindAccountBalance(fstream &account_file, string date);

#endif
