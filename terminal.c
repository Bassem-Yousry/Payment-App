#include <stdio.h>
#include "card.h"
#include "terminal.h"
#include<time.h>
#include<string.h>
char *TransactionDate;
float TransactionAmount;

void getTransactionDateTest(void){

	char *input[10]={"05/02/1990","250/1/1999","687/9/123","00/09/2131","09/09/203","02/32","09/20/2123","10/2/2222","08/42.2123","07/09/2310"};
	ST_terminalData_t termData;
	char results[10]={0,1,1,1,1,1,1,1,1,0};
	int i; 
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: getTransactionDateTest");
	for ( i = 1; i < 11; i++){
		printf("Test Case %i:\n",i);
		TransactionDate=input[i-1];	
		printf("Input Data: %s\n",TransactionDate);
		printf("Expected Result: %i\n",results[i-1]);
		printf("Actual Result: %i\n",getTransactionDate(&termData));
	}
}
void isCardExpriedTest(void){
	ST_terminalData_t t;
	ST_cardData_t c;
	char *cardExp[4]={"02/32","10/20","10/80","01/01"};
	char *TermDate[4]={"05/02/1990","25/11/2020","07/9/2023","09/09/2131"};
	EN_cardError_t results[4]={CARD_OK,WRONG_EXP_DATE,CARD_OK,WRONG_EXP_DATE};
	int i; 
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: isCardExpriedTest");
	for ( i = 1; i < 5; i++){
		printf("Test Case %i:\n",i);
		memcpy(t.transactionDate,TermDate[i-1],10);
		memcpy(c.cardExpirationDate,cardExp[i-1],5);
		printf("Input Data: CardExp=%s TransDate=%s\n",cardExp[i-1],TermDate[i-1]);
		printf("Expected Result: %i\n",results[i-1]);
		printf("Actual Result: %i\n\n",isCardExpired(&c,&t));
	}

	
}
void getTransactionAmountTest(void){
	ST_terminalData_t t;
	float amount[4]={0,-2,213.312,1000000000};
	EN_terminalError_t results[4]={INVALID_AMOUNT,INVALID_AMOUNT,TERMINAL_OK,TERMINAL_OK};
	short int i; 
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: getTransactionAmountTest");
	for ( i = 1; i < 5; i++){
		printf("Test Case %i:\n",i);
		printf("Input Data: %.3f\n",amount[i-1]);
		TransactionAmount=amount[i-1];
		printf("Expected Result: %i\n",results[i-1]);
		printf("Actual Result: %i\n\n",getTransactionAmount(&t));
	}
}
void isBelowMaxAmountTest(void){
	ST_terminalData_t t;
	float amount[4]={9000000,2,213.312,1000000000};
	EN_terminalError_t results[4]={EXCEED_MAX_AMOUNT,TERMINAL_OK,TERMINAL_OK,EXCEED_MAX_AMOUNT};
	short int i; 	
	t.maxTransAmount=TerminalMaxAmount;
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: isBelowMaxAmountTest");
	for ( i = 1; i < 5; i++){
		printf("Test Case %i:\n",i);
		printf("Input Data: %.3f    MaxAmount=1000,000\n",amount[i-1]);
		t.transAmount=amount[i-1];
		printf("Expected Result: %i\n",results[i-1]);
		printf("Actual Result: %i\n\n",isBelowMaxAmount(&t));
	}

}
void setMaxAmountTest(void){
	ST_terminalData_t t;
	float amount[4]={9000000,-2,0,1000000000};
	EN_terminalError_t results[4]={TERMINAL_OK,INVALID_MAX_AMOUNT,INVALID_MAX_AMOUNT,TERMINAL_OK};
	short int i; 	
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: setMaxAmountTest");
	for ( i = 1; i < 5; i++){
		printf("Test Case %i:\n",i);
		printf("Input Data: %.3f \n",amount[i-1]);
		printf("Expected Result: %i\n",results[i-1]);
		printf("Actual Result: %i\n\n",setMaxAmount(&t,amount[i-1]));
	}

}
void isValidCardPANTest(void){
	ST_cardData_t c;
	char* PAN[4]={"4012888888881881","4833120034123456","2833120034123456","8989374615436851"};
	EN_terminalError_t results[4]={TERMINAL_OK,TERMINAL_OK,INVALID_CARD,TERMINAL_OK};
	short int i; 	
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: isValidCardPANTest");
	for ( i = 1; i < 5; i++){
		printf("Test Case %i:\n",i);
		printf("Input Data: %s\n",PAN[i-1]);
		memcpy(c.primaryAccountNumber,PAN[i-1],16);
		c.primaryAccountNumber[16]='\0';
		printf("Expected Result: %i\n",results[i-1]);
		printf("Actual Result: %i\n\n",isValidCardPAN(&c));
	}
}
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
	char DateArr[11];
	int Day,Month,Year;
	struct tm date;
	time_t t ;
	#ifdef TransactionDateTEST

	#else
		termData->maxTransAmount=TerminalMaxAmount; 
		time(&t);
		date=*localtime(&t);
		sprintf(DateArr,"%02i/%02i/%04i",date.tm_mday,date.tm_mon+1,date.tm_year+1900);
		TransactionDate=DateArr;
	#endif
	if (strlen(TransactionDate)!=10||TransactionDate[2]!='/'||TransactionDate[5]!='/')
	{
		return WRONG_DATE;
	}
	sscanf(TransactionDate,"%2d/%2d/%4d",&Day,&Month,&Year);
	if( Day>31||Day<1||Month<1||Month>12)
	{
		return WRONG_DATE;
	}
	memcpy(termData->transactionDate,TransactionDate,10);
	termData->transactionDate[10]='\0';
	return TERMINAL_OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
	#ifdef CardExpiredTest
	#else
	#endif
	int CardMon,CardYear,TranMon,TranYear;
	sscanf((char*)cardData->cardExpirationDate,"%2d/%2d",&CardMon,&CardYear);
	sscanf((char*)termData->transactionDate,"%*c%*c/%2d/%4d",&TranMon,&TranYear);
	CardYear+=2000;
	if (CardYear<TranYear)
	{
		return EXPIRED_CARD;
	}
	else if(CardYear==TranYear)
	{
		if (CardMon>=TranMon)
		{
			return TERMINAL_OK;
		}
	}else
	{
			return TERMINAL_OK;
	}
	return EXPIRED_CARD;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
	#ifdef TransactionAmountTEST

	#else
		scanf("%f",&TransactionAmount);
	#endif

	if (TransactionAmount<=0)
	{
		return INVALID_AMOUNT;
	}
	termData->transAmount=TransactionAmount;
	return TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	#ifdef BelowMaxTest
	#else
	#endif
	return (termData->transAmount>termData->maxTransAmount)?EXCEED_MAX_AMOUNT:TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
	#ifdef MaxAmountTest
	#else
	#endif
	if (maxAmount<=0)
	{
		return INVALID_MAX_AMOUNT ;
	}
	termData->maxTransAmount=maxAmount;
	return TERMINAL_OK;
}
void setAmount(ST_terminalData_t *termData, float Amount){
	termData->transAmount=Amount;
}
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
	
	#ifdef MaxAmountTest
	#else
	#endif
	int i,ii,size ;
	char *PanNum=(char*)cardData->primaryAccountNumber;
	uint8_t checksumControl=0,temp,checksum;   //char to int
	size=strlen(PanNum);
	checksum= PanNum[size-1]-'0';
	for (ii=0, i = size-2; i >= 0; ii++,i--)	//start from second most right digit
	{
		temp=PanNum[i]-'0';
		if(!(ii%2)){
		temp=((temp*2)%10)+((temp*2)/10);
		}
		checksumControl+=temp;
	
	}
	checksumControl=(10-(checksumControl%10));
	if(checksumControl==checksum){
		return TERMINAL_OK;
	}
	return INVALID_CARD;
}
