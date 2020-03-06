#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

map<string, string> buildMap(ifstream& ifs)
{
    map<string, string> m;

    for(string key, value; ifs >> key, getline(ifs, value);)
    {
        m[key] = value.substr(1).substr(0, value.find_last_not_of(' '));
    }

    return m;
}

const string& transForm(const string& s, map<string, string>& m)
{
    auto found = m.find(s);
    if(found != m.end())
    {
        return found->second;
    }
    else
    {
        return s;
    }
}

void convert(ifstream& ifM, ifstream& ifT)
{
    map<string, string> m = buildMap(ifM);

    for(string line; getline(ifT, line);)
    {
        stringstream row(line);

        for(string text; row >> text;)
        {
            cout << transForm(text, m) << " ";
        }
        cout << '\n';
    }
}

int main()
{
    ifstream ifM("transformation.txt");
    ifstream ifT("textToTransform.txt");

    if(ifM && ifT)
    {
        convert(ifM, ifT);
    }
    else
    {
        cout << "Error" << endl;
    }

}


