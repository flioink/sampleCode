#include "Database.h"

    Database::Database(std::string name, std::string lastName, short age, std::string phone)
    :name(name), lastName(lastName), age(age), phone(phone)
    {

    }

    Database::Database(const Database& other)
    {
        name = other.getName();
        lastName = other.getLastName();
        age = other.getAge();
        phone = other.getPhone();
    }

    std::string Database::getName()const
    {
        return this->name;
    }

    std::string Database::getLastName()const
    {
        return this->lastName;
    }

    short Database::getAge()const
    {
        return this->age;
    }

    std::string Database::getPhone()const
    {
        return this->phone;
    }

    void Database::setName(std::string name)
    {
        this->name = name;
    }

    void Database::setLastName(std::string lastName)
    {
        this->lastName = lastName;
    }

    void Database::setAge(short age)
    {
        this->age = age;
    }

    void Database::setPhone(std::string phone)
    {
        this->phone = phone;
    }
