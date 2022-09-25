#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "list.h"
#include "input.h"
#include "string-utils.h"
#include "display.h"



#define HIDDEN_CHAR '*'
#define WORD_SIZE 20



void hideChars(char* printed_word)
{
    char first_char = printed_word[0];
    for(size_t i=0; i<strlen(printed_word); i++)
        printed_word[i] = (printed_word[i] == first_char) ? first_char : HIDDEN_CHAR;
}


void replace_all_char_occurences_in_str(const char* secret_word, char* printed_word, char c)
{
    for(size_t i=0; i<strlen(secret_word); i++)
    {
        if(secret_word[i] == c)
            printed_word[i] = c;
    }
}


void choose_word(const char* file_name, char* secret_word)
{
    FILE* wordlist = NULL;
    char temp_word[WORD_SIZE];
    int nb_words = 0;
    int random_index;

    wordlist = fopen(file_name, "r");
    if(wordlist == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while(fgets(temp_word, WORD_SIZE, wordlist))
        nb_words++;

    if(fseek(wordlist, 0L, SEEK_SET) != 0)
    {
        perror("Error seeking beginning of file");
        exit(EXIT_FAILURE);
    }

    random_index = rand() % nb_words + 1;
    for(int i=0; i<random_index; i++)
        fgets(secret_word, WORD_SIZE, wordlist);
    replace_line_feed(secret_word);
    secret_word = strupr(secret_word);
    fclose(wordlist);
}


int main()
{
    srand(time(NULL));

    int level;
    int attempts = 3;
    char c;
    char file_name[30];
    char secret_word[WORD_SIZE];
    char printed_word[WORD_SIZE];
    bool discovered = false;
    List tried_chars = new_list();

    puts("\n"BLU"[*] Choose the difficulty");
    puts("    1 => EASY");
    puts("    2 => INTERMEDIATE");
    puts("    3 => DIFFICULT"COLOR_RESET"\n");

    if(read_integer(&level) == NULL)
    {
        puts(""RED"You didn't select a difficulty..."COLOR_RESET"");
        exit(EXIT_FAILURE);        
    }

    if(level == 1)
        strcpy(file_name, "wordlists/1_easy.txt");
    else if(level == 2)
         strcpy(file_name, "wordlists/2_intermediate.txt");
    else if(level == 3)
         strcpy(file_name, "wordlists/3_difficult.txt");
    else
    {
        puts(""RED"You didn't select a difficulty..."COLOR_RESET"");
        exit(EXIT_FAILURE);
    }

    choose_word(file_name, secret_word);
    strcpy(printed_word, secret_word);
    hideChars(printed_word);

    while(attempts > 0 && discovered == false)
    {
        printf(""BLU"\n=> %s"COLOR_RESET"\n", printed_word);
        print_list(tried_chars);

        while(true)
        {
            c = read_capital_letter();
            if(contains(tried_chars, c))
               puts(""YEL"You already played this letter !"COLOR_RESET"");
            else
                break;
        }
        tried_chars = add(tried_chars, c);

        if(strchr(secret_word, c) != NULL)
        {
            replace_all_char_occurences_in_str(secret_word, printed_word, c);

            if(strcmp(printed_word, secret_word) == 0)
            {
                puts("\n"GRN"Congratulations, you won !");
                discovered = true;
            }
        }
        else
        {
            attempts--;
            printf(""RED"The word does not contain letter '%c'. %d attempts left..."COLOR_RESET"\n", c, attempts);
            if(attempts == 0)
                puts("\n"RED"Sorry, you lost...");
        }
    }

    printf("The word was %s"COLOR_RESET"\n\n", secret_word);
    tried_chars = destroy_list(tried_chars);
    return EXIT_SUCCESS;
}
