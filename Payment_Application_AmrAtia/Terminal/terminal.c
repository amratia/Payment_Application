#include <stdio.h>
#include "..\Card\card.h"         // including relative path
#include "terminal.h"




//--------------------------------------------------------------------------------------------------------
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("Please enter the transaction date (Format: DD/MM/YYYY)\n");
	gets(termData->transactionDate);
	if (termData->transactionDate == NULL) {
		return WRONG_DATE; // WRONG_DATE error
	}

	else if (strlen(termData->transactionDate) < 10 || strlen(termData->transactionDate) > 10) {
		return WRONG_DATE; // WRONG_NAME error
	}

	else {
		return OKterm; // OK
	}
}
//--------------------------------------------------------------------------------------------------------
EN_terminalError_t isCardExpired(ST_cardData_t myStruct, ST_terminalData_t termData) {
	// termData has transactionDate array[10]     FORMAT: DD/MM/YYYY (3,4,8,9)
	// myStruct has cardExpirationDate array[6]   FORMAT: MM/YY      (0,1,3,4)
	
	int thisYear = (termData.transactionDate[9] - '0') + 10 * (termData.transactionDate[8] - '0');
	int expireYear = (myStruct.cardExpirationDate[4] - '0') + 10 * (myStruct.cardExpirationDate[3] - '0');
	int thisMonth = (termData.transactionDate[4] - '0') + 10 * (termData.transactionDate[3] - '0');
	int expireMonth = (myStruct.cardExpirationDate[1] - '0') + 10 * (myStruct.cardExpirationDate[0] - '0');

	if (thisYear > expireYear)
		return EXPIRED_CARD;
	if (thisYear < expireYear)
		return OK;
	if (thisYear == expireYear) {
		if (thisMonth > expireMonth)
			return EXPIRED_CARD;
		else
			return OKterm;
	} 
}
//--------------------------------------------------------------------------------------------------------
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Please enter the transaction amount\n");
	scanf_s("%f",&(termData->transAmount));
	float myZero = 0;
	if (termData->transAmount <= myZero) {
		return INVALID_AMOUNT; // INVALID_AMOUNT error
	}
	else
		return OKterm;

}
//--------------------------------------------------------------------------------------------------------
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf("Please enter the transaction max amount\n");
	scanf_s("%f", &(termData->maxTransAmount));
	float myZero = 0;
	if (termData->maxTransAmount <= myZero) {
		return INVALID_MAX_AMOUNT; // INVALID_MAX_AMOUNT error
	}
	else
		return OKterm;
}
//--------------------------------------------------------------------------------------------------------
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	else
		return OKterm;
}
