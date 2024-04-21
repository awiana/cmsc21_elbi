// Exercise 3: Recursion
// Tiamzon, Edgar Alan Emmanuel III B.
// ST5L
// 03 - 01 - 24


#include <stdio.h>

// Function prototype
double calculate_growth(double init_pop, int num_years, double annual_GRate);

int main()
{
    // Initialize variables
    double initialPopulation, growthRate, initial_result;
    int years, choice;

    do {
        // Main menu loop
        printf("\n===================================\n");
        printf("    Population Growth Calculator \n");
        printf("===================================\n");

        printf("\n[1] Compute\n");
        printf("[2] Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        // Main functions for every transaction
        switch (choice) {
            case 1:
                // Prompts the user for initial population 
                printf("Initial Population (n): ");
                scanf("%lf", &initialPopulation);

                if (initialPopulation <= 0) // Validation for number of population
                {
                    printf("ERROR: Population must be greater than 0.\n");
                    return 0;
                }

                // Prompts the user to input a growth rate
                printf("Annual Growth Rate (y): ");
                scanf("%lf", &growthRate);

                // Prompts the user to input a number of years
                printf("Number of Years (x): ");
                scanf("%d", &years);

                if (years < 0) // Validation for number of years
                {
                    printf("ERROR: Years should be a positive integer.\n");
                    return 0;
                }

                // Initial calculation
                // Function call
                // Funcion call doesn't need to have data type
                initial_result = calculate_growth(initialPopulation, years, growthRate / 100);

                // Print the result
                printf("\nAfter %d year/s, at %.2lf%% growth rate, the population will be %.2lf\n", years, growthRate, initial_result);
                break;

            case 2:
                printf("Goodbye!\n");
                break;
                
             default:
             	printf("ERROR: Invalid choice! \n");
             	break;
        }
    } while (choice != 2); // Loop until the choice is correct

    return 0;
}

	double calculate_growth(double init_pop, int num_years, double annual_GRate) {
    	// Base Case
    
    	if (num_years == 0) // Checks if the input year/s is valid
    	{
        return init_pop;
    	} 
    	else 
    	{
        return calculate_growth(init_pop + (init_pop * annual_GRate), num_years - 1, annual_GRate); // Equation for calculating the growth population when the year is valid
    	}
}
