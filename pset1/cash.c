#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

// Takes user input for how much change is owed
int get_cents(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);
    return cents;
}

// Calculates maximum number of quarters that can be given back for the change owed
int calculate_quarters(int cents)
{
    int quarters = 0;
    while (cents - 25 >= 0)
    {
        cents -= 25;
        quarters++;
    }
    return quarters;
}

// Calculates maximum number of dimes that can be given back for the change owed
int calculate_dimes(int cents)
{
    int dimes = 0;
    while (cents - 10 >= 0)
    {
        cents -= 10;
        dimes++;
    }
    return dimes;
}

// Calculates maximum number of nickels that can be given back for the change owed
int calculate_nickels(int cents)
{
    int nickels = 0;
    while (cents - 5 >= 0)
    {
        cents -= 5;
        nickels++;
    }
    return nickels;
}

// Calculates maximum number of pennies that can be given back for the change owed
int calculate_pennies(int cents)
{
    int pennies = 0;
    while (cents - 1 >= 0)
    {
        cents--;
        pennies++;
    }
    return pennies;
}
