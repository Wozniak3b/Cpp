#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Users.hpp"
#include "Debts.hpp"

using std::string, std::ofstream, std::ifstream, std::map,
std::vector, std::cout;

class Database {
private:
    map<int, User> users;
    map<int, vector<Debt>> debts;
    
public:
    void addUser(int id, const string& username, const string& secretKey){
        if(users.find(id) != users.end()){
            cout<<"User with ID: "<<id<<" and name: "<<username<<
            " already exist"<<endl;
            return -1;
        }
        users[id]=User(id,username,secretKey);
    }

    void addDebt(int userId, const string& description, float amount){
        if(users.find(userId) == users.end()){
            cout<<"User with ID: "<<id<<" and name: "<<username<<
            " dont exist"<<endl;
            return -1;
        }
        debts[userId].push_back(Debt(description,amount));
    }

    void displayDebts(int userId) const{
        if(debts.find(userId) == debts.end()){
            cout<<"No debts for user with ID: "<<userId<<endl;
            return -1;
        }
        for(const auto& debt: debts.at(userId)){
            cout<<" - Debt: "<<debt.getDescription()
            <<", Amount: "<<debt.getAmount()<<endl;
        }
    }

    void saveToFile(const string& fileName){
        ofstream file(fileName);
        file<<toJson().dump(4);
        file.close();
    }

    void loadFromFile(const string& fileName){
        ifstream file(fileName);
        if(file.is_open()){
            json j;
            file>>j;
            fromJson(j);
            file.close();
        }
    }
};