#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PURPLE "\033[0;35m"
#define BOLD_PURPLE "\033[1;35m"
#define PINK "\033[1;95m"
#define LIGHT_PINK "\033[0;95m"
#define RESET "\033[0m"

#define NOMS_FULL_NAME "Luvinga Nominaanda"

int equalsIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void printBanner() {
    printf("\n" BOLD_PURPLE "==========================================\n" RESET);
    printf(PINK "          * * *   N O M S   * * *         \n" RESET);
    printf(LIGHT_PINK "          Exclusive Friends App           \n" RESET);
    printf(BOLD_PURPLE "==========================================\n" RESET);
}

int isAllowedFriend(const char *name) {
    if (equalsIgnoreCase(name, "Lizzy K") || equalsIgnoreCase(name, "K Lydia")) {
        return 1;
    }
    return 0;
}

int loginScreen(char *loggedInFriend) {
    char answer[20];
    char friendName[50];
    char secretAnswer[100];

    printBanner();

    while (1) {
        printf(PINK "\nAre you Noms' friend? (yes/no): " RESET);
        if (!fgets(answer, sizeof(answer), stdin)) return 0;
        trimNewline(answer);

        if (equalsIgnoreCase(answer, "yes") || equalsIgnoreCase(answer, "y")) {
            break;
        } else if (equalsIgnoreCase(answer, "no") || equalsIgnoreCase(answer, "n")) {
            printf(PURPLE "\nSorry! Only Noms' close friends are allowed inside.\n" RESET);
            return 0;
        } else {
            printf(LIGHT_PINK "Please type 'yes' or 'no'.\n" RESET);
        }
    }

    while (1) {
        printf(PINK "\nEnter your name as it is stored in Noms' app: " RESET);
        if (!fgets(friendName, sizeof(friendName), stdin)) return 0;
        trimNewline(friendName);

        if (isAllowedFriend(friendName)) {
            if (equalsIgnoreCase(friendName, "Lizzy K")) strcpy(loggedInFriend, "Lizzy K");
            else strcpy(loggedInFriend, "K Lydia");
            break;
        } else {
            printf(PURPLE "Name not recognized in Noms' circle! Please try again.\n" RESET);
        }
    }

    while (1) {
        printf(PINK "\nTo prove you are really Noms' friend, enter Noms' full name: " RESET);
        if (!fgets(secretAnswer, sizeof(secretAnswer), stdin)) return 0;
        trimNewline(secretAnswer);

        if (equalsIgnoreCase(secretAnswer, NOMS_FULL_NAME)) {
            printf(PINK "\nVerified! Welcome into Noms, %s!\n" RESET, loggedInFriend);
            return 1;
        } else {
            printf(PURPLE "That's not Noms' full name! Try again.\n" RESET);
        }
    }
}

void nomsDashboard(const char *friendName) {
    char input[20];
    int choice;

    while (1) {
        printf("\n" BOLD_PURPLE "------------------------------------------\n" RESET);
        printf(PINK "   NOMS LOUNGE - Logged in as: %s\n" RESET, friendName);
        printf(BOLD_PURPLE "------------------------------------------\n" RESET);
        printf(LIGHT_PINK "1. View Noms' Friend Circle\n" RESET);
        printf(LIGHT_PINK "2. Leave a Note for Noms\n" RESET);
        printf(LIGHT_PINK "3. Log Out\n" RESET);
        printf(PINK "Choose an option (1-3): " RESET);

        if (!fgets(input, sizeof(input), stdin)) break;
        choice = atoi(input);

        if (choice == 1) {
            printf("\n" BOLD_PURPLE "Noms' Official Besties:\n" RESET);
            printf(PINK "  * Lizzy K\n" RESET);
            printf(PINK "  * K Lydia\n" RESET);
        } else if (choice == 2) {
            char note[200];
            printf(PINK "Write a message for Noms: " RESET);
            if (fgets(note, sizeof(note), stdin)) {
                trimNewline(note);
                FILE *f = fopen("noms_notes.txt", "a");
                if (f) {
                    fprintf(f, "[From %s]: %s\n", friendName, note);
                    fclose(f);
                    printf(PURPLE "Message saved for Noms!\n" RESET);
                }
            }
        } else if (choice == 3) {
            printf(PURPLE "\nLogged out of Noms. Bye %s!\n" RESET, friendName);
            break;
        } else {
            printf(LIGHT_PINK "Please pick 1, 2, or 3.\n" RESET);
        }
    }
}

int main() {
    char currentFriend[50];

    if (loginScreen(currentFriend)) {
        nomsDashboard(currentFriend);
    }

    return 0;
}

