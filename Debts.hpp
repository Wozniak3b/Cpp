#include <string>
#include <cmath>
using std::string;

class Debt{
private:
    int m_id;
    string m_description;
    float m_amount;
    string m_receiver;
    bool m_paid;
public:
    Debt(int id, const string& desc, float amt, const string& receiver, bool paid=false)
        : m_id(id), m_description(desc), m_amount(std::round(amt*100.0)/100.0)
        , m_receiver(receiver), m_paid(paid) {}

    int getId() const {
        return m_id;
    }
    
    float getAmount() const {
        return m_amount;
    }

    string getDescription() const {
        return m_description;
    }

    string getReceiver() const {
        return m_receiver;
    }

    bool isPaid() const {
        return m_isPaid;
    }

    void markAsPaid() {
        m_isPaid = true;
    }

    string serialize() const {
        return std::to_string(m_id) + "," + m_description + "," 
        + std::to_string(m_amount)+ "," + m_receiver+ "," + (m_isPaid ? "1" : "0");
    }

    static Debt deserialize(const string& data) {
        std::istringstream ss(data);
        std::string idStr, description, amountStr, receiver, isPaidStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, description, ',');
        std::getline(ss, amountStr, ',');
        std::getline(ss, receiver, ',');
        std::getline(ss, isPaidStr, ',');
        return Debt(std::stoi(idStr), description, std::stod(amountStr), receiver, isPaidStr == "1");
    }
};
