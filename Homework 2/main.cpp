#include <iostream>
#include <iomanip> //std:setw

using namespace std;

//pass in space-delimited arguments when you call the executable
//Example: ./a.out 1 2 3.3

int main(int argc, char * argv[])
{
	if (argc > 4)
	{
		cout << "Too many arguments. Cannot pass in more than three." << endl;
		return -1;
	}

	int i = 1;
	double loan_amount, yearly_interest_rate, monthly_payment;

	double arguments [3];

	if (argc >= 1)
	{
		while (i < argc)
		{

			try
			{
				arguments[i-1] = stod(argv[i]);
			}
			catch(const std::invalid_argument&)
			{
				if (i==1)
					cout << "(Invalid loan amount): " << argv[i] << endl;
				else if (i==2)
					cout << "(Invalid interest rate): " << argv[i-1] << " " << argv[i] << endl;
				else
					cout << "(Invalid payment): " << argv[i-2] << " " << argv[i-1] << " " << argv[i] << endl;
				return 0;
			}
			i++;
		}
	}
	loan_amount = arguments[0];
	yearly_interest_rate = arguments[1];
	monthly_payment = arguments[2];

	// initialize variables
	int month = 0;
	double monthly_interest_rate = yearly_interest_rate / 1200;
	double total_interest = 0.0;
	double balance = loan_amount;
	double principal = 0.0;
	double monthly_interest = 0.0;
	double last_payment = 0.0;

	// currency formatting
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	if (monthly_payment < 0) {
		cout << "(Invalid payment)" << endl;
		return 0;
	}

	if (balance * monthly_interest_rate >= monthly_payment) {
		cout << "(Insufficient payment)" << endl;
		return 0;
	}

	if (loan_amount < 0) {
		cout << "(Invalid loan amount): " << loan_amount << endl;
		return 0;
	}

	if (yearly_interest_rate < 0) {
		cout << "(Invalid interest rate)" << endl;
		return 0;
	}

	// table setup
	cout << "*********************************************************************" << endl;
	cout << setw(10) << "\tAmortization Table" << endl;
	cout << "*********************************************************************" << endl;
	cout << left << setw(8) << "Month" << setw(15) << "Balance" << setw(15) << "Payment" << setw(8) << "Rate" << setw(13) << "Interest" << setw(13) << "Principal" << endl;
	cout << left << setw(8) << month << "$" << setw(14) << loan_amount << setw(15) << "N/A" << setw(8) << "N/A" << setw(13) << "N/A" << setw(13) << "N/A" << endl;

	// core

	while (balance > 0) {
		month += 1;
		if (balance + (balance * monthly_interest_rate) > monthly_payment) {
			// regular case
			monthly_interest = balance * monthly_interest_rate;
			total_interest += monthly_interest;
			principal = monthly_payment - monthly_interest;
			balance -= principal;
			cout << left << setw(8) << month << "$" << setw(14) << balance << "$" <<setw(14) << monthly_payment << setw(8) << monthly_interest_rate * 100 << "$" << setw(12) << monthly_interest << "$" << setw(12) << principal << endl;
		}
		else {
			// special case: last payment
			monthly_interest = balance * monthly_interest_rate;
			total_interest += monthly_interest;
			last_payment = monthly_interest + balance;
			principal = last_payment - monthly_interest;
			balance = 0;
			cout << left << setw(8) << month << "$" << setw(14) << balance << "$" << setw(14) << last_payment << setw(8) << monthly_interest_rate * 100<< "$" << setw(12) << monthly_interest << "$" <<setw(12) << principal << endl;
		}

	}
	cout << "**********************************************************************" << endl;
	cout << "\nIt takes " << month << " month(s) to pay off the loan." << endl;
	cout << "Total interest paid is: $" << total_interest << endl;
	cout << " " << endl;
	return 0;
		


}
