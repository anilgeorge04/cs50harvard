// Outputs the READABILITY GRADE LEVEL of a passage provided by the user
// Grade Level calculated by the following Coleman-Liau Index formula (rounded to nearest whole number)
// Index = 0.0588 * L - 0.296 * S - 15.8
// L - avg no of letters per 100 words, S - avg no of sentences per 100 words

// Input Passage ASSUMPTIONS & DEFINITIONS made for this software version
// A letter is any character from 'a' to 'z' or 'A' to 'Z'
// A word is a sequence of characters separated by " "
// A hyphenated word is considered to be 1 word, ex: "sister-in-law" is one word with 11 letters
// A sentence shall not start or end with a space, it must only end with "?" or "." or "!"
// A sentence must not have multiple spaces in a row
// Version Limitation: Any period used within one grammatical sentence will also be considered as the end of a sentence
// Ex: "Mr. and Mrs. George are out of town." will be considered as 3 sentences

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float count_letters(long int len, string pass);
float count_words(long int len, string pass);
float count_sentences(long int len, string pass);

int main(void)
{
    string passage;
    passage = get_string("Text: ");
    long int len = strlen(passage);
    // printf("Length: %li\n", len);

    float l = count_letters(len, passage);
    printf("%f letters(s)\n", l);
    float w = count_words(len, passage);
    printf("%f words(s)\n", w);
    float s = count_sentences(len, passage);
    printf("%f sentences(s)\n", s);

    // Average number of letters (L) and sentences (S) per 100 words
    float L = l * 100 / w;
    float S = s * 100 / w;

    // Calculate GRADE by Coleman-Liau Index
    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    // Function round() declared under <math.h>
    // printf("Index %f rounded to %i\n", index, round(index));

    if (round(index) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (round(index) > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

// Count number of letters in the passage
float count_letters(long int len, string pass)
{
    int l_count = 0;
    char pass_cap [len + 1];
    for (int i = 0; i < len; i++)
    {
        // Convert letters to upper case & calculate total letters with ASCII values 65 to 90
        // Function toupper() declared under <ctype.h>
        pass_cap [i] = toupper(pass[i]);
        if (pass_cap[i] >= 65 && pass_cap[i] <= 90)
        {
            l_count += 1;
        }
        pass_cap [len] = '\0';
    }
    // printf("Upper: %s\n", pass_cap);
    return (float) l_count;
}

// Count number of words in the passage
float count_words(long int len, char pass[])
{
    // Function get_string() ensures at least 1 word in input passage
    int w_count = 1;
    for (int i = 0; i < len; i++)
    {
        if (pass[i] == ' ')
        {
            w_count += 1;
        }
    }
    return (float) w_count;
}

// Count number of sentences in the passage
float count_sentences(long int len, char pass[])
{
    // Sentence ends with ? or . or !
    int s_count = 0;
    for (int i = 0; i < len; i++)
    {
        if (pass[i] == '!' || pass[i] == '.' || pass[i] == '?')
        {
            s_count += 1;
        }
    }
    if (s_count == 0)
    {
        return (float) s_count + 1;
    }
    else
    {
        return (float) s_count;
    }
}
