# paymentApplication-project-C-sprints
This project is the first project for the Automotive bootcamp organized by sprints, this project is developed by team 6

## Team Members
- Ahmed Mohamed Hesham
- Momen Hassan
- Ahmed Atef

## About Project 
It consists of three layers:

### 1- Card Module
This module asks the user to enter his Card Holder Name, Primary Account Number, and Card Expiration Date, checks on every input and if there is a wrong input it ask the user to re-enter it.

After completing the previous inputs it saves it in a transaction data structure.
 
### 2- Terminal Module
This module checks on the expiration date at the begging and if the card is expired, it rejects it.

If not, it will asks for the transaction amount, if the transaction amount bigger than the configured maximum transaction amount it will decline the process.

If not, it will save these enteries in the transaction data structure.

### 3- Server Module
This module will recieve the transaction data structure sent from card module and terminal module and then checks on:

1 - If primary account number is valid.

2 - If that account's balance is available for transaction.

3 - If that account's card is not blocked.

Then return those states and then if the server is ok it will subtract the transaction amount from the account's balance.

Finally it saves and list the transaction data and state and the program ends.

---


