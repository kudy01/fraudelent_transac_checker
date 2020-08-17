/* Credit Card and Transactions checker :
*
* 
*Code Written by
Name:- Kushal Jaiswal

*/
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
/* stage numbers */ 
#define STAGE_NUM_ONE 1							
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
/* stage header format string */
#define STG_HEAD "=========================Stage %d=========================\n"	
#define CARD_ID 9 /* 8+1, Card ID */
#define UNIQUE_TRANS_ID 13 /* 12+1, Transaction ID */
#define MAX_NUM_OF_TRANS 21 /* 20+1, the max transactions possible  */
#define LINE_SEPARATOR "%%%%%%%%%%" /* To store the separating line */
#define FORMAT 16 /* 15+1 , to store date and time of transaction */ 
/* Creating a struct to store transactions */
typedef struct transaction {
	char transactionID[UNIQUE_TRANS_ID];
	char cardId[CARD_ID];
	int transactionAmount;
}transaction_t;

/* Creating a struct to store cards */
typedef struct card {
	char id[CARD_ID];
	int dailyLimit;
	int transactionLimit;
}card_t;

card_t *cards;
transaction_t *transactions;
int numofTransactions = 0;

/****************************************************************/
/* Function Prototypes */
void printTransactions(transaction_t *list);
void print_stage_header(int stage_num);
void print_outcome(int check);
int getLargestTransaction(card_t *_cards , int numOfCards);
int CardComparison(const void * x, const void * y);
void stage1();
void stage2();
void stage3();
void stage4();
/****************************************************************/

/* print stage header given stage number */
void 
print_stage_header(int stage_num) {
	printf(STG_HEAD, stage_num);
}

/* Function to print the transactions in stage 3 */
void printTransactions(transaction_t *arr) {
	for(int i=0;i<numofTransactions;i++){
		printf("%s\n",arr[i].transactionID);
	}
}

/* Function to print the desired outcome of the transactions */
void 
print_outcome(int check) {
	if(check == 1) {
		printf("             IN_BOTH_LIMITS\n");
	}
	if(check == 2) {
		printf("             OVER_BOTH_LIMITS\n");
	}
	if(check == 3) {
		printf("             OVER_TRANS_LIMIT\n");
	}
	if(check == 4) {
		printf("             OVER_DAILY_LIMIT\n");
	}
}

/* To get the largest transaction amount */
int
getLargestTransaction(card_t *_cards , int TotCards) {
	int largest = 0;
	for (int i = 0; i < TotCards; i++) {
		if (_cards[i].transactionLimit > largest) {
			largest = _cards[i].transactionLimit;
		}
	}
	return largest;
}

/* To compare two cards (helps with bsearch() in line 329 */
/* Using const void* beacuse the pointers points to memory that 
   should not be modified */
int
CardComparison(const void * x, const void * y) {
	card_t* card1 = (card_t*)x;// copy so that x remains constant throughput 
	card_t* card2 = (card_t*)y;
	
	if (strcmp(card1->id, card2->id) > 0) {
		/* card1 id is greater than card2 id */
		return 1;
	 }

	if (strcmp(card1->id, card2->id) < 0) {
		/* card2 id is greater than card1 id */
		return -1;
	}

	if (strcmp(card1->id, card2->id) == 0) {
		/* card1 id = card2 id */
		return 0;
	}
	/* A dummy return */
	return -99;
}

/****************************************************************/

/* Different stages */
void 
stage1() {
	
	card_t details;
	char input[100];
	
	/* Taking the input from fscanf beacuse fscanf reads till each stage */
	fscanf(stdin, "%s", input);
	strcpy(details.id, input);
	fscanf(stdin, "%s", input);
	details.dailyLimit = atoi(input);
	fscanf(stdin, "%s", input);
	details.transactionLimit = atoi(input);

	printf("Card ID: %s\n", details.id);
	printf("Daily limit: %d\n", details.dailyLimit);
	printf("Transaction limit: %d\n\n", details.transactionLimit);

}

void 
stage2() {

	int totalCards = 0;
	char input[100];
	rewind(stdin); /* to read the file again from the start */
	
	/* reads until the end of line and puts the input in the array */
	while (fscanf(stdin, "%s", input) != EOF) { 
		if (strcmp(input, LINE_SEPARATOR) == 0) {
			/* as soon as the separating line is found break */
			break; 
		}
		totalCards++;
	}
	totalCards = (totalCards / 3); /* because fscanf reads a single word */
	
	/* to read the file again from the start */
	rewind(stdin); 
	
	cards = (card_t*)malloc(totalCards * sizeof(card_t));
	
	int counter = 0;
	int j = 0;
	
	/* fscanf reads until EOF is reached */
	while (fscanf(stdin, "%s", input) != EOF) { 
		/* check whether the separating line is reached or not */
		if (strcmp(input, LINE_SEPARATOR) == 0) {
			break;
		}
		
		if (counter == 0) {
			strcpy(cards[j].id, input);
			/* counter then allows the input to get into the next element 
			   of the struct */
			counter = 1; 
			continue;
		}
		if (counter == 1) {
			cards[j].dailyLimit = atoi(input);
			/* counter then allows the input to get into the next element 
			   of the struct */
			counter = 2;
			continue;
		}
		if (counter == 2) {
			cards[j].transactionLimit = atoi(input);
			/* counter reinitialised to store the next set of inputs */
			counter = 0;
			j++;
		}
	}

	printf("Number of credit cards: %d\n", totalCards);
	
	double limit = 0;
	for (int i = 0; i < totalCards; i++) {
		limit += cards[i].dailyLimit;
	}
	
	double average_limit = limit / totalCards;

	printf("Average daily limit: %.2f\n", average_limit);

	int largestTransaction = getLargestTransaction(cards, totalCards);
	
	/* To find the cards with the largest transaction amount */
	int numOfLargestTransactions = 0;
	for (int i = 0; i < totalCards; i++) {
		if (cards[i].transactionLimit == 
			getLargestTransaction(cards, totalCards)) {
			numOfLargestTransactions++;
		}
	}
	
	card_t *largestTransCards =  
					(card_t*)malloc(numOfLargestTransactions * sizeof(card_t));
	
	int totcards = 0;
	
	for (int i = 0; i < totalCards; i++) {
		if (cards[i].transactionLimit == largestTransaction) {
			/* fitting all the cards having the largest transaction limit in 
			   an array */
			largestTransCards[totcards++] = cards[i];
		}
	}
	
	/* finding the card with the smallest id and largest transaction limit */
    card_t smallestId = largestTransCards[0];
	for (int i = 0; i < totcards; i++) {
		if(strcmp(largestTransCards[i].id,smallestId.id) < 0){
			smallestId = largestTransCards[i];
		}
	}
	
	printf("Card with the largest transaction limit: %s\n\n", smallestId.id);
}

void 
stage3() {
	
	transactions = 
			(transaction_t*)malloc(MAX_NUM_OF_TRANS * sizeof(transaction_t));
    
	transaction_t *Transaction = (transaction_t*)malloc(sizeof(transaction_t));
	
	char input[100];
	/* A dummy string to store the date and time of transaction */
	char dummy[FORMAT];
	/* To read the entire message again and rewind it back later as a 
	   failsafe */
	rewind(stdin);
	while (fscanf(stdin, "%s", input) != EOF) {
	}
	rewind(stdin);
	
	
	int counter = 0;
	int transac_header = 0;
	
	while (strcmp(input, LINE_SEPARATOR) != 0 && transac_header != 1) {
		
		/* input is taken till the separating line is found */
		fscanf(stdin, "%s", input);
		if (strcmp(input, LINE_SEPARATOR) == 0) {
			transac_header = 1;
		}
	}
	/* now the input is taken after the separating line to store the 
		transactions */ 
		
	while (fscanf(stdin, "%s", input) != -1) {
		if (counter == 0) {
			/* the details of the transactions are stored in the struct */  
			strcpy(Transaction->transactionID, input);
			counter = 1;
			continue;
		}
		if (counter == 1) {
			/* the details of the transactions are stored in the struct */ 
			strcpy(Transaction->cardId, input);
			counter = 2;
			continue;
		}
		if (counter == 2) {
			/* the date and time of the transaction is put into a dummy 
			   string */
			strcpy(dummy, input);
			counter = 3;
			continue;
		}
		if (counter == 3) {
			/* the details of the transactions are stored in the struct */ 
			Transaction->transactionAmount = atoi(input);
			/* counter reinitialised to store the next set of inputs */
			counter = 0;
			transactions[numofTransactions++] = *Transaction;
		}
	}

	printTransactions(transactions);

	printf("\n");
	
}
void 
stage4() {

	/* Counting the total number of cards */ 
	int totalCards = 0;
	char input[100];
	rewind(stdin); /* to read the file again from the start */
	
	/* reads until the end of line and puts the input in the array */
	while (fscanf(stdin, "%s", input) != EOF) { 
		if (strcmp(input, LINE_SEPARATOR) == 0) {
			/* as soon as the separating line is found break */
			break; 
		}
		totalCards++;
	}
	totalCards = (totalCards / 3); /* because fscanf reads a single word */
	
	int outcome=0; /* To print the outcome of the transaction */
	
	card_t *check = (card_t*)malloc(sizeof(card_t));
	/* The values have to be sorted for bsearch() to work */
	
	/* To get O(nlogm) average time complexity for this stage we use qsort
	   because it is the fastest sort algorithm and has complexity 
       of O(nlogm)*/
	   
	qsort(cards, totalCards, sizeof(*check), CardComparison);

	for (int i = 0; i < numofTransactions; i++) {
		
		/* Using the Binary Search Algorithm */
		check = (card_t*)bsearch(transactions[i].cardId, cards,
			                  totalCards, sizeof(card_t), CardComparison);
		
		/* Check if transaction amount is less 
		   than transaction and daily limit */
		if ((transactions[i].transactionAmount < check->transactionLimit) && 
			(transactions[i].transactionAmount < check->dailyLimit)) {
			
			printf("%s", transactions[i].transactionID);
			outcome=1;
			print_outcome(outcome);
			/* reinitialising to avoid errors */
			outcome=0;
		}
		
		/* Check if transaction amount is greater 
		   than transaction and daily limit */
		if ((transactions[i].transactionAmount > check->transactionLimit) && 
			(transactions[i].transactionAmount > check->dailyLimit)) {
			
			printf("%s", transactions[i].transactionID);
			outcome=2;
			print_outcome(outcome);
			/* reinitialising to avoid errors */
			outcome=0;
		}
		
		/* Check if transaction amount is greater than transaction limit
		   but less than daily limit */
		if ((transactions[i].transactionAmount > check->transactionLimit) && 
			(transactions[i].transactionAmount < check->dailyLimit)) {
			
			printf("%s", transactions[i].transactionID);
			outcome=3;
			print_outcome(outcome);
			/* reinitialising to avoid errors */
			outcome=0;
		}
		
		/* Check if transaction amount is lesser than transaction limit
		   but greater than daily limit */
		if ((transactions[i].transactionAmount < check->transactionLimit) && 
			(transactions[i].transactionAmount > check->dailyLimit)) {
			
			printf("%s", transactions[i].transactionID);
			outcome=4;
			print_outcome(outcome);
			/* reinitialising to avoid errors */
			outcome=0;
		}
	}

	printf("\n");
	
	/* freeing the malloc-ed variables */
	free(cards);
	free(transactions);
}

/****************************************************************/

int 
main(int argc, char *argv[]) {
	
	/* calling all functions */
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	stage1();
	 
	/* print stage header */
	print_stage_header(STAGE_NUM_TWO);
	stage2();
	
	/* print stage header */
	print_stage_header(STAGE_NUM_THREE);
	stage3();
	
	/* print stage header */
	print_stage_header(STAGE_NUM_FOUR);
	stage4();
	
	return 0;
}
