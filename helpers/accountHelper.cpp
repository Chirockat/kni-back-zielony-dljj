#include <unistd.h>
#include <vector>

#include "operationHelper.h"
#include "accountHelper.h"
#include "..//controllers/monthlyExpenseSummary.h" // for date and dateParse

void ShowAccount(fstream & account_file) {
    account_file.open("account.txt", ios::in);
    cout << "SHOW ACCOUNT:" << endl;
    if (account_file.is_open()) {
        string line;
        while (getline(account_file, line)) {
            cout << line << endl;
        }
        account_file.close();
    }
}

void NewAccountEntry(fstream & account_file, int account_amount, tm t) {
    account_file.open("account.txt", ios::app);
    if (account_file.is_open()) {
        cout << "MAKING NEW ACCOUNT ENTRY" << endl;
        // first line - Date
        account_file << endl
                     << "-" << setw(2) << setfill('0') << t.tm_mday << "." << setw(2) << setfill('0') << t.tm_mon + 1 << "." << t.tm_year + 1900 << endl;
        // second line - account_amount
        account_file << "-" << account_amount << endl;

        account_file.close();
    }
}

void FindAccountBalance(fstream & account_file, string date) {
    account_file.open("account.txt", ios::in);
    if (account_file.is_open()) {
        cout << "FINDING ACCOUNT BALANCE FROM " << date << ":" << endl;
        string line;
        bool hasEntry = false;
        // adding '-' at the beginning of given date, so we can compare easier
        date.insert(0, 1, '-');
        while (getline(account_file, line)) {
            if (date.compare(line) == 0) {
                cout << line << endl;
                for (int i = 0; i <= 0; i++) {
                    getline(account_file, line);
                    cout << line << endl;
                }
                cout << endl;
                hasEntry = true;
            }
        }
        if (!hasEntry) {
            cout << "NO ENTRIES FOUND" << endl;
        }
        account_file.close();
    }
}

vector < accountStatusData > accoutStatusAtEndOfMonth() {
    vector < accountStatusData > accountData;
    fstream account_file;
    string line, saveLine = "";
    int month = 0;
    int year = 0;
    int tempMonth = 0;
    int tempYear = 0;
    Date operationDate;

    account_file.open("account.txt", ios::in);
    if (!account_file.is_open()) {
        cout << "Unable to open file" << endl;
        return accountData;
    }

    while (getline(account_file, line)) {
        saveLine = (line[0] == '-' && !(line[3] == '.' && line[6] == '.')) ? line : saveLine;

        if (line[3] != '.' || line[6] != '.') continue;

        operationDate = parseDate(line.substr(1));
        month = operationDate.month;
        year = operationDate.year;

        if ((month != tempMonth || year != tempYear) && (tempMonth != 0 || tempYear != 0)) {
            accountData.push_back({tempMonth, tempYear, stoi(saveLine.substr(1))
            });
        }

        tempMonth = month;
        tempYear = year;
    }

    try {
        accountData.push_back({tempMonth, tempYear, stoi(saveLine.substr(1))});
    } catch (const std::out_of_range & e) {
        // do nothing
    }

    account_file.close();

    return accountData;
}

void resetAccount() {
    fstream account_file;
    account_file.open("account.txt", ios::out);
    if (account_file.is_open()) {
        cout << "==========RESETING ACCOUNT==========" << endl;
        cout << "reseting";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            sleep(1);
        }
        cout << endl;
        account_file.close();
    }
}

// Debug reset function
// Resets account and operations files with random data
void debugReset(int startYears, int endYears, int startMonth, int endMonth, int startDay, int endDay, int startAmount) {
    resetAccount();
    resetOperations();

    fstream operations_file;
    fstream account_file;
    tm temp;
    temp.tm_mday = startDay;
    temp.tm_mon = startMonth - 1;
    temp.tm_year = (startYears - 1900);
    int temp_amount = startAmount;
    int account_amount = startAmount;
    bool switcher = true;

    NewOperationEntry(operations_file, '+', temp_amount, temp);
    NewAccountEntry(account_file, account_amount, temp);

    srand(time(0));
    while (
        !(
            (temp.tm_year > (endYears - 1900 - 1)) &&
            (((temp.tm_mon + 1) > endMonth) &&
                (temp.tm_mday > endDay)))
    ) {
        if (switcher) {
            temp_amount = rand() % 600 + 100;
            account_amount += temp_amount;
            NewOperationEntry(operations_file, '+', temp_amount, temp);
            switcher = false;
        } else {
            temp_amount = rand() % 300 + 100;
            account_amount -= temp_amount;
            NewOperationEntry(operations_file, '-', temp_amount, temp);
            switcher = true;
        }
        temp.tm_mday += rand() % 5 + 1;
        NewAccountEntry(account_file, account_amount, temp);

        if (temp.tm_mday > 29) {
            temp.tm_mday = rand() % 5 + 1;
            temp.tm_mon++;
        }
        if (temp.tm_mon > 11) {
            temp.tm_mon = 0;
            temp.tm_year++;
        }
    }
}
// Debug reset function overload
void debugReset() {
    // month 1-12, day 1-31
    // where 1 - January, 12 - December
    debugReset(2020, (CurrentDate().tm_year + 1900), 1, CurrentDate().tm_mon, 1, CurrentDate().tm_mday, 9999);
}