// Exercise 7: Strings and Multidimensional Arrays
// Edgar Alan Emmanuel B. Tiamzon III
// ST5L
// 04 - 08 - 24

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int max_num_name = 51; // Maximum length for the name

// Function prototypes
int main_menu(); // Function prototype for the main menu
char *get_len_string(); // Function prototype to get a string of variable length
char **get_crushes(int list_crush); // Function prototype to get an array of crushes
int remove_common_char(char *name1, char *name2); // Function prototype to remove common characters
void calculate_flames(char *name1, char *name2); // Function prototype to calculate FLAMES result
void free_array(char **array, int size); // Function prototype to free memory allocated for an array

int main() { 
    char *name, **crushes; 
    int crush_qty, running = 1, initialized = 0, input_buffer; 

    printf("Enter your name: "); 
    name = get_len_string(); 

    do { // Loop to ensure the user enters a valid number of crushes
        printf("Enter the number of crushes you have: "); 
        scanf("%d", &crush_qty); 

        // Clear the input buffer
        while ((input_buffer = getchar()) != '\n' && input_buffer != EOF); // Clear the input buffer

        if (crush_qty <= 0) { // Check if the number of crushes is less than or equal to zero
            printf("Error: You must have at least one crush to play FLAMES.\n\n");
        }
    } while (crush_qty <= 0); // Continue looping until a valid number of crushes is entered

    while (running) { // Main loop for the program menu
        switch (main_menu()) { 
            case 1: 
                crushes = get_crushes(crush_qty); 
                initialized = 1; // Set the initialized flag to true
                break;
            case 2: 
                if (!initialized) { // Check if crushes have been initialized
                    printf("Error: The array is still empty.\n\n"); 
                    continue; 
                }
                print_all_flames(name, crushes, crush_qty); // Print FLAMES results for all crushes
                break;
            case 0: 
                running = 0; // Set the running flag to false
                printf("Goodbye!\n"); 
                break;
            default: 
                printf("Error: Invalid choice!\n"); 
                break;
        }
    }

    // Free allocated memory
    free(name); 
    free_array(crushes, crush_qty); 

    return 0; 
}

int main_menu() { 
    int choice; // Variable to store the user's choice

    printf("===================================================== \n");
    printf("[1] Input names\n");
    printf("[2] Compute FLAMES results\n");
    printf("[0] Exit\n");
    printf("===================================================== \n");

    printf("Enter your choice: ");
    scanf("%d", &choice); 
    getchar(); 

    return choice;
}

char *get_len_string() { // Function to get a string of variable length
    char *input = (char *)malloc(sizeof(char) * max_num_name); // Allocate memory for the input string
    
    if (input == NULL) { // Check if memory allocation failed
        printf("Memory allocation failed!\n"); // Print an error message
        return NULL; // Return NULL to indicate failure
    }

    int buffer_checker, i = 0; // Variables for buffer checking and indexing

    while (1) { // Loop to read characters until newline or EOF is encountered
        buffer_checker = getchar(); 
        
        if (buffer_checker == '\n' || buffer_checker == EOF) { // Check if newline or EOF is encountered
            input[i] = '\0'; // Terminate the string
            break; // Exit the loop
        }

        input[i] = (char)buffer_checker; // Store the character in the input string
        i++; // Increment the index

        if (i >= max_num_name - 1) { // Check if the maximum length is exceeded
            printf("Number of characters exceeds!\n"); 
            free(input); // Free allocated memory
            return NULL; // 
        }
    }

    return input; // Return the input string
}

char **get_crushes(int list_crush) { // Function to get an array of crushes
    char **array = (char **)malloc(sizeof(char *) * list_crush); // Allocate memory for the array of crushes

    if (array == NULL) { // Check if memory allocation failed
        printf("Memory allocation failed!\n"); // Print an error message
        return NULL; // Return NULL to indicate failure
    }

    for (int i = 0; i < list_crush; i++) { // Loop to get names of crushes
        printf("Enter the name of crush [%d]: ", i + 1); 

        char buffer[max_num_name]; // Buffer to store the input name
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) { 
            printf("Error reading input.\n"); 
            free_array(array, i); 
            return NULL; 
        }

        // Remove trailing newline character
        buffer[strcspn(buffer, "\n")] = '\0'; // Replace newline character with null terminator

        array[i] = strdup(buffer); 
        if (array[i] == NULL) { // Check if memory allocation failed
            printf("Memory allocation failed!\n"); 
            free_array(array, i); 
            return NULL; 
        }
    }

    return array; 
}

int remove_common_char(char *name1, char *name2) { // Function to remove common characters and count remaining characters
    int count = 0; // Variable to count common characters
    int len1 = strlen(name1); 
    int len2 = strlen(name2); 

    char *temp1 = (char *)malloc(sizeof(char) * (len1 + 1)); // Temporary storage for name1
    char *temp2 = (char *)malloc(sizeof(char) * (len2 + 1)); // Temporary storage for name2

    int i = 0, j = 0; 
    while (name1[i] != '\0') { 
        if (isalpha(name1[i])) {
            temp1[j++] = tolower(name1[i]); // Convert character to lowercase and store in temp1
        }
        i++; // Move to the next character
    }
    temp1[j] = '\0'; // Add null terminator to temp1

    i = 0, j = 0; // Reset the indices
    while (name2[i] != '\0') { 
        if (isalpha(name2[i])) { // Check if the character is alphabetic
            temp2[j++] = tolower(name2[i]); // Convert character to lowercase and store in temp2
        }
        i++; // 
    }
    temp2[j] = '\0'; // Add null terminator to temp2

    i = 0; // Reset the index
    while (temp1[i] != '\0') { 
        while (temp2[j] != '\0') { //
            if (temp1[i] == temp2[j]) { // Check if characters match
                temp1[i] = ' '; // Replace common character in temp1 with space
                temp2[j] = ' '; // Replace common character in temp2 with space
                count += 2; 
                break; 
            }
            j++; 
        }
        i++; 
    }

    // Calculate the remaining characters
    count = len1 + len2 - count; // Subtract the count of common characters from the sum of lengths

    free(temp1); 
    free(temp2); 

    return count; 
}

void calculate_flames(char *name1, char *name2) { // Function to calculate FLAMES result
    int count = remove_common_char(name1, name2); 

    int num_let = 6; 
    char flames[] = {'F', 'L', 'A', 'M', 'E', 'S'}; 

    int remove_index = count % 6;

    for (int i = remove_index; i < 5; i++) { 
        flames[i] = flames[i + 1]; // Shift elements to the left
    }
    num_let--; // Decrement the number of letters

    while (num_let > 1) { // Loop to remove letters until one letter remains
        remove_index = count % num_let; // Calculate the index to remove based on the count

        for (int i = remove_index; i < num_let - 1; i++) { // Loop to remove letters from flames array
            flames[i] = flames[i + 1]; // Shift elements to the left
        }
        num_let--; // Decrement the number of letters
    }

    switch (flames[0]) { // Switch statement based on the first letter in flames array
        case 'F': 
            printf("Friends\n");
            break;
        case 'L': 
            printf("Love\n");
            break;
        case 'A': 
            printf("Affection\n");
            break;
        case 'M':
            printf("Marriage\n");
            break;
        case 'E': 
            printf("Engage\n");
            break;
        case 'S': 
            printf("Siblings\n");
            break;
        default: 
            printf("No match\n");
    }
}

void print_all_flames(char *name, char **array, int qty) { // Function to print FLAMES results for all crushes
    for (int i = 0; i < qty; i++) { 
        int remaining_chars = remove_common_char(name, array[i]); 
        printf("Crush #%d: %s\n", i + 1, array[i]); // 
        printf("Remaining Character Count: %d\n", remaining_chars); 
        calculate_flames(name, array[i]); // Calculate and print FLAMES result for the current crush
        printf("\n"); // 
    }
}

void free_array(char **array, int size) { // Function to free memory allocated for an array
    for (int i = 0; i < size; i++) { // 
        free(array[i]); // Free memory allocated for each element
    }
}
