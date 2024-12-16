#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include "classes.h"
#define ADMINS 3

using namespace std;

transactionQueue transactions;
BankGraph branches;

// Utility Functions
string generateAccountNumber()
{
    int accountNumber = 0;
    for (int i = 0; i < 6; ++i)
    {
        int digit = rand() % 10;                    // Generate a single digit
        accountNumber = accountNumber * 10 + digit; // Append digit to account number
    }
    return "AC" + to_string(accountNumber);
}
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
            cout << u.id << " , " << u.username << " , " << u.password << endl;
            if (u.username != "" && u.password != "")
                users.push_back(u);
        }
        file.close();
    }
}
void writeLoginData(vector<User> &users)
{
    ofstream file;
    file.open("textFiles/loginData.txt");
    if (!file)
    {
        cout << endl
             << "File Not Found !";
    }
    else
    {
        for (int i = 0; i < users.size(); i++)
        {
            file << users[i].id << endl;
            file << users[i].username << endl;
            file << users[i].password << endl;
            file << endl;
        }
        file.close();
    }
}

// Dispay Functions
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

// Login Functions
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

// Admin Functions

void manageBranches()
{
    char choice;
    bool exit = false;
    while (!exit)
    {
        refresh();
        cout << endl
             << "1. Add Branch"
             << endl
             << "2. View Branches"
             << endl
             << "3. Add Connection"
             << endl
             << "4. Calculate shortest Distance Between two branches"
             << endl
             << "0. Exit"
             << endl
             << "Your Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case '1':
        {

            cout << endl
                 << "Add Branch";
            string branch;
            cout << endl
                 << "Enter the branch Name : ";
            getline(cin, branch);

            branches.addBranch(branch);

            // Add branch logic here
            break;
        }
        case '2':
        {

            cout << endl
                 << "View Branch";
            branches.displayBranches();
            break;
        }
        case '3':
        {

            cout << endl
                 << "Add Connection";
            branches.displayBranches();
            int idx1 , idx2;
            cout<<endl<<"Choose first branch : ";
            cin >> idx1;
            cout<<"Choose second Branch : ";
            cin >> idx2;
            string branch1 = branches.findBranch(idx1);
            string branch2 = branches.findBranch(idx2);
            if (branch1 != "" && branch2 != ""){
                int weight = 0;
                cout<<endl<<"Enter Cost Between "<<branch1<<" and "<<branch2<<" : ";
                cin >> weight;
                if(weight < 0){
                    cout<<endl<<"Negative values not allowed..."<<endl<<"Weight set to '0'";
                    weight = 0;
                }
                branches.addConnection(branch1 , branch2 , weight);
            }else{
                cout<<endl<<"Invalid Choice..."<<endl;
            }
            break;
        }
        case '4':
        {

            cout << endl
                 << "Calculate shortest Distance Between two branches" << endl;
            branches.displayBranches();
            string start, end;
            int startIdx, endIdx;
            cout << endl
                 << "Choose Starting Branch : ";
            cin >> startIdx;
            cout << endl
                 << "Choose Ending Branch : ";
            cin >> endIdx;
            start = branches.findBranch(startIdx);
            end = branches.findBranch(endIdx);
            if (start != "" && end != "")
            {
                branches.shortestPath(start, end);
            }
            else
            {
                cout << endl
                     << "Invalid Choice...." << endl;
            }

            // Calculate shortest distance logic here
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
void addAccounts(AccountBST &accounts, vector<User> &users)
{
    srand(time(0));
    Account acc;
    string accNumber;
    string name;
    int amount;
    User user;
    cout << endl
         << "Enter Account Details";
    cout << endl
         << "Enter User ID: ";
    cin >> user.id;
    cout << endl
         << "Enter username: ";
    cin >> user.username;
    cout << endl
         << "Enter password: ";
    cin >> user.password;

    if (user.id > 0 && user.username != "" && user.password != "")
    {
        if (accounts.searchAccount(user.id).getID() == 0)
        {
            for (int i = 0; i < users.size(); i++)
            {
                if (users[i].username == user.username)
                {
                    cout << endl
                         << "User ID already exists";
                    return;
                }
            }
            users.push_back(user);
        }
        else
        {
            cout << endl
                 << "User ID already exists";
            return;
        }
    }
    else
    {
        cout << endl
             << "Invalid User Entry";
        return;
    }
    accNumber = generateAccountNumber();
    cout << endl
         << "Enter Account Holder Name: ";
    cin.ignore();
    getline(cin, name);
    cout << endl
         << "Enter Initial Amount: ";
    cin >> amount;
    if (amount < 0)
    {
        cout << endl
             << "Invalid Amount"
             << endl
             << "Amount set to 0"
             << endl;
        return;
    }
    amount = amount < 0 ? 0 : amount;

    acc.setID(user.id);
    acc.setAccountNumber(accNumber);
    acc.setName(name);
    acc.addAmount(amount);
    accounts.insertAccount(acc);
    cout << endl
         << "Account Added Successfully";
}
void deleteAccount(AccountBST &accounts, vector<User> &users)
{
    int id;
    accounts.displayAccounts();
    cout << endl
         << endl
         << "Enter Account ID to Delete: ";
    cin >> id;
    Account &acc = accounts.searchAccount(id);
    if (acc.getID() == 0)
    {
        cout << endl
             << "Account Not Found";
        return;
    }
    accounts.deleteAccount(id);
    for (int i = 3; i < users.size(); i++)
    {
        if (users[i].id == id)
        {
            users.erase(users.begin() + i);
            break;
        }
    }
    cout << endl
         << "Account Deleted Successfully";
}
void updateAccount(AccountBST &accounts, vector<User> &users)
{
    int id;
    accounts.displayAccounts();
    cout << endl;
    cout << endl
         << "Enter User ID to update account : ";
    cin >> id;

    Account &userAcc = accounts.searchAccount(id);
    if (userAcc.getID() == 0)
    {
        cout << endl
             << "Account Not Found";
        return;
    }
    cout << endl
         << "Enter New Name : ";
    string name;
    cin.ignore();
    getline(cin, name);
    userAcc.setName(name);
    cout << endl
         << "Enter New Amount : ";
    int amount;
    cin >> amount;
    if (amount < 0)
    {
        cout << endl
             << "Invalid Amount";
        return;
    }
    userAcc.setAmount(amount);
    string transaction = "(ADMIN Msg) Updated Account Details..  New Amount : " + to_string(amount) + " $   Date: " + __DATE__;
    userAcc.setTransaction(transaction);
    cout << endl
         << "Account Updated Successfully";
}
void manageAccounts(AccountBST &accounts, vector<User> &users)
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
        cin.ignore();

        switch (choice)
        {
        case '1':
            cout << endl
                 << "Add Account";
            addAccounts(accounts, users);
            break;

        case '2':
            cout << endl
                 << "Delete Account";
            deleteAccount(accounts, users);
            break;

        case '3':
            cout << endl
                 << "Update Account";
            updateAccount(accounts, users);
            break;

        case '4':
            cout << endl
                 << "Displaying Accounts"
                 << endl
                 << "===================" << endl
                 << endl;
            accounts.displayAccounts();
            break;

        case '0':
            exit = true;
            break;
        }
    }
}
void processTransactions(AccountBST &accounts)
{
    refresh();
    char choice;
    transactionRequest tr;
    tr = transactions.deQueue();
    if (tr.getSender() == 0)
    {
        cout << endl
             << "No pending transactions" << endl;
        return;
    }
    Account &sender = accounts.searchAccount(tr.getSender());
    Account &reciever = accounts.searchAccount(tr.getReciever());
    cout << endl
         << "AMOUNT : " << tr.getAmount() << "$  FROM  " << sender.getName() << " (ID : " << tr.getSender() << " )  TO  " << reciever.getName() << " (ID : " << tr.getReciever() << " )";
    cout << endl
         << "1. Accept Transaction"
         << endl
         << "2. Reject Transaction";
    cout << endl
         << "Enter your choice : ";
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case '1':
    {
        string transaction;
        if (sender.getAmount() > tr.getAmount())
        {
            sender.withdrawAmount(tr.getAmount());
            reciever.addAmount(tr.getAmount());
            transaction = "Transfer Accepted : " + to_string(tr.getAmount()) + "$ to Account Holder : " + reciever.getName() + " (ID : " + to_string(reciever.getID()) + " ) Date: " + __DATE__;
            sender.setTransaction(transaction);
            cout << endl
                 << transaction;
            transaction = "Received " + to_string(tr.getAmount()) + "$ from Account Holder: " + sender.getName() + " (ID: " + to_string(sender.getID()) + ")  Date: " + __DATE__;
            reciever.setTransaction(transaction);
        }
        else
        {
            transaction = "Transfer Declined Due to Low Balance : " + to_string(tr.getAmount()) + "$ to Account Holder : " + reciever.getName() + " (ID : " + to_string(reciever.getID()) + " )  Date: " + __DATE__;
            sender.setTransaction(transaction);
            cout << endl
                 << transaction;
        }
        break;
    }
    case '2':
    {
        string transaction = "Transfer Declined by Administration : " + to_string(tr.getAmount()) + "$ to Account Holder : " + reciever.getName() + " (ID : " + to_string(reciever.getID()) + " )  Date: " + __DATE__;
        sender.setTransaction(transaction);
        cout << endl
             << transaction;
        break;
    }
    }
}
void generateReports(AccountBST &accounts)
{
    refresh();
    cout << endl;
    accounts.displayAccounts();
    cout << endl
         << endl
         << "Enter Account ID to Generate Report : ";
    int id;
    cin >> id;
    Account &acc = accounts.searchAccount(id);
    if (acc.getID() == 0)
    {
        cout << endl
             << "Account Not Found";
        return;
    }
    cout << endl
         << "Generating Report : " << endl;
    cout << endl
         << "Account Details : " << endl;
    displayAccountHeader();
    acc.displayAccount();
    cout << endl
         << "Transaction History : " << endl;
    acc.displayTransactions();
}

// Customer Functions
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
        cin.ignore();

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
            cout << endl
                 << "Amount Added Successfully";
            cout << endl
                 << "New Amount : " << userAccount.getAmount();
            string transaction = "Deposited " + to_string(amount) + "$  Date: " + __DATE__;
            userAccount.setTransaction(transaction);
            // userAccount.transactions.addTransaction(transaction);
            // accounts.insertAccount(userAccount);
            break;
        }

        case '2':
        {
            cout << endl
                 << "Withdraw Amount";
            int amountW;
            cout << endl
                 << "Current Amount : " << userAccount.getAmount() << endl
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
                     << "Amount Withdrawn Successfully";
                cout << endl
                     << "Remaining Amount : " << userAccount.getAmount();
                string transaction = "Withdrawn " + to_string(amountW) + "$  Date: " + __DATE__;
                userAccount.setTransaction(transaction);
                // accounts.insertAccount(userAccount);
            }
            break;
        }

        case '3':
        {
            cout << endl
                 << "Transfer Amount";
            cout << endl
                 << "Displaying Accounts" << endl
                 << endl;
            accounts.displayAccounts();

            int id;
            cout << endl
                 << "Enter Account ID to Transfer Amount : ";
            cin >> id;
            if (id == userAccount.getID())
            {
                cout << endl
                     << "Cannot Transfer to Same Account";
                break;
            }

            Account &receiverAccount = accounts.searchAccount(id);
            if (receiverAccount.getID() == 0)
            {
                cout << endl
                     << "Account Not Found";
                break;
            }
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
                // userAccount.withdrawAmount(amountT);
                // receiverAccount.addAmount(amountT);
                string transaction = "Transfer Requested : " + to_string(amountT) + "$ to Account Holder: " + receiverAccount.getName() + " (ID: " + to_string(receiverAccount.getID()) + ")  Date: " + __DATE__;
                userAccount.setTransaction(transaction);
                cout << endl
                     << transaction;
                // cout << endl
                //      << transaction;
                // transaction = "Received " + to_string(amountT) + "$ from Account Holder: " + userAccount.getName() + " (ID: " + to_string(userAccount.getID()) + ")";
                // receiverAccount.setTransaction(transaction);
                transactionRequest tr;
                tr.setSenderID(userAccount.getID());
                tr.setReceieverID(id);
                tr.setAmount(amountT);
                transactions.enQueue(tr);
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
            cin.ignore();

            switch (choice)
            {
            case '1':
                cout << endl
                     << "Manage Branches";
                manageBranches();
                break;

            case '2':
                cout << endl
                     << "Manage Accounts";
                manageAccounts(accounts, users);

                break;

            case '3':
                cout << endl
                     << "Process Transactions";
                processTransactions(accounts);
                break;

            case '4':
                cout << endl
                     << "Generate Reports";
                generateReports(accounts);
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
        // userAccount.addAmount(10000);
        displayAccountHeader();
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
            cin.ignore();

            switch (choice)
            {
            case '1':
                cout << endl
                     << "View Account Details";
                cout << endl
                     << endl;
                displayAccountHeader();
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
                     << "View Transaction History" << endl
                     << endl;
                userAccount.displayTransactions(5);
                break;

            case '4':
                cout << endl
                     << "View Account Summary";
                cout << endl
                     << "Account Details:" << endl;
                displayAccountHeader();
                userAccount.displayAccount();
                cout << endl
                     << "Transaction History:" << endl
                     << endl;
                userAccount.displayTransactions();
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
        cin.ignore();

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

// Main Function
int main()
{

    AccountBST accounts;
    string filepathAcc = "textFiles/customerData.txt";
    string graphFile = "textFiles/graphData.txt";
    accounts.loadTreeFromFile(filepathAcc);
    vector<User> users;
    loadLoginData(users);
    branches.readGraphFromFile(graphFile);
    transactions.readFromFile();
    transactions.displayQueue();

    mainMenu(users, accounts);
    accounts.displayAccounts();
    accounts.saveTreeToFile(filepathAcc);
    writeLoginData(users);
    transactions.writeToFile();
    branches.writeGraphToFile(graphFile);
    _getch();
    return 0;
}