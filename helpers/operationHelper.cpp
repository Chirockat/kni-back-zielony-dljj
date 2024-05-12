#include <unistd.h>

#include "operationHelper.h"

tm CurrentDate() {
    time_t tmNow = time(NULL);
    struct tm t = * localtime( & tmNow);
    return t;
}

void ShowAllOperations(fstream & operationsFile) {
    operationsFile.open("operation.txt", ios::in);
    cout << "SHOW ALL OPERATIONS:" << endl;
    if (operationsFile.is_open()) {
        string line;
        while (getline(operationsFile, line)) {
            cout << line << endl;
        }
        operationsFile.close();
    }
}

void NewOperationEntry(fstream & operationsFile, char operationType, int operationAmount, tm t) {
    operationsFile.open("operation.txt", ios::app);
    if (operationsFile.is_open()) {
        cout << "MAKING NEW OPERATION ENTRY" << endl;
        // first line - Date
        operationsFile << endl <<
            "-" << setw(2) << setfill('0') << t.tm_mday << "." << setw(2) << setfill('0') << t.tm_mon + 1 << "." << t.tm_year + 1900 << endl;
        // second line - Operation type
        switch (operationType) {
        case '+':
            operationsFile << "-addFunds" << endl;
            break;
        case '-':
            operationsFile << "-withdrawFunds" << endl;
            break;

        default:
            operationsFile << "ERROR - WRONG OPERATION TYPE" << endl;
            break;
        }
        // third line - operation amount
        operationsFile << "-" << operationAmount << endl;
        operationsFile.close();
    }
}

void FindOperations(fstream & operationsFile, string date) {
    operationsFile.open("operation.txt", ios::in);
    if (operationsFile.is_open()) {
        cout << "FINDING OPERATIONS FROM " << date << ":" << endl;
        string line;
        bool hasEntry = false;
        // adding '-' at the beginning of given date, so we can compare easier
        date.insert(0, 1, '-');
        while (getline(operationsFile, line)) {
            if (date.compare(line) == 0) {
                cout << line << endl;
                for (int i = 0; i <= 1; i++) {
                    getline(operationsFile, line);
                    cout << line << endl;
                }
                cout << endl;
                hasEntry = true;
            }
        }
        if (!hasEntry) {
            cout << "NO ENTRIES FOUND" << endl;
        }
        operationsFile.close();
    }
}
void resetOperations() {
    fstream operationsFile;
    operationsFile.open("operation.txt", ios::out);
    if (operationsFile.is_open()) {
        cout << "==========RESETING OPERATIONS=======" << endl;
        cout << "reseting";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            sleep(1);
        }
        cout << endl;
        operationsFile.close();
    }
}