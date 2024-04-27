#include "timeSlotOperations.h"
#include "monthlyExpenseSummary.h" // for parseDate and Date struct

#include <iostream>
#include <fstream>
#include <sstream>


std::vector<std::string> getOperationsInRange(const std::string& startDateStr, const std::string& endDateStr) {
    std::vector<std::string> operations;

    Date startDate = parseDate(startDateStr);
    Date endDate = parseDate(endDateStr);
    std::ifstream operationsFile("operation.txt");
    std::string line;
    if (operationsFile.is_open()) {
        bool isInRange = false;
        // reads the file line by line
        // if the line starts with a date, it checks if the date is in the range
        // if it is, it starts to add the operations to the vector
        // if the date is out of the range, it stops reading the file
        // date in file must be sorted from oldest date at start of file to newest date at end of file
        while (std::getline(operationsFile, line)) {
            // skips the line if it doesn't contain a date, -00.00.0000 format
            if (line[3] == '.' && line[6] == '.'){
                    Date operationDate = parseDate(line.substr(1));
                    if  (operationDate.year > startDate.year || 
                        (operationDate.year == startDate.year && operationDate.month > startDate.month) ||
                        (operationDate.year == startDate.year && operationDate.month == startDate.month && operationDate.day >= startDate.day)) {
                            isInRange = true;
                }
                    if  (operationDate.year > endDate.year || 
                        (operationDate.year == endDate.year && operationDate.month > endDate.month) ||
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
