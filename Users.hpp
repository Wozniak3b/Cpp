#include <string>
using std::string;


class User{
private:
    int m_id;
    string m_username;
    string m_secretKey;

    static string xorEncryptDecrypt(const string& input, char key) {
        string output = input;
        for (size_t i = 0; i < input.size(); ++i) {
            output[i] = input[i] ^ key;
        }
        return output;
    }

public:
    User(): id(0), username(""), secretKey("") {};

    User(int id, const string& username, const string& secretKey)
        : m_username(username), m_id(id), m_secretKey(secretKey) {}

    string getUsername() const {
        return m_username;
    }

    int getId() const {
        return m_id;
    }

    string getSecretKey() const {
        return m_secretKey;
    }
    
    //Change to text and read from text to values
    string serialize() const {
        string encryptedKey = xorEncryptDecrypt(m_secretKey, 'K');
        return std::to_string(m_id) + "," + m_username + "," + encryptedKey;
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
