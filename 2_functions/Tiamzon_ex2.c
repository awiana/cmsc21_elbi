// Exercise #2: Functions
// Edgar Alan Emmanuel B. Tiamzon III
// ST5L
// 02 - 23 - 24

#include <stdio.h>
#define clear() printf("\033[H\033[J")

// Function prototypes
int pin_verification(int actual_pin);
void check_balance(int actual_pin, float atm_balance);
float deposit(int actual_pin, float atm_balance);
float withdraw(int actual_pin, float atm_balance);
int change_pin(int actual_pin);

int main() {
    // Initialize variables
    int options = 0;
    float atm_balance = 0;
    int actual_pin = 1234;

    do {
        // Main menu loop
        printf("\n===================================\n");
        printf("|     Welcome to Maze Bank!       |\n");
        printf("===================================\n");

        printf("\n[1] Check balance\n");
        printf("[2] Deposit\n");
        printf("[3] Withdraw\n");
        printf("[4] Change PIN\n");
        printf("[5] End transaction\n\n");
        printf("Enter your choice: ");
        scanf("%d", &options);

        // Main functions for every transaction
        switch (options) {
        case 1:
            clear();
            check_balance(actual_pin, atm_balance);
            break;
            

        case 2:
            clear();
            atm_balance = deposit(actual_pin, atm_balance);
            break;
            

        case 3:
            clear();
            atm_balance = withdraw(actual_pin, atm_balance);
            break;
            

        case 4:
            clear();
            actual_pin = change_pin(actual_pin);
            break;
            

        case 5:
            clear();
            printf("Thank you for choosing this bank. Bye!\n");
            break;
            


        default:
            printf("Invalid choice!\n");
            break;
            clear();

        }
    } while (options != 5);

    return 0;
}

// Function that verifies the current PIN of the user's account
// This function will automatically request the user to enter the PIN for every transaction.
int pin_verification(int actual_pin) {
    int enter_pin;

    do {
        printf("Enter PIN (4-digits): ");
        scanf("%d", &enter_pin);

        if (enter_pin < 1000 || enter_pin > 9999) {
            printf("PIN must be 4-digits!\n");
        } 
        else if (enter_pin != actual_pin) {
            printf("Entered PIN is incorrect! Try again.\n");
        }
    } while (enter_pin != actual_pin);

    return enter_pin;
}

// Function that checks the user's balance amount
// For any transaction like deposit and withdraw, the current balance will automatically update as the user wants.
void check_balance(int actual_pin, float atm_balance) {
    pin_verification(actual_pin);

    printf("============================================\n");
    printf("Your current balance: %f\n", atm_balance);
    printf("============================================\n");
}

// Function that enables the user to deposit a certain amount
float deposit(int actual_pin, float atm_balance) {
    float amount_depo;

    pin_verification(actual_pin);

    printf("Enter the Deposit Amount: ");
    scanf("%f", &amount_depo);

    printf("============================================\n");
    printf("Deposit successful! \n");
    printf("Your new balance is: %f\n", atm_balance + amount_depo);
    printf("============================================\n");

    return atm_balance + amount_depo;
}

// Function that enables the user to withdraw a certain amount
float withdraw(int actual_pin, float atm_balance) {
    float amount_withdraw;

    pin_verification(actual_pin);

    printf("Enter the Withdraw Amount: ");
    scanf("%f", &amount_withdraw);

    if (amount_withdraw > atm_balance) {
        printf("===========================================\n");
        printf("You have insufficient balance!\n");
        printf("Your current balance is: %f\n", atm_balance);
        printf("===========================================\n");
    } else if (amount_withdraw < 0) {
        printf("Enter a sufficient amount!\n");
    } else {
        printf("==========================================\n");
        printf("Withdrawal successful! \n");
        printf("Your new balance is: %f\n", atm_balance - amount_withdraw);
        printf("==========================================\n");
        return atm_balance - amount_withdraw;
    }

    return atm_balance;
}

// Function that enables the user to change its current PIN
int change_pin(int actual_pin) {
    int new_pin;

    pin_verification(actual_pin);

    printf("Enter a new PIN: ");
    scanf("%d", &new_pin);

    if (new_pin < 1000 || new_pin > 9999) {
        printf("PIN must be 4-digits!\n");
        return actual_pin;
    } 
    else {
        printf("================================\n");
        printf("PIN successfully changed: %d\n", new_pin);
        printf("================================\n");
        return new_pin;
    }
}
