// This is card.h file 
#ifndef CARD_H
#define CARD_H

typedef unsigned char uint8_t;

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];           // Card holder name is 24 characters string max and 20 min.
	uint8_t primaryAccountNumber[20];     // PAN is 20 characters alphanumeric only string 19 character max, and 16 character min
	uint8_t cardExpirationDate[6];        // Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
}ST_cardData_t;

typedef enum EN_cardError_t
{
	OK,             // OK = 0   
	WRONG_NAME,     // WRONG_NAME = 1  
	WRONG_EXP_DATE, // WRONG_EXP_DATE = 2  
	WRONG_PAN       // WRONG_PAN = 3  

}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


#endif