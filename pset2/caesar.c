#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{   
    // checks if user insert arguments  
    if (argc !=2)
    {
        printf("Usage: .asciimath key\n");
        return 1;
    }
    
    // convert a string to an integer
    int key = atoi(argv[1]);
    
    string plain_text = GetString();
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {   
        // checks if character is an alphabetic letter
        if (isalpha(plain_text[i]))
        {   
            if (isupper(plain_text[i]))
            {   
                // encipher uppercase letters
                int cipher_letter = (plain_text[i] - 'A' + key) % 26 + 'A';
                printf("%c", cipher_letter);
            }  
            else
            {
                // encipher lowercase letters
                int cipher_letter = (plain_text[i] - 'a' + key) % 26 + 'a';
                printf("%c", cipher_letter);
            }
        }
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
    
    return 0;
}