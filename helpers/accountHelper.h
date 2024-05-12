#ifndef ACCOUNT_HELPER
#define ACCOUNT_HELPER

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

struct AccountStatusData {
    int month;
    int year;
    int account_balance;
};

void ShowAccount(fstream &accountFile);
void NewAccountEntry(fstream &accountFile, int accountAmount, tm t);
void FindAccountBalance(fstream &accountFile, string date);
void resetAccount();
void debugReset(int startYears, int endYears, int startMonth, int endMonth, int startDay, int endDay, int startAmount);
void debugReset();
vector<AccountStatusData> accoutStatusAtEndOfMonth();
#endif
