// Exercise #8 & #9 - Structures and Files
// Tiamzon, Edgar Alan Emmanuel III B.
// ST5L
// 04 - 26 - 24


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define the structures
typedef struct
{
    int event_id;
    char event_title[50];
    char artist[50];
    char date_time[25];
    float ticket_price;
    int stock;
} event;


typedef struct
{
    char name[50];
    int array_tickets[5];
    float total_cost;
} customer;


// Function prototypes
int user_menu();
void add_event(event *evnt, int *count);                                       // enables the user to add event details
void add_customer(customer *cust, int *cust_count);                            // enables the user to add customer details
void buy_event(event *evnt, customer *cust, int *count, int *cust_count);      // ask for event ID to be bought by the customer
void edit_details(event *evnt, int count);                                     // edit an event
void delete_details(event *evnt, customer *cust, int *count, int *cust_count); // delete an event
void view_allevents(event *evnt, int count);                                   // view all the events chose by the customer
void view_allcustomer(event *evnt, customer *cust, int cust_count, int count);
int IDchecker(event *evnt, int count);            // checks for event ID duplication
void s_event(event *evnt, int count);             // saving the events information
void s_customer(customer *cust, int cust_count);  // saving the customer's information
void l_event(event *evnt, int *count);            // loads the events information
void l_customer(customer *cust, int *cust_count); // loads the customer's information


int main()
{
    int choice;
    int count = 0;
    int cust_count = 0;
    int event_checker = 0;
    int cust_checker = 0;


    // Allocation of size for struct event
    event *evnt;
    evnt = (event *)malloc(sizeof(event) * 10); // Allocating size of 10 events


    // Allocation of size for struct customer
    customer *cust;
    cust = (customer *)malloc(sizeof(customer) * 10); // Allocating size of 10 customers


    // loading infos
    l_event(evnt, &count);
    l_customer(cust, &cust_count);


    // ! ensure event_checker and customer_checker is updated
    // ! after loading events and customers
    if (count != 0)
    {
        event_checker = 1;
    }
    if (cust_count != 0)
    {
        cust_checker = 1;
    }


    while (1)
    {
        user_menu();
        printf("Enter Choice: ");
        scanf("%d", &choice);


        switch (choice)
        {
        case 1:
            if (count != 10)
            {
                event_checker = 1;
                add_event(evnt, &count);
            }
            else
            {
                printf("List is Full! Only 10 events are allowed.\n");
            }
            break;
        case 2:
            if (event_checker)
            {
                buy_event(evnt, cust, &count, &cust_count);
            }
            else
            {
                printf("There are no events available!\n");
            }
            break;
        case 3:
            edit_details(evnt, count);
            break;
        case 4:
            delete_details(evnt, cust, &count, &cust_count);
            break;
        case 5:
            view_allevents(evnt, count);
            break;
        case 6:
            view_allcustomer(evnt, cust, cust_count, count);
            break;
        case 7:
            s_event(evnt, count);         // save event details after buying
            s_customer(cust, cust_count); // saving customers details after buying
            // Exit the program
            printf("Exiting the program...\n");
            free(evnt); // Free dynamically allocated memory
            free(cust); // Free dynamically allocated memory
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }


    return 0;
}


int user_menu()
{ // user's UI in the loop
    printf("\n==============MENU==============\n");
    printf("[1] Add Event Details\n");
    printf("[2] Buy Ticket\n");
    printf("[3] Edit Event Details\n");
    printf("[4] Delete Event\n");
    printf("[5] View All Events\n");
    printf("[6] View All Customers\n");
    printf("[7] Exit\n");
    printf("================================\n");
}


int IDchecker(event *evnt, int count)
{
    for (int i = 0; i < count; i++)
    { // use loop to check for each event ID with the recently added event ID
        if (evnt[i].event_id == evnt[count].event_id)
        { // compares the recent input event ID with the recent added event ID
            printf("ERROR: Event ID is already exist!\n");
            return 1; // Duplicate found
        }
    }
    return 0; // No duplicate found
}


// enables the users to input details for ticket event, including event ID, title, artist, date and time, ticket price, stock
void add_event(event *evnt, int *count)
{
    printf("\nEnter Event ID: ");
    scanf(" %d", &evnt[*count].event_id);


    // it runs if the event ID have duplicate
    while (IDchecker(evnt, *count))
    {
        return;
    }


    printf("Enter Event Title: ");
    scanf(" %[^\n]", evnt[*count].event_title);


    printf("Enter Artist: ");
    scanf(" %[^\n]", evnt[*count].artist);


    printf("Enter Date & Time: ");
    scanf(" %[^\n]", evnt[*count].date_time);


    printf("Enter Ticket Price: ");
    scanf(" %f", &evnt[*count].ticket_price);


    getchar(); // consume newline character


    printf("Enter Stock: ");
    scanf(" %d", &evnt[*count].stock);


    (*count)++;
    printf("\nSuccessfully added event!\n");
}


void add_customer(customer *cust, int *cust_count)
{
    printf("Customer Name: ");
    char name[50];
    scanf("%s", name);


    // checks for each customer if it is already in the system
    for (int i = 0; i < *cust_count; i++)
    {
        if (strcmp(cust[i].name, name) == 0)
        {
            return;
        }
    }
    // adds the user in the system
    strcpy(cust[*cust_count].name, name);


    (*cust_count)++;
}


// enables the customer to buy ticket for the event
void buy_event(event *evnt, customer *cust, int *count, int *cust_count)
{
    char name[50];
    int event_id;


    // prompts customer's name
    printf("\nCustomer name: ");
    scanf(" %[^\n]", name); // read the customer's name with spaces


    // find the customer index
    int customer_index = -1;
    for (int i = 0; i < *cust_count; i++)
    {
        if (strcmp(cust[i].name, name) == 0)
        {
            customer_index = i;
            break;
        }
    }


    // if the customer is not found, add them to the system
    if (customer_index == -1)
    {
        printf("\n");
        strcpy(cust[*cust_count].name, name);
        customer_index = *cust_count;
        (*cust_count)++;
    }


    // show available events
    printf("-------- EVENTS AVAILABLE --------\n");
    for (int i = 0; i < *count; i++)
    {
        printf("[%d] %s (%s) - %.2f\n", evnt[i].event_id, evnt[i].event_title, evnt[i].artist, evnt[i].ticket_price);
    }


    // ask for event ID to be bought
    printf("\nEnter event ID to buy: ");
    scanf("%d", &event_id);


    // find the event index
    int event_index = -1;
    for (int i = 0; i < *count; i++)
    {
        if (evnt[i].event_id == event_id)
        {
            event_index = i;
            break;
        }
    }


    // check if event index is valid
    if (event_index == -1)
    {
        printf("Event ID not found!\n");
        return;
    }


    // check if event is out of stock
    if (evnt[event_index].stock == 0)
    {
        printf("Event ticket is out of stock!\n");
        return;
    }


    // buy the ticket and update stock
    evnt[event_index].stock--;
    printf("\nSuccessfully bought ticket %d %s %s!\n", evnt[event_index].event_id, evnt[event_index].event_title, evnt[event_index].date_time);


    // update total money spent by customer
    cust[customer_index].total_cost += evnt[event_index].ticket_price;


    // update the customer's array_tickets with the purchased event ID
    for (int i = 0; i < 5; i++)
    {
        if (cust[customer_index].array_tickets[i] == 0)
        {
            cust[customer_index].array_tickets[i] = evnt[event_index].event_id;
            break;
        }
    }
}


// enables the user to edit the event details
void edit_details(event *evnt, int count)
{
    if (count == 0)
    {
        printf("There are no events available to edit!\n");
        return;
    }


    int event_id;
    printf("Enter event ID to edit: ");
    scanf("%d", &event_id);


    // Find the event index
    int event_index = -1;
    for (int i = 0; i < count; i++)
    {
        if (evnt[i].event_id == event_id)
        {
            event_index = i;
            break;
        }
    }


    // Check if the event index is valid
    if (event_index == -1)
    {
        printf("Event ID not found!\n");
        return;
    }


    // Allow the user to edit the event details
    printf("Enter new date & time: ");
    scanf(" %[^\n]", evnt[event_index].date_time);


    printf("Enter new ticket price: ");
    scanf("%f", &evnt[event_index].ticket_price);


    printf("Enter new stock: ");
    scanf("%d", &evnt[event_index].stock);


    printf("\nEvent details updated successfully!\n");
}


// enables the user to delete a specific event detail through event ID
void delete_details(event *evnt, customer *cust, int *count, int *cust_count)
{
    if (*count == 0)
    {
        printf("There are no events available to delete!\n");
        return;
    }


    int event_id;
    printf("Enter event ID to delete: ");
    scanf("%d", &event_id);


    // find the event index
    int event_index = -1;
    for (int i = 0; i < *count; i++)
    {
        if (evnt[i].event_id == event_id)
        {
            event_index = i;
            break;
        }
    }


    // check if the event index is valid
    if (event_index == -1)
    {
        printf("Event ID not found!\n");
        return;
    }


    // shift the elements to overwrite the deleted event
    for (int i = event_index; i < *count - 1; i++)
    {
        evnt[i] = evnt[i + 1];
    }


    // decrement the count to reflect the removal of the event
    (*count)--;


    // removes the customer data
    for (int i = 0; i < *cust_count; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (cust[i].array_tickets[j] == event_id)
            {


                // shift the remaining tickets to the left
                for (int k = j; k < 4; k++)
                {
                    cust[i].array_tickets[k] = cust[i].array_tickets[k + 1];
                }
                cust[i].array_tickets[4] = 0; // set the last element to 0
            }
        }
    }


    printf("\nSuccessfully deleted event detail!\n");
}


// view all the events that are available
void view_allevents(event *evnt, int count)
{
    if (count == 0)
    {
        printf("There have been no events entered!\n");
        return;
    }


    for (int i = 0; i < count; i++)
    {
        printf("\nEvent ID: %d\n", evnt[i].event_id);
        printf("Event Title: %s\n", evnt[i].event_title);
        printf("Artist: %s\n", evnt[i].artist);
        printf("Date and Time: %s\n", evnt[i].date_time);
        printf("Ticket Price: %.2f\n", evnt[i].ticket_price);
        printf("Stock: %d\n", evnt[i].stock);
    }
}


void view_allcustomer(event *evnt, customer *cust, int cust_count, int count)
{
    if (cust_count == 0)
    {
        printf("There are no customers available!\n");
        return;
    }


    printf("\n===== ALL CUSTOMERS =====\n");
    for (int i = 0; i < cust_count; i++)
    {
        printf("Customer Name: %s\n", cust[i].name);
        printf("Tickets Bought:\n");


        // create a copy of the customer's array_tickets to sort
        int sorted_tickets[5];
        for (int j = 0; j < 5; j++)
        {
            sorted_tickets[j] = cust[i].array_tickets[j];
        }


        // sort the array of event IDs in descending order
        for (int j = 0; j < 5 - 1; j++)
        {
            for (int k = j + 1; k < 5; k++)
            {
                if (sorted_tickets[j] < sorted_tickets[k] && sorted_tickets[k] != 0)
                {
                    int temp = sorted_tickets[j];
                    sorted_tickets[j] = sorted_tickets[k];
                    sorted_tickets[k] = temp;
                }
            }
        }


        // print the sorted tickets bought by the customer
        float total_cost = 0.0;
        for (int j = 0; j < 5; j++)
        {
            if (sorted_tickets[j] != 0)
            {
                for (int k = 0; k < count; k++)
                {
                    if (evnt[k].event_id == sorted_tickets[j])
                    {
                        printf("- %d %s %s\n", evnt[k].event_id, evnt[k].event_title, evnt[k].date_time);
                        total_cost += evnt[k].ticket_price; // add ticket price to total cost
                        break;
                    }
                }
            }
            else
            {
                break; // No more tickets for this customer
            }
        }


        // Print total cost for the customer
        printf("Total Cost: %.2f\n\n", total_cost);
    }
}


// saving the event details
void s_event(event *evnt, int count)
{
    FILE *file = fopen("events.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }


    fprintf(file, "%d\n", count);


    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d\n", evnt[i].event_id);
        fprintf(file, "%s\n", evnt[i].event_title);
        fprintf(file, "%s\n", evnt[i].artist);
        fprintf(file, "%s\n", evnt[i].date_time);
        fprintf(file, "%.2f\n", evnt[i].ticket_price);
        fprintf(file, "%d\n", evnt[i].stock);
    }


    fclose(file);
}


// saving the customer details
void s_customer(customer *cust, int cust_count)
{
    FILE *file = fopen("customers.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }


    fprintf(file, "%d\n", cust_count);


    for (int i = 0; i < cust_count; i++)
    {
        fprintf(file, "%s\n", cust[i].name);
        fprintf(file, "%.2f\n", cust[i].total_cost);


        // Write the array of purchased event IDs
        for (int j = 0; j < 5; j++)
        {
            fprintf(file, "%d\n", cust[i].array_tickets[j]);
        }
    }


    fclose(file);
}


// loading the event details
void l_event(event *evnt, int *count)
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printf("Error opening events file! File may not exist.\n");
        return;
    }


    fscanf(file, "%d", count);


    for (int i = 0; i < *count; i++)
    {
        fscanf(file, "%d", &evnt[i].event_id);
        fscanf(file, " %[^\n]", evnt[i].event_title);
        fscanf(file, " %[^\n]", evnt[i].artist);
        fscanf(file, " %[^\n]", evnt[i].date_time);
        fscanf(file, "%f", &evnt[i].ticket_price);
        fscanf(file, "%d", &evnt[i].stock);
    }


    fclose(file);
}


// loading the customer details
void l_customer(customer *cust, int *cust_count)
{
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL)
    {
        printf("Error opening customers file! File may not exist.\n");
        return;
    }


    fscanf(file, "%d", cust_count); //


    for (int i = 0; i < *cust_count; i++)
    {
        fscanf(file, " %[^\n]", cust[i].name);
        fscanf(file, "%f", &cust[i].total_cost);
        for (int j = 0; j < 5; j++)
        {
            fscanf(file, "%d", &cust[i].array_tickets[j]);
        }
    }


    fclose(file);
}
