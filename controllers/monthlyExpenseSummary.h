#ifndef monthlyExpenseSummary_h
#define monthlyExpenseSummary_h

#include <string>
#include <map>
#include <vector>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

struct MonthlyExpenseData {
    int month;
    int year;
    int income;
    int expense;
};

vector<MonthlyExpenseData> monthlyExpenseSummary();
Date parseDate(const std::string& dateStr);


#endif
