 #include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Account {
private:
    int id;
    string name;
    string pin;
    double balance;

public:
    Account(int i, string n, string p, double b) {
        id = i;
        name = n;
        pin = p;
        balance = b;
    }

    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getPin() {
        return pin;
    }

    double getBalance() {
        return balance;
    }

    void checkBalance() {
        cout << "\nCurrent Balance: " << balance << endl;
    }

    void deposit(double amount) {

        if (amount <= 0) {
            cout << "Invalid amount.\n";
            return;
        }

        balance += amount;

        cout << "Deposit Successful!\n";
        cout << "New Balance: " << balance << endl;
    }

    void withdraw(double amount) {

        if (amount <= 0) {
            cout << "Invalid amount.\n";
            return;
        }

        if (amount > balance) {
            cout << "Insufficient Balance!\n";
        }
        else {
            balance -= amount;

            cout << "Withdrawal Successful!\n";
            cout << "New Balance: " << balance << endl;
        }
    }

    void changePin(string newPin) {

        pin = newPin;

        cout << "PIN Successfully Changed!\n";
    }

    bool authenticate(string inputPin) {

        return pin == inputPin;
    }

    string toFileString() {

        return to_string(id) + "," +
               name + "," +
               pin + "," +
               to_string(balance);
    }
};



vector<Account> loadAccounts() {

    vector<Account> accounts;

    ifstream file("accounts.txt");

    string line;

    while (getline(file, line)) {

        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);

        int id = stoi(line.substr(0, pos1));

        string name =
            line.substr(pos1 + 1,
            pos2 - pos1 - 1);

        string pin =
            line.substr(pos2 + 1,
            pos3 - pos2 - 1);

        double balance =
            stod(line.substr(pos3 + 1));

        accounts.push_back(
            Account(id, name, pin, balance)
        );
    }

    file.close();

    return accounts;
}



void saveAccounts(vector<Account>& accounts) {

    ofstream file("accounts.txt");

    for (int i = 0; i < accounts.size(); i++) {

        file << accounts[i].toFileString() << endl;
    }

    file.close();
}


int findAccount(vector<Account>& accounts, string name) {

    for (int i = 0; i < accounts.size(); i++) {

        if (accounts[i].getName() == name) {

            return i;
        }
    }

    return -1;
}


int main() {

   

    vector<Account> accounts = loadAccounts();

    string name;
    string pin;

    cout << "=============================\n";
    cout << "     ATM BANKING SYSTEM\n";
    cout << "=============================\n";

    cout << "Enter Account Name: ";
    cin >> name;

    int index = findAccount(accounts, name);

    if (index == -1) {

        cout << "Account Not Found!\n";
        return 0;
    }

    cout << "Enter PIN: ";
    cin >> pin;

    if (!accounts[index].authenticate(pin)) {

        cout << "Invalid PIN!\n";
        return 0;
    }

    cout << "\nLogin Successful!\n";

    int choice;

    do {

        cout << "\n========== MENU ==========\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Change PIN\n";
        cout << "5. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        double amount;
        string newPin;

        switch (choice) {

        case 1:

            accounts[index].checkBalance();
            break;

        case 2:

            cout << "Enter Deposit Amount: ";
            cin >> amount;

            accounts[index].deposit(amount);

            saveAccounts(accounts);

            break;

        case 3:

            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            accounts[index].withdraw(amount);

            saveAccounts(accounts);

            break;

        case 4:

            cout << "Enter New PIN: ";
            cin >> newPin;

            accounts[index].changePin(newPin);

            saveAccounts(accounts);

            break;

        case 5:

            saveAccounts(accounts);

            cout << "Thank you for using ATM!\n";
            break;

        default:

            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}