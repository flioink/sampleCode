#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "Book.h"
class Library;

class User
{
protected:
    std::string name;
    std::string lastName;

public:

    User(std::string name, std::string lastName);

    std::string getName()const;
    std::string getLastName()const;
};

class Borrower: public User
{
protected:
    friend class Librarian;
    int maxAmountOfBooks;
    int userAmountOfBooks;
    Book* booksInPossession;

public:

    Borrower(std::string name, std::string lastName, int maxAmountOfBooks);
    void returnBook(Library& libToReturnTo, int position);
    Book& getBook(int position);
    void showBooks();

    Borrower(const Book&) = delete; // cpy cstr disable
    Borrower& operator=(const Book&) = delete;
};

class Librarian: public Borrower
{
public:

    Librarian(std::string name, std::string lastName, int maxAmountOfBooks);
    void lendBook(Library& libToLendFrom, Borrower& personToLendTo, int position);
};

#endif // USER_H_INCLUDED
