#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
// Input verification:
bool isValidFormat(const int numArgsRead, const int numArgsNeed);
double getValidDouble(const char* prompt);
int getValidInt(const char* prompt);
int getPosInt(const char* prompt);
double getPosDouble(const char* prompt);

// Checks format valid
bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;
  do {
    scanf("%c", &character);
		if (!isspace(character)){
			formatIsGood = false;
		}
	} while (character != '\n');
  return formatIsGood;
}

// Prompts the user and gets a valid double value.
double getValidDouble(const char* prompt) {
  double num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do {
    printf("%s", prompt);
    numArgsRead = scanf(" %lf", &num);
  } while (!isValidFormat(numArgsRead, numArgsNeeded));

  return num;
}
// Prompts the user and gets a valid integer value.
int getValidInt(const char* prompt) {
  int num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do {
    printf("%s", prompt);
    numArgsRead = scanf(" %d", &num);
  } while (!isValidFormat(numArgsRead, numArgsNeeded));
  return num;
}
// Gets a positive integer value.
int getPosInt(const char* prompt) {
    int num;
    do {
        num = getValidInt(prompt);
    } while (!(num > 0));
    return num;
}
// Gets a positive double value.
double getPosDouble(const char* prompt) {
    double num;
    do {
        num = getValidDouble(prompt);
    } while (!(num > 0));
    return num;
}

// Gets starting balance
double getBalance() {
    return getPosDouble("Enter starting balance: ");
}

// Gets percentage of capital risked
double getPercentRisk() {
    return getPosDouble("What percent of your money will you be risking every bet: ");
}
// Gets winrate of trades
double getWinrate() {
    return getPosDouble("Enter how often you win as a decimal (Format: '.66' = 66%): ");
}
// Gets Reward to Risk (normalized so risk will always be 1 * %risk, reward will be ratio * %risk)
double getRR() {
		double num = getPosDouble("Enter the ratio of your reward for winning to your loss for losing (Format: '2' for 2/1 OR '2.5' for 5/2): ");
		return num;
}

// Gets total number of trades simulated
double getNumTrades() {
    return getPosDouble("How many times will you take a trade under these parameters? ");
}

void simulateTrades(double balance, double risk, double winrate, double rr, double numTrades) {
		printf("$%.2f\n", balance);

		double numTradesBegin = numTrades;


		// For numTrades to simulate...
		while (numTrades > 0)
		{
			// First create random number generator with a 'winrate' chance of winning
			double randomZeroToOne = ((double) rand() / (RAND_MAX));
			bool winTrade = false;

			// If the number from 0 to 1 is less than winrate (ex: .7), simulate a trade won. Otherwise simulate a loss.
			if (randomZeroToOne <= winrate)
			{
				winTrade = true;
			}

			// If game was won, add the reward to the balance, otherwise, subtract the loss from the balance
			if (winTrade == true)
			{
				balance = balance + ((risk * balance) * rr);
			}
			else
			{
				balance = balance - ((risk * balance) * 1);
			}
			numTrades--;
			printf("$%.2f\n", balance);
		}
		printf("Final balance after %.0f trades is: $%.2f", numTradesBegin, balance);
}

int main()
{
		double balance = getBalance();
		double percentRisk = getPercentRisk();
		double winrate = getWinrate();
		double rr = getRR();
		double numTrades = getNumTrades();

    simulateTrades(balance, percentRisk, winrate, rr, numTrades);

    return 0;
}
