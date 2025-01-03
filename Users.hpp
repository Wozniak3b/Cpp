#include <string>
using std::string;


class User{
private:
    int id;
    string username;
    string secretKey;

    static string xorEncryptDecrypt(const string& input, char key) {
        string output = input;
        for (size_t i = 0; i < input.size(); ++i) {
            output[i] = input[i] ^ key;
        }
        return output;
    }

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
        string encryptedKey = xorEncryptDecrypt(secretKey, 'K');
        return std::to_string(id) + "," + username + "," + encryptedKey;
    }

    static User deserialize(const string& data) {
        std::istringstream ss(data);
        std::string idStr, username, encryptedKey;
        std::getline(ss, idStr, ',');
        std::getline(ss, username, ',');
        std::getline(ss, encryptedKey, ',');

        int id = std::stoi(idStr);
        string secretKey = xorEncryptDecrypt(encryptedKey, 'K');

        return User(id, username, secretKey);
    }
};
