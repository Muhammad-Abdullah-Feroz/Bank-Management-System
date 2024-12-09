#include<iostream>
#include<conio.h>
#include <fstream>
#include<vector>
#include<string>
#include "classes.h"

using namespace std;

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
//             cout<<u.id << " , "<<u.username<<" , "<<u.password<<" , "<<u.name<<" , "<<u.accountNumber<<endl;
    
//             users.push_back(u);
//         }
//         file.close();
//     }

AccountBST a;
a.loadTreeFromFile("textFiles/accountsData.txt");

a.displayAccounts();

}