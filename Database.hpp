#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "Users.hpp"
#include "Debts.hpp"

using std::string, std::ofstream, std::ifstream, std::map,
std::vector, std::cout, std::endl;

class Database {
private:
    map<int, User> users;
    map<int, vector<Debt>> debts;

    bool usernameExists(const string& username) const {
        for (const auto& [id, user] : users) {
            if (user.getUsername() == username) {
                return true;
            }
        }
        return false;
    }
    
public:
    void addUser(int id, const string& username, const string& secretKey){
        if (usernameExists(username)) {
            cout << "User with username: " << username << " already exists" << endl;
            return;
        }
        users[id]=User(id,username,secretKey);
    }

    void addDebt(int userId, const string& description, float amount){
        if(users.find(userId) == users.end()){
            cout<<"User with ID: "<<userId<<
            " dont exist"<<endl;
            return;
        }
        debts[userId].push_back(Debt(description,amount));
    }

    void displayUsers() const {
        for (const auto& [id, user] : users) {
            cout<<"ID: "<<id<<", Name: "<< user.getUsername()
            <<", SecretKey: "<<user.getSecretKey()<<endl;
        }
    }

    void displayUserInfo() const {
        for (const auto& [id, user] : users) {
            cout<<"ID: "<<id<<", Name: "<< user.getUsername()<<endl;
        }
    }

    void displayDebts(int userId) const{
        if(debts.find(userId) == debts.end()){
            cout<<"No debts for user with ID: "<<userId<<endl;
            return;
        }
        for(const auto& debt: debts.at(userId)){
            cout<<" - Title: "<<debt.getDescription()
            <<", Amount: "<<debt.getAmount()<<
            " zł"<<endl;
        }
    }

    map<int, User> getUsers() const {
        return users;
    }

    void saveToFile(const string& userFile, const string& debtFile){
        ofstream userOut(userFile);
        ofstream debtOut(debtFile);

        for (const auto& [id, user] : users) {
            userOut<<user.serialize()<<endl;
        }

        for (const auto& [userId, debtList] : debts) {
            for (const auto& debt : debtList) {
                debtOut<<userId<<":"<<debt.serialize()<<endl;
            }
        }

        userOut.close();
        debtOut.close();
    }

    void loadFromFile(const string& userFile, const string& debtFile){
        users.clear();
        debts.clear();

        ifstream userIn(userFile);
        ifstream debtIn(debtFile);

        string line;
        while (std::getline(userIn, line)) {
            User user = User::deserialize(line);
            users[user.getId()] = user;
        }

        while (std::getline(debtIn, line)) {
            std::istringstream ss(line);
            string userIdStr, debtData;
            
            //Separating userId from debt data
            std::getline(ss, userIdStr, ':');
            std::getline(ss, debtData);

            int userId = std::stoi(userIdStr);
            debts[userId].push_back(Debt::deserialize(debtData));
        }

        userIn.close();
        debtIn.close();
    }
};