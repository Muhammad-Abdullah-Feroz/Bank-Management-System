#include<iostream>
#include<conio.h>
#include <fstream>
#include<vector>
#include<string>
#include <cstdlib>
#include "classes.h"

using namespace std;
string generateAccountNumber() {
    int accountNumber = 0;
    for (int i = 0; i < 6; ++i) {
        int digit = rand() % 10; // Generate a single digit
        accountNumber = accountNumber * 10 + digit; // Append digit to account number
    }
    return "AC"+to_string(accountNumber);
}

int main(){
vector<User> users;

// ifstream file;
//     file.open("textFiles/accountsData.txt");
//     if(!file){
//         cout<<endl<<"File Not Found !";
//     }else{
//         while (!file.eof())
//         {
//             Account a;
//             file>>a.setID();
            // cout<<u.id << " , "<<u.username<<" , "<<u.password<<" , "<<u.name<<" , "<<u.accountNumber<<endl;
    
//             users.push_back(u);
//         }
//         file.close();
//     }

srand(time(0));
cout<<endl<<generateAccountNumber();

// AccountBST a;
// a.loadTreeFromFile("textFiles/accountsData.txt");

// a.displayAccounts();

}