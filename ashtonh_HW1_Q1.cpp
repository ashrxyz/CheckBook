#include <iostream>
#include <string>

using namespace std;

// Defining the Check struct
struct Check{
    int checkNum;          // Check number
    string checkMemo;      // Memo associated with the check
    double checkAmount;    // Amount of the check
};

// Defining the CheckBook class
class CheckBook{
public:
    // Default constructor
    CheckBook(): balance(0), numOfChecks(0), checkLimit(5){}

    // Constructor with initial balance
    CheckBook(double initialBalance): balance(initialBalance), numOfChecks(0), checkLimit(5){}

    // Function to deposit money into the account
    void deposit(double amount){
        balance += amount;
        lastDeposit = amount;
    }

    // Function to display recent checks
    void displayChecks() const{
        cout<<"Recent Checks: "<<endl;
        for(int i=numOfChecks - 1; i>=0; --i){
            cout<<"Check #"<<checks[i].checkNum<<": "<<checks[i].checkMemo<<" - $"<<checks[i].checkAmount<<endl;
        }
    }

    // Function to write a check
    bool writeCheck(double amount){
        if(amount<=balance){
            cout<<"Enter Check Memo: ";
            cin>>checks[numOfChecks].checkMemo;

            checks[numOfChecks].checkNum = numOfChecks + 1;

            checks[numOfChecks].checkAmount = amount;

            balance -= amount;
            ++numOfChecks;

            cout<<"Check successfully written."<<endl;

            return true;
        } else {
            cout<<"Unable to write check."<<endl;
            return false;
        }
    }

    // Getter function for balance
    double getBalance() const{
        return balance;
    }

private:
    double balance;        // Current balance in the account
    double lastDeposit;    // Amount of the last deposit
    int numOfChecks;       // Number of checks written
    const int checkLimit;  // Maximum number of checks allowed
    Check checks[5];       // Array to store checks
};

// Main function
int main(){
    // Create a CheckBook object with an initial balance of $1000
    CheckBook myCheckBook(1000);

    // Display initial checks
    myCheckBook.displayChecks();

    // Deposit $500
    myCheckBook.deposit(500);
    cout<<"Deposited $500. Current Balance: $"<<myCheckBook.getBalance()<<endl;

    // Write a check of $200
    myCheckBook.writeCheck(200);

    // Display checks after writing
    myCheckBook.displayChecks();

    // Try to write a check of $1000 (should fail)
    myCheckBook.writeCheck(1000);

    // Display final checks and balance
    myCheckBook.displayChecks();
    cout<<"Final Balance: $"<<myCheckBook.getBalance()<<endl;

    return 0;
}
