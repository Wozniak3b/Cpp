#include <string>
using std::string;


class User{
private:
    int id;
    string username;
    string secretKey;

public:
    User(){};

    User(int id, const string& username, const string& secretKey)
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
        return User(std::stoi(idStr), username, secretKey);
    }
};
