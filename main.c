#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//defining vars
#define MAX_LINES 100
#define MAX_LEN 100

//making a simple way to return strings
typedef struct {
    char lines[MAX_LINES][MAX_LEN];
    int count;
} StringArray;

//file reader
StringArray load_file() {
    StringArray result = {.count = 0};

    char* filename = "text.txt";

    //getting the file
    FILE *f = fopen(filename, "r");

    printf("Trying to read %s\n", filename);

    //checking if the file was opened
    if (!f) {
        printf("File not found\n");
        return result;
    }

    printf("%s, has been found\n", filename);

    //placing all the inputs into the file
    while (fgets(result.lines[result.count], MAX_LEN, f)) {
        result.count++;
    }
    fclose(f);
    return result;
}

//getting a random word from the list
char* getting_word(StringArray array) {
    //getting the count of the list
    int list_size = array.count;

    //getting the random word from the list
    srand(time(NULL));
    int random_inx = rand() % list_size;
    char* word = array.lines[random_inx];

    return word;

}

//counting the number of letters in a word
int letter_count(char* word) {
    int count = 0;
    for (int i = 0; i < strlen(word); i++) {
        ++count;
    }
    return count;
}

//printing the correct ammount of blank spaces in the word
void space_print(int word_size) {
    for (int i = 0; i < word_size; i++) {
        printf("_");
    }
    printf("\n");
}

//keeping track of how many times you can miss
void missing_tracker(int misses) {
    printf("Tries Left: %d\n", misses);
}

int checking_guess(char guess, char* word, int word_size) {
    int i = 0;
    while (i < word_size) {
        if (guess == word[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}

int main() {
    //loading the main text file
    StringArray array_list = load_file();

    //vars that will help make the game
    char* word = getting_word(array_list);
    int words_count_null = letter_count(word); //for looping the original string
    int words_count = --words_count_null; //for displaying the word
    int misses_left = 10;

    printf("Orginal word: %s", word);
    //for the game
    missing_tracker(misses_left);
    printf("Length of word: %d\n", words_count);
    space_print(words_count_null);
    char guess;
    printf("Guess a letter: \n");
    scanf("%c", &guess);

    if (checking_guess(guess, word, words_count_null)) {
        printf("There is a letter like this!\n");
    }
    else {
        printf("No letter here\n");
    }


    return 0;
}