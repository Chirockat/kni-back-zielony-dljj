#ifndef OPERATIONS_HELPER
#define OPERATIONS_HELPER

#include<iostream>
#include<fstream>
#include<string>
#include<ctime>

using namespace std;

void ShowAllOperations(fstream &operations_file);
void NewOperationEntry(fstream &operations_file, char operation_type, int amount, tm t);
tm CurrentDate();

#endif