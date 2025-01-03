#include <string>
#include <cmath>
using std::string;

class Debt{
private:
    string m_description;
    float m_amount;
    string m_receiver;
public:
    Debt(const string& desc, float amt, const string& receiver)
        : m_description(desc), m_amount(std::round(amt*100.0)/100.0), m_receiver(receiver) {}

    float getAmount() const {
        return m_amount;
    }

    string getDescription() const {
        return m_description;
    }

    string getReceiver() const {
        return m_receiver;
    }

    string serialize() const {
        return m_description + "," + std::to_string(m_amount)+ "," + m_receiver;
    }

    static Debt deserialize(const string& data) {
        std::istringstream ss(data);
        std::string description, amountStr, receiver;
        std::getline(ss, description, ',');
        std::getline(ss, amountStr, ',');
        std::getline(ss, receiver, ',');
        return Debt(description, std::stod(amountStr), receiver);
    }
};
