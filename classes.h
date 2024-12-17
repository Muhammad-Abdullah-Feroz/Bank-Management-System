#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <conio.h>
#include"Graphs.h"
using namespace std;

void displayAccountHeader()
{
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(10) << "UserID"
         << "| " << left << setw(20) << "Name"
         << "| " << left << setw(20) << "Branch Name"
         << "| " << left << setw(16) << "Account Number"
         << "| " << right << setw(15) << "Amount" << " |" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
}

class User
{
public:
    int id;
    string username;
    string password;
    User()
    {
        id = 0;
        username = "";
        password = "";
    }
};
class TransactionStack;

class tNode
{
    string transaction;
    tNode *next;
    friend class TransactionStack;
    friend class AccountBST;

public:
    tNode(const string &transaction)
    {
        this->transaction = transaction;
        next = nullptr;
    }
};

class TransactionStack
{
private:
    tNode *top;
    int currentSize;
    friend class AccountBST;
public:
    TransactionStack() : top(nullptr), currentSize(0) {}

    ~TransactionStack()
    {
        while (top != nullptr)
        {
            tNode *temp = top;
            top = top->next;
            delete temp;
        }
    }

    void addTransaction(const string &transaction)
    {
        tNode *newtNode = new tNode(transaction);
        newtNode->next = top;
        top = newtNode;
        currentSize++;
    }

    void displayTransactions() const
    {
        if (top == nullptr)
        {
            cout << "No transactions recorded." << endl;
            return;
        }

        cout << "Transactions:" << endl;
        tNode *current = top;
        short count = 1;
        while (current != nullptr)
        {
            cout << endl
                 << count << ". " << current->transaction << endl;
            current = current->next;
            count++;
        }
    }

    void displayTopNTransactions(int n) const
    {
        if (top == nullptr)
        {
            cout << "No transactions recorded." << endl;
            return;
        }

        if (n <= 0)
        {
            cout << "Invalid number of transactions to display." << endl;
            return;
        }

        tNode *current = top;
        short count = 1;
        while (current != nullptr && count <= n)
        {
            cout << endl
                 << count << ". " << current->transaction << endl;
            current = current->next;
            count++;
        }
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }

    int transactionCount() const
    {
        return currentSize;
    }
};

class AccountBST;
class Account
{
    int userID;
    string name;
    string accountNumber;
    string branchName;
    float amount;
    TransactionStack transactions;
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
    void setName(string n)
    {
        name = n;
    }
    void setAccountNumber(string n)
    {
        accountNumber = n;
    }
    void setBranchName(string n)
    {
        branchName = n;
    }
    void setAmount(float n)
    {
        amount = n;
    }
    void addAmount(int n)
    {
        amount += n;
    }
    void withdrawAmount(int n)
    {
        amount -= n;
    }
    float getAmount()
    {
        return amount;
    }
    int getID()
    {
        return userID;
    }
    string getName()
    {
        return name;
    }
    string getBranchName()
    {
        return branchName;
    }
    string getAccountNumber()
    {
        return accountNumber;
    }
    void setTransaction(string transaction)
    {
        transactions.addTransaction(transaction);
    }
    void displayTransactions()
    {
        transactions.displayTransactions();
    }
    void displayTransactions(int n)
    {
        transactions.displayTopNTransactions(n);
    }
    void displayAccount()
    {

        // cout << "-----------------------------------------------------------------------" << endl;
        cout << "| " << left << setw(10) << userID
             << "| " << left << setw(20) << name
             << "| " << left << setw(20) << branchName
             << "| " << left << setw(16) << accountNumber
             << "| " << right << setw(15) << fixed << setprecision(2) << amount
             << " |" << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;
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

        Account *ac = new Account();
        return *ac;
    }

    void saveNodesToFile(AccountNode *root, ofstream &file)
    {
        if (root != nullptr)
        {
            file << root->acc.userID << endl;
            file << root->acc.name << endl;
            file << root->acc.branchName << endl;
            file << root->acc.accountNumber << endl;
            file << root->acc.amount << endl;

            // Save transactions
            file << root->acc.transactions.transactionCount() << endl; // Number of transactions
            tNode *current = root->acc.transactions.top;
            while (current != nullptr)
            {
                file << current->transaction << endl;
                current = current->next;
            }
            file << endl; // Separate entries with an empty line

            saveNodesToFile(root->left, file);
            saveNodesToFile(root->right, file);
        }
    }

    AccountNode *deleteNode(AccountNode *root, int userID)
    {
        if (!root)
            return nullptr;

        if (userID < root->acc.userID)
        {
            root->left = deleteNode(root->left, userID);
        }
        else if (userID > root->acc.userID)
        {
            root->right = deleteNode(root->right, userID);
        }
        else
        {
            // Case 1: Node with no children
            if (!root->left && !root->right)
            {
                delete root;
                return nullptr;
            }

            // Case 2: Node with one child
            if (!root->left)
            {
                AccountNode *temp = root->right;
                temp->parent = root->parent;
                delete root;
                return temp;
            }
            else if (!root->right)
            {
                AccountNode *temp = root->left;
                temp->parent = root->parent;
                delete root;
                return temp;
            }

            // Case 3: Node with two children
            AccountNode *successor = findMin(root->right);
            root->acc = successor->acc; // Replace with successor's data
            root->right = deleteNode(root->right, successor->acc.userID);
        }

        return root;
    }

    AccountNode *findMin(AccountNode *node)
    {
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }

public:
    void deleteAccount(int userID)
    {
        root = deleteNode(root, userID);
    }

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
            displayAccountHeader();
            displayNodes(this->root);
        }
        else
        {
            cout << "No Accounts Found" << endl;
        }
    }

    void saveTreeToFile(string filepath)
    {
        ofstream file;
        file.open(filepath);
        if (!file)
        {
            cout << endl
                 << "File Not Found !";
        }
        else
        {
            saveNodesToFile(this->root, file);
            file.close();
        }
    }

   void loadTreeFromFile(string filepath) {
    ifstream file;
    file.open(filepath);

    if (!file) {
        cout << endl
             << "File Not Found!" << endl;
        return;
    }

    while (!file.eof()) {
        Account a;

        file >> a.userID;
        if (file.eof()) break; 
        file.ignore();                  
        getline(file, a.name);   
        getline(file, a.branchName);      
        getline(file, a.accountNumber); 
        file >> a.amount;
        file.ignore(); 

        this->insertAccount(a);

        Account &refAccount = this->searchAccount(a.userID);

        int transactionCount;
        file >> transactionCount; 
        file.ignore();

        vector<string> transactions;
        for (int i = 0; i < transactionCount; i++) {
            string transaction;
            getline(file, transaction); 
            transactions.push_back(transaction);
        }

        for (int i = transactionCount - 1; i >= 0; i--) {
            refAccount.setTransaction(transactions[i]);
        }
    }

    file.close();
}
};

class transactionQueue;
class transactionRequest
{
    int senderID;
    int recieverID;
    float amount;
    float tax;
    friend class transactionQueue;

public:
    transactionRequest()
    {
        senderID = recieverID = 0;
        amount = 0;
    }
    void setSenderID(int id)
    {
        senderID = id;
    }
    void setReceieverID(int id)
    {
        recieverID = id;
    }
    void setAmount(float n)
    {
        amount = n;
    }
    void setTax(float n)
    {
        tax = n;
    }
    int getSender()
    {
        return senderID;
    }
    int getReciever()
    {
        return recieverID;
    }
    float getAmount()
    {
        return amount;
    }
    float getTax()
    {
        return tax;
    }
};
class transactionNode
{
    transactionRequest transaction;
    transactionNode *next;
    transactionNode *prev;
    friend class transactionQueue;

public:
    transactionNode()
    {
        next = prev = nullptr;
    }
    transactionNode(transactionRequest trans)
    {
        this->transaction = trans;
        next = prev = nullptr;
    }
};
class transactionQueue
{

    transactionNode *head;
    transactionNode *tail;

public:
    transactionQueue()
    {
        tail = head = nullptr;
    }
    void enQueue(transactionRequest transaction)
    {
        transactionNode *newNode = new transactionNode(transaction);
        if (head == nullptr)
        {
            head = newNode;
            tail = head;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    transactionRequest deQueue()
    {
        transactionRequest tr;
        if (head == nullptr)
        {
            return tr;
        }

        transactionNode *temp = head;
        if (head == tail)
        { // Only one element in the queue
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }

        tr = temp->transaction;
        delete temp;
        return tr;
    }

    void readFromFile()
    {
        ifstream file;
        file.open("textFiles/transactionData.txt");
        if (!file)
        {
            cout << endl
                 << "File Not Found !";
        }
        else
        {
            while (!file.eof())
            {
                transactionRequest tr;
                file >> tr.senderID;
                file >> tr.recieverID;
                file >> tr.tax;
                file >> tr.amount;
                file.ignore();
                if (tr.senderID == 0)
                {
                    break;
                }
                enQueue(tr);
            }
            file.close();
        }
    }
    void writeToFile()
    {
        ofstream file;
        file.open("textFiles/transactionData.txt");
        if (!file)
        {
            cout << endl
                 << "File Not Found !";
        }
        else
        {
            transactionNode *current = head;
            while (current != nullptr)
            {
                file << current->transaction.senderID << endl;
                file << current->transaction.recieverID << endl;
                file << current->transaction.tax << endl;
                file << current->transaction.amount << endl
                     << endl;
                current = current->next;
            }
            file.close();
        }
    }

    void displayQueue()
    {
        if (head == nullptr)
        {
            cout << "No pending transaction...\n";
            return;
        }

        transactionNode *current = head;
        while (current != nullptr)
        {
            cout << endl
                 << "Sender ID: " << current->transaction.getSender() << ", ";
            cout << "Receiver ID: " << current->transaction.getReciever() << ", ";
            cout << "Amount: " << current->transaction.getAmount() << "\n";
            current = current->next;
        }
    }
};
