#include <iostream>
#include <filesystem>
#include "Database.hpp"
using std::cout, std::endl, std::cin, std::string;
namespace fs = std::filesystem;
#define line cout<<"---------------------"<<endl;

void displayMenu(){
    cout<<endl;
    cout<<"1. Login"<<endl;
    cout<<"2. Register"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<endl;
}

void displayUserMenu(){
    cout<<endl;
    cout<<"1. Add debt"<<endl;
    cout<<"2. Display my debts"<<endl;
    cout<<"3. Logout"<<endl;
    cout<<"Choose option: ";
    cout<<endl;
}

int main() {
    Database db;

    if(fs::exists("users.txt") && fs::exists("debts.txt")){
        db.loadFromFile("users.txt", "debts.txt");
    } else {
        cout<<"Files not found. Starting with empty database"<<endl;
    }

    int choice;
    while(true){
        displayMenu();
        cin>>choice;

        if(choice==1){
            line;
            string username, secretKey;
            cout<<"Username: ";
            cin>>username;
            cout<<"Password: ";
            cin>>secretKey;

            bool loggedIn=false;
            for (const auto& [id, user] : db.getUsers()) {
                if (user.getUsername() == username && user.getSecretKey() == secretKey) {
                    loggedIn = true;
                    int currentUserId = id;
                    while (loggedIn) {
                        displayUserMenu();
                        cin >> choice;
                        if (choice == 1) {

                            string description;
                            float amount;
                            int userId=0;
                            line;
                            cout<<"Here are all the users:"<<endl;
                            db.displayUserInfo();
                            cout<<endl;
                            cout<<" Which user ID: ";
                            cin>>userId;

                            //need to add check if is int
                            if(userId>db.getUsers().size() || userId<0){
                                cout<<"Invalid user ID"<<endl;
                                break;
                            }

                            cout << "Description: ";
                            cin.ignore();
                            std::getline(cin, description);
                            cout << "Amount: ";
                            cin >> amount;
                            db.addDebt(userId, description, amount);

                        } else if (choice == 2) {
                            // Display Debts
                            line;
                            db.displayDebts(currentUserId);
                        } else if (choice == 3) {
                            // Logout
                            loggedIn = false;
                            break;
                        }
                    }
                }
            }
            if (!loggedIn) {
                line;
                cout << "Invalid username or password" << endl;
            }
        }
        else if(choice==2){
            int newUserId=0;
            for (const auto& [id, user] : db.getUsers()) {
                if(id>newUserId){
                    newUserId=id;
                }
            }
            newUserId++;

            line;
            string username, secretKey;
            cout<<"Username: ";
            cin>>username;
            cout<<"Password: ";
            cin>>secretKey;
            db.addUser(newUserId, username, secretKey);
            cout << "User registered with ID: " << newUserId << endl;
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }
    

    db.saveToFile("users.txt", "debts.txt");
    return 0;
}
