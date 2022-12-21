#ifndef card_H
#define card_H
// to enter test mode uncomment the directives below
//#define NAME_TEST
//#define EXP_TEST 
//#define PAN_TEST
typedef  unsigned char uint8_t;

typedef enum EN_cardError_t
{
     CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
typedef struct ST_cardData_t
{
     uint8_t cardHolderName[25];
     uint8_t primaryAccountNumber[20];
     uint8_t cardExpirationDate[6];
}ST_cardData_t;

void getCardHolderNameTest(void);
void getCardExpiryDateTest (void);
void getCardPANTest (void);
void setCardName(ST_cardData_t *cardData,char *name);
void setCardPAN(ST_cardData_t *cardData,char *PAN);
void setCardEXP(ST_cardData_t *cardData,char *EXP);
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
#endif // ndef
