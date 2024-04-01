#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void
print_help()
{
    char *help =
    "Usage: spag [OPTION]...\n"
    "A simple command-line password generator written in C. By default, it\n"
    "prints to standard output a 16 character random password, that can\n"
    "include majuscules, minuscules, numbers and symbols.\n"
    "\n"
    "Options:\n"
    "  -h, --help            display this list of options and exit\n"
    "  -l, --length=LENGTH   set the LENGTH of the password(s)\n"
    "  -m, --no-minuscules   disable minuscule characters\n"
    "  -M, --no-majuscules   disable majuscule characters\n"
    "  -n, --no-numbers      disable numbers\n"
    "  -q, --quantity=QUANTITY\n"
    "                        set the QUANTITY of passwords to be generated\n"
    "  -s, --no-symbols      disable symbols\n"
    ;
    printf("%s", help);
}

char *
concatenate_strings(char *string1, char *string2)
{
    char *new_string = malloc(strlen(string1) + strlen(string2) + 1);
    if (new_string == NULL) {
        fprintf(stderr, "failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    strcpy(new_string, string1);
    strcat(new_string, string2);
    return new_string;
}

char *
generate_password(int length, bool majuscules, bool minuscules, bool numbers, bool symbols)
{
    // variable for holding all the enabled characters
    char *characters = "";
    
    // adding character sets to the "characters" variable
    if (minuscules)
        characters = concatenate_strings(characters, "abcdefghijklmnopqrstuvwxyz");
    if (majuscules)
        characters = concatenate_strings(characters, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (numbers)
        characters = concatenate_strings(characters, "0123456789");
    if (symbols)
        characters = concatenate_strings(characters, "!\"#$%%&'()*+,-./:;<=>?@[\\]^_`{|}~");

    // checking if all character sets have been disabled
    if (strcmp(characters, "") == 0) {
        fprintf(stderr, "you need to leave at least one set of characters enabled\n");
        exit(EXIT_FAILURE);
    }

    // allocating memory for the password variable
    char *password = malloc(length + 1);
    if (password == NULL) {
        fprintf(stderr, "failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    // inserting random enabled characters in the password variable
    for (int i = 0; i < length; i++)
        password[i] = characters[rand() % strlen(characters)];
    password[length] = '\0';

    return password;
}

int
main(int argc, char *argv[])
{
    // variables used during password generation and their default values
    int length = 16;
    int quantity = 1;
    bool majuscules = true;
    bool minuscules = true;
    bool numbers = true;
    bool symbols = true;

    // processing any options that were passed to the program
    int c;
    while (1) {
        static struct option long_options[] =
        {
            {"help",          no_argument,       0, 'h'},
            {"length",        required_argument, 0, 'l'},
            {"no-minuscules", no_argument,       0, 'm'},
            {"no-majuscules", no_argument,       0, 'M'},
            {"no-numbers",    no_argument,       0, 'n'},
            {"quantity",      required_argument, 0, 'q'},
            {"no-symbols",    no_argument,       0, 's'},
            {0, 0, 0, 0}
        };
        
        int option_index = 0;

        c = getopt_long(argc, argv, "hl:mMnq:s", long_options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 'h':
                print_help();
                return EXIT_SUCCESS;
            case 'l':
                length = atoi(optarg);
                break;
            case 'm':
                minuscules = false;
                break;
            case 'M':
                majuscules = false;
                break;
            case 'n':
                numbers = false;
                break;
            case 'q':
                quantity = atoi(optarg);
                break;
            case 's':
                symbols = false;
                break;
            case '?':
                return EXIT_FAILURE;
        }
    }

    // generating and printing password(s)
    srand((unsigned int)time(NULL));
    for (int i = 0; i < quantity; i++) {
        char *password = generate_password(length, majuscules, minuscules, numbers, symbols);
        printf("%s\n", password);
    }

    return EXIT_SUCCESS;
}