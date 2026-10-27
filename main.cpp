#include <iostream>
#include <vector>
#include <cctype>
#include <string>

using namespace std;

class Account {
    string name;
    inline static vector<string> names;
    vector<double> transactions;
    int transactions_amount = 0;
    double balance = 0;

public:
    Account(string n = "unknown") {
        name = n;
        names.push_back(n);
    }

    static bool chack_name(string n) {
        for (int i = 0; i < names.size(); i++) {
            if (n == names[i])
                return true;
        }
        return false;
    }

    static int chack_obj(string n) {
        for (int i = 0; i < names.size(); i++) {
            if (n == names[i])
                return i;
        }
        return -1;
    }

    void addtransaction(double tr) {
        transactions.push_back(tr);
        balance += tr;
        transactions_amount++;

        if (tr > 0)
            cout << "Deposit is done successfully" << endl;
        else
            cout << "Withdraw is done successfully" << endl;
    }

    void withdraw(double tr) {
        if (tr <= 0) {
            cout << "Sorry, transaction can't be done\n" << endl;
            return;
        }

        if (tr > balance) {
            cout << "Sorry, transaction can't be done\n" << endl;
            return;
        }

        if (tr <= balance) {
            cout << "The balance before the withdraw: \n" << balance << endl;
            addtransaction(-tr);
            cout << "The balance after the withdraw: \n" << balance << endl;
        }
    }

    void show() {
        cout << "Name: " << name << endl;

        for (int i = 0; i < transactions.size(); i++) {
            cout << "Transaction (" << i + 1 << "): "
                 << transactions[i] << "   ";
        }

        cout << "\nThe amount of transactions: \n"
             << transactions_amount << endl;
        cout << "The Total balance: \n" << balance << endl;
    }
};

int main() {
    char chos;
    string name;
    vector<Account> acc;

    while (true) {
        while (true) {
            cout << "Welcome to the bank simulator" << endl;
            cout << "Do you have an account? (Enter x to exit)" << endl;
            cin >> chos;

            if (chos == 'n' || chos == 'N') {
                cout << "Enter your name to make an account" << endl;
                cin >> name;

                if (Account::chack_name(name) == true) {
                    cout << "Sorry the name is already taken\n";
                    cout << "Try another one\n" << endl;
                    continue;
                } else if (Account::chack_name(name) == false) {
                    acc.push_back(name);
                    break;
                }
            } else if (chos == 'y' || chos == 'Y') {
                cout << "Enter your account name" << endl;
                cin >> name;

                if (Account::chack_name(name) == true) {
                    cout << "Welcome " << name << endl;

                    while (true) {
                        string ope;
                        cout << "What operations you want to make\n" << endl;
                        cout << "Withdraw = 'wi'   deposit = 'de'   "
                                "show = 'sh'   logout = 'log'"
                             << endl;
                        cin >> ope;

                        for (int i = 0; i < ope.length(); i++) {
                            ope[i] = static_cast<char>(
                                tolower(static_cast<unsigned char>(ope[i])));
                        }

                        double num;

                        if (ope == "de") {
                            cout << "Enter the deposit amount" << endl;
                            cin >> num;

                            if (num > 0) {
                                acc[Account::chack_obj(name)].addtransaction(num);
                            } else {
                                cout << "Sorry deposit cant be done\n" << endl;
                                continue;
                            }
                        } else if (ope == "wi") {
                            cout << "Enter the withdraw amount" << endl;
                            cin >> num;
                            acc[Account::chack_obj(name)].withdraw(num);
                        } else if (ope == "sh") {
                            acc[Account::chack_obj(name)].show();
                        } else if (ope == "log") {
                            cout << "Exiting from " << name
                                 << " Account...\n" << endl;
                            break;
                        } else {
                            cout << "Invalid input or unknown operation\n" << endl;
                            continue;
                        }
                    }
                } else {
                    cout << "Sorry, there is no such name\n" << endl;
                }
            } else if (chos == 'x' || chos == 'X') {
                return 0;
            } else {
                cout << "Sorry, wrong input please try again" << endl;
            }
        }
    }
}
