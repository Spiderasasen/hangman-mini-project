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

//placing things into a list
void appendList(char guess, char array[], int* size) {
    // prevent duplicates
    for (int i = 0; i < *size; i++) {
        if (array[i] == guess) return;
    }

    array[*size] = guess;
    (*size)++;
    array[*size] = '\0';
}


//printing out the list with the guess
void word_revile(char correct_letters[], int correct_size, char* word, int word_size) {
    for (int i = 0; i < word_size; i++) {
        int found = 0;

        for (int j = 0; j < correct_size; j++) {
            if (word[i] == correct_letters[j]) {
                found = 1;
                break;
            }
        }

        if (found)
            printf("%c", word[i]);
        else
            printf("_");
    }
    printf("\n");
}

//checks the correct list to see if it cotains all letters of the word
int is_finished(char correct_letters[], int correct_size, char* word, int word_size) {
    for (int i = 0; i < word_size; i++) {
        int found = 0;

        for (int j = 0; j < correct_size; j++) {
            if (word[i] == correct_letters[j]) {
                found = 1;
                break;
            }
        }

        if (!found) return 0;
    }
    return 1;
}


int main() {
    //loading the main text file
    StringArray array_list = load_file();

    //vars that will help make the game
    char* word = getting_word(array_list);
    int words_count_null = letter_count(word); //for looping the original string
    int words_count = --words_count_null; //for displaying the word
    int misses_left = 10;
    char correct[MAX_LEN] = "";
    char incorrect[MAX_LEN] = "";
    int correct_size = 0;
    int incorrect_size = 0;
    int win_check = 0;

    word[strcspn(word, "\n")] = '\0'; // remove newline
    int word_size = strlen(word);

    while (!win_check && misses_left > 0) {

        printf("Tries Left: %d\n", misses_left);
        printf("Incorrect letters: %s\n", incorrect);

        word_revile(correct, correct_size, word, word_size);

        char guess;
        printf("Guess a letter: ");
        scanf(" %c", &guess);

        if (checking_guess(guess, word, word_size)) {
            appendList(guess, correct, &correct_size);
        } else {
            appendList(guess, incorrect, &incorrect_size);
            misses_left--;
        }

        win_check = is_finished(correct, correct_size, word, word_size);
    }


    return 0;
}