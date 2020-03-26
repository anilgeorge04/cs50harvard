// This software converts a plain text to cipher text using a 26-alphabet key
// The key from left to right is used to map each of the 26 alphabets in order from 'A' to 'Z'
// Key must be passed at run time in command line, gets stored in argv[1]
// Key must not have repeating alphabets to ensure unique mapping of alphabets
// Cipher text only encrypts the alphabets, it leaves all other characters as is
// Cipher text retains the case (upper or lower) of the plain text regardless of case of the key

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool checkkey(char key[]);
void encrypt(long int text_len, char plain[], char key[]);

int main(int argc, string argv[])
{
    // Check that 1 key is passed correctly at run time
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        // printf("%i\n", argc);
        return 1;
    }
    else
    {
        int key_len = strlen(argv[1]);
        // Check that the key is 26 characters long
        if (key_len != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            bool valid = checkkey(argv[1]);
            if (valid == false)
            {
                // printf("Invalid key: Character repeat or non-alphabet character in key.")
                return 1;
            }
            else
            {
                string plain = get_string("plaintext: ");
                encrypt(strlen(plain), plain, argv[1]);
                return 0;
            }
        }
    }
}

// Check that the key does not have non-alphabet or repeating characters
bool checkkey(char key[])
{
    for (int i = 0; i < 26; i++)
    {
        if (toupper(key[i]) < 65 || toupper(key[i]) > 90)
        {
            printf("Do not include non-alphabet character in key.\n");
            return false;
            break;
        }
        else
        {
            int j = 25;
            while (j > i)
            {
                if (key[i] == key[j])
                {
                    printf("Do not repeat characters in key.\n");
                    return false;
                    break;
                }
                j--;
            }
        }
    }
    return true;
}

// Encrypt plain text according to provided key
void encrypt(long int text_len, char plain[], char key[])
{
    char cipher[text_len + 1];
    // Alphabet index stored in alpha_num where a or A is 0 and z or Z is 25
    // This index is used to go fetch the encrypted value from key
    int alpha_num = 0;
    for (int i = 0; i < text_len; i++)
    {
        alpha_num = toupper(plain[i]) - 65;
        if (plain[i] >= 65 && plain [i] <= 90)
        {
            cipher[i] = toupper(key[alpha_num]);
        }
        else if (plain[i] >= 97 && plain [i] <= 122)
        {
            cipher[i] = tolower(key[alpha_num]);
        }
        else
        {
            cipher[i] = plain[i];
        }
    }
    cipher[text_len] = '\0';
    printf("ciphertext: %s\n", cipher);
}