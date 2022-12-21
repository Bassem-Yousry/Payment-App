#include<stdio.h>
#include<string.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
void appStart(void){
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	ST_accountsDB_t accountRefrence;
	ST_transaction_t transData;
	/* getting card info*/
	printf("\nEnter CardHolder Name : ");
	if(getCardHolderName(&cardData)) {puts("Invalid Name make sure the 19>=length>=16");return;}
	getchar();
	printf("\nEnter EXP Date : ");
	if(getCardExpiryDate(&cardData)){puts("Invalid EXP ,Format:MM/YY");return;}
	getchar();
	printf("\nEnter PAN : ");
	if(getCardPAN(&cardData)||isValidCardPAN(&cardData)){puts("Invalid EXP ,Format:MM/YY");return;}
	getchar();
	if(getTransactionDate(&termData)){puts("Invalid Transaction Date");return;}
	if(isCardExpired(&cardData, &termData)){puts("Declined Expired Card");return;}
	printf("\nEnter Transaction Amount (max=1000,000) : ");
	if(getTransactionAmount(&termData)){puts("Invalid Amount");return;}
	getchar();
	if(isBelowMaxAmount(&termData)){puts("Declined amount exceeding the limit");return;}
	if(isValidAccount(&cardData, &accountRefrence)){puts("Account Not found");return;}
	if(isBlockedAccount(&accountRefrence)){puts("Blocked Account ");return;}
	if( isAmountAvailable(&termData, &accountRefrence)){puts("Declined Insuffecient Funds ");return;}
	transData.cardHolderData=cardData;
	transData.terminalData=termData;
	transData.transState=recieveTransactionData(&transData);
	saveTransaction(&transData);
	puts("Transaction Approved");
}
