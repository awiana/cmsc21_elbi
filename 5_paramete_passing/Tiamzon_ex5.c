// Exercise 5: Parameter Passing
// Tiamzon, Edgar Alan Emmanuel III B.
// ST5L
// 03 - 15 - 24

#include <stdio.h>

// Function prototypes
void getInput(int *x, int *y);
void swapValues(int *num1, int *num2);
int primeChecker(int y);
void getLargest(int x, int y, int *large_VAL1, int *large_VAL2, int *large_VAL3);
void printLargest(int *large_VAL1, int *large_VAL2, int *large_VAL3);

int main()
{
    int x, y, large_VAL1, large_VAL2, large_VAL3; // initialize variable

    do
    {
        getInput(&x, &y); // passing the addresses variables x and y as arguments

        if (x < 2 && y < 2)
        {
            printf("Invalid range!\n");
            continue;
        }

        if (x > y)
        {
            swapValues(&x, &y);
        }

        getLargest(x, y, &large_VAL1, &large_VAL2, &large_VAL3); // getting the largest variables with the addresses
        printLargest(&large_VAL1, &large_VAL2, &large_VAL3);     // printing the largest variables with the addresses

    } while (large_VAL1 == 0 && large_VAL2 == 0 && large_VAL3 == 0); // executes at least once and continues the loop as long as the three variables are equal to 0

    return 0;
}

void getInput(int *x, int *y)
{

    printf("\nEnter a value for x: ");
    scanf("%d", x);

    printf("Enter a value for y: ");
    scanf("%d", y);
}

void swapValues(int *num1, int *num2)
{ // code reference: https://stackoverflow.com/questions/73925426/pass-by-reference-in-c-for-swapping-function

    int swap;

    swap = *num1; // actual swapping of values
    *num1 = *num2;
    *num2 = swap;
}

int primeChecker(int y)
{ // code reference: https://www.programiz.com/c-programming/examples/prime-number

    int i;

    if (y <= 1)
    {
        return 0;
    }
    for (i = 2; i < y; i++)
    {
        if (y % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

void getLargest(int x, int y, int *large_VAL1, int *large_VAL2, int *large_VAL3)
{   

    *large_VAL1 = *large_VAL2 = *large_VAL3 = 0; // it initialize largest primes to 0

    for (int i = y; i >= x; i--)
    {

        if (primeChecker(i))
        {
            if (i > *large_VAL1)
            {
                *large_VAL3 = *large_VAL2;
                *large_VAL2 = *large_VAL1;
                *large_VAL1 = i;
            }

            else if (i > *large_VAL2)
            {
                *large_VAL3 = *large_VAL2;
                *large_VAL2 = i;
            }

            else if (i > *large_VAL3)
            {
                *large_VAL3 = i;
            }
        }
    }
}

void printLargest(int *large_VAL1, int *large_VAL2, int *large_VAL3)
{

    if (*large_VAL1 == 0)
    {
        printf("There is no prime number! \n");
    }

    else if (*large_VAL2 == 0)
    {
        printf("There is one prime number: %d", *large_VAL1);
    }

    else if (*large_VAL3 == 0)
    {
        printf("There is two prime numbers: %d, %d", *large_VAL1, *large_VAL2);
    }

    else
    {
        printf("There is three prime numbers: %d, %d, %d", *large_VAL1, *large_VAL2, *large_VAL3);
    }
}
