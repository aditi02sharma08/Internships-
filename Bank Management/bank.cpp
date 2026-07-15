#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdio>
using namespace std;

class BankAccount
{
private:
    int accountNumber;
    string customerName;
    double balance;

public:
    void createAccount()
    {
        cout << "\nEnter Account Number: ";

        while (!(cin >> accountNumber))
        {
            cout << "Invalid Account Number! Enter again: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Customer Name: ";
        getline(cin, customerName);

        cout << "Enter Initial Balance: ";

        while (!(cin >> balance))
        {
            cout << "Invalid Balance! Enter again: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        ofstream file("bank.txt", ios::app);

        if (file.is_open())
        {
            file << accountNumber << "|" << customerName << "|" << balance << endl;
            
            file.close();

            cout << "\nAccount Created Successfully!\n";
        }
        else
        {
            cout << "\nError opening file!\n";
        }
    }

    void deposit()
    {
        int accNo;
        double amount;
        bool found = false;

        cout << "\nEnter Account Number: ";

        while (!(cin >> accNo))
        {
            cout << "Invalid Account Number! Enter again: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter Deposit Amount: ";

        while (!(cin >> amount))
        {
            cout << "Invalid Amount! Enter again: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        ifstream file("bank.txt");

        if (!file.is_open())
        {
            cout << "\nBank file not found!\n";
            return;
        }

        ofstream tempFile("temp.txt");

        while (file >> accountNumber)
        {
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            getline(file, customerName);

            file >> balance;

            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (accountNumber == accNo)
            {
                balance = balance + amount;
                found = true;
            }

            tempFile << accountNumber << '\n';
            tempFile << customerName << '\n';
            tempFile << balance << '\n';
        }

        file.close();
        tempFile.close();

        remove("bank.txt");
        rename("temp.txt", "bank.txt");

        if (found)
        {
            cout << "\nAmount Deposited Successfully!\n";
        }
        else
        {
            cout << "\nAccount Not Found!\n";
        }
    }

    void withdraw()
    {
        int accNo;
        double amount;
        bool found = false;
        bool success = false;

        cout << "\nEnter Account Number: ";

        while (!(cin >> accNo))
        {
            cout << "Invalid Account Number! Enter again: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter Withdrawal Amount: ";

        while (!(cin >> amount))
        {
            cout << "Invalid Amount! Enter again: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        ifstream file("bank.txt");

        if (!file.is_open())
        {
            cout << "\nBank file not found!\n";
            return;
        }

        ofstream tempFile("temp.txt");

        while (file >> accountNumber)
        {
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            getline(file, customerName);

            file >> balance;

            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (accountNumber == accNo)
            {
                found = true;

                if (amount <= balance)
                {
                    balance = balance - amount;
                    success = true;
                }
            }

            tempFile << accountNumber << '\n';
            tempFile << customerName << '\n';
            tempFile << balance << '\n';
        }

        file.close();
        tempFile.close();

        remove("bank.txt");
        rename("temp.txt", "bank.txt");

        if (!found)
        {
            cout << "\nAccount Not Found!\n";
        }
        else if (success)
        {
            cout << "\nAmount Withdrawn Successfully!\n";
        }
        else
        {
            cout << "\nInsufficient Balance!\n";
        }
    }

    void checkBalance()
    {
        int accNo;
        bool found = false;

        cout << "\nEnter Account Number: ";

        while (!(cin >> accNo))
        {
            cout << "Invalid Account Number! Enter again: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        ifstream file("bank.txt");

        if (!file.is_open())
        {
            cout << "\nBank file not found!\n";
            return;
        }

        while (file >> accountNumber)
        {
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            getline(file, customerName);

            file >> balance;

            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (accountNumber == accNo)
            {
                cout << "\nAccount Number : " << accountNumber;
                cout << "\nCustomer Name  : " << customerName;
                cout << "\nCurrent Balance: Rs. " << balance << endl;

                found = true;
                break;
            }
        }

        file.close();

        if (!found)
        {
            cout << "\nAccount Not Found!\n";
        }
    }
};

int main()
{
    BankAccount account;
    int choice;

    do
    {
        cout << "\n================================";
        cout << "\n   BANK MANAGEMENT APPLICATION";
        cout << "\n================================";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Exit";
        cout << "\n================================";

        cout << "\nEnter Your Choice: ";

        if (!(cin >> choice))
        {
            cout << "\nInvalid Input! Please enter a number from 1 to 5.\n";

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        switch (choice)
        {
        case 1:
            account.createAccount();
            break;

        case 2:
            account.deposit();
            break;

        case 3:
            account.withdraw();
            break;

        case 4:
            account.checkBalance();
            break;

        case 5:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice! Please enter 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}
