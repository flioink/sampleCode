#include "User.h"
#include "Library.h"

    User::User(std::string name, std::string lastName):
    name(name), lastName(lastName)
    {

    }

    std::string User::getName()const
    {
        return this->name;
    }

    std::string User::getLastName()const
    {
        return this->lastName;
    }


    Borrower::Borrower(std::string name, std::string lastName, int maxAmountOfBooks):
    User(name, lastName)
    {
        this->maxAmountOfBooks = maxAmountOfBooks;
        this->userAmountOfBooks = 0;
        this->booksInPossession = new Book[maxAmountOfBooks];
    }

    void Borrower::returnBook(Library& libToReturnTo, int position)
    {
        if(this->userAmountOfBooks > 0 && position < this->userAmountOfBooks)
        {
            libToReturnTo.addBook(booksInPossession[position]);

            for(int i = 0; i < maxAmountOfBooks - 1; i++)
            {
                if(i >= position)
                {
                    booksInPossession[i] = booksInPossession[i + 1];
                }
            }

            this->userAmountOfBooks--;
        }

    }

    Book& Borrower::getBook(int position)
    {
        if(position < userAmountOfBooks)
        {
            return booksInPossession[position];
        }

        else
        {
            return booksInPossession[0];
        }

    }

    void Borrower::showBooks()
    {
        std::cout << getName() << " " << getLastName() << " books: " << std::endl << std::endl;

        for(int i = 0; i < userAmountOfBooks; i++)
        {
            std::cout << "Position in User-> " << i << std::endl;
            std::cout << "ID [" << getBook(i).getID() << "]" << std::endl;
            std::cout << "Title: " << getBook(i).getTitle() << std::endl;
            std::cout << "Author: " << getBook(i).getAuthor() << std::endl;
            std::cout << "Year Published: " << getBook(i).getPublicationYear() << std::endl;

            if(i < userAmountOfBooks - 1)
            {
                std::cout << "----------------------" << std::endl;
            }

            else
            {
                std::cout << std::endl;
            }
        }


    }


    Librarian::Librarian(std::string name, std::string lastName, int maxAmountOfBooks):
    Borrower(name, lastName, maxAmountOfBooks)
    {

    }

    void Librarian::lendBook(Library& libToLendFrom, Borrower& personToLendTo, int position)
    {
        if(libToLendFrom.currentAmountOfBooks > 0)
        {
            if(personToLendTo.userAmountOfBooks < personToLendTo.maxAmountOfBooks && position < libToLendFrom.currentAmountOfBooks)
            {
               personToLendTo.booksInPossession[personToLendTo.userAmountOfBooks] = libToLendFrom.books[position];

               for(int i = 0; i < libToLendFrom.maxAmountOfBooks - 1; i++)
               {
                   if(i >= position)
                   {
                       libToLendFrom.books[i] = libToLendFrom.books[i + 1];
                   }
               }
                    personToLendTo.userAmountOfBooks++;
                    libToLendFrom.currentAmountOfBooks--;
            }
        }

    }
