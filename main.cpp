#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include "classes.h"
#define ADMINS 3

void loadLoginData(vector<User> &users)
{
    ifstream file;
    file.open("textFiles/loginData.txt");
    if (!file)
    {
        cout << endl
             << "File Not Found !";
    }
    else
    {
        while (!file.eof())
        {
            User u;
            file >> u.id;
            file.ignore();
            getline(file, u.username);
            getline(file, u.password);
            file.ignore();
            // cout<<u.id << " , "<<u.username<<" , "<<u.password<<endl;

            users.push_back(u);
        }
        file.close();
    }
}

using namespace std;

void refresh()
{
    _getch();
    system("cls");
    cout << endl
         << "=====================================================================" << endl
         << "|||           ||||||||||\\   |||\\     /|||   |||||||||||           |||" << endl
         << "|||           |||     |||   ||||\\   /||||   |||                   |||" << endl
         << "|||           ||||||||||/   ||| || || |||   |||||||||||           |||" << endl
         << "|||           |||     |||   |||  |||  |||           |||           |||" << endl
         << "|||           ||||||||||/   |||       |||   |||||||||||           |||" << endl
         << "=====================================================================" << endl;
}

bool adminLogin(vector<User> users)
{
    short attempts = 3;
    string password, username;
    while (attempts > 0)
    {
        cout << endl;
        cout << endl
             << "Enter Your Username : ";
        cin >> username;
        cout << "Enter your Password : ";
        cin >> password;

        for (int i = 0; i < ADMINS; i++)
        {
            if (users[i].username == username && users[i].password == password)
            {
                cout << endl
                     << "User Authenticated...";
                return true;
                break;
            }
        }
        cout << endl
             << "Invalid Credentials...";
        attempts--;
        cout << endl
             << "Attempts Left : " << attempts;
    }
    return false;
}
bool userLogin(const vector<User> &users, int &userID)
{
    int attempts = 3;
    string username, password;

    while (attempts > 0)
    {
        cout << endl
             << "Enter Your Username: ";
        cin >> username;
        cout << "Enter Your Password: ";
        cin >> password;

        // Check credentials
        for (int i = 3; i < users.size(); i++)
        {
            if (users[i].username == username && users[i].password == password)
            {
                cout << endl
                     << "User Authenticated..." << endl;
                userID = users[i].id;
                return true;
            }
        }

        cout << endl
             << "Invalid Credentials..." << endl;
        attempts--;
        cout << endl
             << "Attempts Left : " << attempts;
    }

    return false;
}

void performTransaction(Account &userAccount, AccountBST &accounts)
{
    char choice;
    bool exit = false;
    while (!exit)
    {
        refresh();
        cout << endl
             << "1. Deposit Amount"
             << endl
             << "2. Withdraw Amount"
             << endl
             << "3. Transfer Amount"
             << endl
             << "0. Exit"
             << endl
             << endl
             << "Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            cout << endl
                 << "Deposit Amount";
            int amount;
            cout << endl
                 << "Enter Amount to Deposit : ";
            cin >> amount;
            userAccount.addAmount(amount);
            // accounts.insertAccount(userAccount);
            break;
        }

        case '2':
        {
            cout << endl
                 << "Withdraw Amount";
            int amountW;
            cout << endl
                 << "Enter Amount to Withdraw : ";
            cin >> amountW;
            if (amountW > userAccount.getAmount())
            {
                cout << endl
                     << "Not enough balance to withdraw";
            }
            else
            {
                userAccount.withdrawAmount(amountW);
                cout << endl
                     << "Remaining Amount : " << userAccount.getAmount();
                // accounts.insertAccount(userAccount);
            }
            break;
        }

        case '3':
        {
            cout << endl
                 << "Transfer Amount";
            cout << endl
                 << "Displaying Accounts";
            accounts.displayAccounts();

            int id;
            cout << endl
                 << "Enter Account ID to Transfer Amount : ";
            cin >> id;

            Account &receiverAccount = accounts.searchAccount(id);
            int amountT;
            cout << endl
                 << "Enter Amount to Transfer : ";
            cin >> amountT;
            if (amountT > userAccount.getAmount())
            {
                cout << endl
                     << "Not enough balance to transfer";
            }
            else
            {
                userAccount.withdrawAmount(amountT);
                receiverAccount.addAmount(amountT);
                // accounts.insertAccount(userAccount);
                // accounts.insertAccount(receiverAccount);
            }
            break;
        }

        case '0':
            exit = true;
            break;

        default:
            cout << endl
                 << "Invalid Choice";
            break;
        }
    }
}

void manageAccounts(AccountBST accounts)
{
    char choice;
    bool exit = false;

    while (!exit)
    {
        refresh();
        cout << endl
             << "1. Add Account" << endl
             << "2. Delete Account" << endl
             << "3. Update Account Details" << endl
             << "4. Display All Accounts" << endl
             << "0. Exit" << endl
             << endl
             << "Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            cout << endl
                 << "Add Account";
            break;

        case '2':
            cout << endl
                 << "Delete Account";
            break;

        case '3':
            cout << endl
                 << "Update Account";
            break;

        case '4':
            cout << endl
                 << "Displaying Accounts"
                 << endl
                 << "===================";
            accounts.displayAccounts();
            break;

        case '0':
            exit = true;
            break;
        }
    }
}

// Menu Functions
void adminMenu(vector<User> &users, AccountBST &accounts)
{
    if (adminLogin(users))
    {
        char choice;
        bool exit = false;
        while (!exit)
        {
            refresh();
            cout << endl
                 << "1. Manage Branches"
                 << endl
                 << "2. Manage Accounts"
                 << endl
                 << "3. Process Transaction"
                 << endl
                 << "4. Generate Reports"
                 << endl
                 << "0. Exit"
                 << endl
                 << endl
                 << "Your Choice : ";
            // choice = _getche();
            cin >> choice;

            switch (choice)
            {
            case '1':
                cout << endl
                     << "Manage Branches";
                break;

            case '2':
                cout << endl
                     << "Manage Accounts";
                manageAccounts(accounts);

                break;

            case '3':
                cout << endl
                     << "Process Transactions";
                break;

            case '4':
                cout << endl
                     << "Generate Reports";
                break;

            case '0':
                exit = true;
                break;

            default:
                cout << endl
                     << "Invalid Choice";
                break;
            }
        }
    }
}
void customerMenu(vector<User> &users, AccountBST &accounts)
{
    int userID = -1;
    if (userLogin(users, userID))
    {
        Account &userAccount = accounts.searchAccount(userID);
        userAccount.addAmount(10000);
        userAccount.displayAccount();
        char choice;
        bool exit = false;
        while (!exit)
        {
            refresh();
            cout << endl
                 << "1. View Account Details"
                 << endl
                 << "2. Perform Transaction"
                 << endl
                 << "3. View Transaction History"
                 << endl
                 << "4. View Account Summary"
                 << endl
                 << "0. Exit"
                 << endl
                 << endl
                 << "Your Choice: ";
            // choice = _getche();
            cin >> choice;

            switch (choice)
            {
            case '1':
                cout << endl
                     << "View Account Details";
                cout << endl;
                userAccount.displayAccount();
                _getch();
                break;

            case '2':
                cout << endl
                     << "Perform Transaction";
                performTransaction(userAccount, accounts);
                break;
                break;

            case '3':
                cout << endl
                     << "View Transaction History";
                break;

            case '4':
                cout << endl
                     << "View Account Summary";
                break;

            case '0':
                exit = true;
                break;

            default:
                cout << endl
                     << "Invalid Choice";
                break;
            }
        }
    }
}

void mainMenu(vector<User> &users, AccountBST &accounts)
{
    char choice;
    bool exit = false;
    while (!exit)
    {
        refresh();
        cout << endl
             << "1. Admin"
             << endl
             << "2. Customer"
             << endl
             << "0. Exit"
             << endl
             << endl
             << "Your Choice : ";
        // choice = _getche();
        cin >> choice;

        switch (choice)
        {
        case '1':
            // Admin Menu Call
            cout << endl
                 << "Admin Menu";
            adminMenu(users, accounts);
            break;

        case '2':
            // Customer Menu Call
            cout << endl
                 << "Customer Menu";
            customerMenu(users, accounts);
            break;

        case '0':
            exit = true;
            break;

        default:
            break;
        }
    }
}

int main()
{
    AccountBST accounts;
    string filepathAcc = "textFiles/customerData.txt";
    accounts.loadTreeFromFile(filepathAcc);
    vector<User> users;
    loadLoginData(users);

    mainMenu(users, accounts);
    accounts.displayAccounts();
    _getch();
    return 0;
}