// Author: Ashton Herrick
// Program: HW2, Q2
// Date Created: 2/20/2024
// Date Last Modified: 2/23/2024
//
// Problem:
// To create a program that simulates a checkbook. The program must include a struct, a class with multiple functions, and a test function to verify the work being done.
// The program developed should show checks in chronological order, the check memo, and how much the check is issued for.

#include <iostream>
#include <string>
#include <cstdlib> // to use the rand feature

using namespace std;

// Structure representing a check
struct Check{
    int checkNum;           // Check number
    string checkMemo;       // Memo assigned to the check
    float checkAmount;      // Amount of the check
};

// Overload operator to compare Check object with a float
bool operator>(const Check& check, float amount){
    return check.checkAmount > amount;
}

// Overloaded operator to display Check displays
ostream& operator<<(ostream& os, const Check& check){
    os<<"checkNum: "<<check.checkNum<<", checkMemo: "<<check.checkMemo<<", checkAmount: "<<check.checkAmount;
    return os;
}

// Class representing a CheckBook
class CheckBook{
private:
    float balance;          // Current balance of the checkbook
    Check* chkPtr;          // Pointer to an array of Check objects
    float lastDeposit;      // Amount of the last deposit
    int numOfChecks;        // Number of checks written
    int checkBookSize;      // Number of checks the checkbook can hold

public:
    // Default constructor
    CheckBook(): balance(0), lastDeposit(0), numOfChecks(0), checkBookSize(4){
        chkPtr = new Check[checkBookSize];
    }

    // Constructor with initial balance
    CheckBook(float initialBalance): balance(initialBalance), lastDeposit(0), numOfChecks(0), checkBookSize(2){
        chkPtr = new Check[checkBookSize];
    }

    // Destructor
    ~CheckBook(){
        delete[] chkPtr;
    }

    // Copy constructor
    CheckBook(const CheckBook& other): balance(other.balance), lastDeposit(other.lastDeposit), numOfChecks(other.numOfChecks), checkBookSize(other.checkBookSize){
        chkPtr = new Check[checkBookSize];
        for(int i=0; i<checkBookSize; ++i){
            chkPtr[i] = other.chkPtr[i];
        }
    }

    // Assignment operator
    CheckBook& operator=(const CheckBook& other){
        if(this != &other){
            delete[] chkPtr;

            balance = other.balance;
            lastDeposit = other.lastDeposit;
            numOfChecks = other.numOfChecks;
            checkBookSize = other.checkBookSize;

            chkPtr = new Check[checkBookSize];
            for(int i=0; i<checkBookSize; ++i){
                chkPtr[i] = other.chkPtr[i];
            }
        }
        return *this;
    }

    // Getter for balance
    float getBalance()const{
        return balance;
    }

    // Setter for balance
    void setBalance(float newBalance){
        balance = newBalance;
    }

    // Getter for lastDeposit
    float getLastDeposit()const{
        return lastDeposit;
    }

    // Setter for lastDeposit
    void setLastDeposit(float newLastDeposit){
        lastDeposit = newLastDeposit;
    }

    // Getter for numOfChecks
    int getNumOfChecks()const{
        return numOfChecks;
    }

    // Setter for numOfChecks
    void setNumOfChecks(int newNumOfChecks){
        numOfChecks = newNumOfChecks;
    }

    // Getter for checkBookSize
    int getCheckBookSize()const{
        return checkBookSize;
    }

    // Setter for checkBookSize
    void setCheckBookSize(int newCheckBookSize){
        checkBookSize = newCheckBookSize;
    }

    // Function to deposit an amount
    void deposit(float amount){
        balance += amount;
        lastDeposit = amount;
    }

    // Function to write a check
    bool writeCheck(Check c_amount){
        if(c_amount > balance){
            return false;
        }

        if(numOfChecks >= checkBookSize/2){
            int newCheckBookSize = 2 * checkBookSize;
            Check* newChkPtr = new Check[newCheckBookSize];

            for(int i=0; i<checkBookSize; ++i){
                newChkPtr[i] = chkPtr[i];
            }

            delete[] chkPtr;

            chkPtr = newChkPtr;
            checkBookSize = newCheckBookSize;

            cout<<"Warning: A new check book has been ordered. Check array doubled."<<endl;
        }

        // List of memo options
        string memoList[] = {"Manga", "Hair Salon", "Movie Theater", "Sushi", "Taco Bell", "Gas Station", "Clothing"};
        int memoIndex = rand() % (sizeof(memoList) / sizeof(memoList[0]));
        c_amount.checkMemo = memoList[memoIndex];

        // Assign random memo and updating the check details
        c_amount.checkNum = ++numOfChecks;
        balance -= c_amount.checkAmount;

        if(numOfChecks <= checkBookSize){
            chkPtr[numOfChecks - 1] = c_amount;
        }

        return true;
    }

    // Function to display all checks
    void displayChecks()const{
        for(int i = numOfChecks - 1; i>=0; --i){
            cout<<chkPtr[i]<<endl;
        }
    }
};

// Function to test check writing
void checkTest(CheckBook& checkBook, float initialBalance);

int main(){
    CheckBook myCheckBook;

    float initialBalance = 100.0;

    checkTest(myCheckBook, initialBalance);

    return 0;
}

// Function to test check writing by taking away the balance
void checkTest(CheckBook& checkBook, float initialBalance){
        checkBook.setBalance(initialBalance);

        while(checkBook.getBalance()>0){
            Check newCheck;
            newCheck.checkAmount = rand() % 20 + 1;
            checkBook.writeCheck(newCheck);
        }

        cout<<"Checks after balance is exhuasted:"<<endl;
        checkBook.displayChecks();
}