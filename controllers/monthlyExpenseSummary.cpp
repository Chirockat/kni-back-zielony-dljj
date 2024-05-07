#include "monthlyExpenseSummary.h"
#include "..//helpers/operationHelper.h" // for CurremtDate

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <map>
#include <vector>

Date parseDate(const string& dateStr) {
    Date date;
    stringstream ss(dateStr);
    char dot;
    ss >> date.day >> dot >> date.month >> dot >> date.year;
    return date;
}

vector<monthlyExpenseData> monthlyExpenseSummary() {
    // variables
    vector<monthlyExpenseData> summary;
    monthlyExpenseData data;
    // set for first time because of "+=" operation
    data.month = 0;
    data.year = 0;
    data.income = 0;
    data.expense = 0;
    Date operationDate;
    operationDate.day = 0;
    operationDate.month = 0;
    operationDate.year = 0;

    string line;
    int month = 0;
    int bountryMonth = 0, bountryYear = 0;
    
    

    fstream operations_file;
    operations_file.open("operation.txt", ios::in);
    if(!operations_file.is_open()){
        cout << "Unable to open file" << endl;
        return summary;
    }
    
    // checks the last 6 months
    bountryYear = CurrentDate().tm_year + 1900;
    bountryMonth = CurrentDate().tm_mon - 5; // 6 past months not counting current month should be showing 7 in total
    if (bountryMonth <= 0) {
        bountryMonth += 12;
        bountryYear -= 1;
    }
    // set for first time
    month = bountryMonth;

    // Main logic
    while (getline(operations_file, line)) {
        // skips the line if it doesn't contain a date, -00.00.0000 format
        if (line[3] == '.' && line[6] == '.'){
            operationDate = parseDate(line.substr(1));
            
            // checks the last 6 months if older it skips
            if(operationDate.year < bountryYear || (operationDate.year == bountryYear && operationDate.month < bountryMonth)){
                continue;
            }
            // check if month changed
            if (operationDate.month != month){
                if (month != 0){
                    data.month = month;
                    if(month == 12){
                        data.year = operationDate.year - 1;
                    } else {
                        data.year = operationDate.year;
                    }
                    summary.push_back(data);
                }
                data.income = 0;
                data.expense = 0;
            }


            // Relays on this format of the file
            // -dd.mm.yyyy
            // -operationType
            // -amount
            month = operationDate.month;
            if (getline(operations_file, line) && line[0] == '-') {
                if (line == "-addFunds") {
                    getline(operations_file, line);
                    data.income += stoi(line.substr(1));
                } else if (line == "-withdrawFunds") {
                    getline(operations_file, line);
                    data.expense += stoi(line.substr(1));
                }
            }
        }
    }
    // push last month
    data.month = operationDate.month;
    data.year = operationDate.year;
    summary.push_back(data);
    operations_file.close();

    // catches no data cases
    if(summary[0].year == 0){
        return {};
    }
    return summary;
}
