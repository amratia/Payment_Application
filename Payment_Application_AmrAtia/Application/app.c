#include <stdio.h>
#include <string.h>
#include "app.h"
#include "..\Card\card.h"         // including relative path
#include "..\Terminal\terminal.h" // including relative path
#include "..\Server\server.h" // including relative path


ST_cardData_t myStruct;     // to store Card Data
ST_terminalData_t termData; // to store Terminal Data


int main() {
	//------------------------------------------------- CARD MODULE FUNCTION CALL
	int error = 0; // ok 
	error = getCardHolderName(&myStruct);
	if (error == 1) {
		printf("Wrong Card Holder Name");
		return 0;
	}
	error = getCardExpiryDate(&myStruct);
	if (error == 2) {
		printf("Wrong Card Expiry Date");
		return 0;
	}
	error = getCardPAN(&myStruct);
	if (error == 3) {
		printf("Wrong Card PAN");
		return 0;
	}
	//------------------------------------------------- TERMINAL MODULE FUNCTION CALL

	int termError = 0;
	termError = getTransactionDate(&termData);       // error = 1
	if (termError == 1) {
		printf("Wrong Transaction Date");
		return 0;
	}
	termError = isCardExpired(myStruct, termData);    // error = 2
	if (termError == 2) {
		printf("Card Expired");
		return 0;
	}
	termError = getTransactionAmount(&termData);     // error = 3
	if (termError == 3) {
		printf("Wrong Transaction Amount");
		return 0;
	}
	termError = setMaxAmount(&termData);             // error = 5
	if (termError == 5) {
		printf("Wrong Max Amount");
		return 0;
	}
	termError = isBelowMaxAmount(&termData);         // error = 4
	if (termError == 4) {
		printf("Transaction amount exceeds max amount");
		return 0;
	}

	//------------------------------------------------- SERVER MODULE FUNCTION CALL
	
	// Passing Card Data and Terminal Data to Transactions structure
	ST_transaction anyTransaction; 
	anyTransaction.cardHolderData = myStruct;
	anyTransaction.terminalData = termData;	

	int serverError = 0;
	serverError = recieveTransactionData(&anyTransaction);
	if (serverError == 2) {
		printf("DECLINED_STOLEN_CARD\n");
		return 0;
	}
	if (serverError == 1) {
		printf("DECLINED_INSUFFECIENT_FUND\n");
		return 0;
	}
	if (serverError == 3) {
		printf("INTERNAL_SERVER_ERROR\n");
		return 0;
	}
	if (serverError == 0) {
		printf("Approved! Your Transaction was successful\n");
		return 0;
	}	

	return 0;
}