#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <limits>
#include <vector>
#include "Database.h"

using namespace std;

vector<Database> database;

short peopleInDatabase;

void pressEnter();
void addPerson();
void displayAll();
void saveToFile();
void loadFromFile();
void searchName();

int main()
{


    loadFromFile();

    char choice;

    /*int arr[2][3] = {{1, 5, 7},
                     {9, 6, 8}};

    int row = sizeof(arr)/ sizeof(arr[0]);
    int col = sizeof(arr[0])/ sizeof(arr[0][0]);

    cout << row << endl;
    cout << col << endl;*///find rows and columns ina an array

do{
    cout << "Number of people in Database: " << peopleInDatabase << endl;
    cout << "Choose an option from the menu below:" << endl << endl;
    cout << "1.Add Person" << endl;
    cout << "2.Display All" << endl;
    cout << "3.Save To File" << endl;
    cout << "4.Load from file" << endl;
    cout << "5.Search Name" << endl;
    cout << "6.Remove Person" << endl << endl;

    choice = getch();

    switch(choice)
    {
    case '1':
        addPerson();
        break;
    case '2':
        displayAll();
        break;
    case '3':
        saveToFile();
        break;
    case '4':
        loadFromFile();
        break;
    case '5':
        searchName();
        break;
    case '6':
        cout << "test6" << endl;
        break;

    }

    pressEnter();

    system("cls");


}while(choice != 27);

    return 0;
}

void pressEnter()
{
    do{
        cout << "Press 'Enter' to continue" << endl;
    }while(getch() != 13);
}

void addPerson()
{
    string name, lastName, phone;
    short age;

    cout << "Enter name: ";
    cin >> name;

    cout << "Enter Last Name: ";
    cin >> lastName;

    cout << "Enter age: ";
    while(!(cin >> age))
    {
        cout << "bad value, retry: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter Phone Number: ";
    cin >> phone;

    database.push_back(Database(name, lastName, age, phone));
    peopleInDatabase++;
}

void displayAll()
{
    if(peopleInDatabase > 0)
    {
        int i = 0;
        for(vector<Database>::iterator it = database.begin(); it != database.end(); it++)
        {
            cout << "Person index: " << (i++) + 1 << endl;
            cout << "Name: " << it->getName() << endl;
            cout << "Last Name: " << it->getLastName() << endl;
            cout << "Age: " << it->getAge() << endl;
            cout << "Phone: " << it->getPhone() << endl;
            if(i < peopleInDatabase)
            {
                cout << "-----------------------" << endl;
            }
            else
            {
                cout << endl;
            }
        }
    }
}

void saveToFile()
{
    if(peopleInDatabase > 0)
    {
        ofstream file("dataSave.txt");

        if(file.is_open())
        {
            file << peopleInDatabase << endl;

            for(int i = 0; i < peopleInDatabase; i++)
            {
                file << database[i].getName() << endl;
                file << database[i].getLastName() << endl;
                file << database[i].getAge() << endl;
                file << database[i].getPhone() << endl;
            }

            file.close();
        }

        else
        {
            cout << "Cannot access the file" << endl;
        }
    }

    else
    {
        cout << "Empty Database" << endl;
    }
}


void loadFromFile()
{
    ifstream file("dataSave.txt");

    if(file.is_open())
    {
        file >> peopleInDatabase;

        string name, lastName, phone;
        short age;

        for(int i = 0; i < peopleInDatabase; i++)
        {
            file >> name;
            file >> lastName;
            file >> age;
            file >> phone;
            database.push_back(Database(name, lastName, age, phone));

        }
    }

    else
    {
        cout << "Cannot access the file" << endl;
    }
}


void searchName()
{
    if(peopleInDatabase > 0)
    {
        string name;
        cout << "Enter name: ";
        cin >> name;
        int match = 0;
        vector<int> ls;

        for(int i = 0; i < peopleInDatabase; i++)
        {
            if(database[i].getName() == name)
            {
                match++;
                ls.push_back(i);
            }
        }

        cout << "Matches found: " << match << endl;


        for(int i = 0; i < match; i++)
        {
            cout << "Person index: " << (ls[i]) + 1 << endl;
            cout << "Name: " << database[ls[i]].getName() << endl;
            cout << "Last Name: " << database[ls[i]].getLastName() << endl;
            cout << "Age: " << database[ls[i]].getAge() << endl;
            cout << "Phone: " << database[ls[i]].getPhone() << endl;
            if(match == 0)
            {
                cout << endl;
            }
            else if(i < match - 1)
            {
                cout << "-------" << endl;
            }

            else
            {
                cout << endl;
            }
        }

    }

    else
    {
        cout << "Empty Database" << endl;
    }
}
































































































































