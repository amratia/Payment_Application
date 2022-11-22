#include <stdio.h>
#include <string.h>
#include "server.h"

int accountIndex;

// server-side transactions' database
ST_transaction myDataSetTransactions[255] = { 0 }; // Also ZERO by default because global array

// server-side accounts' database
ST_accountsDB_t myDataSetAccounts[255] = { {100,"1234567899876543210"},{200,"1234567891234567890"},
	{400,"1231231231231231230"},{600,"4564564564564564560"},{1000,"7897897897897897890"} };

int TransactionNumber = 0;

EN_transStat_t recieveTransactionData(ST_transaction* transData) {
	
	//If the account does not exist return DECLINED_STOLEN_CARD ------------------------------------------------
	int checkAccount = isValidAccount(&transData->cardHolderData);
	if (checkAccount == 3) { //ACCOUNT_NOT_FOUND
		return DECLINED_STOLEN_CARD;
		transData->transState = DECLINED_STOLEN_CARD;
	}
	else
		transData->transState = APPROVED;


	//if the amount is not available will return DECLINED_INSUFFECIENT_FUND -------------------------------------
	int checkAmount = isAmountAvailable(&transData->terminalData);
	if (checkAmount == 4) { // LOW_BALANCE
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	else
		transData->transState = APPROVED;

	if (transData->transState == APPROVED) {
		myDataSetAccounts[accountIndex].balance = myDataSetAccounts[accountIndex].balance - transData->terminalData.transAmount;
		int mytemp = myDataSetAccounts[accountIndex].balance;
		printf("Your balance after the transaction is %d\n", mytemp);
	}

	int saveMyTransaction = saveTransaction(&transData);
	if (saveMyTransaction == 0) { // Save successful --> return transaction state
		return transData->transState;
	}
	if (saveMyTransaction != 0) {//save was not successful
		return INTERNAL_SERVER_ERROR;
	}

	

}
//--------------------------------------------------------------------------------------------------------
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {

	int accountExist = 0; // it doesn't exist
	for (int i = 0; i < 255; i++) {
		if (strcmp(cardData->primaryAccountNumber , myDataSetAccounts[i].primaryAccountNumber) == 0) {
			// if strcmp == 0 --> strings are the same
			accountExist = accountExist + 1;
			accountIndex = i;
		}
	}
	if (accountExist == 0)
		return ACCOUNT_NOT_FOUND;
	if (accountExist == 1) {
		printf("Your account exists\n");
		int temp = myDataSetAccounts[accountIndex].balance;
		printf("Your balance is %d\n", temp);
		printf("-----------------------------\n");
		return OKserver;
	}
		

}
//--------------------------------------------------------------------------------------------------------
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	if (termData->transAmount > myDataSetAccounts[accountIndex].balance)
		return LOW_BALANCE;
	else
		return OKserver;

}
//--------------------------------------------------------------------------------------------------------
EN_serverError_t saveTransaction(ST_transaction* transData) {
	//This function will take all transaction data into the transactions database.
	myDataSetTransactions[TransactionNumber].cardHolderData = transData->cardHolderData;
	myDataSetTransactions[TransactionNumber].terminalData = transData->terminalData;
	myDataSetTransactions[TransactionNumber].transState = transData->transState;
	myDataSetTransactions[TransactionNumber].transactionSequenceNumber = TransactionNumber;
	TransactionNumber++;

	return OKserver;
}

