#include <iostream>
#include "Book.h"
#include "Library.h"
#include "User.h"
#include <cstdlib>

using namespace std;

int main()
{
    Library library(7);

    const Book book1("\"1984\"", "G. Orwell", 1949);
    const Book book2("\"Captain Nemo\"", "J.Vernes", 1870);
    const Book book3("\"Demon Haunted World\"", "C. Sagan", 1993);
    const Book book4("\"Animal Farm\"", "G. Orwell", 1945);
    const Book book5("\"The Gulag Archipelago\"", "A. Solzhenitsyn", 1973);
    const Book book6 = book4;
    const Book book7 = book4;

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);
    library.addBook(book4);
    library.addBook(book5);
    library.addBook(book6);
    library.addBook(book7);



    Borrower borrower("Todor", "Kolev", 7);

    Librarian librarian("Foo", "Bar", 7);

    char choice;
    int position;

    while(true)
    {
        library.showBooks();
        borrower.showBooks();

        cout << "Borrow or return a book: ";
        cin >> choice;

        switch(choice)
        {
            case 'b':
            case 'B':
                cout << "Enter the position in the Library: ";
                cin >> position;
                librarian.lendBook(library, borrower, position);
                break;

            case 'r':
            case 'R':
                cout << "Enter the position in the User: ";
                cin >> position;

                borrower.returnBook(library, position);
        }


        system("cls");
    }


    return 0;
}
