/**
 * Author: Jakub Wozniak 2025
 * @file Users.hpp
 * @brief This file contains the definition of the Users class.
 */
#include <string>
#include <sstream>
using std::string;

namespace jw{

/**
 * @brief Class representing a user.
 */
class User{
private:
    int m_id; ///< User ID
    string m_username; ///< Username
    string m_secretKey; ///< Secret key

    /**
     * @brief Encrypts or decrypts a string using XOR encryption.
     * @param input The input string to be encrypted or decrypted.
     * @param key The key used for XOR encryption.
     * @return The encrypted or decrypted string.
     */
    static string xorEncryptDecrypt(const string& input, char key) {
        string output = input;
        for (size_t i = 0; i < input.size(); ++i) {
            output[i] = input[i] ^ key;
        }
        return output;
    }

public:
    /**
     * @brief Default constructor.
     */
    User(): m_id(0), m_username(""), m_secretKey("") {};

    /**
     * @brief Parameterized constructor.
     * @param id User ID.
     * @param username Username.
     * @param secretKey Secret key.
     */
    User(int id, const string& username, const string& secretKey)
        : m_username(username), m_id(id), m_secretKey(secretKey) {}

    /**
     * @brief Gets the username.
     * @return The username.
     */
    string getUsername() const {
        return m_username;
    }

    /**
     * @brief Gets the user ID.
     * @return The user ID.
     */
    int getId() const {
        return m_id;
    }

    /**
     * @brief Gets the secret key.
     * @return The secret key.
     */
    string getSecretKey() const {
        return m_secretKey;
    }
    
    /**
     * @brief Serializes the user data to a string.
     * @return The serialized user data.
     */
    string serialize() const {
        string encryptedKey = xorEncryptDecrypt(m_secretKey, 'K');
        return std::to_string(m_id) + "," + m_username + "," + encryptedKey;
    }

    /**
     * @brief Deserializes a string to create a User object.
     * @param data The serialized user data.
     * @return The deserialized User object.
     */
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

}
