// Exercise # 1: Introduction to C
// Edgar Alan Emmanuel B. Tiamzon III
// ST5L 
// 02 - 16 - 24

# include<stdio.h>

int main(){

	int choice;
	float weight, height, BMI_metric, inches, calculate_height, BMI_standard ;

	do{ // This menu contains the required choices for the user
		printf("\n=====Menu=====");
		printf("\n[1] Metric");
		printf("\n[2] Standard");
		printf("\n[3] Exit");
		printf("\nPlease Enter your choice: ");
		scanf("%d", &choice);

	switch(choice){
		case 1: // user chose the metric option
			printf("\nEnter weight in kilograms: "); // asks the user to prompt its weight
			scanf("%f", &weight);

			printf("Enter height in centimeters: "); // asks the user to prompt its height
			scanf("%f", &height);

		BMI_metric = (weight*10000)/(height*height); // BMI formula in metric measurement

		printf("\nYour BMI is: %f", BMI_metric);

		if (BMI_metric < 18.5){
			printf("\nYour BMI category is: Underweight\n"); // This category prompts if the user is underweight
		}

		else if (BMI_metric >= 18.5 && BMI_metric < 25){
			printf("\nYour BMI category is: Normal Weight\n"); // This category prompts if the user is normal weight
		}

		else if (BMI_metric >= 25 && BMI_metric < 30){
			printf("\nYour BMI category is: Overweight\n"); // This category prompts if the user is overweight
		}

		else{
			printf("\nYour BMI category is: Obese\n"); // This category prompts if the user is obese
		}

		break;


	case 2: // user chose the standard option
			printf("Enter weight in pounds: "); // asks the user to prompt its weight in pounds
			scanf("%f", &weight);

			printf("Enter height in feet: "); // asks the user to prompt its height in feet
			scanf("%f", &height);

			printf("Enter height in inches: "); // asks the user to prompt its height in inches
			scanf("%f", &inches);


			calculate_height = (height*12) + inches; // calculate the total height or height in feet
			BMI_standard = (weight / (calculate_height*calculate_height))*703; // BMI formula in standard measurement

			printf("\nYour BMI is: %f", BMI_standard);

		if (BMI_standard < 18.5){
			printf("\nBMI category: Underweight\n"); // This category prompts if the user is underweight
		}

		else if (BMI_standard >= 18.5 && BMI_standard < 25){
			printf("\nBMI category is: Normal Weight\n"); // This category prompts if the user is normal weight
		}

		else if (BMI_standard >= 25 && BMI_standard < 30){
			printf("\nBMI category is: Overweight\n"); // This category prompts if the user is overweight
		}

		else{
			printf("\nBMI category is: Obese\n"); // This category prompts if the user is obese
		}
		break;


	case 3: 
		printf("\nProgram Terminated. Thank you!\n"); // the program is being termindated once the user choose 3
		break;

	default:
		printf("Invalid Choice! Select 1-3 only!\n"); // prompts invalid whenever the user did not choose among the 3 choices

	}

	}while(choice != 3); // the menu will continue to loop
	return 0; 

}
