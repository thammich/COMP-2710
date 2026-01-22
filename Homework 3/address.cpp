//implementation code for address struct here
#include "address.h"
#include <string>

using std::string;

string address::address_info()
{
    string info = "";
    
    info += address_line1 + "\n";
    if (!address_line2.empty())
    {
        info += address_line2 + "\n";
    }
    else
    {
        info += "\n";
    }
    info += city + "\n";
    info += state + "\n";
    info += zip + "\n";

    return info;
}