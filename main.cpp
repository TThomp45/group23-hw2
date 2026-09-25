#include <iostream>
#include "loan.h"

using namespace std;

//pass in space-delimited arguments when you call the executable
//Example: ./a.out 1 2 3.3
int main( int argc, char * argv[] )
{
	if (argc > 4) 
	{
		cout << "Too many arguments. Cannot pass in more than three." << endl;
		return -1;
	}

	int i = 1;
	double loan_amount, yearly_interest_rate, monthly_payment;

	double arguments [3] = {0, 0, 0};   // start at 0 so missing values are caught below

	if (argc > 1)
	{
		while ( i < argc )
		{

			try
			{
				arguments[i-1] = stod(argv[i]);
			}
			catch(const std::invalid_argument&)
			{
				if(i==1)
					cout << "(Invalid loan amount): " << argv[i] << endl;
				else if (i==2)
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

	// Check the loan amount (must be more than 0)
	if (loan_amount <= 0)
	{
		cout << "(Invalid loan amount)" << endl;
		return -2;
	}

	// Check the interest rate (0% is allowed, negative is not)
	if (yearly_interest_rate < 0)
	{
		cout << "(Invalid interest rate)" << endl;
		return -2;
	}

	// Check the monthly payment (must be more than 0)
	if (monthly_payment <= 0)
	{
		cout << "(Invalid payment)" << endl;
		return -2;
	}

	// The payment has to be bigger than the first month's interest,
	// otherwise the loan would never get paid off
	double first_month_interest = loan_amount * (yearly_interest_rate / 12 / 100);
	if (monthly_payment <= first_month_interest)
	{
		cout << "(Insufficient payment)" << endl;
		return -3;
	}

	// Show the inputs like the sample in the PDF
	cout << endl;
	cout << "Loan Amount: " << loan_amount << endl;
	cout << "Interest Rate (% per year): " << yearly_interest_rate << endl;
	cout << "Monthly Payments: " << monthly_payment << endl;
	cout << endl;

	printAmortizationTable(loan_amount, yearly_interest_rate, monthly_payment);

	return 0;
}
