#include <unistd.h>
#include <vector>

#include "operationHelper.h"
#include "accountHelper.h"
#include "..//controllers/monthlyExpenseSummary.h" // for date and dateParse

void ShowAccount(fstream &account_file)
{
    account_file.open("account.txt", ios::in);
    cout << "SHOW ACCOUNT:" << endl;
    if (account_file.is_open())
    {
        string line;
        while (getline(account_file, line))
        {
            cout << line << endl;
        }
        account_file.close();
    }
}

void NewAccountEntry(fstream &account_file, int account_amount, tm t)
{
    account_file.open("account.txt", ios::app);
    if (account_file.is_open())
    {
        cout << "MAKING NEW ACCOUNT ENTRY" << endl;
        // first line - Date
        account_file << endl
                     << "-" << setw(2) << setfill('0') << t.tm_mday << "." << setw(2) << setfill('0') << t.tm_mon + 1 << "." << t.tm_year + 1900 << endl;
        // second line - account_amount
        account_file << "-" << account_amount << endl;

        account_file.close();
    }
}

void FindAccountBalance(fstream &account_file, string date)
{
    account_file.open("account.txt", ios::in);
    if (account_file.is_open())
    {
        cout << "FINDING ACCOUNT BALANCE FROM " << date << ":" << endl;
        string line;
        bool hasEntry = false;
        // adding '-' at the beginning of given date, so we can compare easier
        date.insert(0, 1, '-');
        while (getline(account_file, line))
        {
            if (date.compare(line) == 0)
            {
                cout << line << endl;
                for (int i = 0; i <= 0; i++)
                {
                    getline(account_file, line);
                    cout << line << endl;
                }
                cout << endl;
                hasEntry = true;
            }
        }
        if (!hasEntry)
        {
            cout << "NO ENTRIES FOUND" << endl;
        }
        account_file.close();
    }
}
vector<accountStatusData> accoutStatusAtEndOfMonth()
{
    // Variables
    vector<accountStatusData> accountData;
    fstream account_file;
    string line, saveLine = "";
    int month = 0, year = 0;
    int tempMonth = 0, tempYear = 0;
    Date operationDate;
    
    account_file.open("account.txt", ios::in);
    if (!account_file.is_open())
    {
        cout << "Unable to open file" << endl;
        return accountData;
    }

    // Main logic
    while (getline(account_file, line)) {
        // skips the line if it doesn't contain a date, -00.00.0000 format
        if (line[3] == '.' && line[6] == '.'){
            operationDate = parseDate(line.substr(1));
            month = operationDate.month;
            year = operationDate.year;
            // set for first time
            if(tempMonth == 0 && tempYear == 0){
                tempMonth = month;
                tempYear = year;
            }
            // check if month or year changed
            if (month != tempMonth || year != tempYear){
                getline(account_file, line);
                accountData.push_back({tempMonth, tempYear, stoi(saveLine.substr(1))}); // push data here
                tempMonth = month;
                tempYear = year;
            }
        }
        // save last line with accout balance
        if(line[0] == '-'){
            saveLine = line;
        }
    }
    // last month, catch empty line
    try{
        accountData.push_back({tempMonth, tempYear, stoi(saveLine.substr(1))});// push data here
    }
    catch(const std::out_of_range& e){
        // do nothing
    }
    
    account_file.close();

    return accountData;
}

void resetAccount()
{
    fstream account_file;
    account_file.open("account.txt", ios::out);
    if (account_file.is_open()){
        cout << "==========RESETING ACCOUNT==========" << endl;
        sleep(3);
        account_file.close();}
}

// Debug reset function
// Resets account and operations files with random data
void debugReset(int startYears, int endYears, int startMonth, int endMonth, int startDay, int endDay, int startAmount)
{
    // Reset files
    resetAccount();
    resetOperations();

    // Variables
    fstream operations_file;
    fstream account_file;
    tm temp;
    temp.tm_mday = startDay;
    temp.tm_mon = startMonth - 1;
    temp.tm_year = (startYears-1900);
    int temp_amount = startAmount;
    int account_amount = startAmount;
    bool switcher = true;

    // Initial data
    NewOperationEntry(operations_file, '+', temp_amount, temp);
    NewAccountEntry(account_file, account_amount, temp);

    //Main Logic for generating random data
    srand(time(0));
    while(//stop when the date is bigger than today
    !(
        (temp.tm_year > (endYears - 1900 - 1)) 
        && 
        (((temp.tm_mon+1) > endMonth) 
        && 
        (temp.tm_mday > endDay)))
    ){
        if(switcher){
            temp_amount = rand() % 600 + 100;
            account_amount += temp_amount;
            NewOperationEntry(operations_file, '+', temp_amount, temp);
            NewAccountEntry(account_file, account_amount, temp);
            temp.tm_mday += rand() % 5 + 1;
            switcher = false;
        } else {
            temp_amount = rand() % 300 + 100;
            account_amount -= temp_amount;
            NewOperationEntry(operations_file, '-', temp_amount, temp);
            NewAccountEntry(account_file, account_amount, temp);
            temp.tm_mday += rand() % 5 + 1;
            switcher = true;
        }

        // Change month and year if needed
        if(temp.tm_mday > 29){
            temp.tm_mday = rand() % 5 + 1;
            temp.tm_mon++;
        }
        if(temp.tm_mon > 11){
            temp.tm_mon = 0;
            temp.tm_year++;
        }
    }
}
// Debug reset function overload
void debugReset()
{
    // month 1-12, day 1-31
    // where 1 - January, 12 - December
    debugReset(2020, (CurrentDate().tm_year + 1900), 1, CurrentDate().tm_mon, 1, CurrentDate().tm_mday, 9999);
}