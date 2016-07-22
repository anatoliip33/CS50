#include <cs50.h>
#include <stdio.h>

int main(void)
{   
    int height;
    
    do
    {
        printf("height: ");
        height = GetInt();
    }
    while(height > 23 || height < 0 );
    
    for (int rows = 0; rows < height; rows++)
    {   
        for(int space = 0; space < height-rows-1; space++)
        {
            printf(" ");
        }
        for(int hash = 0; hash < rows+2; hash++)
        {
            printf("#");
        }
        
        printf("\n");
    }
    return 0;
}