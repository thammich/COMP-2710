//implementation code for credit_card struct here
#include "credit_card.h"
#include <string>
#include <sstream>
#include <iomanip>

using std::string;

bool credit_card::make_purchase(double purchase_amount)
{
    if (current_balance + purchase_amount <= limit)
    {
        current_balance += purchase_amount;
        return true;
    } 
    return false;
}

bool credit_card::make_payment(double payment_amount)
{
    if (payment_amount <= current_balance && payment_amount > 0)
    {
        current_balance -= payment_amount;
        return true;
    }
    return false;
}

string credit_card::credit_card_info()
{
    string info = ""; 

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    info += "Credit card number: " + std::to_string(cc_number) + "\n";
    oss << limit;
    info += "Credit Card Limit: $" + oss.str() + "\n";
    oss.str("");
    oss << current_balance;
    info += "Current Balance: $" + oss.str();

    return info;
}


