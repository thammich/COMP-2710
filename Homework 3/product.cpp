#include "product.h"
#include <string>
#include <iomanip>
#include <sstream>

std::string product::product_info()
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    std::string info = "Name: " + name + "\n";
    info += "Description: " + description + "\n";
    oss << price;
    info += "Price: $" + oss.str();
    return info;
}
