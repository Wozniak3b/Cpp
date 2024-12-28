#include <string>
using std::string;


class User: public Database {
private:
    int id;
    string username;
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
