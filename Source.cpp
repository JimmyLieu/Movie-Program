//Jimmy Lieu
//Movie Seat Ticket Reservation Program (Simple)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define NUM_THEATERS 10
#define NUM_ADMINS 5

//function prototypes
//these are void because there is no arguments
void showWelcomeScreen();
void mainErrorMessage();
void printSeperators();
void printMovieDetails(int theater, int movieID, int numSeats, int currentAttendance, double pricePerTicket, int isIMax);
void listAllMovies(int movieIDs[], int numSeats[], int currentAttendance[], double pricePerTicket[], int isIMax[]);
void processNewMovie(int movieIDs[], int numSeats[], int currentAttendance[], double pricePerTicket[], int isIMax[]);
void printOutAdmins(int codes[]);

// mainExitMessage is an int because option = mainExitMessage();
int mainExitMessage();
int isAdminCode(int candidateCode, int codes[]);
int authenticate(int validCodes[]);

void main() {
    //Parallel arrays to hold information for each theater
    int movieIDs[NUM_THEATERS];
    int numSeats[NUM_THEATERS];
    int currentAttendance[NUM_THEATERS];
    double pricePerTicket[NUM_THEATERS];
    int isIMax[NUM_THEATERS];


    for (int i = 0; i < NUM_THEATERS; i++) {
        movieIDs[i] = 0;
        numSeats[i] = 0;
        currentAttendance[i] = 0;
        pricePerTicket[i] = 0.0;
        isIMax[i] = 0;
    }

    //test a movie
    /*int theater = 3;
    movieIDs[theater] = 763054;
    numSeats[theater] = 60;
    currentAttendance[theater] = 3;
    pricePerTicket[theater] = 10.50;
    isIMax[theater] = 1;
    printMovieDetails(theater, movieIDs[theater], numSeats[theater], currentAttendance[theater], pricePerTicket[theater], isIMax[theater]);
    */
    int adminIDs[] = {1010,1111,1212,1313,1414};
    int option;
    do {
        showWelcomeScreen();
        printf("Please choose one of the options above: ");
        scanf("%d", &option);
        switch (option) {
        case 0://adjust admins
            int adminNumber;
            option = authenticate(adminIDs);
            if (option != 6) {
                printOutAdmins(adminIDs);
                printf("Please enter the ID you wish to change or an invalid ID to cancel: ");
                scanf("%d", &adminNumber);
                if (adminNumber >= 0 && adminNumber < NUM_ADMINS) {
                    printf("Please enter the new ID: ");
                    scanf("%d", &adminIDs[adminNumber]);
                }
            }
            break;
        case 1:
            option = authenticate(adminIDs);
            if (option != 6) {
                processNewMovie(movieIDs, numSeats, currentAttendance, pricePerTicket, isIMax);
            }
            break;
        case 2: 
            option = authenticate(adminIDs);
            if (option != 6) {
                //All of the code for case 2 except the break (FP3)
            }
            break;
        case 3:
            listAllMovies(movieIDs, numSeats, currentAttendance, pricePerTicket, isIMax);
            break;
        case 4:
            int movieNumber;
            listAllMovies(movieIDs, numSeats, currentAttendance, pricePerTicket, isIMax);
            printf("Please enter the number of the movie for which you wish to buy a ticket: ");
            scanf("%d", &movieNumber);
            movieNumber--;
            if (currentAttendance[movieNumber] < numSeats[movieNumber]) {
                currentAttendance[movieNumber]++;
                printf("You have successfully purchased a ticket for %d.", movieIDs[movieNumber]);
            }
            else
                printf("%d is already full. Ticket not purchased.", movieIDs[movieNumber]);
            break;
        case 5:
            listAllMovies(movieIDs, numSeats, currentAttendance, pricePerTicket, isIMax);
            printf("Please enter the number of the movie for which you wish to cancel a ticket: ");
            scanf("%d", &movieNumber);
            movieNumber--;
            if (currentAttendance[movieNumber] >= 1) {
                currentAttendance[movieNumber]--;
                printf("You have successfully cancelled a ticket for %d.", movieIDs[movieNumber]);
            }
            else
                printf("%d is already empty. Ticket not cancelled.", movieIDs[movieNumber]);
            break;
        case 6:
            option = mainExitMessage();
            break;
        default:
            mainErrorMessage();
            printf("\n\n");
            break;
        }
        for (int i = 0; i < 20; i++)
            printf("\n");
    } while (option != 6);

}
void showWelcomeScreen() {
    printf("      Simple Movie Ticket Booking System\n");
    printSeperators();
    printf("||      0- Change an Admin         (admin only)      ||\n");
    printf("||      1- Process a New Movie     (admin only)      ||\n");
    printf("||      2- Edit a movie            (admin only)      ||\n");
    printf("||      3- View the list of Movies                   ||\n");
    printf("||      4- Purchase a Ticket                         ||\n");
    printf("||      5- Cancel a Ticket                           ||\n");
    printf("||      6- Exit                                      ||\n");
    printSeperators();
}
void mainErrorMessage() {
    printf("\nInvalid input! Please choose a valid option.\n");
}
int mainExitMessage() {
    int returnMe = 0;
    char response;
    do {
        printf("Are you sure you wish to exit (Y/N): ");
        scanf("%c", &response);
    } while (response != 'Y' && response != 'y' && response != 'N' &&
        response != 'n');
    if (response == 'Y' || response == 'y')
        return 6;
    return returnMe;
}
void printSeperators() {
    printf("====================================================\n");
}
void printMovieDetails(int theater, int movieID, int numSeats, int currentAttendance, double pricePerTicket, int isIMax) {
    printSeperators();
    printf("Movie ID: %d\t\t\t\t", movieID);
    if (isIMax)
        printf("IN IMAX");
    printf("\n%d/%d seats are currently taken\t\t\tTheater: %d\n", currentAttendance, numSeats, theater);
    printf("Movie Price: $ %.2f\n", pricePerTicket);
    printSeperators();
}
void listAllMovies(int movieIDs[], int numSeats[], int currentAttendance[], double pricePerTicket[], int isIMax[]) {
    for (int i = 0; i < NUM_THEATERS; i++) {
        printMovieDetails(i + 1, movieIDs[i], numSeats[i], currentAttendance[i], pricePerTicket[i], isIMax[i]);
    }
}
void processNewMovie(int movieIDs[], int numSeats[], int currentAttendance[], double pricePerTicket[], int isIMax[]) {
    int movieNumber;
    do {
        printf("Please enter the movie number to replace: ");
        scanf("%d", &movieNumber);
    } while (movieNumber < 1 || movieNumber > NUM_THEATERS);
    movieNumber--;
    printf("Please enter the ID of the movie: ");
    scanf("%d", &movieIDs[movieNumber]);
    printf("Please enter the number of seats: ");
    scanf("%d", &numSeats[movieNumber]);
    printf("Enter the price per ticket: ");
    scanf("%lf", &pricePerTicket[movieNumber]);
    currentAttendance[movieNumber] = 0;
    char myChar;
    printf("Is the movie in IMax (Y for Yes): ");
    scanf(" %c", &myChar);
    if (myChar == 'Y' || myChar == 'y')
        isIMax[movieNumber] = 1;
    else
        isIMax[movieNumber] = 0;
}

int isAdminCode(int candidateCode, int codes[]) {
    for (int i = 0; i < NUM_ADMINS; i++)
        if (codes[i] == candidateCode)
            return 1;
    return 0;
}
int authenticate(int validCodes[]) {
    int adminCode, guesses = 1;
    do {
        guesses++;
        printf("You must be an admin to perform this action. You have 3 attempts to log on.\n");
        printf("Please enter your code: ");
        scanf("%d", &adminCode);
    } while (!isAdminCode(adminCode, validCodes) && guesses <=3);
    if (!isAdminCode(adminCode, validCodes)) {
        printf("SECURITY VIOLATION! SYSTEM EXITING!!!! WORLD ENDING!!!! SPEND TIME WITH YOUR FAMILY!!");
        return 6;
    }
    else
        return 3276;
}
void printOutAdmins(int codes[]) {
    for (int i = 0; i < NUM_ADMINS; i++)
        printf("%d: %d\n", i, codes[i]);

}