#include <iostream>
#include <string>
using namespace std;

enum PaymentType
{
    Cash = 1,
    Card,
    BankTransfer
};

struct Payment
{
    int paymentNumber;
    PaymentType paymentType;
    string cardNumber;
    string bankAccount;

    void setPayment(int number, PaymentType type, const string& card = "", const string& bank = "") {
        paymentNumber = number;
        paymentType = type;
        if (paymentType == Card) cardNumber = card;
        if (paymentType == BankTransfer) bankAccount = bank;
    }

    void displayPayment() const
    {
        cout << "\nPayment " << paymentNumber << ":\n";
        cout << "Type: ";
        if (paymentType == Cash) cout << "Cash";
        else if (paymentType == Card) cout << "Card";
        else if (paymentType == BankTransfer) cout << "Bank Transfer";
        cout << "\nDetails: ";
        if (paymentType == Card) cout << "Card Number: " << cardNumber;
        else if (paymentType == BankTransfer) cout << "Bank Account: " << bankAccount;
        cout << endl;
    }

    PaymentType getPaymentType() const
    {
        return paymentType;
    }
};

int main()
{
    const int numberOfPayments = 2;
    Payment payments[numberOfPayments];
    int cashCount = 0, cardCount = 0, bankTransferCount = 0;

    for (int i = 0; i < numberOfPayments; ++i) {
        int paymentType;
        string cardNumber, bankAccount;
        cout << "Enter data for payment " << i + 1 << ":\n";
        int paymentNumber;
        cout << "Payment number: ";
        cin >> paymentNumber;
        cout << "Payment type (1 - Cash, 2 - Card, 3 - Bank Transfer): ";
        cin >> paymentType;

        if (paymentType == Card) {
            cout << "Enter card number: ";
            cin >> cardNumber;
        } else if (paymentType == BankTransfer) {
            cout << "Enter bank account: ";
            cin >> bankAccount;
        }

        payments[i].setPayment(paymentNumber, static_cast<PaymentType>(paymentType), cardNumber, bankAccount);

        if (paymentType == Cash) cashCount++;
        else if (paymentType == Card) cardCount++;
        else if (paymentType == BankTransfer) bankTransferCount++;
    }

    for (int i = 0; i < numberOfPayments; ++i) {
        payments[i].displayPayment();
    }

    cout << "\nCash payments: " << cashCount;
    cout << "\nCard payments: " << cardCount;
    cout << "\nBank transfer payments: " << bankTransferCount << endl;

    return 0;
}