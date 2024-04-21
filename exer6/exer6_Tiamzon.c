// Exercse 6: Arrays
// Tiamzon, Edgar Alan Emmanuel III B.
// ST5L
// 03 - 22 - 24

#include <stdio.h>
#include <stdlib.h>

int get_size(); // getting the size of an array
void filled_Arr(int array_size, int *array); // inputs values in the array
void factor_Arr(int *array, int size, int index); // factors single element within the array
void factor_AllArr(int *array, int size); // factors all elements within the array

int main() {
    int input_size, choice, initialized = 0;
    input_size = get_size(); // calls the function that allows the user to input the size of the array

    // create dynamic array of length input_size    
    int *array = (int *)malloc(sizeof(int) * input_size); // considering the size of an array in input_size

    // loop main menu
    // allows the user to choose a function
    do { 
        printf("-------------------------------------------\n");
        printf("0 | Input numbers\n");
        printf("1 | Factors of an element in the array\n");
        printf("2 | Factors of all elements in the array\n");
        printf("3 | Exit\n");
        printf("-------------------------------------------\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 0:
                filled_Arr(input_size, array); // calls the function that will fill the elements of the array based on the user's input
                initialized = 1; // this is used as a flag to indicate whether the array has been initialized with values
                printf("\n");
                break;

            case 1:
                if (!initialized) { // checks for initialization
                    printf("ERROR: Array is empty! \n");
                    printf("\n");
                    continue;
                }
                int index; // returns value

                printf("Enter the index of the element: "); // allows the user to specify on which index they want to factor
                scanf("%d", &index);

                if (index < 0 || index >= input_size) { // this validates if the user's input for index are within the range of the given array
                    printf("ERROR: Invalid index range! \n");
                    printf("\n");
                    continue;
                }
                factor_Arr(array, input_size, index); // calls the function to factor a single element
                printf("\n");
                break;

            case 2:
                if (!initialized) { // checks for initialization
                    printf("ERROR: Array is empty! \n");
                    printf("\n");
                    continue;
                }
                factor_AllArr(array, input_size); // calls the funcion to factor all array
                printf("\n");
                break;

            case 3:
                printf("Program is terminating....Good bye!");
                free(array); // free the array before exiting the program
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 3); // 

    return 0;
}

// Asks the user to enter the size of the array
int get_size() { 
    int array_size = 0; // this check if there are already array to be found

    do {
        printf("Enter the size of the array: ");
        scanf("%d", &array_size);

        if (array_size <= 0) {
            printf("ERROR: Invalid size!\n");
        }

    } while (array_size < 1);

    return array_size;
}

// Asks the user to input values for the given array
void filled_Arr(int array_size, int *array) {
    int i;
    
    // indicates the loop on the entered array
    for (i = 0; i < array_size; i++) { // asks the for valid index

        do {
            printf("Enter array [%d]: ", i);
            scanf("%d", &array[i]);

            if (array[i] <= 0) {
                printf("\nERROR: Enter a non-negative integer!\n");
            }
        } while (array[i] <= 0);
    }
}

// It prompts the factor values of a single element within the array
void factor_Arr(int *array, int size, int index) {
    int i;
    int hasFactors = 0; // this checks if any factors are found
    int element = array[index]; // The chosen element

    printf("The factors of %d in the array are: ", element);

    for (i = 2; i <= element / 2; i++) { // loop starts at 2 because factors of an array cannot be greater that half of the number except on the number itself and 1
        if (element % i == 0) {

            // Check if the factor exists in the array
            int j, factorExists = 0;
            for (j = 0; j < size; j++) {
                if (array[j] == i) {
                    factorExists = 1;
                    break;
                }
            }
            if (factorExists) {
                printf("%d ", i);
                hasFactors = 1;
            }
        }
    }

    if (!hasFactors) { // checks if the value has factors to be found within the array
        printf("None");
    }
    printf("\n");
}

// It prompts the factor values of all elements within the array
void factor_AllArr(int *array, int size) {
    int i;
    for (i = 0; i < size; i++) { // iterate based on the given array to factor all the elements
        printf("\n");
        factor_Arr(array, size, i); // calls the function as it has the same loop to check for factors
    }
}
