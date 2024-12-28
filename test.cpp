#include <iostream>
#include "Database.hpp"
using std::cout, std::endl;

int main() {
    Database db;

    db.addUser(1, "Jan", "secret123");
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
    loadedDb.displayDebts(1);

    return 0;
}
