#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <conio.h>

using namespace std;

void displayAccountHeader()
{
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(10) << "UserID"
         << "| " << left << setw(20) << "Name"
         << "| " << left << setw(16) << "Account Number"
         << "| " << right << setw(15) << "Amount" << " |" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
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
    int maxSize;
    int currentSize;

public:
    TransactionStack() : top(nullptr), maxSize(5), currentSize(0) {}

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
        if (currentSize == maxSize)
        {
            tNode *current = top;
            while (current->next != nullptr && current->next->next != nullptr)
            {
                current = current->next;
            }

            tNode *temp = current->next;
            current->next = nullptr;
            delete temp;
            currentSize--;
        }

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
    int amount;
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
    string getName()
    {
        return name;
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

        Account *ac = new Account();
        return *ac;
    }

    void saveNodesToFile(AccountNode *root, ofstream &file)
    {
        if (root != nullptr)
        {
            // Write each account's data in the correct format
            file << root->acc.userID << endl;
            file << root->acc.name << endl;
            file << root->acc.accountNumber << endl;
            file << root->acc.amount << endl
                 << endl;
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

    void loadTreeFromFile(string filepath)
    {
        ifstream file;
        file.open(filepath);

        if (!file)
        {
            cout << endl
                 << "File Not Found!" << endl;
            return;
        }

        while (!file.eof())
        {
            Account a;
            // Read the account details in the same order they are written to the file
            file >> a.userID;
            file.ignore();                  // Ignore newline after reading userID
            getline(file, a.name);          // Read the name
            getline(file, a.accountNumber); // Read the account number
            file >> a.amount;
            file.ignore(); // Ignore newline after reading the amount

            a.displayAccount();

            if (a.userID == 0)
            {
                break;
            }
            this->insertAccount(a);
        }
        file.close();
    }
};
