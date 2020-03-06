#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct PersonInfo
{
    string name;
    vector<string> phones;
};

bool valid(const string& s)
{
    return isdigit(s[0]);
}

const string format(const string& s)
{
    return s.substr(0, 3) + "-" + s.substr(3, 3) + "-" + s.substr(6);
}

int main()
{
    ifstream ifs("phoneNumbers.txt");
    if(!ifs){cout << "Error opening file";}

    vector<PersonInfo> people;
    stringstream record;

    for(string line; getline(ifs, line);)
    {
        PersonInfo info;
        record.clear();
        record.str(line);
        record >> info.name;

        for(string word; record >> word;)
        {
            info.phones.push_back(word);
        }
        people.push_back(info);
    }

    for(const auto& entry: people)
    {
        stringstream formatted, badNums;

        for(const auto& nums: entry.phones)
        {
            if(valid(nums))
            {
                formatted << " " << format(nums);
            }
            else
            {
                badNums << " " << nums;
            }
        }

        if(badNums.str().empty())
        {
            cout << entry.name << formatted.str() << endl;
        }
        else
        {
            cout << "Error on: " << entry.name << badNums.str() << endl;
        }
    }

}
