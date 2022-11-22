#include <stdio.h>
#include <string.h>
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Please enter your name (between 20 and 24 Characters)\n");
	gets(cardData->cardHolderName);
	if (cardData->cardHolderName == NULL) {
		return WRONG_NAME; // WRONG_NAME error
	}
		
	else if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24) {
		return WRONG_NAME; // WRONG_NAME error
	}
		
	else {
		return OK; // OK
	}
		
}
//--------------------------------------------------------------------------------------------------------
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Please enter the card's expire date (Format: MM/YY)\n");
	gets(cardData->cardExpirationDate);
	if (cardData->cardExpirationDate == NULL) {
		return WRONG_EXP_DATE; // WRONG_EXP_DATE error
	}

	else if (strlen(cardData->cardExpirationDate) < 5 || strlen(cardData->cardExpirationDate) > 5) {
		return WRONG_EXP_DATE; // WRONG_EXP_DATE error
	}

	else {
		return OK; // OK
	}
}
//--------------------------------------------------------------------------------------------------------
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Please enter the card's PAN number\n");
	gets(cardData->primaryAccountNumber);
	if (cardData->primaryAccountNumber == NULL) {
		return WRONG_PAN; // WRONG_PAN error
	}

	else if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19) {
		return WRONG_PAN; // WRONG_PAN error
	}

	else {
		return OK; // OK
	}
}


