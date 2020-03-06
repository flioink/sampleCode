#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

using std::stringstream;
using std::initializer_list;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ostream;
using std::getline;

int main()
{
    ifstream ifs("masterText.txt");
    vector<string> input;
    decltype(input.size())lineNo{0};
    map<string, set<decltype(input.size())>> dict;

    for(string line; getline(ifs, line); ++lineNo)
    {
        stringstream lineStr(line);
        input.push_back(line);
        for(string text, word; lineStr >> text; word.clear())
        {
            remove_copy_if(text.begin(), text.end(), back_inserter(word), ispunct);
            dict[word].insert(lineNo);
        }
    }

    while(true)
    {
        string s;
        cout << "Enter a word to look for or q to quit: ";
        if(!(cin >> s) || s == "q")break;

        map<string, set<decltype(input.size())>>::iterator found = dict.find(s);
        if(found != dict.end())
        {
            cout << s << " is present on " << found->second.size()
            << (found->second.size() == 1 ? " line." : " lines.") << endl;
            for(auto& i: found->second)
            {
                cout << "\t(line" << i + 1 << ") " << input.at(i) << endl;
            }
        }
        else
        {
            cout << "The word is not found." << endl;
        }
    }


}
