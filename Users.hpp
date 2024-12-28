#include <string>
using std::string;


class User{
private:
    string username;
    int id;
    string secretKey;

public:
    User(const string& username, int id, const string& secretKey)
        : username(username), id(id), secretKey(secretKey) {}

    string getUsername() const {
        return username;
    }

    int getId() const {
        return id;
    }

    string getSecretKey() const {
        return secretKey;
    }
    
    //Change to text and read from text to values
    string serialize() const {
        return std::to_string(id) + "," + username + "," + secretKey;
    }

    static User deserialize(const string& data) {
        std::istringstream ss(data);
        std::string idStr, username, secretKey;
        std::getline(ss, idStr, ',');
        std::getline(ss, username, ',');
        std::getline(ss, secretKey, ',');
        return User(std::stoi(idStr), name, secretKey);
    }
};
