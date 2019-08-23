#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <string>

class Database
{
private:
    std::string name;
    std::string lastName;
    short age;
    std::string phone;
public:

    Database() = default;
    Database(std::string name, std::string lastName, short age, std::string phone);

    void setName(std::string name);
    void setLastName(std::string lastName);
    void setAge(short age);
    void setPhone(std::string phone);

    std::string getName()const;
    std::string getLastName()const;
    short getAge()const;
    std::string getPhone()const;
};

#endif // DATABASE_H_INCLUDED
