#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Transaction structure for stack
struct Transaction {
    string type; // Deposit or Withdraw
    double amount;
};

// Account node for Linked List
class Account {
public:
    int accNo;
    string name;
    string type;
    double balance;
    stack<Transaction> history; // Stack to store transaction history
    Account* next; // Pointer to next node (Linked List)

    Account(int a, string n, string t, double b) {
        accNo = a;
        name = n;
        type = t;
        balance = b;
        next = nullptr;
    }

    void deposit(double amount) {
        balance += amount;
        history.push({"Deposit", amount});
        cout << "Amount Deposited Successfully!\n";
    }

    void withdraw(double amount) {
        if (amount > balance)
            cout << "Insufficient Balance!\n";
        else {
            balance -= amount;
            history.push({"Withdraw", amount});
            cout << "Amount Withdrawn Successfully!\n";
        }
    }

    void display() {
        cout << "\nAccount No: " << accNo
             << "\nName: " << name
             << "\nType: " << type
             << "\nBalance: " << balance
             << "\n---------------------------";
    }

    void showTransactions() {
        if (history.empty()) {
            cout << "No Transactions yet!\n";
            return;
        }
        cout << "\nRecent Transactions:\n";
        stack<Transaction> temp = history;
        while (!temp.empty()) {
            cout << temp.top().type << " : Rs. " << temp.top().amount << endl;
            temp.pop();
        }
    }
};

// Linked List class
class Bank {
private:
    Account* head;
    int accCounter;

public:
    Bank() {
        head = nullptr;
        accCounter = 1001;
    }

    void createAccount() {
        string name, type;
        double balance;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Account Type (Saving/Current): ";
        cin >> type;
        cout << "Enter Initial Balance: ";
        cin >> balance;

        Account* newAcc = new Account(accCounter++, name, type, balance);
        newAcc->next = head;
        head = newAcc;
        cout << "Account Created Successfully! Account No: " << newAcc->accNo << endl;
    }

    Account* searchAccount(int acc) {
        Account* temp = head;
        while (temp != nullptr) {
            if (temp->accNo == acc)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void depositMoney() {
        int acc;
        double amt;
        cout << "Enter Account No: ";
        cin >> acc;
        Account* accPtr = searchAccount(acc);
        if (accPtr != nullptr) {
            cout << "Enter Amount to Deposit: ";
            cin >> amt;
            accPtr->deposit(amt);
        } else {
            cout << "Account Not Found!\n";
        }
    }

    void withdrawMoney() {
        int acc;
        double amt;
        cout << "Enter Account No: ";
        cin >> acc;
        Account* accPtr = searchAccount(acc);
        if (accPtr != nullptr) {
            cout << "Enter Amount to Withdraw: ";
            cin >> amt;
            accPtr->withdraw(amt);
        } else {
            cout << "Account Not Found!\n";
        }
    }

    void displayAll() {
        Account* temp = head;
        if (temp == nullptr) {
            cout << "No Accounts Found!\n";
            return;
        }
        while (temp != nullptr) {
            temp->display();
            temp = temp->next;
        }
    }

    void showHistory() {
        int acc;
        cout << "Enter Account No: ";
        cin >> acc;
        Account* accPtr = searchAccount(acc);
        if (accPtr != nullptr) {
            accPtr->showTransactions();
        } else {
            cout << "Account Not Found!\n";
        }
    }
};

int main() {
    Bank bank;
    int choice;

    while (true) {
        cout << "\n===== MINI BANKING SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Display All Accounts\n";
        cout << "5. Show Transaction History\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.depositMoney();
                break;
            case 3:
                bank.withdrawMoney();
                break;
            case 4:
                bank.displayAll();
                break;
            case 5:
                bank.showHistory();
                break;
            case 6:
                cout << "Thank you for using our banking system!\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

