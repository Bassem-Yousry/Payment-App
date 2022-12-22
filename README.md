# Payment-App
  A simple app that implements the SALE transaction
  It includes Luhn card PAN for validation
  
 https://www.youtube.com/playlist?list=PLR1_kFCzdgsXmWhS-8S2-GGysLTitpXRJ
 
 ## Flow Chart
 ![{4ED04FED-06D2-44B9-89ED-2CDC35C720DC} png](https://video.udacity-data.com/topher/2022/June/62bc647c_payment-flowchart/payment-flowchart.jpeg)
 ## Screenshots 
 - ### folder structure
 
  <img src="https://user-images.githubusercontent.com/56139834/209214657-474c11b8-b445-4e0c-996e-4dc4edc8edca.PNG" width="300" height="500">
  
 - ### Card Module
 #### Constraints 
     1) Card Holder Name must be 20 characters minimum and 24 characters maximum .
     2) Card Expiry Date must be in form MM/YY.
     3) Primary Account Number must be 16 characters minimum and 19 characters maximum.
 ![ png](https://user-images.githubusercontent.com/56139834/208898035-cf2b179b-fc0c-442f-b2a5-8d8ffb271dc3.png)
 - ### Terminal Module
 #### Constraints 
     1) Transaction Date must be in form DD/MM/YYYY.
     2) Transaction Amount must be a positive non-zero value.
     3) Terminal Max Amount must be set as an initialization for the Terminal.
  ![{4ED04FED-06D2-44B9-89ED-2CDC35C720DC} png](https://user-images.githubusercontent.com/56139834/208898015-da03ba7a-8ae8-4ad7-b3b9-88fe91fdec22.png)
 - ### Server Module 
 ![{4ED04FED-06D2-44B9-89ED-2CDC35C720DC} png](https://user-images.githubusercontent.com/56139834/208898020-3c932d5f-fdc5-4ffe-8e96-888524e5be90.png)
 - ### App Module
  ![{4ED04FED-06D2-44B9-89ED-2CDC35C720DC} png](https://user-images.githubusercontent.com/56139834/208898028-93e29ccc-9c12-469d-b760-1735c40e070f.png)
 
 ## Testing Functions
     
   **to enter test mode you need to uncomment the preproccessor directive for each function in the module header file**
 <details>
           <summary>Card Module</summary><p>  

- `void getCardHolderNameTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208899334-c523fc64-ce85-4ec5-a039-9ee268758899.PNG" width="700" height="500">
 
- `void getCardExpiryDateTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208982646-0edc412e-04e9-4509-b6d5-7e0c649c4339.PNG" width="700" height="500">

- `void getCardPANTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208984246-5621abcf-ca36-42c7-952b-769ac4fa188a.PNG" width="700" height="500">
 </p>
 </details>
 
  <details>
             <summary>Terminal Module</summary><p>  
- `void getTransactionDateTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208985095-e791f86c-628f-4470-b44e-4ce3d278b1ad.PNG" width="700" height="500">
 
- `void isCardExpriedTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208985602-161a1da0-8438-4f63-8e65-49a13aae6dbb.PNG" width="700" height="500">

- `void getTransactionAmountTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208985859-2a13d01b-2d6e-461b-963b-f70d927cd3b4.PNG" width="700" height="500">

- `void isBelowMaxAmountTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208986222-43108250-b6f5-49c6-816c-bc54bd757199.PNG" width="700" height="500">
 
- `void setMaxAmountTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208986434-4776e917-2735-475d-beb8-f08dcacbad29.PNG" width="700" height="500">

- `void isValidCardPANTest(void)`
   This function use [luhn algoritm](https://www.dcode.fr/luhn-algorithm#f0 "Named link title") to validate the PAN 
 <img src="https://user-images.githubusercontent.com/56139834/208985859-2a13d01b-2d6e-461b-963b-f70d927cd3b4.PNG" width="700" height="500">
 </p>
 </details>
 <details>
           <summary>Server Module</summary><p>  
 - `void recieveTransactionDataTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208989728-df5aa801-1c04-4be5-9e9f-2b8a1ecac24b.PNG" width="700" height="500">
 
- `void isValidAccountTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208990115-f1e24164-35d7-4f11-8098-7747f321e27c.PNG" width="700" height="500">

- `void isBlockedAccountTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208990283-6a6c51a3-ef12-4971-a098-c137e9e41ccd.PNG" width="700" height="500">

- `void isAmountAvailableTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208990617-fe6bef6e-da3c-41af-bc0c-3c997f924256.PNG" width="700" height="500">
 
- `void saveTransactionTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208990950-a56dfa55-7bbf-49af-9d0e-5d29ec610c3e.PNG" width="700" height="500">

- `void listSavedTransactionsTest(void)`
 <img src="https://user-images.githubusercontent.com/56139834/208991192-64ab6195-ac87-4c0b-a1a6-8967c67e44ea.PNG" width="700" height="500">
 </p>
 </details>

  ## Testing the application ## 
  **First u need to comment the preprocessor directives in card.h & terminal.h to exit test mode **
 1) Transaction is approved and my account balance is reduced by the withdrawn amount. 
    the AccountDB on the right is before the transaction made
 <img src="https://user-images.githubusercontent.com/56139834/208992944-a9f59d27-a2ae-44fc-97d4-a5f5f3084324.PNG" width="700" height="500">
 2) Exceed the maximum amount user story
 <img src="https://user-images.githubusercontent.com/56139834/208993244-86cd78f9-625e-4931-a117-0fd484ea63fe.PNG" width="700" height="500">
 3) Insufficient fund user story
 <img src="https://user-images.githubusercontent.com/56139834/208993635-e5cf84f3-5d90-41e0-8bf4-f72ceb85537e.PNG" width="700" height="500">
 4) Expired card user story
 <img src="https://user-images.githubusercontent.com/56139834/208993652-43ed5003-9bc2-4b40-91a5-25e28dfee68f.PNG" width="700" height="500">
 5) Stolen card user story
 <img src="https://user-images.githubusercontent.com/56139834/208993662-deacb828-db68-45f0-9367-875cc248c149.PNG" width="700" height="500">
 
 

