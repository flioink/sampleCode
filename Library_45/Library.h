#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include "Book.h"
#include "User.h"

class Library
{
private:
    int maxAmountOfBooks;
    int currentAmountOfBooks;
    Book* books;

public:

    Library(int maxAmountOfBooks);
    ~Library();
    void addBook(const Book& book);
    Book& getBook(int position);
    void showBooks();
    friend void Librarian::lendBook(Library& libToLendFrom, Borrower& personToLendTo, int position);
};


#endif // LIBRARY_H_INCLUDED
