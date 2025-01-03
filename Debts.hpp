#include <string>
#include <cmath>
using std::string;

class Debt{
private:
    string description;
    float amount;
    string receiver;
public:
    Debt(const string& desc, float amt, const string& receiver)
        : description(desc), amount(std::round(amt*100.0)/100.0), receiver(receiver) {}

    float getAmount() const {
        return amount;
    }

    string getDescription() const {
        return description;
    }

    string getReceiver() const {
        return receiver;
    }

    string serialize() const {
        return description + "," + std::to_string(amount)+ "," + receiver;
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
