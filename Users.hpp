#include <string>
using std::string;


class Users{
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
};
