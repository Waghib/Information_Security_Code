// Exercise 1: Buffer Overflow, and Tools
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX_NAME_SIZE 256
void prepare_random_num_generator(void);
void game(void)
{
    int number; // to hold the random number 
    char buffer[24]; // to hold the player's name
    // Get a random number (from 0 to RAND_MAX)
    number = rand();
    printf("Please enter your name: ");
    fgets(buffer, MAX_NAME_SIZE, stdin); // input from 'Standard In'
    printf("Welcome ");                  // printf(buffer); //
    if (number < (int)(RAND_MAX / 20))   // Only win one time in 20
    {
        printf("YOU WIN!");
    }
    else
    {
        printf("YOU LOSE... too bad.");
    }
    printf("\n"); // 'End of line' / 'Newline' character
    return;
}
int main(void)
{
    // Program starts here.
    // Prepare the random number generator
    prepare_random_num_generator();
    game();
    return 0;
}
// ------------------------------------------------------------------------
void prepare_random_num_generator(void)
{
    struct timeval tv;
    gettimeofday(&tv,
                 NULL);
    srand(tv.tv_usec);
    return;
}

// ------------------------------------------------------------------------
