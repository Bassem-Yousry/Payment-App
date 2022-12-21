#ifndef terminal_h
//#define terminaL_h
// to enter test mode uncomment the directives below

//#define TransactionDateTEST
//#define CardExpriedTest
//#define TransactionAmountTEST
#define BelowMaxTest
#define MaxAmountTest
#define  TerminalMaxAmount 1000000
typedef struct ST_terminalData_t
{
     float transAmount;
     float maxTransAmount;
     uint8_t transactionDate[11];
}ST_terminalData_t;
typedef enum EN_terminalError_t
{
     TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;
void getTransactionDateTest(void); 
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void);
void setAmount(ST_terminalData_t *termData, float Amount);
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional

#endif // ndef
