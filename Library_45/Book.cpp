    #include "Book.h"

    int Book::numberOfBooks = 0;

    Book::Book(std::string title, std::string author, int publicationYear):
    title(title), author(author), publicationYear(publicationYear)
    {
        this->ID = Book::numberOfBooks++;
    }

    std::string Book::getTitle()const
    {
        return this->title;
    }

    std::string Book::getAuthor()const
    {
        return this->author;
    }

    int Book::getPublicationYear()const
    {
        return this->publicationYear;
    }

    int Book::getID()const
    {
        return this->ID;
    }

    Book::Book(const Book& book)
    {
        this->title = book.getTitle();
        this->author = book.getAuthor();
        this->publicationYear = book.getPublicationYear();
        this->ID = Book::numberOfBooks++;
    }
