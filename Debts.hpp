#include <string>
using std::string;

class Debts{
private:
    float amount;
    string description;
    bool isPaid;

public:
    Debt(float amt, const std::string& desc, bool paid)
        : amount(amt), description(desc), isPaid(paid) {}

    float getAmount() const {
        return amount;
    }

    string getDescription() const {
        return description;
    }

    bool getIsPaid() const {
        return isPaid;
    }

    void markAsPaid() {
        isPaid = true;
    }
};
