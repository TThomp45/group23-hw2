#include <iostream>
#include "loan.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc > 4) 
	{
		cout << "Too many arguments. Cannot pass in more than three." << endl;
		return -1;
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
					cout << "(Invalid interest rate): " << argv[i-1] << " " << argv[i] << endl;
				else
					cout << "(Invalid payment): " << argv[i-2] << " " << argv[i-1] << " " << argv[i] << endl;
				return -2;
			}
			i++;
		}
	}

	loan_amount = arguments[0];
	yearly_interest_rate = arguments[1];
	monthly_payment = arguments[2];

	if (loan_amount <= 0)
	{
		cout << "(Invalid loan amount): " << argv[1] << endl;
		return -2;
	}

	if (yearly_interest_rate < 0)
	{
		cout << "(Invalid interest rate): " << argv[1] << " " << argv[2] << endl;
		return -2;
	}

	if (monthly_payment <= 0)
	{
		cout << "(Invalid payment): " << argv[1] << " " << argv[2] << " " << argv[3] << endl;
		return -2;
	}

	// Validate sufficient payment BEFORE printing inputs
	double first_month_interest = loan_amount * (yearly_interest_rate / 12.0 / 100.0);
	if (monthly_payment <= first_month_interest)
	{
		cout << "(Insufficient payment): " << argv[1] << " " << argv[2] << " " << argv[3] << endl;
		return -3;
	}

	// Print inputs ONLY when all checks pass
	cout << "\nLoan Amount: " << loan_amount << endl;
	cout << "Interest Rate (% per year): " << yearly_interest_rate << endl;
	cout << "Monthly Payments: " << monthly_payment << endl;
	cout << endl;

	printAmortizationTable(loan_amount, yearly_interest_rate, monthly_payment);

	return 0;
}