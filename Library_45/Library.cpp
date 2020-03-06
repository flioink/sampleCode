#include "Library.h"

    Library::Library(int maxAmountOfBooks):
    maxAmountOfBooks(maxAmountOfBooks), currentAmountOfBooks(0)
    {
        books = new Book[maxAmountOfBooks];
    }

    Library::~Library()
    {
        delete[] books;
    }

    void Library::addBook(const Book& book)
    {
        if(currentAmountOfBooks < maxAmountOfBooks)
        {
            books[currentAmountOfBooks++] = book;
        }

    }

    Book& Library::getBook(int position)
    {
        if(position < currentAmountOfBooks)
        {
            return books[position];
        }

        else
        {
            return books[0];
        }
    }

    void Library::showBooks()
    {
        for(int i = 0; i < currentAmountOfBooks; i++)
        {
            std::cout << "Position in Library-> " << i << std::endl;
            std::cout << "ID [" << getBook(i).getID() << "]" << std::endl;
            std::cout << "Title: " << getBook(i).getTitle() << std::endl;
            std::cout << "Author: " << getBook(i).getAuthor() << std::endl;
            std::cout << "Year Published: " << getBook(i).getPublicationYear() << std::endl;

            if(i < currentAmountOfBooks - 1)
            {
                std::cout << "----------------------" << std::endl;
            }

            else
            {
                std::cout << std::endl;
            }
        }

    }
