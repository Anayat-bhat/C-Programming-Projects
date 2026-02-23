#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define BOOK_FILE "books.txt"
#define MAX_TITLE 100
#define MAX_AUTHOR 100



typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int isIssued;
} Book;

/* ---------- Function Declarations ---------- */


void adminMenu();
void userMenu();
void addBook();
void viewBooks();
void issueBook();
void returnBook();
Book* loadBooks(int *count);
void saveBooks(Book *books, int count);


/* ---------- Load Books from File ---------- */


Book* loadBooks(int *count) {
    FILE *fp = fopen(BOOK_FILE, "r");

    if (!fp) {
        *count = 0;
        return NULL;
    }

    Book temp;
    int c = 0;

    while (fscanf(fp, "%d|%99[^|]|%99[^|]|%d\n",
                  &temp.id, temp.title, temp.author, &temp.isIssued) != EOF) {
        c++;
    }

    rewind(fp);

    Book *books = (Book*) malloc(c * sizeof(Book));
    if (!books) {
        printf("Memory allocation failed!\n");
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < c; i++) {
        fscanf(fp, "%d|%99[^|]|%99[^|]|%d\n",
               &books[i].id,
               books[i].title,
               books[i].author,
               &books[i].isIssued);
    }

    fclose(fp);
    *count = c;
    return books;
}



/* ---------- Save Books to File ---------- */


void saveBooks(Book *books, int count) {
    FILE *fp = fopen(BOOK_FILE, "w");
    if (!fp) {
        printf("Error saving data!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d|%s|%s|%d\n",
                books[i].id,
                books[i].title,
                books[i].author,
                books[i].isIssued);
    }

    fclose(fp);
}



/* ---------- Add Book ---------- */



void addBook() {
    int count;
    Book *books = loadBooks(&count);

    books = realloc(books, (count + 1) * sizeof(Book));
    if (!books) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &books[count].id);
    getchar();

    printf("Enter Title: ");
    fgets(books[count].title, MAX_TITLE, stdin);
    books[count].title[strcspn(books[count].title, "\n")] = 0;

    printf("Enter Author: ");
    fgets(books[count].author, MAX_AUTHOR, stdin);
    books[count].author[strcspn(books[count].author, "\n")] = 0;

    books[count].isIssued = 0;

    count++;
    saveBooks(books, count);
    free(books);

    printf("Book added successfully!\n");
}



/* ---------- View Books ---------- */



void viewBooks() {
    int count;
    Book *books = loadBooks(&count);

    if (!books || count == 0) {
        printf("No books available.\n");
        return;
    }

    printf("\n------ Book List ------\n");

    for (int i = 0; i < count; i++) {
        printf("ID: %d\n", books[i].id);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Status: %s\n\n",
               books[i].isIssued ? "Issued" : "Available");
    }

    free(books);
}



/* ---------- Issue Book ---------- */


void issueBook() {
    int count, id, found = 0;
    Book *books = loadBooks(&count);

    if (!books || count == 0) {
        printf("No books available.\n");
        return;
    }

    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (books[i].id == id && books[i].isIssued == 0) {
            books[i].isIssued = 1;
            found = 1;
            break;
        }
    }

    if (found) {
        saveBooks(books, count);
        printf("Book issued successfully!\n");
    } else {
        printf("Book not available or not found.\n");
    }

    free(books);
}


/* ---------- Return Book ---------- */



void returnBook() {
    int count, id, found = 0;
    Book *books = loadBooks(&count);

    if (!books || count == 0) {
        printf("No books available.\n");
        return;
    }

    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (books[i].id == id && books[i].isIssued == 1) {
            books[i].isIssued = 0;
            found = 1;
            break;
        }
    }

    if (found) {
        saveBooks(books, count);
        printf("Book returned successfully!\n");
    } else {
        printf("Book not found or not issued.\n");
    }

    free(books);
}



/* ---------- Admin Menu ---------- */



void adminMenu() {
    int choice;
    do {
        printf("\n--- ADMIN MENU ---\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 3);
}



/* ---------- User Menu ---------- */



void userMenu() {
    int choice;
    do {
        printf("\n--- USER MENU ---\n");
        printf("1. View Books\n");
        printf("2. Issue Book\n");
        printf("3. Return Book\n");
        printf("4. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewBooks(); break;
            case 2: issueBook(); break;
            case 3: returnBook(); break;
            case 4: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);
}



/* ---------- Main ---------- */



int main() {
    int choice;

    do {
        printf("\n====== LIBRARY MANAGEMENT SYSTEM ======\n");
        printf("1. Admin Mode\n");
        printf("2. User Mode\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: adminMenu(); break;
            case 2: userMenu(); break;
            case 3: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}