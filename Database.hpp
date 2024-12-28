#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "Users.hpp"
#include "Debts.hpp"

using std::vector, std::string, std::map;

class Database {
private:
    vector<User> users;
    map<int, vector<Debts>> userDebts;

public:
    void addUser(const string& user) {
        users.push_back(user);
    }

    void removeUser(const string& user) {
        auto it = std::find(users.begin(), users.end(), user);
        if (it != users.end()) {
            int index = std::distance(users.begin(), it);
            users.erase(it);
            userDebts.erase(index);
        }
    }

    void addDebt(int userId, const Debts& debt) {
        userDebts[userId].push_back(debt);
    }
};