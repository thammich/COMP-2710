#include "transaction.h"
#include <string>

std::string transaction::transaction_info()
{
    std::string info = "Transaction #: " + std::to_string(transaction_number) + "\n";
    info += "Customer:\n";
    info += customer.person_info() + "\n";
    info += "Product:\n" + purchased_item.product_info() + "\n";
    info += "Quantity: " + std::to_string(quantity) + "\n";
    return info;
}
