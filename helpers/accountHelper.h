#ifndef ACCOUNT_HELPER
#define ACCOUNT_HELPER

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

struct accountStatusData
{
    int month;
    int year;
    int account_balance;
};

void ShowAccount(fstream &account_file);
void NewAccountEntry(fstream &account_file, int account_amount, tm t);
void FindAccountBalance(fstream &account_file, string date);
void resetAccount();
void debugReset(int startYears, int endYears, int startMonth, int endMonth, int startDay, int endDay, int startAmount);
void debugReset();
vector<accountStatusData> accoutStatusAtEndOfMonth();
#endif
