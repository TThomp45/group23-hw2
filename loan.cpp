#include "loan.h"
#include <iostream>
#include <iomanip>

using namespace std;

void printAmortizationTable(double loan, double yearlyRate, double monthlyPayment) {
    double monthlyRate = yearlyRate / 12.0;
    double firstMonthInterest = loan * (monthlyRate / 100.0);

    // Validate if regular payment covers monthly interest
    if (monthlyPayment <= firstMonthInterest) {
        cout << "(Insufficient payment): " << loan << " " << yearlyRate << " " << monthlyPayment << "\n";
        return;
    }

    cout << "*****************************************************************\n";
    cout << "\tAmortization Table\n";
    cout << "*****************************************************************\n";
    
    // Column header alignment
    cout << left << setw(7) << "Month" 
         << setw(14) << "Balance" 
         << setw(12) << "Payment" 
         << setw(8) << "Rate" 
         << setw(12) << "Interest" 
         << "Principal\n";

    // Month 0 row
    cout << left << setw(7) << 0;
    cout << fixed << setprecision(2);
    cout << "$" << setw(13) << loan;
    cout << resetiosflags(ios::fixed); // Reset fixed formatting for Rate column
    cout << left << setw(12) << "N/A" 
         << setw(8) << "N/A" 
         << setw(12) << "N/A" 
         << "N/A\n";

    int month = 0;
    double totalInterest = 0.0;
    double balance = loan;

    while (balance > 0) {
        month++;
        double interest = balance * (monthlyRate / 100.0);
        double actualPayment = monthlyPayment;
        double principal = 0.0;

        // Last payment calculation
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

        // Print Balance & Payment (2 decimal places)
        cout << fixed << setprecision(2);
        cout << "$" << setw(13) << balance 
             << "$" << setw(11) << actualPayment;

        // Print Rate (Default float output: 1.5, 1, 4.16667, 0)
        cout << resetiosflags(ios::fixed) << defaultfloat;
        cout << left << setw(8) << monthlyRate;

        // Print Interest & Principal (2 decimal places)
        cout << fixed << setprecision(2);
        cout << "$" << setw(11) << interest 
             << "$" << principal << "\n";
    }

    cout << "*****************************************************************\n\n";
    cout << "It takes " << month << " months to pay off the loan.\n";
    cout << "Total interest paid is: $" << fixed << setprecision(2) << totalInterest << "\n";
}