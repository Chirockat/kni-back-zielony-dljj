#include "monthlyExpenseSummary.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <ctime>

Date parseDate(const std::string& dateStr) {
    Date date;
    std::stringstream ss(dateStr);
    char dot;
    ss >> date.day >> dot >> date.month >> dot >> date.year;
    return date;
}

tm currentDate(){
    time_t tmNow = time(NULL);
    struct tm t = *localtime(&tmNow);
    return t;
}

std::map<int, std::pair<int, int>> monthlyExpenseSummary() {
    // map<month, pair<income, expense>>
    std::map<int, std::pair<int, int>> summary;
    std::string line;
    int month = 0;
    int tempmonth = 0, tempYear = 0;


    std::fstream operations_file;
    operations_file.open("operation.txt", ios::in);
    if(!operations_file.is_open()){
        std::cout << "Unable to open file" << std::endl;
        return summary;
    }
    
    // checks the last 6 months
    tempYear = currentDate().tm_year + 1900;
    tempmonth = currentDate().tm_mon - 6;
    if (tempmonth < 0) {
        tempmonth += 12;
        tempYear -= 1;
    }

    while (std::getline(operations_file, line)) {
        // skips the line if it doesn't contain a date, -00.00.0000 format
        if (line[3] == '.' && line[6] == '.'){
            Date operationDate = parseDate(line.substr(1));
            
            // TODO: to be tested with older operation.txt data
            // checks the last 6 months if older it skips
            if(operationDate.year < tempYear || (operationDate.year == tempYear && operationDate.month < tempmonth)){
                continue;
            }

            // Main logic relays on this format of the file
            // -dd.mm.yyyy
            // -operationType
            // -amount
            month = operationDate.month;
            if (std::getline(operations_file, line) && line[0] == '-') {
                if (line == "-addFunds") {
                    std::getline(operations_file, line);
                    int amount = std::stoi(line.substr(1));
                    summary[month].first += amount;
                } else if (line == "-withdrawFunds") {
                    std::getline(operations_file, line);
                    int amount = std::stoi(line.substr(1));
                    summary[month].second += amount;
                }
            }
        }
    }

    operations_file.close();
    
    return summary;
}
