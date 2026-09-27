#include "loan.h"
#include <iostream>
#include <iomanip>

using namespace std;

void printAmortizationTable(double loan, double yearlyRate, double monthlyPayment) {
    double monthlyRate = yearlyRate / 12.0;
    double firstMonthInterest = loan * (monthlyRate / 100.0);

    // Special Case Check: Ensure monthly payment exceeds first month's interest
    if (monthlyPayment <= firstMonthInterest) {
        cout << "(Insufficient payment)\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "*****************************************************************\n";
    cout << "\tAmortization Table\n";
    cout << "*****************************************************************\n";
    cout << left << setw(8) << "Month" 
         << setw(10) << "Balance" 
         << setw(10) << "Payment" 
         << setw(8) << "Rate" 
         << setw(10) << "Interest" 
         << "Principal\n";

    // Row 0
    cout << left << setw(8) << 0 
         << "$" << setw(9) << loan 
         << setw(10) << "N/A" 
         << setw(8) << "N/A" 
         << setw(10) << "N/A" 
         << "N/A\n";

    int month = 0;
    double totalInterest = 0.0;
    double balance = loan;

    while (balance > 0) {
        month++;
        double interest = balance * (monthlyRate / 100.0);
        double actualPayment = monthlyPayment;
        double principal = 0.0;

        // Last Payment Handling
        if (balance + interest <= monthlyPayment) {
            actualPayment = balance + interest;
            principal = balance;
            balance = 0.0;
        } else {
            principal = monthlyPayment - interest;
            balance -= principal;
        }

        totalInterest += interest;

        cout << left << setw(8) << month 
             << "$" << setw(9) << balance 
             << "$" << setw(9) << actualPayment 
             << setw(8) << monthlyRate 
             << "$" << setw(9) << interest 
             << "$" << principal << "\n";
    }

    cout << "*****************************************************************\n\n";
    cout << "It takes " << month << " months to pay off the loan.\n";
    cout << "Total interest paid is: $" << totalInterest << "\n";
}