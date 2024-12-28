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
                            cout << "Description: ";
                            std::getline(cin, description);
                            cout << "Amount: ";
                            cin >> amount;
                            db.addDebt(userId, description, amount);

                        } else if (choice == 2) {
                            // Display Debts
                            db.displayDebts(currentUserId);
                        } else if (choice == 3) {
                            // Logout
                            loggedIn = false;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    db.saveToFile("users.txt", "debts.txt");

    /*db.addUser(1, "Jan", "secret123");
    db.addUser(2, "Anna", "secret456");

    db.addDebt(1, "Zakup laptopa", 3500.00);
    db.addDebt(1, "Rachunek za prąd", 150.75);
    db.addDebt(2, "Pożyczka od kolegi", 500.00);

    cout<<"Użytkownicy:"<<endl;
    db.displayUsers();

    cout<<"\nDługi użytkownika Jan (ID: 1):"<<endl;
    db.displayDebts(1);

    db.saveToFile("users.txt", "debts.txt");

    Database loadedDb;
    loadedDb.loadFromFile("users.txt", "debts.txt");

    cout<<"\nDane po odczycie z plików:"<<endl;
    loadedDb.displayUsers();
    loadedDb.displayDebts(1);*/

    return 0;
}
