#ifndef OPERATIONS_HELPER
#define OPERATIONS_HELPER

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

void ShowAllOperations(fstream &operationsFile);
void NewOperationEntry(fstream &operationsFile, char operationType, int operationAmount, tm t);
tm CurrentDate();
void FindOperations(fstream &operationsFile, string date);
void resetOperations();
#endif
