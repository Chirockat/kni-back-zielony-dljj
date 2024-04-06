#ifndef TimeSlotOperations_h
#define TimeSlotOperations_h

#include <string>
#include <vector>

struct Date {
    int day;
    int month;
    int year;
};

std::vector<std::string> getOperationsInRange(const std::string& startDateStr, const std::string& endDateStr);

#endif // TimeSlotOperations_h
