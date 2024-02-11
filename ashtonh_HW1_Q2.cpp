#include <iostream>
#include <string>

using namespace std;

// Class representing a single check
class Check{
public:
    // Default constructor
    Check(): checkNum(0), checkMemo(""), checkAmount(0){
        number++;
    }

    // Getter and setter functions for checkNum
    int get_checkNum() const{
        return checkNum;
    }

    void set_checkNum(int num){
        checkNum = num;
    }

    // Getter and setter functions for checkMemo
    const string& get_checkMemo() const{
        return checkMemo;
    }

    void set_checkMemo(const string& memo){
        checkMemo = memo;
    }

    // Getter and setter functions for checkAmount
    double get_checkAmount() const{
        return checkAmount;
    }

    void set_checkAmount(double amount){
        checkAmount = amount;
    }

    // Static function to get the total number of Check objects created
    static int getNumber(){
        return number;
    }

private:
    int checkNum;           // Check number
    string checkMemo;       // Memo associated with the check
    double checkAmount;     // Amount of the check

    // Static member to keep track of the total number of Check objects
    static int number;
};

// Initialize the static member outside the class
int Check::number = 0;

// Class representing a CheckBook
class CheckBook{
public:
    // Default constructor
    CheckBook() : balance(0), numOfChecks(0), checkLimit(N){}

    // Constructor with an initial balance
    CheckBook(double initialBalance) : balance(initialBalance), numOfChecks(0), checkLimit(N){}

    // Function to deposit an amount into the CheckBook
    void deposit(double amount){
        balance += amount;
        lastDeposit = amount;
    }

    // Function to display recent checks
    void displayChecks() const{
        cout<<"Recent Checks: "<<endl;
        for(int i = numOfChecks - 1; i>=0; --i){
            cout<<"Check #"<<checks[i].get_checkNum()<<": "<<checks[i].get_checkMemo()<<" - $"<<checks[i].get_checkAmount()<<endl;
        }
    }

    // Static function to get the total number of checks written across all CheckBooks
    static int getAllChecks(){
        return allChecks;
    }

    // Function to write a check
    bool writeCheck(double amount){
        if(numOfChecks < N && allChecks < 10 && balance >= amount){
            checks[numOfChecks].set_checkNum(allChecks + 1);
            checks[numOfChecks].set_checkAmount(amount);

            numOfChecks++;
            allChecks++;

            balance -= amount;

            return true; // Check successfully written
        } else {
            return false; // Check not written
        }
    }

private:
    // Static constant for the check limit
    static const int N = 5;

    double balance;         // Current balance in the account
    double lastDeposit;     // Amount of the last deposit
    int numOfChecks;        // Number of checks written
    const int checkLimit;   // Maximum number of checks allowed
    Check checks[N];        // Array to store checks

    // Static member to keep track of the total number of checks written across all CheckBooks
    static int allChecks;
};

// Initialize the static member outside the class
int CheckBook::allChecks = 0;

// Main function for testing CheckBook class
int main(){
    // Create two CheckBook instances with initial balances
    CheckBook cb1(1000), cb2(500);

    // Perform check writing operations for both CheckBooks
    for(int i=0; i<10; i++){
        cb1.writeCheck(150);
        cb2.writeCheck(130);
    }

    cout<<"cb1 check details"<<endl;
    cb1.displayChecks();
    cout<<"cb2 check details"<<endl;
    cb2.displayChecks();
    cout<<cb1.getAllChecks()<<endl;
    cout<<cb2.getAllChecks()<<endl;

    return 0;
}
