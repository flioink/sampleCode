#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#include <iostream>
#include <string>

class Book
{
private:
    std::string title;
    std::string author;
    int publicationYear;
    int ID;

public:
    static int numberOfBooks;

    Book() = default;
    Book(std::string title, std::string author, int publicationYear);

    std::string getTitle()const;
    std::string getAuthor()const;
    int getPublicationYear()const;
    int getID()const;

    Book(const Book& book);
};


#endif // BOOK_H_INCLUDED
