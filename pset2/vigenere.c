#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{        
    string keyword = argv[1];
    
    // checks if user insert keyword argument
    if (argc !=2)
    {
        printf("Must have string keyword\n");
        return 1;
    }
    
    // loop checks each character for alphabetical
    for (int k = 0, m = strlen(keyword); k < m; k++)
    {
        if (isalpha(keyword[k]) == false)
        {
            printf("Keyword must only contain letters A-Z and a-z\n");
            return 1;
        }
    }
    
    string plain_text = GetString();
    
    int keyword_length = strlen(keyword);
    int j = 0; 
    
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {          
        if (isalpha(plain_text[i]))
        {   
            // wraparound
            // when j == keyword_length back to zero char 
            j %= keyword_length;
            
            // convert keyword char(upper, lower) to integer
            // according to task
            int cipher = toupper(keyword[j]) - 'A';
                            
            if (isupper(plain_text[i]))
            {                                            
                int cipher_letter = (plain_text[i] - 'A' + cipher) % 26 + 'A';
                printf("%c", cipher_letter);                           
            }
            else
            {                    
                int cipher_letter = (plain_text[i] - 'a' + cipher) % 26 + 'a';
                printf("%c", cipher_letter);        
            }
            
            j++;          
        }
        else
        {
            printf("%c", plain_text[i]);
        } 
    }
    printf("\n");
    
    return 0;
}