#ifndef _ADMIN_H_
#define _ADMIN_H_
#include <fileIO.h>
#include <display.h>
#include <user.h>

/* Admin will have the folloing functionality
    1. To add new account holders to data file
    2. To delete account holders from data file
    3. Display a list of all the account holders with ACno & bal
    4. Update the balance after customer has performed
       -> a deposit or withdraw transaction
    5. Display the account number of the last entry
    6. Check whether an account exists or not
    7. Retrieve name, address, balance & also entire details
    8. Transaction details
    9. Calculate the interest to date on the deposit
        -> if a particular customer has not withdrawn for more than a month
*/

class Admin {
public:
    virtual ~Admin();
    bool Login();
    int addNewAccount(const string dbPath);             //done 1
    int allAccountHolders(const string dbPath);         //done 2
    int GetAccountDetail(unsigned long accountNumber, const string dbPath); //3 
    void deleteAccount(unsigned long accountNumber, const string dbPath);   //5 done

    void AdminSubRoutine(const string dbPath);
};

#endif