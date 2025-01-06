/**
 * Author: Jakub Wozniak 2025
 * @file Database.hpp
 * @brief This file contains the definition of the Database class which manages users and their debts.
 * 
 * This is the main class of the application which is designed for managing debts.
 * It allows adding users, adding debts for users, marking debts as paid, displaying users and their debts,
 * and saving/loading the data to/from files.
 */
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

namespace jw {

/**
 * @class Database
 * @brief Manages users and their debts.
 */
class Database {
private:
    map<int, User> users; ///< Map of user IDs to User objects.
    map<int, vector<Debt>> debts; ///< Map of user IDs to their list of debts.
    int nextDebtId=1; ///< ID to be assigned to the next debt.

    /**
     * @brief Checks if a username already exists in the database.
     * @param username The username to check.
     * @return True if the username exists, false otherwise.
     */
    bool usernameExists(const string& username) const {
        for (const auto& [id, user] : users) {
            if (user.getUsername() == username) {
                return true;
            }
        }
        return false;
    }
    
public:
    /**
     * @brief Adds a new user to the database.
     * @param id The ID of the user.
     * @param username The username of the user.
     * @param secretKey The secret key of the user.
     */
    void addUser(int id, const string& username, const string& secretKey){
        if (usernameExists(username)) {
            cout << "User with username: " << username << " already exists" << endl;
            return;
        }
        users[id]=User(id,username,secretKey);
    }

    /**
     * @brief Adds a new debt for a user.
     * @param userId The ID of the user.
     * @param description The description of the debt.
     * @param amount The amount of the debt.
     * @param receiver The receiver of the debt.
     */
    void addDebt(int userId, const string& description, float amount, const string& receiver){
        if(users.find(userId) == users.end()){
            cout<<"User with ID: "<<userId<<
            " dont exist"<<endl;
            return;
        }
        debts[userId].push_back(Debt(nextDebtId, description,amount, receiver));
    }

    /**
     * @brief Marks a debt as paid.
     * @param userId The ID of the user.
     * @param debtId The ID of the debt.
     */
    void markDebtAsPaid(int userId, int debtId) {
        if (debts.find(userId) == debts.end()) {
            cout << "No debts for user with ID: " << userId << endl;
            return;
        }
        for (auto& debt : debts[userId]) {
            if (debt.getId() == debtId) {
                debt.markAsPaid();
                cout << "Debt with ID: " << debtId << " marked as paid." << endl;
                return;
            }
        }
        cout << "Debt with ID: " << debtId << " not found." << endl;
    }

    /**
     * @brief Displays all users in the database.
     */
    void displayUsers() const {
        for (const auto& [id, user] : users) {
            cout<<"ID: "<<id<<", Name: "<< user.getUsername()
            <<", SecretKey: "<<user.getSecretKey()<<endl;
        }
    }

    /**
     * @brief Displays basic information (ID and Username) of all users in the database.
     */
    void displayUserInfo() const {
        for (const auto& [id, user] : users) {
            cout<<"ID: "<<id<<", Name: "<< user.getUsername()<<endl;
        }
    }

    /**
     * @brief Displays all debts of a user.
     * @param userId The ID of the user.
     */
    void displayDebts(int userId) const{
        if(debts.find(userId) == debts.end()){
            cout<<"No debts for user with ID: "<<userId<<endl;
            return;
        }
        for(const auto& debt: debts.at(userId)){
            cout<<" -ID: "<<debt.getId()<<", Title: "<<debt.getDescription()
            <<", Amount: "<<debt.getAmount()<<
            " zł"<<", Receiver: "<<debt.getReceiver()
            <<", Paid: "<<(debt.isPaid() ? "Yes" : "No")<<endl;
        }
    }

    /**
     * @brief Gets all users in the database.
     * @return A map of user IDs to User objects.
     */
    map<int, User> getUsers() const {
        return users;
    }

    /**
     * @brief Saves the users and debts to files.
     * @param userFile The file to save users to.
     * @param debtFile The file to save debts to.
     */
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

    /**
     * @brief Loads the users and debts from files.
     * @param userFile The file to load users from.
     * @param debtFile The file to load debts from.
     */
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
            Debt debt = Debt::deserialize(debtData);
            debts[userId].push_back(debt);
            if (debt.getId() >= nextDebtId) {
                nextDebtId = debt.getId() + 1;
            }
        }

        userIn.close();
        debtIn.close();
    }
};

}