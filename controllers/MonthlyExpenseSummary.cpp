#include "MonthlyExpenseSummary.h"
#include "operationHelper.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>

struct Date {
    int day;
    int month;
    int year;
};

Date parseDate(const std::string& dateStr) {
    Date date;
    std::stringstream ss(dateStr);
    char dot;
    ss >> date.day >> dot >> date.month >> dot >> date.year;
    return date;
}

std::map<int, std::pair<int, int>> monthlyExpenseSummary(const std::string& operations_file) {
    std::map<int, std::pair<int, int>> summary;

    //Open file
    std::ifstream operationsFile(operation.txt);
    if (operationsFile.is_open()) {
        std::string line;
        int currentMonth = 0;
        int addedFunds = 0;
        int withdrawnFunds = 0;
        while (std::getline(operationsFile, line)) {
            if (line[0] == '-')
                {
                Date operationDate = parseDate(line.substr(1));

                if (operationDate.year == 2024) {
                    if (operationDate.month != currentMonth) {
                        if (currentMonth != 0) {
                            summary[currentMonth] = std::make_pair(addedFunds, withdrawnFunds);
                        }
                        //NEXT MONTH
                        currentMonth = operationDate.month;
                        addedFunds = 0;
                        withdrawnFunds = 0;
                    }
                }
            } else {
                int amount = std::stoi(line.substr(1));
                if (line.find("addFunds") != std::string::npos) {
                    addedFunds += amount;
                } else if (line.find("withdrawFunds") != std::string::npos) {
                    withdrawnFunds += amount;
                }
            }
        }
        summary[currentMonth] = std::make_pair(addedFunds, withdrawnFunds);
        operationsFile.close();
    } else {
        std::cerr << "Unable to open " << operations_file << std::endl;
    }

    return summary;
}
