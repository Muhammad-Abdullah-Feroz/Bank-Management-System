#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <conio.h>

using namespace std;

class User
{
public:
    int id;
    string username;
    string password;
};

class AccountBST;
class Account
{
    int userID;
    string name;
    string accountNumber;
    int amount;
    friend class AccountBST;

public:
    Account()
    {
        userID = 0;
        name = "";
        accountNumber = "";
        amount = 0;
    }
    void setID(int n)
    {
        userID = n;
    }
    void addAmount(int n)
    {
        amount += n;
    }
    void withdrawAmount(int n)
    {
        amount -= n;
    }
    int getAmount()
    {
        return amount;
    }
    int getID()
    {
        return userID;
    }
    void displayAccount()
    {

        // cout << "-----------------------------------------------------------------------" << endl;
        cout << "| " << left << setw(10) << userID
             << "| " << left << setw(20) << name
             << "| " << left << setw(16) << accountNumber
             << "| " << right << setw(15) << fixed << setprecision(2) << amount
             << " |" << endl;
        cout << "-----------------------------------------------------------------------" << endl;
    }
};

class AccountNode
{
    Account acc;
    AccountNode *parent;
    AccountNode *left;
    AccountNode *right;
    friend class AccountBST;

public:
    AccountNode(Account a)
    {
        acc = a;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    AccountNode()
    {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class AccountBST
{
    AccountNode *root;

    AccountNode *insertNode(AccountNode *root, AccountNode *newNode)
    {
        if (root)
        {
            if (newNode->acc.getID() > root->acc.getID())
            {
                AccountNode *n = insertNode(root->right, newNode);
                n->parent = root;
                root->right = n;
                return root;
            }
            else if (newNode->acc.getID() < root->acc.getID())
            {
                AccountNode *n = insertNode(root->left, newNode);
                n->parent = root;
                root->left = n;
                return root;
            }
            else
            {
                return root;
            }
        }
        else
        {
            return newNode;
        }
    }

    void displayNodes(AccountNode *root)
    {
        if (root)
        {
            displayNodes(root->left);
            root->acc.displayAccount();
            displayNodes(root->right);
        }
    }
    Account &searchAccountNode(AccountNode *root, int id)
    {
        if (root)
        {
            if (root->acc.userID == id)
            {
                return root->acc;
            }
            if (root->acc.userID < id)
            {
                return searchAccountNode(root->right, id);
            }
            if (root->acc.userID > id)
            {
                return searchAccountNode(root->left, id);
            }
        }
        else
        {
            Account *ac = new Account();
            return *ac;
        }
    }

public:
    AccountBST()
    {
        root = nullptr;
    }

    Account &searchAccount(int id)
    {
        return searchAccountNode(this->root, id);
    }

    void insertAccount(Account acc)
    {
        AccountNode *newNode = new AccountNode(acc);
        this->root = insertNode(this->root, newNode);
    }

    void displayAccounts()
    {
        if (this->root)
        {
            cout << "-----------------------------------------------------------------------" << endl;
            cout << "| " << left << setw(10) << "UserID"
                 << "| " << left << setw(20) << "Name"
                 << "| " << left << setw(16) << "Account Number"
                 << "| " << right << setw(15) << "Amount" << " |" << endl;
            cout << "-----------------------------------------------------------------------" << endl;
            displayNodes(this->root);
        }
        else
        {
            cout << "No Accounts Found" << endl;
        }
    }

    void loadTreeFromFile(string filepath)
    {
        ifstream file;
        file.open(filepath);
        if (!file)
        {
            cout << endl
                 << "File Not Found !";
        }
        else
        {
            while (!file.eof())
            {
                Account a;
                file >> a.userID;
                file.ignore();
                getline(file, a.name);
                getline(file, a.accountNumber);
                file >> a.amount;
                file.ignore();
                // cout << a.userID << " , "<< a.name << " , "<< a.accountNumber << " , " << a.amount << endl;

                this->insertAccount(a);
            }
            file.close();
        }
    }
};
