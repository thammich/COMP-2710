#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "address.h"
#include "credit_card.h"
#include "person.h"
#include "product.h"
#include "store.h"
#include "transaction.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::getline;

int main()
{
	//import from text files
	Store store1;

	credit_card credit_cards[100];
	string credit_card_names[100];
	int num_credit_cards = 0;

	ifstream credit_card_file("credit_card.txt");
	if (credit_card_file.is_open())
	{
		credit_card_file >> num_credit_cards;
		credit_card_file.ignore();

		for (int i = 0; i < num_credit_cards; i++)
		{
			getline(credit_card_file, credit_card_names[i]);
			credit_card_file >> credit_cards[i].cc_number;
			credit_card_file >> credit_cards[i].limit;
			credit_card_file >> credit_cards[i].current_balance;
			credit_card_file.ignore();
		}
			credit_card_file.close();
	}	

	ifstream people_file("people.txt");
	if (people_file.is_open())
	{
		int num_people;
		people_file >> num_people;
		people_file.ignore();

		for (int i = 0; i < num_people; i++)
		{
			Person person;
			string name;
			string phone;
			address address;

			getline(people_file, name);
			getline(people_file, phone);
			getline(people_file, address.address_line1);
			getline(people_file, address.address_line2);
			getline(people_file, address.city);
			getline(people_file, address.state);
			getline(people_file, address.zip);

			person.name(name);
			person.phone(phone);
			person.person_address(address);

			for (int j = 0; j < num_credit_cards; j++)
			{
				if (credit_card_names[j] == name)
				{
					person.person_credit_card(credit_cards[j]);
					break;
				}
			}
			store1.add_customer(person);
		}
		people_file.close();
	}

	ifstream product_file("products.txt");
	if (product_file.is_open())
	{
		int num_products;
		product_file >> num_products;
		product_file.ignore();

		for (int i = 0; i < num_products; i++)
		{
		product product;
		getline(product_file, product.name);
		getline(product_file, product.description);
		product_file >> product.price;
		product_file.ignore();

		store1.add_product(product);
		}
		product_file.close();
	}

	//add to store and other variables

	//print store info after you finish importing info
	//from text files and add them to your store
	cout << "Store info: " << endl << endl;
	cout << store1.store_info() << endl << endl;

	//make random number of random transactions	
	int random_number_of_transactions = rand() % 90 + 10;

	for (int i = 0; i < random_number_of_transactions; i++)
	{
		int random_customer = rand() % store1.num_customers();
		Person customer = store1.get_customer(random_customer);
		
		int random_product = rand() % store1.num_products();
		product item = store1.get_product(random_product);

		int quantity = rand() % 10 + 1;

		bool success = store1.make_purchase(customer, item, quantity);

		if (success)
		{
			cout << "Successfull transaction!" << endl;
			cout << "Transaction Details:" << endl;
			transaction newest = store1.get_transaction(store1.num_transactions() - 1);
			cout << newest.transaction_info() << endl;
		}
		else
		{
            cout << "Unsuccessfull transaction!" << endl;
            cout << "Transaction Details:" << endl;
            cout << "Person:" << endl;
			cout << customer.person_info() << endl;			
            cout << "Product:" << endl;
			cout << item.product_info() << endl;	
            cout << "Purchase Quantity: " << quantity << endl << endl;
		}
	}

	//print store info at the end
	cout << "Store info: " << endl << endl;
	cout << store1.store_info() << endl << endl;
}
