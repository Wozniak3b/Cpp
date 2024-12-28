#include <string>
using std::string;

class Debt{
private:
    string description;
    float amount;
public:
    Debt(const string& desc, float amt)
        : description(desc), amount(amt) {}

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
};
