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

map<int, pair<int, int>> monthlyExpenseSummary(const string& operations_file);


#endif
