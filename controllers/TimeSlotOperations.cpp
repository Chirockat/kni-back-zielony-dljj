#include "timeSlotOperations.h"


#include <iostream>
#include <fstream>
#include <sstream>


Date parseDate(const std::string& dateStr) {
    Date date;
    std::stringstream ss(dateStr);
    char dot;
    ss >> date.day >> dot >> date.month >> dot >> date.year;
    return date;
}

std::vector<std::string> getOperationsInRange(const std::string& startDateStr, const std::string& endDateStr) {
    std::vector<std::string> operations;

    Date startDate = parseDate(startDateStr);
    Date endDate = parseDate(endDateStr);

    std::ifstream operationsFile("operation.txt");
    if (operationsFile.is_open()) {
        std::string line;
        bool isInRange = false;
        while (std::getline(operationsFile, line)) {
            if (line[0] == '-') {
//Checking if a line contains a date and Parsing the date from a line to check if the operation date is in range
                Date operationDate = parseDate(line.substr(1));
                if (operationDate.year > startDate.year || (operationDate.year == startDate.year && operationDate.month > startDate.month) ||
                    (operationDate.year == startDate.year && operationDate.month == startDate.month && operationDate.day >= startDate.day)) {
                    isInRange = true;
                }
                if (operationDate.year > endDate.year || (operationDate.year == endDate.year && operationDate.month > endDate.month) ||
                    (operationDate.year == endDate.year && operationDate.month == endDate.month && operationDate.day > endDate.day)) {
                    break;
                }
            }
            if (isInRange) {
                operations.push_back(line);
            }
        }
        operationsFile.close();
    } else {
        std::cout << "Unable to open operation.txt" << std::endl;
    }

    return operations;
}
