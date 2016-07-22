#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{   
    float change;
    int coins = 0;
    int amount;
    
    do
    {
        printf("O hai! How much change is owed?\n");
        change = GetFloat();       
        
    }
    while(change <= 0);
    
    //convert change into cents
    amount = (int)round(change*100); 
    
    // quarters
    while(amount >= 25)
    {
      coins++;
      amount -= 25;
    }
    
    // ten cents
    while(amount >= 10)
    {
      coins++;
      amount -= 10;
    }
    
    // five cents
    while(amount >= 5)
    {
      coins++;
      amount -= 5;
    }
    
    // one cent
    while(amount >= 1)
    {
      coins++;
      amount -= 1;
    }
    
    // prints number of coins in change
    printf("%d\n", coins);
    
    return 0;
}