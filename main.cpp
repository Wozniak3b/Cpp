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
    cout<<"Choose an option: ";
    cout<<endl;
}

void displayMenuEmpty(){
    cout<<endl;
    cout<<"2. Register"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<endl;
    cout<<"Choose an option: ";
    cout<<endl;
}

void displayUserMenu(){
    cout<<endl;
    cout<<"1. Add debt"<<endl;
    cout<<"2. Display my debts"<<endl;
    cout<<"3. Mark debt as paid"<<endl;
    cout<<"4. Logout"<<endl;
    cout<<endl;
    cout<<"Choose an option: ";
    cout<<endl;
}

int main() {
    Database db;
    bool files=true;
    if(fs::exists("users.txt") && fs::exists("debts.txt")){
        db.loadFromFile("users.txt", "debts.txt");
    } else {
        cout<<"Files not found. Starting with empty database"<<endl;
        files=false;
    }

    int choice;
    while(true){
        if(!files){
            displayMenuEmpty();
            files=true;
        } else {
            displayMenu();
        }
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
                        if(db.getUsers().size()==1 && choice==1){
                            cout<<"No other users to add debt to"<<endl;
                            break;
                        }
                        if (choice == 1) {

                            string description;
                            float amount;
                            int userId=0;
                            line;
                            cout<<"Here are all the users:"<<endl;
                            db.displayUserInfo();
                            line;
                            cout<<endl;
                            cout<<"Which user ID: ";
                            cin>>userId;

                            if(cin.fail()) {
                                cin.clear();
                                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                cout<<"Invalid input"<<endl;
                                break;
                            }

                            if(userId>db.getUsers().size() || userId<0){
                                cout<<"Invalid user ID"<<endl;
                                break;
                            }

                            cout<<"Description: ";
                            cin.ignore();
                            std::getline(cin, description);

                            cout<<"Amount: ";
                            cin>>amount;
                            if(amount<0){
                                cout<<"Amount can't be negative"<<endl;
                                break;
                            }
                            cout<<"Debt added successfully"<<endl;
                            db.addDebt(userId, description, amount,db.getUsers().at(currentUserId).getUsername());

                        } else if (choice == 2) {
                            // Display Debts
                            line;
                            db.displayDebts(currentUserId);
                        }else if(choice==3) {
                            cout<<"Debt marked as paid"<<endl;
                        }else if (choice == 4) {
                            // Logout
                            db.saveToFile("users.txt", "debts.txt");
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

            int userSize=db.getUsers().size();
            db.addUser(newUserId, username, secretKey);

            if(db.getUsers().size()>userSize){
                cout << "User registered with ID: " << newUserId << endl;
            }
            db.saveToFile("users.txt", "debts.txt");
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
