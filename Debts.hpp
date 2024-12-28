#include <string>
using std::string;

class Debt{
private:
    float amount;
    string description;
public:
    Debt(float amt, const std::string& desc, bool paid)
        : amount(amt), description(desc), isPaid(paid) {}

    float getAmount() const {
        return amount;
    }

    string getDescription() const {
        return description;
    }

    string serialize() const {
        return description + "," + std::to_string(amount);
    }

    static Debt deserialize(const string& data) {
        std::istringstream ss(data);
        std::string description, amountStr;
        std::getline(ss, description, ',');
        std::getline(ss, amountStr, ',');
        return Debt(description, std::stod(amountStr));
    }
}
