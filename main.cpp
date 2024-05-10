#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "helpers/operationHelper.h"
#include "helpers/accountHelper.h"
#include "controllers/monthlyExpenseSummary.h"
#include "controllers/timeSlotOperations.h"
 // To make everything work, we attach 5 cpp files instead of 1, for example:
// g++ helpers/operationHelper.cpp helpers/accountHelper.cpp controllers/monthlyExpenseSummary.cpp controllers/timeSlotOperations.cpp main.cpp -o main

using namespace std;

int main(int argc, char * argv[]) {
   if (argc > 1 && string(argv[1]) == "debug") {
       debugReset();
   }
   if (argc > 1 && string(argv[1]) == "reset") {
       resetOperations();
       resetAccount();
   }

   // Account status example
   cout << "ACCOUNT STATUS AT THE END OF EACH MONTH:" << endl;
   if (accoutStatusAtEndOfMonth().empty()) {
       cout << "No data available" << endl;
   } else {
       for (auto item: accoutStatusAtEndOfMonth()) {
           cout << "Year: " << item.year << " Month: " << item.month << " Account balance: " << item.account_balance << endl;
       }
   }
   cout << "=============================" << endl;

   // Monthly expense summary example
   cout << "MONTHLY EXPENSE SUMMARY:" << endl;
   if (monthlyExpenseSummary().empty()) {
       cout << "No data available" << endl;
   } else {
       for (auto item: monthlyExpenseSummary()) {
           cout << "Year: " << item.year << " Month: " << item.month << " Income: " << item.income << " Expense: " << item.expense << endl;
       }
   }
   cout << "=============================" << endl;
   return 0;
}

/* Account and Operations examples
   fstream operations_file;
   fstream account_file;

   tm t = CurrentDate();
   NewOperationEntry(operations_file, '-', 500, t);
   ShowAllOperations(operations_file);
   FindOperations(operations_file, "18.02.2024");

   NewAccountEntry(account_file, 100, t);
   ShowAccount(account_file);
   FindAccountBalance(account_file, "18.02.2024");
*/

/* Time slot operations example
   string startDate,endDate;
   cout << "ENTER THE BEGINNING OF THE TIME PERIOD (dd.mm.rrrr): ";
   cin >> startDate;
   cout << "ENTER THE FINISH OF THE TIME PERIOD (dd.mm.rrrr): ";
   cin >> endDate;
   vector<std::string> operations = getOperationsInRange(startDate, endDate);
   cout << "OPERATIONS IN RANGE:" << " " << startDate << " - " << endDate << endl;
   for (const string& operation : operations) {
      cout << operation << endl;
   }
*/