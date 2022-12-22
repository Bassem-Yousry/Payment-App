#include <stdio.h>
#include <string.h>
#include "card.h"
char * TestCardName;
char * TestCardExp;
char * TestCardPan;


void getCardHolderNameTest(void){
	char *input[4]={"bassem mohamed yousry","Ahmed","aahmed mohamed youssef gamal",""};
	ST_cardData_t cardData;
	EN_cardError_t results[4]={CARD_OK,WRONG_NAME,WRONG_NAME,WRONG_NAME};
	int i; 
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: getCardHolderName");
	for ( i = 1; i < 5; i++){
		printf("Test Case %i:\n",i);
		TestCardName=input[i-1];	
		printf("Input Data: %s\n",TestCardName);
		printf("Expected Result: %i\n",results[i-1]);
		printf("Actual Result: %i\n",getCardHolderName(&cardData));
	}
}
void getCardExpiryDateTest (void){

	char *input[10]={"05/2090","05/31","687/9","20/9","01/23","02/32","09/20","10/32","08/42","07/09"};
	ST_cardData_t cardData;
	EN_cardError_t results[10]={WRONG_EXP_DATE,CARD_OK,WRONG_EXP_DATE,WRONG_EXP_DATE,
								CARD_OK,CARD_OK,CARD_OK,CARD_OK,CARD_OK,CARD_OK};
	int i; 
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: getCardExpiryDate");
	for ( i = 1; i < 11; i++){
		printf("Test Case %i:\n",i);
		TestCardExp=input[i-1];	
		printf("Input Data: %s\n",TestCardExp);
		printf("Expected Result: %i\n",results[i-1]);
		printf("Actual Result: %i\n",getCardExpiryDate(&cardData));
	}
}
void getCardPANTest (void){
char *input[4]={"1234567890123456","12345678901234567890","123456789a123456","123455"};
	ST_cardData_t cardData;
	EN_cardError_t results[4]={CARD_OK,WRONG_PAN,WRONG_PAN,WRONG_PAN};
	int i; 
	puts("Tester Name: Bassem Yousry");
	puts("Function Name: getCardPAN ");
	for ( i = 1; i < 5; i++){
		printf("Test Case %i:\n",i);
		TestCardPan=input[i-1];	
		printf("Input Data: %s\n",TestCardPan);
		printf("Expected Result: %i\n",results[i-1]);
		printf("Actual Result: %i\n",getCardPAN(&cardData));
	}
}
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
	char Name[50];
	int size;
	#ifdef NAME_TEST
	#else
		scanf("%[^\n]s",Name);
		TestCardName=Name;
	#endif
	size=strlen( TestCardName);
	if (size>24||size<20)
		{
			return WRONG_NAME;
		}
	memcpy(cardData->cardHolderName,TestCardName,size);
	cardData->cardHolderName[size]='\0';
	return CARD_OK;
	
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	int x,month,year;
	char Date[50];
	#if defined EXP_TEST
	#else
		scanf("%s",Date);
		TestCardExp=Date;
	#endif
	x=strlen(TestCardExp);
	//EXP Format MM/YY
	if (!(x==5)|| TestCardExp[2]!='/' )
		{
			return WRONG_EXP_DATE;
		}
	sscanf(TestCardExp,"%2d/%2d",&month,&year);
	if( month>12||month<1||year<1||year>99){
		return WRONG_EXP_DATE;
	}

	memcpy(cardData->cardExpirationDate,TestCardExp,x);
	cardData->cardExpirationDate[5]='\0';
	return CARD_OK;
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
	int x;
	char c,ss[50];
	#if defined PAN_TEST
	
	#else
		scanf("%[^\n]s",ss);
		TestCardPan=ss;
	#endif
	x=strlen(TestCardPan);	
	if (x>19 || x<16 )
		{
			return WRONG_PAN;
		}
	for ( c = 0; c < x; c++)
	{
		if (TestCardPan[c]<'0'||TestCardPan[c]>'9')
		{
			return WRONG_PAN;
		}
	}
	
	//printf("%i %i\n",month,year);
	memcpy(cardData->primaryAccountNumber,TestCardPan,x);
	cardData->primaryAccountNumber[x]='\0';
	return CARD_OK;
	
	}

void setCardName(ST_cardData_t *cardData,char *name){
	int size;
	size=strlen( name);
	memcpy(cardData->cardHolderName,name,size);
	cardData->cardHolderName[size]='\0';
}
void setCardPAN(ST_cardData_t *cardData,char *PAN){
	int size;
	size=strlen( PAN);
	memcpy(cardData->primaryAccountNumber,PAN,size);
	cardData->primaryAccountNumber[size]='\0';
}
void setCardEXP(ST_cardData_t *cardData,char *EXP){
	int size;
	size=strlen( EXP);
	memcpy(cardData->cardExpirationDate,EXP,size);
	cardData->cardExpirationDate[size]='\0';
}