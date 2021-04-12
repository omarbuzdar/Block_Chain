#include <iostream>
#include <string>

using namespace std;
#include <openssl/sha.h>


struct Transaction {
    Transaction *prev;
    int amount;
    string sender;
    string reciever;
    string nonce;
    string hash;
};

class TransactionChain {
    public:
        TransactionChain() { head = NULL; }
        void add(int inAmount, string inSender, string inReciever)
        {
            
            Transaction* t = new Transaction;
            if(head == NULL)
            {
                head = t;
                head->prev = NULL;
                head->amount = inAmount;
                head->sender = inSender;

                //can put outside of if-else
                string nonce = "";
                string nonce_hash_key;
                string nonce_hash;
                nonce += char(rand()%26 + 97) ;
                nonce_hash_key = to_string(inAmount) + inSender + inReciever + nonce;
                string nonce_hash = SHA256(nonce_hash_key);
                while (nonce_hash[nonce_hash.size() -1] != 0)
                {
                   nonce = "";
                   nonce += char(rand() %26 + 97) ;
                   nonce_hash_key = to_string(inAmount) + inSender + inReciever + nonce;
                   nonce_hash = SHA256(nonce_hash_key);

                }
                
                head->nonce = nonce;
                head->hash = "NULL";

            }
            else {
                t->prev = head;
                
                t->amount = inAmount;
                t->sender = inSender;

                string nonce = "";
                string nonce_hash_key;
                string nonce_hash;
                nonce += char(rand()%26 + 97) ;
                nonce_hash_key = to_string(inAmount) + inSender + inReciever + nonce;
                string nonce_hash = SHA256(nonce_hash_key);
                while (nonce_hash[nonce_hash.size() -1] != 0)
                {
                   nonce = "";
                   nonce += char(rand() %26 + 97) ;
                   nonce_hash_key = to_string(inAmount) + inSender + inReciever + nonce;
                   nonce_hash = SHA256(nonce_hash_key);

                }
                
                head->nonce = nonce;
                string hash_key = to_string(head->amount) + head->sender + head->reciever + head->hash + head->nonce;
                head->hash = SHA256(hash_key);
                head = t;

            }
        }
        
        int getBalance(string name) {
            int balance = 50;
            Transaction* point = head;
            while (point)
            {
                if(point->sender == name) {
                    balance -= point->amount;
                }
                else if (point->reciever == name) {
                    balance += point->amount;
                }
            }
            return balance;
        }

        void print() {
            printHelper(head);
            
        }
        void printHelper(Transaction *cursor) {
            if(cursor == NULL)
            {
                return;
            }
            else {
                return printHelper(cursor->prev);
                cout << "Amount: " << cursor->amount;
                cout << "Sender: " << cursor->sender;
                cout << "Reciever: " << cursor->reciever;
                cout << "Nonce: " << cursor->nonce;
                cout << "Hash: " << cursor->hash;
            }
        }

    private:
        Transaction* head = NULL;
};

int main() {
    TransactionChain chain;
    cout << "Welcome to the transaction-chain application..."<< endl;
    cout << "1) Add a transaction to the chain." << endl;
    cout << "2) Find balance of a person." << endl;
    cout << "3) Print the chain." << endl;
    cout << "4) Exit" << endl;
    cout << "Which operation do you want to make? (1,2,3,4):\n";

    int option;
    cin >> option;

    
    while (option != 4)
    {
       if(option == 1)
       {
           int amount;
           string sender;
           string reciever;
           cout << "Integer amount of money:\n";
           cin >> amount;//ask again if
           if (isdigit(amount) == false) {
               cout << "Integer amount of money:\n";
               cin >> amount;
           }
           cout << "Sender name\n";
           cin >> sender;
           cout << "Reciever name\n";
           cin >> reciever;

           chain.add(amount, sender, reciever);

       }
       else if(option == 2)
       {

       }
       else if(option == 3)
       {

       }
       else {
           cout << "wrong operation!" << endl;
       }

       cout << "Which operation do you want to make? (1,2,3,4):\n";
       cin >> option;
    }
    return 0;
}