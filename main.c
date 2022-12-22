#include<stdio.h>
#include <string.h>
#include<time.h>
#include"card\card.h"
#include"terminal\terminal.h"
#include"server\server.h"
#include"app\app.h"

void main(){
	/*Card Module*/
	//getCardHolderNameTest();
	//getCardExpiryDateTest ();
	//getCardPANTest ();

	/*Terminal Module*/
	//getTransactionDateTest();
	//isCardExpriedTest();
	//getTransactionAmountTest();
	//isBelowMaxAmountTest();
	//setMaxAmountTest();
	//isValidCardPANTest();

	/*Server Module*/
	isBlockedAccountTest();
	isValidAccountTest();
	isAmountAvailableTest();
	saveTransactionTest();	
	recieveTransactionDataTest();
	listSavedTransactionsTest();

	/*App Module*/
//	appStart();


	getchar();
	getchar();
}