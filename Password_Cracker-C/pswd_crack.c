//This program uses brute force to "crack" passwords
//it supports capital and lowercase letters, numbers, and most symbols
//it takes a long time with passwords more than 3 characters
//DISCLAIMER: "this program is for educational purposes only
// and I don't condone hacking or illegal things" -Cody

 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 15 //max length of password
#define ALPH_SIZE 94 //size of the alphabet (counting all used symbols and numbers)


//returns a character array containing all possible characters in the password
char* getAlph(){
    char *alph = malloc(ALPH_SIZE * sizeof(char)); //allocate memory for 93 chars + \0
    if (alph == NULL) { //error handling
        printf("Memory allocation failed\n");
        exit(1);
    }
    //fills the array characters from the ascii table
    for(int i = 0; i < ALPH_SIZE - 1; i++){
        alph[i] = i + 33; //the first character used, "!", is ascii 33
        //printf("%c ", alph[i]);
    }
    alph[ALPH_SIZE - 1] = '\0'; //end string
    return alph;
}
//recursive cracking algorithm
//finds permutations of the alphabet with the same length as the password
void crack(char alph[], char guess[], int setSize, int len, char password[], bool *found) {
    if (len == 0) { //base case, length will be 0 when a full permutation is formed
        if(strcmp(guess, password) == 0){ //if the password is found
            printf("PASSWORD FOUND: %s", guess);
            *found = true;
            return;
        }
        printf("%s\n", guess); //print permutations to console
        return;
    }

    for (int i = 0; i < setSize; ++i) { //iterates through all of the characters in our alphabet
        if(*found == true){ //stop function if the password is found
            return;
        }
        char nextGuess[16]; //will contain the current guess with the next letter on the end
        strcpy(nextGuess, guess); 
        char letter[2];
        letter[0] = alph[i];
        letter[1] = '\0';
        strcat(nextGuess, letter);
        //recursive call with the nextGuess, and the length decremented because a character was added
        crack(alph, nextGuess, setSize, len - 1, password, found);
    }

}

int main(){
    char password[MAX_LENGTH]; //max 15 chars for password
    int length;
    //get the alphabet
    char* alphabet = getAlph();
    //inititalize the guess
    char guess[MAX_LENGTH + 1];
    guess[0] = '\0';
    //boolean whether or not the password is found
    bool f = false;
    bool *found = &f;
    //prompt user for password
    printf("*****************************\n");
    printf("Brute Force Password Cracker!\n");
    printf("Be advised that passwords longer than 3 characters take LONG periods of time to crack.\n");
    printf("Password can't contain spaces or tildas.\n");
    printf("Enter password (15 characters max): ");
    scanf("%s", password);
    length = strlen(password);
    //crack the password
    crack(alphabet, guess, strlen(alphabet), length, password, found);
    //free malloc
    free(alphabet);
    return 0;
}