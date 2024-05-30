// Exercise # 10 - Linked List
// Tiamzon, Edgar Alan Emmanuel III B.
// ST5L
// 05 -05 - 24

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Used to create an instance of an event
typedef struct event_tag {
	char event_id[5];
	char event_title[20];
	char artist[20];
	char datetime[20];
	float ticket_price;
	int stock;
	int soldCount;
	struct event_tag *nextEvent;
} event;

//Used to create a booking linked list for each customer.
struct bookings {
	struct event_tag *event_booked;
	struct bookings *nextBooking;
};

//Used to create an instance of a customer
typedef struct customer_tag {
	char name[20];
	struct customer_tag *nextCustomer;
	struct bookings *ticketsBought;
	int total_cost;
} customer;

event *events_head = NULL;
customer *customers_head = NULL;

// Function prototypes
void add_event(event **events_head);
void buy_ticket(event *events, customer **customers);
void edit_event(event *events);
void delete_event(event **head);
void view_all_events(event *head);
void view_all_customers(customer *head);
void s_events(event *head);
void s_customers(customer *head);
void l_events(event **head);
void l_customers(customer **head);

int main() {
    int choice;

    do {
        printf("\n==============MENU==============\n");
        printf("[1] Add Event Details\n");
        printf("[2] Buy Ticket\n");
        printf("[3] Edit Event Details\n");
        printf("[4] Delete Event\n");
        printf("[5] View All Events\n");
        printf("[6] View All Customers\n");
        printf("[7] Exit\n");
        printf("================================\n");
    
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_event(&events_head);
                break;
            case 2:
                buy_ticket(events_head, &customers_head);
                break;
            case 3:
                edit_event(events_head);
                break;
            case 4:
                delete_event(&events_head);
                break;
            case 5:
                view_all_events(events_head);
                break;
            case 6:
                view_all_customers(customers_head);
                break;
            case 7:
                printf("Exiting the program...");
                break;
            default:
                printf("ERROR: Invalid choice!\n");
        }

    } while (choice != 7);

    // Save data to files before exiting
    s_events(events_head);
    s_customers(customers_head);


    return 0;
}

void IDchecker(event *head, char *event_id) {
    event *cur_event = head;
    while (cur_event != NULL){
        if (strcmp(cur_event->event_id, event_id) == 0){
            printf("\nERROR: Event ID already exists!\n");
            return;
        }
        cur_event = cur_event->nextEvent;
    }
}

void add_event(event **events_head) {
    event *new_event = (event *)malloc(sizeof(event));
    if (new_event == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("\nEnter Event ID: ");
    scanf("%s", new_event->event_id);

    // Check for duplicate event ID
    IDchecker(*events_head, new_event->event_id);
    if (*events_head != NULL && strcmp(new_event->event_id, (*events_head)->event_id) == 0) {
        free(new_event); // Free memory allocated for new event
        return;
    }
    
    printf("Enter Event Title: ");
    scanf(" %[^\n]", new_event->event_title);

    printf("Enter Artist: ");
    scanf(" %[^\n]", new_event->artist);

    printf("Enter Date & Time: ");
    scanf(" %[^\n]", new_event->datetime);

    printf("Enter Ticket Price: ");
    scanf("%f", &new_event->ticket_price);

    printf("Enter Stock: ");
    scanf("%d", &new_event->stock);

    new_event->nextEvent = *events_head;
    *events_head = new_event;

    printf("\nSuccessful added event!\n");
}

void buy_ticket(event *events_head, customer **customers) {
    // Check if there are no events available
    if (events_head == NULL) {
        printf("\nThere are no events available!\n");
        return;
    }

    char name[20];
    printf("\nEnter customer name: ");
    scanf(" %[^\n]", name);

    customer *cur_customer = NULL;
    customer *prev_customer = NULL;
    cur_customer = *customers;

    // Loop through existing customers to find if the customer already exists
    while (cur_customer != NULL) {
        if (strcmp(cur_customer->name, name) == 0) {
            break;
        }
        prev_customer = cur_customer;
        cur_customer = cur_customer->nextCustomer;
    }

    // If customer doesn't exist, create a new one
    if (cur_customer == NULL) {
        cur_customer = (customer *)malloc(sizeof(customer));
        strcpy(cur_customer->name, name);
        cur_customer->total_cost = 0;
        cur_customer->ticketsBought = NULL;
        cur_customer->nextCustomer = NULL;

        // Insert new customer at the beginning of the list
        if (prev_customer == NULL) {
            *customers = cur_customer;
        } else {
            prev_customer->nextCustomer = cur_customer;
        }
    }

    // Display available events
    printf("\n-------- EVENTS AVAILABLE --------\n");
    event *cur_event = events_head;
    while (cur_event != NULL) {
        printf("[%s] %s (%s) - %.2f\n", cur_event->event_id, cur_event->event_title, cur_event->artist, cur_event->ticket_price);
        cur_event = cur_event->nextEvent;
    }

    char event_id[5];
    printf("\nEnter event ID to buy: ");
    scanf("%s", event_id);

    // Find the event in the events list
    cur_event = events_head;
    while (cur_event != NULL) {
        if (strcmp(cur_event->event_id, event_id) == 0) {
            // Event found, proceed with ticket purchase logic
            if (cur_event->stock == 0) {
                printf("\nEvent ticket is out of stock!\n");
                return;
            }
            
            // Create a new booking node
            struct bookings *new_booking = (struct bookings *)malloc(sizeof(struct bookings));
            new_booking->event_booked = cur_event;
            new_booking->nextBooking = cur_customer->ticketsBought;
            cur_customer->ticketsBought = new_booking;
            
            cur_event->stock--;
            cur_customer->total_cost += cur_event->ticket_price;

            printf("\nSuccessfully bought ticket %s %s %s!\n", cur_event->event_id, cur_event->event_title, cur_event->datetime);
            return;
        }
        cur_event = cur_event->nextEvent;
    }

    // If event not found
    printf("\nEvent ID not found!\n");
}


void edit_event(event *events) {
    if (events_head == NULL) {
        printf("\nThere are no events available!\n");
        return;
    }

    char event_id[5];
    printf("\nEnter Event ID: ");
    scanf("%s", event_id);

    event *cur_event = events_head;

    // Loop through the linked list of events to find the event with the specified ID
    while (cur_event != NULL) {
        if (strcmp(cur_event->event_id, event_id) == 0) {
            // Event found, proceed with editing
            printf("Enter New Date and Time: ");
            scanf(" %[^\n]", cur_event->datetime);

            printf("Enter New Price: ");
            scanf("%f", &cur_event->ticket_price);

            printf("Enter New Stock: ");
            scanf("%d", &cur_event->stock);

            printf("\nEvent Details Successfully Edited!\n");
            return; // Exit the function after editing
        }
        cur_event = cur_event->nextEvent;
    }

    // If the loop exits without finding the event
    printf("Event not found.\n");
}

void delete_event(event **events_head) {
    if (*events_head == NULL) {
        printf("\nThere are no events available!\n");
        return;
    }

    char event_id[5];
    printf("\nEnter event ID to delete: ");
    scanf("%s", event_id);

    event *cur_event = *events_head;
    event *prev_event = NULL;

    // Traverse the linked list to find the event to delete
    while (cur_event != NULL) {
        if (strcmp(cur_event->event_id, event_id) == 0) {
            // Event found, unlink it from the list
            if (prev_event == NULL) {
                // If the event to delete is the events_head of the list
                *events_head = cur_event->nextEvent;
            } else {
                // If the event to delete is not the events_head of the list
                prev_event->nextEvent = cur_event->nextEvent;
            }
            // Free the memory allocated for the event
            free(cur_event);
            printf("\nSuccessfully deleted event detail!\n");
            return;
        }
        // Move to the next event node
        prev_event = cur_event;
        cur_event = cur_event->nextEvent;
    }

    // If the loop exits without finding the event
    printf("Event with ID not found.\n");
}


void view_all_events(event *events_head) {
    if (events_head == NULL) {
        printf("\nThere are no events available!\n");
        return;
    }

    printf("\n-------- ALL EVENTS --------\n");

    // Print the events without sorting
    event *cur_event = events_head;
    while (cur_event != NULL) {
        printf("\nEvent ID: %s\n", cur_event->event_id);
        printf("Event Title: %s\n", cur_event->event_title);
        printf("Artist: %s\n", cur_event->artist);
        printf("Date and Time: %s\n", cur_event->datetime);
        printf("Ticket Price: %.2f\n", cur_event->ticket_price);
        printf("Stock: %d\n", cur_event->stock);
        cur_event = cur_event->nextEvent;
    }
}

void view_all_customers(customer *customers_head) {
    if (customers_head == NULL) {
        printf("\nThere are no customers yet!\n");
        return;
    }
    // Traverse the linked list of customers
    printf("\n===== ALL CUSTOMERS =====\n");
    customer *cur_customer = customers_head;
    while (cur_customer != NULL) {
        printf("\nCustomer Name: %s\n", cur_customer->name); // Displaying customer details
        printf("Tickets Bought:\n");

        // Initialize total cost to 0.0 for each customer
        float total_cost = 0.0;

        // Traverse the linked list of bookings for the current customer
        struct bookings *current_booking = cur_customer->ticketsBought;
        while (current_booking != NULL) {
            printf("- %s %s %s \n", current_booking->event_booked->event_id, 
                   current_booking->event_booked->event_title, current_booking->event_booked->datetime);
            
            // Add the price of each ticket to the total cost
            total_cost += current_booking->event_booked->ticket_price;

            current_booking = current_booking->nextBooking;
        }

        printf("Total Cost: %.2f\n", total_cost); // Displaying total cost
        cur_customer = cur_customer->nextCustomer;
    }
}


void s_events(event *events_head) {
    FILE *file = fopen("events1.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    event *cur_event = events_head;
    while (cur_event != NULL) {
        // Format the datetime string to match the example format
        char formatted_datetime[50]; // Adjust the buffer size to accommodate the formatted datetime
        sprintf(formatted_datetime, "%s, %.2f, %d, %d", cur_event->datetime, cur_event->ticket_price, cur_event->stock, cur_event->soldCount);
        int title_len = strlen(cur_event->event_title); // Get the length of the event title
        fprintf(file, "%s\n%d\n%s\n%s\n%s\n", cur_event->event_id, title_len, cur_event->event_title, cur_event->artist, formatted_datetime);
        cur_event = cur_event->nextEvent;
    }
    fclose(file);
}

void s_customers(customer *customers_head) {
    FILE *file = fopen("customers1.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    customer *cur_customer = customers_head;
    while (cur_customer != NULL) {
        fprintf(file, "%s\n%d\n", cur_customer->name, cur_customer->total_cost);
        // Save the bookings information if needed
        // Traverse the bookings list and save each booking
        struct bookings *current_booking = cur_customer->ticketsBought;
        while (current_booking != NULL) {
            fprintf(file, "%s\n", current_booking->event_booked->event_id);
            current_booking = current_booking->nextBooking;
        }
        fprintf(file, "END\n"); // Add a delimiter to mark the end of bookings for a customer
        cur_customer = cur_customer->nextCustomer;
    }
    fclose(file);
}


void l_events(event **events_head) {
    FILE *file = fopen("events1.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    char event_id[5];
    char event_title[20];
    char artist[20];
    char datetime[30]; // Adjust the buffer size to accommodate the formatted datetime
    float ticket_price;
    int stock;
    int soldCount;
    int title_len; // Declare title_len as an integer variable
    while (fscanf(file, "%s\n%d\n%[^,],%[^,],%[^,],%[^,],%f,%d,%d\n", event_id, &title_len, event_title, artist, datetime, &ticket_price, &stock, &soldCount) != EOF) {
        // Create a new event node and populate its details
        event *new_event = (event *)malloc(sizeof(event));
        strcpy(new_event->event_id, event_id);
        strncpy(new_event->event_title, event_title, title_len); // Use strncpy to copy limited characters
        new_event->event_title[title_len] = '\0'; // Add null terminator to ensure string termination
        strcpy(new_event->artist, artist);
        sscanf(datetime, "%[^,], %f, %d, %d", new_event->datetime, &new_event->ticket_price, &new_event->stock, &new_event->soldCount);
        new_event->nextEvent = *events_head;
        *events_head = new_event;
    }
    fclose(file);
}


void l_customers(customer **customers_head) {
    FILE *file = fopen("customers1.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    char name[20];
    int total_cost;
    while (fscanf(file, "%s\n%d\n", name, &total_cost) != EOF) {
        // Create a new customer node and populate its details
        customer *new_customer = (customer *)malloc(sizeof(customer));
        strcpy(new_customer->name, name);
        new_customer->total_cost = total_cost;
        // Initialize other fields if needed
        new_customer->nextCustomer = *customers_head;
        *customers_head = new_customer;
    }
    fclose(file);
}
