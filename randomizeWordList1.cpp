#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using std::vector;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;
using std::cin;

string addBackSlash(const string& s);
void randomizeCaseList(const string& fileLoc, char choice, int permut);

int main()
{
    srand(time(nullptr));

    char ch;
    int pm = 1;

    cout << "Enter file location: ";//ask for the file location
    string loc;
    cin >> loc;

    cout << "Select a mode:\n";// ask for mode
    cout << "'u' for all Upper case" << endl;
    cout << "'l' for all Lower case" << endl;
    cout << "'r' for randomized case for each letter" << endl;
    cin >> ch;

    if(ch == 'r')//if r is chosen it will ask you how many variants to produce per word
    {
        cout << "Select number of permutations per word(cannot be 0 or negative): ";
        cin >> pm;
    }

    randomizeCaseList(loc, ch, pm);


}

string addBackSlash(const string& s)//not needed actually
{
    string tmp = s;

    for(size_t i = 0; i != tmp.size();)
    {
        if(tmp[i] == '\\')
        {
            tmp.insert(++i, "\\");

        }
        else
        {
            ++i;
        }
    }

    return tmp;
}


void randomizeCaseList(const string& fileLoc, char choice, int permut = 1)
{
    ifstream ifs(fileLoc);
    if(!ifs)
    {
        cout << "Could not access the file" << endl;
        return;
    }

    //container for the words from input file
    vector<string> inputList;
    string word;

    //load the file into memory
    while(ifs >> word)
    {
        if(word.size() > 3)
        inputList.push_back(word);
    }
    ifs.close();

    // append a random number to the new file to avoid overwriting
    int verNum = rand() % 9999;

    string outName;

    if(choice == 'r')//append to the name based on which version is used
    {
        outName = fileLoc + "RandLowerUpper" + std::to_string(verNum) + ".txt";
    }
    else if(choice == 'u')
    {
        outName = fileLoc + "Upper" + std::to_string(verNum) + ".txt";
    }
    else if(choice == 'l')
    {
        outName = fileLoc + "Lower" + std::to_string(verNum) + ".txt";
    }

    ofstream ofs(outName);

    //permut is just how many times are the cases switched around, can't be zero or negative
    //it doesn't do anything if 'r' is not used
    if(permut <= 0)
        {
            cout << "Number of random permutations cannot be 0 or negative, exitting!\n";
            return;
        }


    switch(choice)
    {

    case 'r'://randomize upper and lower case
        //might as well give some feedback
        cout << "Randomizing upper and lower cases within each entry, please wait..." << endl;

        for(auto it = inputList.begin(); it != inputList.end(); ++it)
        {
            //get iterator contents in a string
            string tmp = *it;

            //loop through each string

            for(int p = 0; p != permut; ++p)//loop through as many times as permut
            {
                for(int i = 0; i != tmp.size(); ++i)
                {
                        if(rand()%2)
                        {
                            tmp[i] = toupper(tmp[i]);
                        }

                        else
                        {
                            tmp[i] = tolower(tmp[i]);
                        }
                }

                ofs << tmp << endl;
            }
        }
        cout << "Completed!" << endl;

        break;

    case 'u'://upper case only

        cout << "Setting all entries to upper case, please wait..." << endl;

        for(auto it = inputList.begin(); it != inputList.end(); ++it)
        {
            //get iterator contents in a string
            string tmp = *it;

            //loop through each string
            for(int i = 0; i != tmp.size(); ++i)
            {
                //Make everything Upper Case
                tmp[i] = toupper(tmp[i]);
            }

            ofs << tmp << endl;
        }
        cout << "Completed!" << endl;
        break;


    case 'l'://lower case only

        cout << "Setting all entries to upper case, please wait..." << endl;

        for(auto it = inputList.begin(); it != inputList.end(); ++it)
        {
            //get iterator contents in a string
            string tmp = *it;

            //loop through each string
            for(int i = 0; i != tmp.size(); ++i)
            {
                //Make everything Lower Case
                tmp[i] = tolower(tmp[i]);
            }

            ofs << tmp << endl;
        }
        cout << "Completed!" << endl;
        break;

    default:
        cout << "Improper values used.";
        break;

    }

}

