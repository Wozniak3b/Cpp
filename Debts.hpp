/**
 * Author: Jakub Wozniak 2025
 * @file Debts.hpp
 * @brief This file contains the definition of the Debts class.
 */
#include <string>
#include <cmath>
#include <sstream> // Added for std::istringstream
using std::string;

namespace jw{

/**
 * @class Debt
 * @brief Represents a debt with an ID, description, amount, receiver, and payment status.
 */
class Debt{
private:
    int m_id; ///< ID of the debt
    string m_description; ///< Description of the debt
    float m_amount; ///< Amount of the debt
    string m_receiver; ///< Receiver of the debt
    bool m_paid; ///< Payment status of the debt
public:
    /**
     * @brief Default constructor for Debt.
     */
    Debt() : m_id(0), m_description(""), m_amount(0.0), m_receiver(""), m_paid(false) {}

    /**
     * @brief Parameterized constructor for Debt.
     * @param id ID of the debt
     * @param desc Description of the debt
     * @param amt Amount of the debt
     * @param receiver Receiver of the debt
     * @param paid Payment status of the debt (default is false)
     */
    Debt(int id, const string& desc, float amt, const string& receiver, bool paid=false)
        : m_id(id), m_description(desc), m_amount(std::round(amt*100.0)/100.0)
        , m_receiver(receiver), m_paid(paid) {}

    /**
     * @brief Gets the ID of the debt.
     * @return ID of the debt
     */
    int getId() const {
        return m_id;
    }
    
    /**
     * @brief Gets the amount of the debt.
     * @return Amount of the debt
     */
    float getAmount() const {
        return m_amount;
    }

    /**
     * @brief Gets the description of the debt.
     * @return Description of the debt
     */
    string getDescription() const {
        return m_description;
    }

    /**
     * @brief Gets the receiver of the debt.
     * @return Receiver of the debt
     */
    string getReceiver() const {
        return m_receiver;
    }

    /**
     * @brief Checks if the debt is paid.
     * @return True if the debt is paid, false otherwise
     */
    bool isPaid() const {
        return m_paid;
    }

    /**
     * @brief Marks the debt as paid.
     */
    void markAsPaid() {
        m_paid = true;
    }

    /**
     * @brief Serializes the debt to a string.
     * @return Serialized string representation of the debt
     */
    string serialize() const {
        return std::to_string(m_id) + "," + m_description + "," 
        + std::to_string(m_amount)+ "," + m_receiver+ "," + (m_paid ? "1" : "0");
    }

    /**
     * @brief Deserializes a string to a Debt object.
     * @param data Serialized string representation of the debt
     * @return Deserialized Debt object
     */
    static Debt deserialize(const string& data) {
        std::istringstream ss(data);
        std::string idStr, description, amountStr, receiver, isPaidStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, description, ',');
        std::getline(ss, amountStr, ',');
        std::getline(ss, receiver, ',');
        std::getline(ss, isPaidStr, ',');
        return Debt(std::stoi(idStr), description, 
        std::stod(amountStr), receiver, isPaidStr == "1");
    }
};

}