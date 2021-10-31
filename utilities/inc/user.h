#ifndef _USER_H_
#define _USER_H_

#include <fileIO.h>

using namespace std;

class User {


public:
	unsigned long accountNumber;
	string accountHolderName;
	char accountType;
	unsigned long long accountBalance;

	virtual ~User();
	void printDetails();
	void UserSubRoutine(const string dbPath);
	

};

typedef struct transaction {
	unsigned long amount;
	time_t time;
};


int makeTransaction(unsigned long accountNumber, char transactionType, string dbPath);

#endif // !_USER_H_
