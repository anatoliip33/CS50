#include <cs50.h>
#include <stdio.h>

int main(void)
{   
    // cycle for positive number of minutes
    int minutes;
    do 
    {
        printf("How long minutes do you take a shower: ");
        minutes = GetInt();
    }
    while(minutes < 1);
    
    // count the number of bottles
    int bottles = 12 * minutes;
    
    printf("minutes: %i\n", minutes);
    printf("bottles: %i\n", bottles);
}