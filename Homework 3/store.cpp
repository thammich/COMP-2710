#include "store.h"
#include <iostream>
#include <string>

using namespace std;

static bool equal_products(const product& a, const product& b) {
    return a.name == b.name && a.description == b.description && a.price == b.price;
}
static bool equal_people(Person& a, Person& b) {
    return a.name() == b.name() && a.phone() == b.phone();
}

//Constructor
Store::Store()
: num_customers_(0), num_products_(0), num_transactions_(0)
{

}

//Getters and Setters
void Store::num_customers(int customer_count) { num_customers_ = customer_count; }
int  Store::num_customers() { return num_customers_; }

void Store::num_products(int product_count) { num_products_ = product_count; }
int  Store::num_products() { return num_products_; }

void Store::num_transactions(int transaction_count) { num_transactions_ = transaction_count; }
int  Store::num_transactions() { return num_transactions_; }

//Customer Methods
bool Store::add_customer(Person customer) {
    if (num_customers_ >= 100) return false;
    customers_[num_customers_++] = customer;
    return true;
}

bool Store::update_customer(int index, Person customer) {
    if (index < 0 || index >= num_customers_) return false;
    customers_[index] = customer;
    return true;
}

Person Store::get_customer(int index) {
    return customers_[index];
}

int Store::find_customer(Person cust) {
    for (int i = 0; i < num_customers_; i++) {
        if (equal_people(customers_[i], cust)) return i;
    }
    return -1;
}

//Product Methods
bool Store::add_product(product item) {
    if (num_customers_ >= 100) return false;
    products_[num_products_++] = item;
    return true;
}
product Store::get_product(int index) {
    return products_[index];
}

//Transaction Methods
bool Store::add_transaction(transaction ntransaction) {
    if (num_transactions_ >= 100) return false;
    transactions_[num_transactions_++] = ntransaction;
    return true;
}
transaction Store::get_transaction(int index) {
    return transactions_[index];
}

//Purchase
bool Store::make_purchase(Person cust, product item, int amount) {
    if (amount <= 0) return false;

    int cidx = find_customer(cust);
    if (cidx < 0) return false;

    int pidx = -1;
    for(int i = 0; i < num_products_; i++) {
        if (equal_products(products_[i], item)) {
            pidx = i;
            break;
        }
    }
    if (pidx < 0) return false;

    double total_cost = products_[pidx].price * amount;

    credit_card cc = customers_[cidx].person_credit_card();

    if (!cc.make_purchase(total_cost))
    {
        return false;
    }

    customers_[cidx].person_credit_card(cc);

    transaction t;
    t.transaction_number = num_transactions_ + 1;
    t.customer = customers_[cidx];
    t.purchased_item = products_[pidx];
    t.quantity = amount;

    return add_transaction(t);
    }
string Store::product_info() {
    string result = "\nProducts:\n";
    for (int i = 0; i < num_products_; i++) {
        result += products_[i].product_info();
        if (i < num_products_ - 1) {
            result += "\n";
        }
    }
    return result;
}

string Store::transaction_info() {
    string result = "\nAll Transactions:\n";
    for (int i = 0; i < num_transactions_; i++) {
        result += transactions_[i].transaction_info();
        if (i < num_transactions_ - 1) {
            result += "\n";
        }
    }
    return result;
}

string Store::customer_info() {
    string result = "Customers:\n";
    for (int i = 0; i < num_customers_; i++) {
        result += customers_[i].person_info();
        if (i < num_customers_ - 1) {
            result += "\n";
        }
    }
    return result;
}

string Store::store_info() {
    string info = "";
    info += customer_info() + "\n" + product_info() + "\n" + transaction_info();
    return info;
}

string Store::purchase_history(Person cust) {
    string result = "Purchase history for " + cust.name() + " (" + cust.phone() + "):\n";
    int count = 0;

    for (int i = 0; i < num_transactions_; i++) {
        if (equal_people(transactions_[i].customer, cust)) {
            result += "  [" + to_string(i) + "] " + transactions_[i].transaction_info() + "\n";
            count++;
        }
    }

    if (count == 0) result += "  (none)\n";
    return result;
}


