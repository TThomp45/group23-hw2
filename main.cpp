#include <iostream>
#include <string>
#include "loan.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc > 4) 
	{
		cout << "Too many arguments. Cannot pass in more than three." << endl;
		return 0;
	}

	int i = 1;
	double loan_amount = 0, yearly_interest_rate = 0, monthly_payment = 0;
	double arguments[3] = {0, 0, 0};

	if (argc > 1)
	{
		while (i < argc)
		{
			try
			{
				arguments[i-1] = stod(argv[i]);
			}
			catch(const std::invalid_argument&)
			{
				if (i == 1)
					cout << "(Invalid loan amount): " << argv[i] << endl;
				else if (i == 2)
					cout << "(Invalid interest rate): " << argv[1] << " " << argv[i] << endl;
				else
					cout << "(Invalid payment): " << argv[1] << " " << argv[2] << " " << argv[i] << endl;
				return 0;
			}
			i++;
		}
	}

	loan_amount = arguments[0];
	yearly_interest_rate = arguments[1];
	monthly_payment = arguments[2];

	// Check loan amount
	if (argc <= 1 || loan_amount <= 0)
	{
		cout << "(Invalid loan amount): " << (argc > 1 ? argv[1] : "") << endl;
		return 0;
	}

	// Check interest rate
	if (argc <= 2 || yearly_interest_rate < 0)
	{
		cout << "(Invalid interest rate): " << argv[1] << " " << (argc > 2 ? argv[2] : "") << endl;
		return 0;
	}

	// Check monthly payment
	if (argc <= 3 || monthly_payment <= 0)
	{
		cout << "(Invalid payment): " << argv[1] << " " << argv[2] << " " << (argc > 3 ? argv[3] : "") << endl;
		return 0;
	}

	// Check insufficient payment
	double first_month_interest = loan_amount * (yearly_interest_rate / 12.0 / 100.0);
	if (monthly_payment <= first_month_interest)
	{
		cout << "(Insufficient payment): " << argv[1] << " " << argv[2] << " " << argv[3] << endl;
		return 0;
	}

	// Call table generator directly
	printAmortizationTable(loan_amount, yearly_interest_rate, monthly_payment);

	return 0;
}