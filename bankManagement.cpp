#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
enum TransactionType{DEPOSIT,WITHDRAW};
enum AccountType{SAVINGS,CURRENT};
const int max_customers=20;

int genAccountNo(string );

class Customer{
    int customerId;
    string name;
    string address;
    string contactNo;
public:
    Customer( string n, string addr, string contact): name(n), address(addr), contactNo(contact) {}
    Customer(){}
    string getContactNo() const{
        return contactNo;
    }
    string getName() const{
        return name;
    }
    string getAddress() const{
        return address;
    }
    void setId(int id){
        customerId=id;
    }


};
class Account{
    int accountPin;
    int accountNo;
    float balance;  
    AccountType accountType;
public:
    Account(int accn,float b,AccountType t,int p):accountNo(accn),balance(b),accountType(t),accountPin(p){}
    Account (){}
    void setBalance(float b){
        balance=b;
    }
    float getBalance(){
        return balance;
    }
    int getAccountNo(){
        return accountNo;
    }
    int getAccountPin(){
        return accountPin;
    }
    void updateBalance(float b, TransactionType t){
        if(t==DEPOSIT){
            balance=balance+b;
            cout<<"Deposited, current account balance is: "<<getBalance()<<endl;
        }
        else{
            balance=balance-b;
            cout<<"Withdrawn, current account balance is: "<<getBalance()<<endl;
        }
    }

};
// class Transaction{
//     //string transactionID;
//     float amount;    
//     TransactionType transactionType;
// public:
//     Transaction(/*string id,*/float a, TransactionType t):/*transactionID(id),*/amount(a), transactionType(t){ }
//     Transaction(){}
//     void setAmount(int amt){
//         amount=amt;
//     }
// };
class Bank{
    Customer customers[max_customers];
    Account accounts[max_customers];
    // Transaction transactions[max_customers*4];
    int totalCustomers=0;
    int totalTransaction=0;

public:
    Bank(){}
    void accountOpen(Customer c ,AccountType t,int pin){
        if(t==SAVINGS){
        totalCustomers++;
        if(totalCustomers>=max_customers){
            cout<<"Max amount of customers reached.";
        }
        else{
        int accountNo=genAccountNo(c.getContactNo());
        Account newAccount(accountNo,0.00,t,pin);
        accounts[totalCustomers-1]=newAccount;
        customers[totalCustomers-1]=c;
        c.setId(totalCustomers);
        cout<<"Account created\nAccount number "<<accountNo<<"\nCustomer ID(REMEMBER IT): "<<totalCustomers<<endl;
        cout << "Customer added: " << customers[totalCustomers-1].getName() << " | ID: " << totalCustomers << endl;
        }
        }
        else{

        }
    }
    void displayCustomerInfo(int id){
        cout<<"Info of customer is as follows \n";
        cout<<"Customer name: "<<customers[id-1].getName()<<endl;    
        cout<<"Customer address: "<<customers[id-1].getAddress()<<endl;
        cout<<"Customer contact number: "<<customers[id-1].getContactNo()<<endl;
       
    }
    void accountBalance(int id){
        int accno;
        cout<<"Enter account number: ";
        cin>>accno;
        if(accounts[id-1].getAccountNo()==accno){
            int pin;
            cout<<"Enter account pin: ";
            cin>>pin;
            if(accounts[id-1].getAccountPin()==pin){
                cout<<"Balane is: "<<accounts[id-1].getBalance()<<endl;
            }
            else
            cout<<"Invalid pin\n";
        }
        else
        cout<<"Invalid account number\n";
    }
    void makeTransaction(float amt, TransactionType t,int id,int pin){
        if(accounts[id-1].getAccountPin()==pin){
            accounts[id-1].updateBalance(amt,t);
        }
        else
            cout<<"INVALID PIN";
    }    

};
int genAccountNo(string s){
    int result = 0;
    for (char ch : s) {
        if (isdigit(ch)) {
            result = result * 10 + (ch - '0');
        }
    }
    return result;
}

int main(){
int l=0;
while(l==0){
    Bank bank;
    int x;
    cout<<"===============================================================================================================\n";
    cout<<"Options:\n1. Create a new account\n2. Check account balance\n3. Make a transaction\n4. Customer Information\n5. Exit the program\n";
    cin>>x;
    switch (x)
    {
    case(1):{
        int t,pin;
        string name,add,cno;
        cout<<"Enter customer name: ";
        cin>>name;
        cout<<"Enter customer address: ";
        cin>>add;
        cout<<"Enter contact no: ";
        cin>>cno;
        cout<<"Enter type(0 for SAVINGS / 1 for CURRENT): ";
        cin>>t;
        cout<<"Decide a 4 digit integer PIN for your account: ";
        cin>>pin;
        Customer customer(name,add,cno);
        bank.accountOpen(customer,(AccountType)t,pin);


        break;
    } 
    case 2:{
        int id;
        cout<<"Enter customer ID: ";
        cin>>id;
        bank.accountBalance(id);
        break;
    }
    case 3:{
        int t,id,pin;
        float amt;
        cout<<"Enter the customer ID: ";
        cin>>id;
        cout<<"Enter PIN: ";
        cin>>pin;
        cout<<"Do you want to diposit or withdraw money? (0 for DEPOSIT / 1 for WITHDRAW): ";
        cin>>t;
        cout<<"Enter the amount: ";
        cin>>amt;
        if(amt<0){
            cout<<"Enter positive amount only";
        }
        else
            bank.makeTransaction(amt,(TransactionType)t,id,pin);
        
        break;  
    }
    case 4:{
        int id;
        cout<<"Enter customer ID: ";
        cin>>id;
        bank.displayCustomerInfo(id);
        break;
    }
    case 5:
        l=1;
        break;
    
    default:
        cout<<"Invalid option selected"<<endl;
        break;
    }
}
return 0;
}
