#include<stdio.h>
#include<string.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
int Num_of_trans=0;

void isBlockedAccountTest(void){
	int i;
	ST_cardData_t c;
	ST_accountsDB_t d;
	char*pan[4]={"8989374615436851","5807007076043875","4012888888881881","4833120034123456"};
	EN_serverError_t results[4]={SERVER_OK,BLOCKED_ACCOUNT,SERVER_OK,BLOCKED_ACCOUNT};
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: isBlockedAccountTest");
	for ( i = 0; i < 4; i++)
	{
		d=*getAccountFromDB(pan[i]);
		printf("Test Case %i:\n",i+1);
		printf("Input Data: PAN=%s \n",d.primaryAccountNumber);
		printf("Expected Result: %i\n",results[i]);
		printf("Actual Result: %i\n\n",isBlockedAccount(&d));
	} 
}
void isValidAccountTest(void){
	int i;
	ST_cardData_t c;
	ST_accountsDB_t accountRefrence;
	char *PAN_DB[4]={"8989374615436851","5807007076043875","4012888888881881","4012888888881886"};
	EN_serverError_t results[4]={SERVER_OK,SERVER_OK,SERVER_OK,ACCOUNT_NOT_FOUND};
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: isValidAccountTest");
	for ( i = 0; i < 4; i++)
	{
		printf("Test Case %i:\n",i+1);
		setCardPAN(&c,PAN_DB[i]);
		printf("Input Data: PAN=%s \n",PAN_DB[i]);
		printf("Expected Result: %i\n",results[i]);
		printf("Actual Result: %i\n\n",isValidAccount(&c,&accountRefrence));
	} 

}
void recieveTransactionDataTest(void){
	ST_transaction_t Trans;int i;
	ST_cardData_t c;
	ST_terminalData_t t;
	char *PAN_DB[4]={"8989374615436851","5807007076043875","4012888888881881","4012888888881886"};
	float TransAmount[4]={2032,20,21312,1};
	EN_transState_t results[4]={APPROVED,DECLINED_STOLEN_CARD,DECLINED_INSUFFECIENT_FUND,FRAUD_CARD};
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: recieveTransactionDataTest");
	for ( i = 0; i < 4; i++)
	{
		printf("Test Case %i:\n",i+1);
		setCardPAN(&c,PAN_DB[i]);
		setAmount(&t,TransAmount[i]);
		Trans.cardHolderData=c;
		Trans.terminalData=t;
		printf("Input Data: PAN=%s , TransAmount=%.2f\n",PAN_DB[i],TransAmount[i]);
		Trans.transState=recieveTransactionData(&Trans);
		printf("Expected Result: %i\n",results[i]);
		printf("Actual Result: %i\n\n",Trans.transState);
	} 


	
}
void isAmountAvailableTest(void){
	int i;
	ST_terminalData_t t;	
	ST_accountsDB_t d;
	EN_serverError_t results[4]={SERVER_OK ,LOW_BALANCE,LOW_BALANCE,SERVER_OK};	
	char*pan[4]={"8989374615436851","5807007076043875","4012888888881881","4833120034123456"};
	setAmount(&t,2000);
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: isAmountAvailableTest");
	for ( i = 0; i < 4; i++)
	{
		d=*getAccountFromDB(pan[i]);
		printf("Test Case %i:\n",i+1);
		printf("Input Data: AccountBalance=%f TansactionAmount=%f \n",d.balance,2000.0);
		printf("Expected Result: %i\n",results[i]);
		printf("Actual Result: %i\n\n",isAmountAvailable(&t,&d));
	} 
}
void saveTransactionTest(void){
	ST_transaction_t Trans;int i;
	ST_cardData_t c;
	ST_terminalData_t t;
	char *PAN_DB[4]={"8989374615436851","5807007076043875","4012888888881881","4012888888881886"};
	char *names[4]={"bassem mohamed yousry","Ahmeddd ahmed ahmed","ahmed mohamed youssef","salah ahmed mohamed"};
	char *ExpDates[4]={"05/20","05/31","68/90","20/09"};
	float TransAmount[4]={2032,20,21312,1};
	EN_transState_t results[4]={APPROVED,APPROVED,APPROVED,APPROVED};
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: saveTransactionTest");
	for ( i = 0; i < 4; i++)
	{
		printf("Test Case %i:\n",i+1);
		setCardName(&c,names[i]);
		setCardPAN(&c,PAN_DB[i]);
		setCardEXP(&c,ExpDates[i]);
		setAmount(&t,TransAmount[i]);
		getTransactionDate(&t);
		setMaxAmount(&t,100000);
		Trans.cardHolderData=c;
		Trans.terminalData=t;		
		Trans.transState=recieveTransactionData(&Trans);
		printf("Input Data: PAN=%s , TransDate=%s\n",PAN_DB[i],Trans.terminalData.transactionDate);
		printf("Expected Result: %i\n",results[i]);
		printf("Actual Result: %i\n\n",saveTransaction(&Trans));
	} 
}
void listSavedTransactionsTest(void){
	saveTransactionTest();
	listSavedTransactions();
}
ST_accountsDB_t* getAccountFromDB(char *Pan){
	ST_accountsDB_t  returnAccount;
	int stateDB,size;
	float balanceDB;
	char PanDB[80],line[150];
	FILE * fptr =fopen("accDB.txt","r");
	 if(fptr == NULL)
   {
      printf("Error in DB!");   
	     return NULL ;
   }
	while (!feof(fptr))
	{
		fscanf(fptr,"%[^\n]s",&line);
		fgetc(fptr);	//skip new line char '\n'
		sscanf(line,"%f %i %s",&balanceDB,&stateDB,PanDB);
		if (!strcmp(PanDB,Pan))
		 {
			 returnAccount.balance=balanceDB;
			 returnAccount.state=(EN_accountState_t) stateDB;
			 size=strlen(Pan);
			 memcpy(returnAccount.primaryAccountNumber,Pan,size);
			 returnAccount.primaryAccountNumber[size]='\0';
			 fclose(fptr);
			 return &returnAccount;
		}
	}
	return NULL;

}
uint8_t updateBalanceOfAccountInDB(char *Pan,float NewBalance){
	ST_accountsDB_t  returnAccount;
	int Lineindex=0,stateDB=0,count=0;
	float balanceDB=0;
	char PanDB[90]=" ",line[100]=" ";	
	int lineIndexArr[50]={0};//holds the start position index of each line
	FILE * fptr=NULL ;
	fptr=fopen("accDB.txt","r+");
	 if(fptr == NULL)
   {
      printf("Error in DB!");   
	     return 1 ;
   }
	 while (!feof(fptr)){
		 count++;
		 if (fgetc(fptr)=='\n')
		 {
			 lineIndexArr[++Lineindex]=count;
		 }
	 }
	fseek( fptr, 0, SEEK_SET );	//move pointer to the beginning of the line
	Lineindex=0;
	count=0;
	while (!feof(fptr))
	{
		fscanf(fptr,"%[^\n]s",&line);
		fgetc(fptr);	//skip new line char '\n'
		sscanf(line,"%f %i %s",&balanceDB,&stateDB,PanDB);
		if (!strcmp(PanDB,Pan))
		 {
			fseek( fptr, lineIndexArr[Lineindex], SEEK_SET );	//move pointer to the beginning of the line
			/*delete data line*/
			while (count<strlen(line))
			{
				fputc(0,fptr);
				count++;
			}
			fseek( fptr, lineIndexArr[Lineindex], SEEK_SET );		//move pointer to the start of the line
			fprintf(fptr,"%.1f %i %s",NewBalance,stateDB,PanDB);	//update balance
			fclose(fptr);
			return 0;
		 }
			Lineindex++;
	}
	return 1;

}
EN_transState_t recieveTransactionData(ST_transaction_t *transData){
	uint8_t *PAN;int i;
	ST_accountsDB_t accDB,*accDBptr;
	PAN=transData->cardHolderData.primaryAccountNumber;		
	accDBptr=getAccountFromDB((char*)PAN);
	if (accDBptr==NULL)
	{
		return FRAUD_CARD;
	}
	accDB=*accDBptr;	
	if (accDB.balance < transData->terminalData.transAmount)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (accDB.state==BLOCKED)
	{
		return DECLINED_STOLEN_CARD;
	}
	if (Num_of_trans >= MaxTransactionsDB)
	{
		return INTERNAL_SERVER_ERROR;
	}else
	{
		updateBalanceOfAccountInDB((char*)PAN, accDB.balance-transData->terminalData.transAmount);
		return APPROVED;
	}
	return FRAUD_CARD;
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
	int i;
	uint8_t *accDBPAN,*PAN=cardData->primaryAccountNumber;
	ST_accountsDB_t *accPtr;
	accPtr=getAccountFromDB((char*)PAN);
	
	if (!accPtr==NULL)
		{
			*accountRefrence=*accPtr;
			return SERVER_OK ;
		}
	
	accountRefrence=NULL;
	return ACCOUNT_NOT_FOUND;

}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
	return (accountRefrence->state==BLOCKED)?BLOCKED_ACCOUNT:SERVER_OK;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){
	return (termData->transAmount > accountRefrence->balance)?LOW_BALANCE:SERVER_OK;

}
EN_serverError_t saveTransaction(ST_transaction_t *transData){
char line[90];int TranNumDB=0;
FILE * fptr =fopen("TransactionDB.txt","a+");	
fseek(fptr,0,SEEK_END);
TranNumDB=ftell(fptr)/100;
Num_of_trans=TranNumDB;
fseek(fptr,0,SEEK_SET);
transData->transactionSequenceNumber=Num_of_trans;
Num_of_trans++;
if (Num_of_trans>MaxTransactionsDB){
		return SAVING_FAILED;
	}
	 if(fptr == NULL)
   {
      printf("Error!");   
	     return ;
   }
fseek(fptr,0,SEEK_END);
fprintf(fptr,"%04u\n%s\n%.2f\n%i\n%.2f\n%s\n%s\n%s\n##############\n",
		transData->transactionSequenceNumber,(char*)transData->terminalData.transactionDate,
		transData->terminalData.transAmount,transData->transState,
		transData->terminalData.maxTransAmount,(char*)transData->cardHolderData.cardHolderName,
		(char*)transData->cardHolderData.primaryAccountNumber,(char*)transData->cardHolderData.cardExpirationDate);
fclose(fptr);
return SERVER_OK;
//listSavedTransactions ();
return SERVER_OK;
}
void listSavedTransactions(void){
int currentPos=0,EndPos=0;
FILE* fptr=fopen("TransactionDB.txt","r");
char TranWord[30];
fseek(fptr,0,SEEK_END);
EndPos=ftell(fptr);
fseek(fptr,0,SEEK_SET);
while(!feof(fptr))
{
	currentPos=ftell(fptr);
	if((EndPos-currentPos)<=10){fclose(fptr);break; }
	puts("#########################");
	fscanf(fptr,"%s",TranWord);
	fgetc(fptr);//skip \n char
	printf("Transaction Sequence Number: %s\n",TranWord);
	fscanf(fptr,"%s",TranWord);
	fgetc(fptr);//skip \n char
	printf("Transaction Date: %s\n",TranWord);
	fscanf(fptr,"%s",TranWord);
	fgetc(fptr);//skip \n char
	printf("Transaction Amount: %s\n",TranWord);
	fscanf(fptr,"%s",TranWord);
	fgetc(fptr);//skip \n char
	printf("Transaction State: %s\n",TranWord);
	fscanf(fptr,"%s",TranWord);
	fgetc(fptr);//skip \n char
	printf("Terminal Max Amount: %s\n",TranWord);
	fscanf(fptr,"%[^\n]s",TranWord);
	fgetc(fptr);//skip \n char
	printf("Cardholder Name: %s\n",TranWord);
	fscanf(fptr,"%s",TranWord);
	fgetc(fptr);//skip \n char
	printf("PAN: %s\n",TranWord);
	fscanf(fptr,"%s",TranWord);
	fgetc(fptr);//skip \n char
	printf("Card Expiration Date: %s\n",TranWord);
	puts("#########################\n");
	fscanf(fptr,"%s",TranWord);
	fgetc(fptr);//skip \n char

}
}

