#include <iostream>
#include <fstream>
#include <string>

#include "helpers/operationHelper.h"
#include "helpers/accountHelper.h"
#include "controllers/MonthlyExpenseSummary.h"
#include "controllers/TimeSlotOperations.h"
// To make everything work, we attach 3 cpp files instead of 1, for example:
// g++ helpers//operationHelper.cpp helpers//accountHelper.cpp  main.cpp -o main .\main

using namespace std;

int main()
{
    fstream operations_file;
    fstream account_file;
    tm t = CurrentDate();
    NewOperationEntry(operations_file, '-', 500, t);
    ShowAllOperations(operations_file);
    FindOperations(operations_file, "18.02.2024");

    NewAccountEntry(account_file, 100, t);
    ShowAccount(account_file);
    FindAccountBalance(account_file, "18.02.2024");

    string startDate,endDate;
    cout << "ENTER THE BEGINNING OF THE TIME PERIOD (dd.mm.rrrr): ";
    cin >> startDate;
    cout << "ENTER THE FINISH OF THE TIME PERIOD (dd.mm.rrrr): ";
    cin >> endDate;

    vector<std::string> operations = getOperationsInRange(startDate, endDate);
    for (const string& operation : operations) {
        cout << operation << endl;
    }

    return 0;
}
