#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

// Template for Library record
struct Bookl {
    int BookId;
    char Bookname[30];
    float Book_price;
};
typedef struct Bookl record;

// Global Variables.
record book;
FILE *fp = NULL;

// Function prototypes.
void printLogo(void);
int password(const char *p);
void addBook(void);
void displayALLBook(void);
int countAllBook(void);
void searchById(void);
void searchByName(void);
void updateBookRec(void);
void deleteRec(void);
int Time(void);
int ch;

int main() {
    int choice;
    printLogo();
    // Checking Password
    printf("\t\t\t\tEnter the Password: ");
    if (password("Poornima") == 0) {
        printf("\n\t\t\tWrong Password.\n");
        getch();
        exit(0);
    }
    while (1) {
        system("cls");
        printLogo();
        Time();
        printf("\n\t\tAvailable Choices are:\n");
        printf("\t\t1. Add a New Book in Database.\n");
        printf("\t\t2. Display ALL Records of Books.\n");
        printf("\t\t3. Count ALL Records of Books in Library.\n");
        printf("\t\t4. Search Book By ID or Name.\n");
        printf("\t\t5. Update the Book Records.\n");
        printf("\t\t6. Delete the Book Records from Database.\n");
        printf("\t\t7. Exit.\n");
        printf("\t\tSelect a Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                Time();
                addBook();
                getch();
                break;
            case 2:
                system("cls");
                Time();
                displayALLBook();
                getch();
                break;
            case 3:
                Time();
                printf("\t\t\tTotal Record: %d\n", countAllBook());
                getch();
                break;
            case 4:
                system("cls");
                printLogo();
                Time();
                printf("\t\t\tSelect choices:\n");
                printf("\t\t\t1. Search Book by ID:\n");
                printf("\t\t\t2. Search Book by Name:\n");
                printf("\t\t\tEnter the Choice: ");
                scanf("%d", &ch);
                switch (ch) {
                    case 1:
                        Time();
                        searchById();
                        getch();
                        break;
                    case 2:
                        Time();
                        searchByName();
                        getch();
                        break;
                    default:
                        Time();
                        printf("\t\t\tWrong Choice:");
                        getch();
                        break;
                }
                break;
            case 5:
                system("cls");
                Time();
                updateBookRec();
                getch();
                break;
            case 6:
                system("cls");
                Time();
                deleteRec();
                getch();
                break;
            case 7:
                printLogo();
                Time();
                printf("\t\t\t\t Thank you for Visiting us.");
                getch();
                system("cls");
                exit(0);
            default:
                printf("\t\t\tThis choice is not Available.");
                getch();
                break;
        }
    }
    return 0;
}

void printLogo(void) {
    system("cls");
    printf("\n\t\t\tLIBRARY MANAGEMENT SYSTEM\n");
    printf("\t\t\tPOORNIMA COLLEGE OF ENGINEERING\n");
    printf("\t\t\tSitapura, Jaipur\n");
}

int password(const char *p) {
    char ch, pw[20];
    int i, flag = 1;
    for (i = 0; i < strlen(p); i++) {
        ch = getch();
        putchar('*');
        if (ch != p[i]) {
            flag = 0;
        }
    }
    return flag;
}

void addBook(void) {
    fp = fopen("Library_Database.bin", "ab+");
    if (fp == NULL) {
        printLogo();
        printf("\t\t\tFile Opening ERROR!");
        return;
    }
    fflush(stdin);
    printf("\t\tEnter Book Name: ");
    fgets(book.Bookname, 30, stdin);
    printf("\t\tEnter Book_ID: ");
    scanf("%d", &book.BookId);
    printf("\t\tEnter Book_Price:₹ ");
    scanf("%f", &book.Book_price);
    fwrite(&book, sizeof(book), 1, fp);
    fclose(fp);
    printLogo();
    printf("\t\t\t\tRecord is Added successfully.");
}

void displayALLBook(void) {
    printLogo();
    Time();
    fp = fopen("Library_Database.bin", "rb");
    if (fp == NULL) {
        printf("\t\t\tFile Opening ERROR!");
        return;
    }
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        printf("\t\t\tNAME: %s", book.Bookname);
        printf("\t\t\tBookID: %d\n", book.BookId);
        printf("\t\t\tBook_Price: %f\n", book.Book_price);
    }
    fclose(fp);
}

int countAllBook(void) {
    printLogo();
    Time();
    int count = 0;
    fp = fopen("Library_Database.bin", "rb");
    fseek(fp, 0, SEEK_END);
    count = ftell(fp) / sizeof(book);
    fclose(fp);
    return count;
}

void searchById(void) {
    int Id;
    printLogo();
    Time();
    printf("\t\t\tEnter Book ID: ");
    scanf("%d", &Id);
    fp = fopen("Library_Database.bin", "rb");
    if (fp == NULL) {
        printf("\t\t\tFile Opening ERROR!");
        return;
    }
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (Id == book.BookId) {
            Time();
            printf("\t\t\tNAME: %s", book.Bookname);
            printf("\t\t\tBookID: %d\n", book.BookId);
            printf("\t\t\tBook_Price: %f\n", book.Book_price);
            fclose(fp);
            return;
        }
    }
    printLogo();
    printf("\t\t\tThis record Doesn't Exist");
    fclose(fp);
}

void searchByName(void) {
    char BookName[30];
    fflush(stdin);
    printLogo();
    Time();
    printf("\t\t\tEnter Book Name: ");
    fgets(BookName, 30, stdin);
    fp = fopen("Library_Database.bin", "rb");
    if (fp == NULL) {
        printf("\t\t\tFile Opening ERROR!");
        return;
    }
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (strcmp(BookName, book.Bookname) == 0) {
            Time();
            printf("\t\t\tNAME: %s", book.Bookname);
            printf("\t\t\tBookID: %d\n", book.BookId);
            printf("\t\t\tBook_Price: %f\n", book.Book_price);
            fclose(fp);
            return;
        }
    }
    printLogo();
    printf("\t\t\tThis record Doesn't Exist");
    fclose(fp);
}

void deleteRec(void) {
    system("cls");
    printLogo();
    Time();
    int id;
    int flag = 0;
    FILE *tempf = fopen("temp.bin", "wb+");
    fp = fopen("Library_Database.bin", "rb");
    if (tempf == NULL || fp == NULL) {
        printf("\t\t\tFile Opening ERROR!!!!!!!!!!!!");
        return;
    }
    printf("\t\t\tEnter BOOK_Id: ");
    scanf("%d", &id);
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (book.BookId == id) {
            flag = 1;
            continue;
        }
        fwrite(&book, sizeof(book), 1, tempf);
    }
    fclose(fp);
    fclose(tempf);
    system("cls");
    printLogo();
    if (flag == 1) {
        Time();
        remove("Library_Database.bin");
        rename("temp.bin", "Library_Database.bin");
        printf("\t\t\t\t\tRecord is deleted:");
    } else {
        Time();
        printf("\t\t\t\t\tRecord does not Exist.");
        remove("temp.bin");
    }
}

void updateBookRec(void) {
    int id;
    int flag = 0;
    FILE *tempf = fopen("temp.bin", "wb+");
    fp = fopen("Library_Database.bin", "rb");
    if (tempf == NULL || fp == NULL) {
        printf("\t\t\tFile Opening ERROR!!!!!!!!!!!!");
        return;
    }
    printf("\t\t\tEnter Book_Id: ");
    scanf("%d", &id);
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (book.BookId == id) {
            flag = 1;
            printf("\t\t\tEnter updated Book_Id: ");
            scanf("%d", &book.BookId);
            printf("\t\t\tEnter the updated Book_Name: ");
            fflush(stdin);
            fgets(book.Bookname, 30, stdin);
            printf("\t\t\tEnter Updated Book_Price: ");
            scanf("%f", &book.Book_price);
            fwrite(&book, sizeof(book), 1, tempf);
            continue;
        }
        fwrite(&book, sizeof(book), 1, tempf);
    }
    fclose(fp);
    fclose(tempf);
    system("cls");
    printLogo();
    if (flag == 1) {
        remove("Library_Database.bin");
        rename("temp.bin", "Library_Database.bin");
        printf("\t\t\t\t\tRecord is Updated:");
    } else {
        printf("\t\t\t\t\tRecord does not Exist.");
        remove("temp.bin");
    }
}

int Time(void) {
    time_t t = time(NULL);
    printf("\t\tCurrent Date/Time: %s\n", ctime(&t));
    return 0;
}
