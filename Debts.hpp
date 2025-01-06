#include <string>
#include <cmath>
using std::string;

namespace jw{

class Debt{
private:
    int m_id;
    string m_description;
    float m_amount;
    string m_receiver;
    bool m_paid;
public:
    Debt() : m_id(0), m_description(""), m_amount(0.0), m_receiver(""), m_paid(false) {}

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
        return m_paid;
    }

    void markAsPaid() {
        m_paid = true;
    }

    string serialize() const {
        return std::to_string(m_id) + "," + m_description + "," 
        + std::to_string(m_amount)+ "," + m_receiver+ "," + (m_paid ? "1" : "0");
    }

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