// Exercise # 11 - Doubly Linked List
// Tiamzon, Edgar Alan Emmanuel III B.
// ST5L
// 05 - 12 - 24

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_tag {
    char *data;
    struct node_tag *prev;
    struct node_tag *next;
} NODE;

NODE *str_head = NULL; 
NODE *str_tail = NULL; 
NODE *str_current = NULL;

// Stack to store undo history
NODE *undo_stack = NULL; // new stack for undo history
NODE *redo_stack = NULL; // new stack for redo history

// Function prototypes
void curr_string(); // entering a current string that is opt for changes 
void edit_string(); // options in editing a string
void rep_string(NODE **head); // replacing a current string
void change_char(); // function for changing an index in a string
void app_string(); // function for appending a string
void undo(); // function that allows to take back the previous data (string)
void redo(); // function that restores the change that was undone
void stored_undo(); // function for storing the previous string for undo // ERROR: first entered and last entered string cannot undo
void stored_redo(); // function for storing the previous string for redo // ERROR: first entered and last entered string cannot redo

int main() {
    int choice;

    printf("\n");
    curr_string(); // get the current string from the user
    do {
        printf("\n==========MENU==========\n");
        printf("[1] Edit String\n");
        printf("[2] Undo\n");
        printf("[3] Redo\n");
        printf("[4] Exit\n");
        printf("========================\n");

        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                edit_string();
                break;

            case 2:
                undo();
                break;

            case 3:
                redo();
                break;

            case 4:
                printf("Exiting the program....\n");
                break;

            default:
                printf("ERROR: Invalid Choice!\n");
        }
    } while (choice != 4);

    return 0;
}

// function to get the current string from the user
void curr_string() {
    if (str_head != NULL) {
        // free existing string data
        free(str_head->data);
        free(str_head);
    }

    str_head = (NODE *)malloc(sizeof(NODE));
    if (str_head == NULL) {
        printf("Memory allocation failed.");
        exit(1);
    }

    str_head->data = (char *)malloc(sizeof(char) * 100); // allocates characters up to 99 in storing new strings
    if (str_head->data == NULL) {
        printf("Memory allocation failed.");
        exit(1);
    }

    printf("Current string: ");
    scanf("%s", str_head->data);
    while (getchar() != '\n'); // clears the input buffer to prevent additional characters


    str_head->prev = NULL;
    str_head->next = NULL;

    // set str_current to str_head
    str_current = str_head;

    return;
}

// function to edit the string
void edit_string() {
    int choice;

    do {
        printf("\n========================");
        printf("\n[1] Replace String\n");
        printf("[2] Change Character At\n");
        printf("[3] Append a String\n");
        printf("[4] Back to Menu\n");
        printf("========================\n");

        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                rep_string(&str_head);
                return;  // return to main menu

            case 2:
                change_char();
                return;  // return to main menu

            case 3:
                app_string();
                return;  // return to main menu

            case 4:
                return; // return to main menu
                break;

            default:
                printf("ERROR: Invalid Choice!\n");
        }

    } while (choice != 4);
}

// function to replace the string
void rep_string(NODE **head) {
    NODE *current = *head;

    if (current == NULL) {
        printf("\nNo string to replace.\n");
        return;
    }

    // store the current string for undo
    stored_undo(current->data);

    printf("\nEnter new string: ");

    // allocate memory for the new string
    char *new_string = (char *)malloc(sizeof(char) * 100); // adjusting the size of the string into 100

    if (new_string == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    scanf(" %[^\n]", new_string); // note the space before %[^\n]
    while (getchar() != '\n'); // clear the input buffer

    // free memory of old string
    free(current->data);

    // update data pointer to point to new string
    current->data = new_string;

    // update str_current
    str_current = current;

    // print the current string from the new entered string
    printf("Current string: %s\n", current->data);
    printf("\nString replaced successfully!\n");

    return;
}

// function to change a character in the string
void change_char() {
    int index;
    char new_char;

    // validate the current string
    if (str_current == NULL || str_current->data == NULL) {
        printf("\nNo string to change.\n");
        return;
    }

    // store the current string for undo
    stored_undo(str_current->data);

    // take input for the index
    printf("\nEnter index (0-%lu): ", strlen(str_current->data) - 1);
    scanf("%d", &index);

    // validate the index
    if (index < 0 || index >= strlen(str_current->data)) {
        printf("ERROR: Invalid index!\n");
        return;
    }

    // take input for the new character
    printf("Enter new character: ");
    scanf(" %c", &new_char); 

    // update the character at the specified index
    str_current->data[index] = new_char;

    // print the updated string
    printf("Current string: %s\n", str_current->data);
    printf("\nCharacter changed successfully!\n");
}

// function to append a string
void app_string() {
    char str[100];
    
    // ensure that the current pointer is valid
    if (str_current == NULL || str_current->data == NULL) {
        printf("\nNo current string to append to.\n");
        return;
    }

    // store the current string for undo
    stored_undo(str_current->data);

    printf("\nEnter string to append: ");
    getchar(); // consume the newline character left in the input buffer
    fgets(str, sizeof(str), stdin);
    
    // remove the newline character at the end
    str[strcspn(str, "\n")] = '\0';

    // calculate the combined length of the current string and the string to append
    // size_t function is used for storing maximum size of an array for any data type
    size_t combined_len = strlen(str_current->data) + strlen(str);

    // check if the combined length exceeds the maximum allowed length
    if (combined_len > 99) {
        printf("Combined length exceeds maximum allowed length.\n");
        return;
    }

    // append the new string to the current string
    strcat(str_current->data, str);

    // print the updated current string
    printf("Current String: %s\n", str_current->data);
    printf("\nString appended successfully!\n");
}

// function to insert a new string into the undo history
void stored_undo() {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->data = strdup(str_head->data);
    new_node->next = undo_stack;
    undo_stack = new_node;
}

// function to insert a new string into the redo history
void stored_redo() {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->data = strdup(str_head->data);
    new_node->next = redo_stack;
    redo_stack = new_node;
}


// function to undo the last edit operation
void undo() {
    if (undo_stack == NULL || undo_stack->next == NULL) {
        printf("Cannot Undo!\n");
        return;
    }

    // pop the last string from the undo stack
    NODE *last_state = undo_stack;
    undo_stack = undo_stack->next;

    // swap the current linked list state with the undone status
    NODE *temp = str_head;
    str_head = last_state;
    last_state = temp;

    // insert the undone status onto the redo stack
    stored_redo();

    // free the memory of the previous status
    free(last_state->data);
    free(last_state);

    printf("Current String: %s\n", str_head->data);
}

// function to redo the last undone operation
void redo() {
    if (redo_stack == NULL) {
        printf("Cannot Redo!\n");
        return;
    }

    // pop the last string from the redo stack
    NODE *last_state = redo_stack;
    redo_stack = redo_stack->next;

    // swap the current linked list with the redone status
    NODE *temp = str_head;
    str_head = last_state;
    last_state = temp;

    // insert the redone state onto the undo stack
    stored_undo();

    // free the memory of the previous state
    free(last_state->data);
    free(last_state);

    printf("Current String: %s\n", str_head->data);
}
