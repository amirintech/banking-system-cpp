#include <iostream>
#include <map>

using namespace std;

struct Account {
    int accountNumber{};
    string ownerName{};
    double balance{};
};

// Accounts store
map<int, Account> accountsStore{};

// Functions' prototypes
void menu();

bool accountExists(const Account &account);

void createAccount(int accountNumber, string &ownerName, double balance);

void listAccounts();

void closeAccount(int accountNumber);

void deposit(int accountNumber, double amount);

void withdraw(int accountNumber, double amount);

// Main
int main() {
    while (true) {
        menu();

        int accountNumber{};
        string ownerName{};
        double balance{};
        double amount{};

        int command{};
        cout << ">> ";
        cin >> command;
        switch (command) {
            case 1:  // Opening account
                cout << "Enter account number, owner's name, and balance respectively: ";
                cin >> accountNumber >> ownerName >> balance;
                createAccount(accountNumber, ownerName, balance);
                break;


            case 2:  // Closing account
                cout << "Enter account number: ";
                cin >> accountNumber;
                closeAccount(accountNumber);
                break;


            case 3:  // Deposit
                cout << "Enter account number and amount respectively: ";
                cin >> accountNumber >> amount;
                deposit(accountNumber, amount);
                break;


            case 4: // Withdraw
                cout << "Enter account number and amount respectively: ";
                cin >> accountNumber >> amount;
                withdraw(accountNumber, amount);
                break;


            case 5:  // List all accounts
                listAccounts();
                break;


            case 6: // Quit
                return 0;

            default :
                cout << "Error: Unknown command.";
        }
    }
}

// Functions
void menu() {
    // convert command numbers to enum
    cout << endl;
    cout << "Select a command by number:" << endl;
    cout << "===========================" << endl;
    cout << "1) Open an account" << endl;
    cout << "2) Close an account" << endl;
    cout << "3) Deposit" << endl;
    cout << "4) Withdraw" << endl;
    cout << "5) List all accounts" << endl;
    cout << "6) Quit" << endl;
}

bool accountExists(const int accountNumber) {
    return accountsStore.find(accountNumber) != accountsStore.end();
}

void createAccount(int accountNumber, string &ownerName, double balance) {
    if (accountExists(accountNumber)) {
        cout << "Error: cannot create new account, for an account with number " << accountNumber << " already exists."
             << endl;
        return;
    }

    const Account account{accountNumber, ownerName, balance};
    accountsStore[accountNumber] = account;
    cout << "Account has been created successfully." << endl;
}

void closeAccount(int accountNumber) {
    if (!accountExists(accountNumber)) {
        cout << "Error: the account number you have provided does not exist." << endl;
        return;
    }

    auto it = accountsStore.find(accountNumber);
    accountsStore.erase(it);
    cout << "Account number " << accountNumber << " has been closed and deleted from the system." << endl;
}

void deposit(int accountNumber, double amount) {
    if (!accountExists(accountNumber)) {
        cout << "Error: the account number you have provided does not exist." << endl;
        return;
    }

    if (amount <= 0)
        cout << "Error: amount should be greater than zero." << endl;

    accountsStore[accountNumber].balance += amount;
    cout << "$" << amount << " has been add to account number " << accountNumber << "." << endl;
}

void withdraw(int accountNumber, double amount) {
    if (!accountExists(accountNumber)) {
        cout << "Error: the account number you have provided does not exist." << endl;
        return;
    }

    const double availableBalance = accountsStore[accountNumber].balance;
    if (amount > availableBalance) {
        cout << "Error: Insufficient funds. This account has only $" << availableBalance << " available." << endl;
        return;
    }

    accountsStore[accountNumber].balance -= amount;
    cout << "$" << amount << " has been withdrawn from account number " << accountNumber << " and $"
         << (accountsStore[accountNumber].balance) << " is remaining." << endl;
}

void listAccounts() {
    if (accountsStore.empty()) {
        cout << "Error: there is no accounts to list." << endl;
        return;
    }

    cout << "Showing " << accountsStore.size() << " accounts:" << endl;
    cout << "================================================" << endl;

    for (const auto &bucket: accountsStore) {
        const auto &[accountNumber, ownerName, balance] = bucket.second;

        cout << ">> " << "Number: " << accountNumber << "   "
             << "Owner: " << ownerName << "   "
             << "Balance: " << balance << "   "
             << endl;
    }
}
