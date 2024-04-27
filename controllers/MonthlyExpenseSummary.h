#ifndef monthlyExpenseSummary_h
#define monthlyExpenseSummary_h

#include <string>
#include <map>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

map<int, pair<int, int>> monthlyExpenseSummary();
Date parseDate(const std::string& dateStr);


#endif
