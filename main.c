#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

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


int main() {
    StringArray array_list = load_file();
    char* word = getting_word(array_list);
    printf("%s\n", word);
    return 0;
}