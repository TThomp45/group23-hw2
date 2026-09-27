#include "loan.h"
#include <iostream>
#include <iomanip>

using namespace std;

void printAmortizationTable(double loan, double yearlyRate, double monthlyPayment) {
    cout << "*****************************************************************\n";
    cout << "\tAmortization Table\n";
    cout << "*****************************************************************\n";
    
    // Output headers with exact spacing matching expected output
    cout << left << setw(7) << "Month" 
         << setw(14) << "Balance" 
         << setw(12) << "Payment" 
         << setw(8) << "Rate" 
         << setw(12) << "Interest" 
         << "Principal\n";

    // Row 0 output
    cout << left << setw(7) << 0;
    cout << fixed << setprecision(2);
    cout << "$" << setw(13) << loan;
    cout << resetiosflags(ios::fixed);
    cout << left << setw(12) << "N/A" 
         << setw(8) << "N/A" 
         << setw(12) << "N/A" 
         << "N/A\n";

    int month = 0;
    double monthlyRate = yearlyRate / 12.0;
    double totalInterest = 0.0;
    double balance = loan;

    while (balance > 0) {
        month++;
        double interest = balance * (monthlyRate / 100.0);
        double actualPayment = monthlyPayment;
        double principal = 0.0;

        // Final payment check
        if (balance + interest <= monthlyPayment) {
            actualPayment = balance + interest;
            principal = balance;
            balance = 0.0;
        } else {
            principal = monthlyPayment - interest;
            balance -= principal;
        }

        totalInterest += interest;

        // Print Month
        cout << left << setw(7) << month;

        // Print Balance & Payment
        cout << fixed << setprecision(2);
        cout << "$" << setw(13) << balance 
             << "$" << setw(11) << actualPayment;

        // Print Rate (unformatted precision to output 1.5, 1, 4.16667, 0)
        cout << resetiosflags(ios::fixed) << defaultfloat;
        cout << left << setw(8) << monthlyRate;

        // Print Interest & Principal
        cout << fixed << setprecision(2);
        cout << "$" << setw(11) << interest 
             << "$" << principal << "\n";
    }

    cout << "*****************************************************************\n\n";
    cout << "It takes " << month << " months to pay off the loan.\n";
    cout << "Total interest paid is: $" << fixed << setprecision(2) << totalInterest << "\n";
}