#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_MOVIES 7
#define TOTAL_SEATS 60

// Structure for Movie Details
typedef struct {
    int movieId;
    char movieTitle[30];
    char day[20];
} Movie;

// Global Data Storage
Movie movieDetails[NUM_MOVIES] = {
    {1001, "Hobbit", "Monday"},
    {1002, "Avatar", "Tuesday"},
    {1003, "Harry Potter", "Wednesday"},
    {1004, "Minions", "Thursday"},
    {1005, "Interstellar", "Friday"},
    {1006, "Moana", "Saturday"},
    {1007, "Inception", "Sunday"}
};

int movieBookDatabase[NUM_MOVIES][TOTAL_SEATS] = {0};

// Function Declarations
void systemMenu();
void displayMovieList();
void checkAvailableSeat();
void seatReservation(int sessionId);
void cancelReservation();
void createBill(const char *name, int bookingId, int sessionId, int seatCount, const char *mobile, 
                double snacksPrice, double beveragesRate, double discount, int offerPop, int offerSoft, 
                double subtotal, const int seatNumbers[], const char *timeLabel);
int findMovieIndex(int sessionId);

int main() {
    systemMenu();
    return 0;
}

// System Main Menu
void systemMenu() {
    int selection;
    do {
        printf("\n\t\t\tMovie Ticket Booking System\n");
        printf("  =====================================================================\n");
        printf("||\t\t1 - Display Movie List\t\t\t\t\t||\n");
        printf("||\t\t2 - Check Available Seats\t\t\t\t||\n");
        printf("||\t\t3 - Seat Reservation\t\t\t\t\t||\n");
        printf("||\t\t4 - Cancel Reservation\t\t\t\t\t||\n");
        printf("||\t\t5 - Exit System\t\t\t\t\t\t||\n");
        printf("||======================================================================||\n");
        printf("\nEnter your selection (1-5): ");
        
        if (scanf("%d", &selection) != 1) {
            printf("\n[Error] Invalid input format. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (selection) {
            case 1:
                displayMovieList();
                break;
            case 2:
                checkAvailableSeat();
                break;
            case 3: {
                int sessionId;
                printf("\nWhen is your Booking?\n");
                printf("1001-Mon, 1002-Tue, 1003-Wed, 1004-Thu, 1005-Fri, 1006-Sat, 1007-Sun\n");
                printf("Enter Session ID: ");
                scanf("%d", &sessionId);
                if (findMovieIndex(sessionId) != -1) {
                    seatReservation(sessionId);
                } else {
                    printf("\n[Error] Invalid Session ID!\n");
                }
                break;
            }
            case 4:
                cancelReservation();
                break;
            case 5:
                printf("\n=============================== System Exiting ===============================\n\n");
                return;
            default:
                printf("\n[Error] Invalid selection! Please choose between 1 and 5.\n");
                break;
        }
    } while (selection != 5);
}

// Helper to find movie index by Session ID
int findMovieIndex(int sessionId) {
    for (int i = 0; i < NUM_MOVIES; i++) {
        if (movieDetails[i].movieId == sessionId) {
            return i;
        }
    }
    return -1;
}

// Display Movie List
void displayMovieList() {
    printf("\n\n\t\t\t\tNow Showing .............\n\n");
    printf("======================================================================\n");
    printf("\tID\tTitle\t\tDay\t\tStandard Price (Rs)\n");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < NUM_MOVIES; i++) {
        printf("\t%d\t%-12s\t%-10s\t1000.00\n", 
               movieDetails[i].movieId, movieDetails[i].movieTitle, movieDetails[i].day);
    }
    printf("======================================================================\n\n");

    char choice;
    printf("Do you want to proceed to check seats? (y/n): ");
    scanf(" %c", &choice);
    if (tolower(choice) == 'y') {
        checkAvailableSeat();
    }
}

// Check Available Seats
void checkAvailableSeat() {
    int sessionId;
    printf("\nEnter Session ID (1001-1007): ");
    scanf("%d", &sessionId);

    int idx = findMovieIndex(sessionId);
    if (idx == -1) {
        printf("\n[Error] Invalid Session ID!\n");
        return;
    }

    printf("\n\nAvailable Seats for %s (%s)\n", movieDetails[idx].movieTitle, movieDetails[idx].day);
    printf("\t\t\t\t----------------- SCREEN -----------------\n\n");

    int seatNum = 1;
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 10; col++) {
            if (movieBookDatabase[idx][seatNum - 1] == 0) {
                printf("%8d", seatNum);
            } else {
                printf("%8s", "X");
            }
            seatNum++;
        }
        printf("\n\n");
    }

    char choice;
    printf("Do you want to reserve seats for this session? (y/n): ");
    scanf(" %c", &choice);
    if (tolower(choice) == 'y') {
        seatReservation(sessionId);
    }
}

// Seat Reservation Function
void seatReservation(int sessionId) {
    int idx = findMovieIndex(sessionId);
    if (idx == -1) {
        printf("\n[Error] Invalid Session ID!\n");
        return;
    }

    int seatCount;
    printf("How many seats do you want to book (1-%d)? ", TOTAL_SEATS);
    scanf("%d", &seatCount);

    if (seatCount < 1 || seatCount > TOTAL_SEATS) {
        printf("\n[Error] Invalid seat count!\n");
        return;
    }

    int seatNumbers[TOTAL_SEATS];
    for (int i = 0; i < seatCount; i++) {
        int intSeatNumber;
        printf("Enter Seat Number %d (1-%d): ", i + 1, TOTAL_SEATS);
        scanf("%d", &intSeatNumber);

        if (intSeatNumber < 1 || intSeatNumber > TOTAL_SEATS) {
            printf("\n[Error] Seat number out of range! Try again.\n");
            i--;
            continue;
        }

        if (movieBookDatabase[idx][intSeatNumber - 1] == 0) {
            seatNumbers[i] = intSeatNumber;
            movieBookDatabase[idx][intSeatNumber - 1] = intSeatNumber;
        } else {
            printf("\n[Error] Seat %d is already booked! Choose another.\n", intSeatNumber);
            i--;
        }
    }

    int timeChoice;
    printf("Enter the Time for the Show:\n");
    printf("1. Morning\n2. Evening\n3. Night\nChoice: ");
    scanf("%d", &timeChoice);

    const char *timeLabel = "Night";
    switch (timeChoice) {
        case 1:
            timeLabel = "Morning";
            break;
        case 2:
            timeLabel = "Evening";
            break;
        case 3:
        default:
            timeLabel = "Night";
            break;
    }

    char customerName[50];
    char mobileNum[15];
    printf("Enter your Name: ");
    scanf("%49s", customerName);

    printf("Enter your Mobile Number: ");
    scanf("%14s", mobileNum);

    int students, oldPeople, popcorn, softDrink;
    printf("How many students in your group? ");
    scanf("%d", &students);
    printf("How many senior citizens (age > 60)? ");
    scanf("%d", &oldPeople);
    printf("Enter Popcorn count: ");
    scanf("%d", &popcorn);
    printf("Enter Soft Drink count: ");
    scanf("%d", &softDrink);

    double popcornRate = 250.0;
    double softDrinkRate = 100.0;
    double snacksPrice = popcornRate * popcorn;
    double beveragesRate = softDrink * softDrinkRate;
    double totalMovieTicketRate = seatCount * 1000.0;

    double discountPercentage = 0.0;
    if (oldPeople > 0) {
        discountPercentage = 0.20;
    } else if (students > 0) {
        discountPercentage = 0.15;
    } else if (seatCount > 10) {
        discountPercentage = 0.10;
    }

    int offerSoft = seatCount / 5;
    int offerPop = softDrink / 10;

    double discount = (beveragesRate + totalMovieTicketRate) * discountPercentage;
    double subtotal = totalMovieTicketRate + snacksPrice + beveragesRate - discount;

    static int bookingIdCounter = 101;
    createBill(customerName, bookingIdCounter++, sessionId, seatCount, mobileNum, 
               snacksPrice, beveragesRate, discount, offerPop, offerSoft, subtotal, seatNumbers, timeLabel);
}

// Create Bill & Print Ticket
void createBill(const char *name, int bookingId, int sessionId, int seatCount, const char *mobile, 
                double snacksPrice, double beveragesRate, double discount, int offerPop, int offerSoft, 
                double subtotal, const int seatNumbers[], const char *timeLabel) {
    int idx = findMovieIndex(sessionId);

    printf("\n----------------------------- Theater Booking Ticket -----------------------------\n");
    printf("==================================================================================\n");
    printf("Book ID  : %d\t\t\tShow Name : %s\n", bookingId, movieDetails[idx].movieTitle);
    printf("Customer : %s\t\t\tMobile    : %s\n", name, mobile);
    printf("Day      : %s\t\t\tShow Time : %s\n", movieDetails[idx].day, timeLabel);
    printf("\nNo of seats : %d ( ", seatCount);
    for (int i = 0; i < seatCount; i++) {
        printf("%d ", seatNumbers[i]);
    }
    printf(")\n\n");
    printf("Price for snacks    : Rs. %.2lf\n", snacksPrice);
    printf("Price for beverages : Rs. %.2lf\n", beveragesRate);
    printf("Discounts Applied   : Rs. %.2lf\n", discount);
    printf("Free Offers         : %d Popcorn(s) and %d Soft Drink(s)\n", offerPop, offerSoft);
    printf("----------------------------------------------------------------------------------\n");
    printf("\t\t\t\tSub Total : Rs. %.2lf\n", subtotal);
    printf("==================================================================================\n");
    printf("Thank You, Come Again!\n\n");
}

// Cancel Reservation Function
void cancelReservation() {
    int sessionId;
    printf("\nEnter Session ID for Cancellation (1001-1007): ");
    scanf("%d", &sessionId);

    int idx = findMovieIndex(sessionId);
    if (idx == -1) {
        printf("\n[Error] Invalid Session ID!\n");
        return;
    }

    int canceledSeats[TOTAL_SEATS];
    int canceledCount = 0;
    int seatToCancel;

    printf("Which seat do you want to cancel? (Enter -1 to finish): \n");
    while (1) {
        scanf("%d", &seatToCancel);
        if (seatToCancel == -1) {
            break;
        }

        if (seatToCancel < 1 || seatToCancel > TOTAL_SEATS) {
            printf("[Error] Seat number must be between 1 and %d.\n", TOTAL_SEATS);
            continue;
        }

        if (movieBookDatabase[idx][seatToCancel - 1] == seatToCancel) {
            movieBookDatabase[idx][seatToCancel - 1] = 0;
            canceledSeats[canceledCount++] = seatToCancel;
            printf("Seat %d successfully canceled.\n", seatToCancel);
        } else {
            printf("Seat %d was not booked or is already free.\n", seatToCancel);
        }
    }

    if (canceledCount > 0) {
        printf("\nSuccessfully canceled seats: ");
        for (int i = 0; i < canceledCount; i++) {
            printf("%d%s", canceledSeats[i], (i == canceledCount - 1) ? "" : ", ");
        }
        printf("\n");
    } else {
        printf("\nNo seats were canceled.\n");
    }
}
