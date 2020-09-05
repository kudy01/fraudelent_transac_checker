# fraudelent_transac_checker
in this program, the message consists credit card records, sorted by card id, followed by daily limit and transaction limit.The transaction limit does not exceed the daily limit.
The line “%%%%%%%%%%” indicates the end of credit card records and the start of transactions.The transactions are sorted by date and time.The program works in 4 stages.
The first stage reads the entire message and outputs the first credit card record. The second stage counts the number of records and displays the one with the largest transaction 
limit as well as the average daily limit for the cards. The 3rd stage designs a struct to represent a transaction, reads in the transactions, stores them in a linked data structure, and outputs their IDs.
The next stage checks whether a transaction may be fraudulent.The program goes through the transactions. For each transaction, it check if the transaction exceeds the transaction limit or the daily limit of the corre- sponding credit card.

Example:
SAMPLE INPUT -
3tu2iywy 10000 800
ceww0p66 150 100
v0xyil5t 3000 500
vb3dtxp0 5000 300
xnwxw8tl 2000 800
%%%%%%%%%%
v5buvljyh0lg vb3dtxp0 2020:04:07:03:50:45 42
1yuy3noa2uxu xnwxw8tl 2020:04:08:04:16:20 729
gl3utnnwxf49 xnwxw8tl 2020:04:08:05:39:00 670
9mopqy3snk3h ceww0p66 2020:04:15:08:06:49 86
6hjqaydtmrq5 vb3dtxp0 2020:04:15:10:09:50 213
mlgtqk8oo74e ceww0p66 2020:04:15:13:45:29 95
u7s604f0u6bz xnwxw8tl 2020:04:22:15:30:43 799
2siil57yqe5k vb3dtxp0 2020:04:23:17:26:20 573
vzdg2z09t7zp v0xyil5t 2020:04:29:18:03:00 3489
n6lcvjyrhvwt 3tu2iywy 2020:04:29:23:07:00 4592

SAMPLE OUTPUT-
=========================Stage 1=========================
Card ID: 3tu2iywy
Daily limit: 10000
Transaction limit: 800

=========================Stage 2=========================
Number of credit cards: 5
Average daily limit: 4030.00
Card with the largest transaction limit: 3tu2iywy

=========================Stage 3=========================
v5buvljyh0lg
1yuy3noa2uxu
gl3utnnwxf49
9mopqy3snk3h
6hjqaydtmrq5
mlgtqk8oo74e
u7s604f0u6bz
2siil57yqe5k
vzdg2z09t7zp
n6lcvjyrhvwt

=========================Stage 4=========================
v5buvljyh0lg             IN_BOTH_LIMITS
1yuy3noa2uxu             IN_BOTH_LIMITS
gl3utnnwxf49             IN_BOTH_LIMITS
9mopqy3snk3h             IN_BOTH_LIMITS
6hjqaydtmrq5             IN_BOTH_LIMITS
mlgtqk8oo74e             IN_BOTH_LIMITS
u7s604f0u6bz             IN_BOTH_LIMITS
2siil57yqe5k             OVER_TRANS_LIMIT
vzdg2z09t7zp             OVER_BOTH_LIMITs
n6lcvjyrhvwt             OVER_TRANS_LIMIT
