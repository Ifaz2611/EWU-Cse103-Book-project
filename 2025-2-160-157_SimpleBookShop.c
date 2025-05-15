#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 500          // Maximum number of books the shop can store
#define TITLE_LEN 50           // Maximum length of a book title
#define AUTHOR_LEN 30          // Maximum length of author's name

// Book record structure
struct Book {
    char title[TITLE_LEN + 1];     // Title of the book (+1 for null terminator)
    char author[AUTHOR_LEN + 1];   // Author's name
    double price;                  // Price of the book
    int copies;                    // Number of copies available
};

// Global array to hold the books
struct Book library[MAX_BOOKS];
int bookCount = 0;  // Number of books currently in the system

// Function declarations
void showWelcomeMessage();
void showGoodByeMessage();
void showMenuOptions();
void showBooks();
void addBook();
void searchBook();
void showNumberOfBooks();

int main() {
    int choice;

    showWelcomeMessage();  // display a custom greeting
    showMenuOptions();     // list the menu items once at start

    // Main menu loop: repeats until option 6 is chosen
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume the leftover newline

        switch (choice) {
            case 1:
                showMenuOptions();   // redisplay menu
                break;
            case 2:
                showBooks();         // list all books
                break;
            case 3:
                addBook();           // prompt to add a new book
                break;
            case 4:
                searchBook();        // prompt to search by title
                break;
            case 5:
                showNumberOfBooks(); // display total copies
                break;
            case 6:
                showGoodByeMessage(); // exit message
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}

// Displays the welcome banner
void showWelcomeMessage() {
    printf("======================================\n");
    printf("  Welcome to the Ultimate Book Heaven!\n");
    printf("======================================\n\n");
}

// Displays the exit banner
void showGoodByeMessage() {
    printf("\n======================================\n");
    printf("  Thank you for using Book Heaven!\n");
    printf("    Have a great day ahead!\n");
    printf("======================================\n");
}

// Shows the exact menu you provided
void showMenuOptions() {
    printf("Please select a menu option number(1-6):\n");
    printf("1) Display this menu.\n");
    printf("2) Show all available books.\n");
    printf("3) Add a book to the book shop.\n");
    printf("4) Search a book by title.\n");
    printf("5) Display the total number of books.\n");
    printf("6) Exit from this book shop system.\n\n");
}

// Prints every book’s details or indicates none exist yet
void showBooks() {
    if (bookCount == 0) {
        printf("No books in the system yet.\n");
        return;
    }
    printf("\nList of Books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Book %d:\n", i + 1);
        printf("  Enter Title : %s\n", library[i].title);
        printf("  Author: %s\n", library[i].author);
        printf("  Price : %.2f TK\n", library[i].price);
        printf("  Copies: %d\n\n", library[i].copies);
    }
}

// Reads user input to populate a new Book struct
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Cannot add more books: library is full.\n");
        return;
    }
    printf("\nEnter details for book %d:\n", bookCount + 1);

    printf("Book Title (max %d chars): ", TITLE_LEN);
    fgets(library[bookCount].title, sizeof(library[bookCount].title), stdin);
    library[bookCount].title[strcspn(library[bookCount].title, "\n")] = '\0';

    printf("Book Author (max %d chars): ", AUTHOR_LEN);
    fgets(library[bookCount].author, sizeof(library[bookCount].author), stdin);
    library[bookCount].author[strcspn(library[bookCount].author, "\n")] = '\0';

    printf("Book Price (0.0 - 100000.99 TK): ");
    scanf("%lf", &library[bookCount].price);

    printf("Number of copies: ");
    scanf("%d", &library[bookCount].copies);
    getchar(); // consume newline

    bookCount++;
    printf("Book added successfully!\n");
}

// Performs case-insensitive title search and prints the result
void searchBook() {
    char query[TITLE_LEN + 1];
    printf("\nEnter title to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    for (int i = 0; i < bookCount; i++) {
        if (strcasecmp(library[i].title, query) == 0) {
            printf("Book found! Details:\n");
            printf("  Title : %s\n", library[i].title);
            printf("  Author: %s\n", library[i].author);
            printf("  Price : %.2f TK\n", library[i].price);
            printf("  Copies: %d\n", library[i].copies);
            return;
        }
    }
    printf("Book not found.\n");
}

// Sums and displays the total number of copies across all titles
void showNumberOfBooks() {
    int totalCopies = 0;
    for (int i = 0; i < bookCount; i++) {
        totalCopies += library[i].copies;
    }
    printf("\nTotal number of book copies in the library: %d\n", totalCopies);
}
