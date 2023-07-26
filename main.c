#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_CONTACTS 100

struct Contact {
    char name[100];
    char address[100];
    char gender[10];
    char email[100];
    char phone[15];
};

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void sleep_ms(int milliseconds) {
    Sleep(milliseconds);
}

void password(void) {
    char passwords[20] = "Satara@123"; // Change this to your desired password
    gotoxy(22, 2);
    int j;
    int z;
    char name[40] = "Enter Password:";
    z = strlen(name);
    for (j = 0; j <= 16; j++) {
        sleep_ms(50);
        printf("\xDB");
    }
    for (j = 0; j <= z; j++) {
        sleep_ms(60);
        printf(" %c", name[j]);
    }
    for (j = 0; j <= 16; j++) {
        sleep_ms(50);
        printf("\xDB");
    }
    gotoxy(30, 4);
    printf("Password:");

    char ch, pass[20];
    int i = 0;
    while (1) {
        ch = getch();
        if (ch == 13) {
            pass[i] = '\0'; // Null-terminate the password string
            break;
        } else if (ch == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Erase the last printed character
            }
        } else {
            pass[i] = ch;
            i++;
            printf("*"); 
        }
    }

    if (strcmp(pass, passwords) == 0) {
        gotoxy(30, 6);
        printf("CORRECT PASSWORD.");
        sleep_ms(1000);
    } else {
        gotoxy(30, 6);
        printf("You entered the wrong password.");
        sleep_ms(700);
        system("cls");
        exit(0);
    }
}

void addContact(struct Contact *phonebook, int *numContacts) {
    if (*numContacts >= MAX_CONTACTS) {
        printf("Phonebook is full. Cannot add more contacts.\n");
        return;
    }

    printf("Enter the name: ");
    fgets(phonebook[*numContacts].name, sizeof(phonebook[*numContacts].name), stdin);
    printf("Enter the address: ");
    fgets(phonebook[*numContacts].address, sizeof(phonebook[*numContacts].address), stdin);
    printf("Enter the gender: ");
    fgets(phonebook[*numContacts].gender, sizeof(phonebook[*numContacts].gender), stdin);
    printf("Enter the email: ");
    fgets(phonebook[*numContacts].email, sizeof(phonebook[*numContacts].email), stdin);
    printf("Enter the phone number: ");
    fgets(phonebook[*numContacts].phone, sizeof(phonebook[*numContacts].phone), stdin);

    (*numContacts)++;
    printf("Contact added successfully!\n");
}

void searchContact(struct Contact *phonebook, int numContacts, const char *searchName) {
    int found = 0;
    for (int i = 0; i < numContacts; i++) {
        if (strcmp(phonebook[i].name, searchName) == 0) {
            found = 1;
            printf("Contact Found:\n");
            printf("Name: %s", phonebook[i].name);
            printf("Address: %s", phonebook[i].address);
            printf("Gender: %s", phonebook[i].gender);
            printf("Email: %s", phonebook[i].email);
            printf("Phone: %s", phonebook[i].phone);
            break;
        }
    }

    if (!found) {
        printf("Contact not found.\n");
    }
}

void listContacts(struct Contact *phonebook, int numContacts) {
    printf("***** LIST OF CONTACTS *****\n");
    for (int i = 0; i < numContacts; i++) {
        printf("Contact %d:\n", i + 1);
        printf("Name: %s", phonebook[i].name);
        printf("Address: %s", phonebook[i].address);
        printf("Gender: %s", phonebook[i].gender);
        printf("Email: %s", phonebook[i].email);
        printf("Phone: %s", phonebook[i].phone);
        printf("---------------------------\n");
    }
}

void saveContactsToFile(struct Contact *phonebook, int numContacts) {
    FILE *file = fopen("phonebook.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving contacts.\n");
        return;
    }

    for (int i = 0; i < numContacts; i++) {
        fprintf(file, "%s|%s|%s|%s|%s\n", phonebook[i].name, phonebook[i].address, phonebook[i].gender,
                phonebook[i].email, phonebook[i].phone);
    }

    fclose(file);
    printf("Contacts saved to file.\n");
}

void loadContactsFromFile(struct Contact *phonebook, int *numContacts) {
    FILE *file = fopen("phonebook.txt", "r");
    if (file == NULL) {
        printf("Error opening file for loading contacts.\n");
        return;
    }

    char line[255];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|\n]", phonebook[*numContacts].name, phonebook[*numContacts].address,
               phonebook[*numContacts].gender, phonebook[*numContacts].email, phonebook[*numContacts].phone);
        (*numContacts)++;
    }

    fclose(file);
    printf("Contacts loaded from file.\n");
}

int main() {
    struct Contact phonebook[MAX_CONTACTS];
    int numContacts = 0;
    char searchName[100];

    password(); // Check password before accessing the data

    // Load contacts from the file (if any) during program startup
    loadContactsFromFile(phonebook, &numContacts);

    int choice;
    do {
        printf("\n***** PHONEBOOK MENU *****\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. List All Contacts\n");
                // ... (previous code)

        printf("6. Save Contacts to File\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1:
                addContact(phonebook, &numContacts);
                break;
            case 2:
                printf("Enter the name to search: ");
                fgets(searchName, sizeof(searchName), stdin);
                searchContact(phonebook, numContacts, searchName);
                break;
            case 3:
                listContacts(phonebook, numContacts);
                break;
            // Add cases for modifying and deleting contacts...
            case 6:
                saveContactsToFile(phonebook, numContacts);
                break;
            case 7:
                printf("Exiting the phonebook application. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}


    
