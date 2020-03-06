#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Database.h"

using namespace std;
short peopleInDatabase;
vector<Database>database;

void pressEnter();
bool checkNum(string& s);
void addPerson();
void displayAll();
void saveToFile();
void loadFromFile();
void searchName();
void removePerson();
void edit();

int main()
{
    char choice;
    loadFromFile();

    do{
        cout << "Number Of People In Database: " << peopleInDatabase << endl; // Menu items
        cout << "Select an option from the menu below:" << endl;
        cout << "1. Add Person" << endl;
        cout << "2. Display All" << endl;
        cout << "3. Save" << endl;
        cout << "4. Load" << endl;
        cout << "5. Search Name" << endl;
        cout << "6. Remove Person" << endl;
        cout << "7. Edit" << endl << endl;

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
            removePerson();
            break;

            case '7':
            edit();
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
        cout << "Press 'Enter' to continue..." << endl;
    }while(getch()!= 13);
}

bool checkNum(string& s)
{
    if(s[0] == '0')
    {
        return false;
    }

    for(size_t i = 0; i < s.size();)
    {
        if(s[i] >= '0' && s[i] <= '9')
        {
            ++i;
        }

        else
        {
            return false;
        }
    }

    return true;
}
void addPerson()
{
    string name, lastName, phone;
    short age;

    cout << "Enter name: ";
    getline(cin, name, '\n');

    cout << "Enter last name: ";
    getline(cin, lastName, '\n');

    string test("");
    cout << "Enter age: ";
    getline(cin, test, '\n');

    while(!checkNum(test))
    {
        cout << "Enter age: ";
        getline(cin, test, '\n');
    }

    age = stoi(test);

    cout << "Enter Phone Number: ";
    getline(cin, phone, '\n');

    database.push_back(Database(name, lastName, age, phone));
    peopleInDatabase++;
}

void displayAll()
{
    if(peopleInDatabase > 0)
    {
        for(int i = 0; i != peopleInDatabase; ++i)
        {
            cout << "Person index: " << i + 1 << endl;
            cout << "Name: " << database[i].getName() << endl;
            cout << "Last Name: " << database[i].getLastName() << endl;
            cout << "Age: " << database[i].getAge() << endl;
            cout << "Phone Number: " << database[i].getPhone() << endl;
            if(i < peopleInDatabase - 1)
            {
                cout << "-------------------" << endl;
            }
            else
            {
                cout << endl;
            }
        }

    }
    else
    {
        cout << "Database is empty." << endl;
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

            for(int i = 0; i != peopleInDatabase; ++i)
            {
                file << database[i].getName() << endl;
                file << database[i].getLastName() << endl;
                file << database[i].getAge() << endl;
                file << database[i].getPhone() << endl;
            }
        }
        else
        {
            cout << "Error opening file." << endl;
        }

    }

    else
    {
        cout << "Database is empty." << endl;
    }
}

void loadFromFile()
{
    ifstream file("dataSave.txt");
    stringstream record;
    string line;

    if(file.is_open())
    {


        string name, lastName, phone;
        short age = 0;
        string temp;

        file >> peopleInDatabase;
        getline(file, temp, '\n');//Buffer into temp to get rid of empty spaces.

       for(int i = 0; i < peopleInDatabase; ++i)
       {

           getline(file, name, '\n');
           getline(file, lastName, '\n');
           file >> age;
           getline(file, temp, '\n');
           getline(file, phone, '\n');

           database.push_back(Database(name, lastName, age, phone));
       }

    }
    else
    {
        cout << "Error opening file." << endl;
    }
}

void searchName()
{
    if(peopleInDatabase > 0)
    {
        string name;
        cout << "Enter the first name: ";
        cin >> name;
        int match = 0;
        vector<int> ls;

         for(int i = 0; i != peopleInDatabase; ++i)
         {
             if(database[i].getName() == name)
             {
                match++;
                ls.push_back(i);
             }
         }
         cout << "Matches found: " << match << endl;

         for(int i = 0; i != match; ++i)
         {
            cout << "Person index: " << ls[i] + 1 << endl;
            cout << "Name: " << database[ls[i]].getName() << endl;
            cout << "Last Name: " << database[ls[i]].getLastName() << endl;
            cout << "Age: " << database[ls[i]].getAge() << endl;
            cout << "Phone Number: " << database[ls[i]].getPhone() << endl;

            if(i < match - 1)
            {
                cout << "-------------------" << endl;
            }

            else
            {
                cout << endl;
            }

         }

    }

    else
    {
        cout << "Database is empty." << endl;
    }
}

void removePerson()
{
    if(peopleInDatabase > 0)
    {
        int index;

        cout << "Enter index: ";
        cin >> index;
        if(index <= peopleInDatabase)
        {
            for(int k = index; k < peopleInDatabase; ++k)
            {
                database[k - 1] = database[k];
            }
            database.pop_back();
            peopleInDatabase--;
        }

        else
        {
            cout << "Invalid Index." << endl;
        }
    }

    else
    {
        cout << "Database is empty." << endl;
    }
}

void edit()
{
    if(peopleInDatabase > 0)
    {
        char choice;
        int index;
        string tmp;

        cout << "Enter index to be modified: ";
        cin >> tmp;
        while(!checkNum(tmp))
        {
            cout << "Enter proper value: ";
            cin >> tmp;
        }
        index = stoi(tmp);

        if(index <= peopleInDatabase)
        {
            cout << "Select option" << endl;
            cout << "Press 'n' to change name" << endl;
            cout << "Press 'l' to change last name" << endl;
            cout << "Press 'a' to change age" << endl;
            cout << "Press 'p' to change phone number" << endl;

            do{
            choice = getch();
            }while(choice != 'n' && choice != 'l' && choice != 'a' && choice != 'p');// User must enter a valid option


            switch(choice)
            {
                case 'n':
                    {
                        cout << "Set new name:";
                        string name;
                        cin >> name;
                        database[index - 1].setName(name);

                    }
                    break;

                case 'l':
                    {
                        cout << "Set new last name:";
                        string lastName;
                        cin >> lastName;
                        database[index - 1].setLastName(lastName);

                    }
                    break;

                case 'a':
                    {
                        cout << "Set new age:";
                        short age;

                        string tmp = "";

                        cin >> tmp;

                        while(!checkNum(tmp))
                        {
                            cout << "Improper value detected, please retry: ";
                            cin >> tmp;
                        }
                        age = stoi(tmp);

                        database[index - 1].setAge(age);

                    }
                    break;

                case 'p':
                    {
                        cout << "Set new phone number:";
                        string phone;
                        cin >> phone;
                        database[index - 1].setPhone(phone);

                    }
                     break;
            }



        }

        else
        {
            cout << "Invalid Index" << endl;
        }

    }

    else
    {

    }
}
