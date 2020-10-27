#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <conio.h>

using std::vector;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;
using std::cin;

void interface();
void randomizeCaseList(const string& fileLoc, char choice, int permut);
string appendName(const string& fileLoc, const char& choice);
void loadFile(ifstream& ifs, vector<string>& input);
string randomizeUpperAndLowerCase(const string& tmp, int permut);
string setAllToUpper(const string& tmp);
string setAllToLower(const string& tmp);
string setFirstLetterToUpper(const string& tmp);

int main()
{
    srand(time(nullptr));

    char ch;

    do{
    interface();
    cout << "again?: ";
    ch = getch();
    }while(ch != 'q');

    return 0;
}

void interface()
{
    char ch;
    int pm = 1;

    cout << "Enter file location: ";//ask for the file location
    string loc;
    cin >> loc;

    cout << "Select a mode:\n";// ask for mode
    cout << "'u' for all Upper case" << endl;
    cout << "'l' for all Lower case" << endl;
    cout << "'r' for randomized case for each letter" << endl;
    cout << "'c' for capitalizing each word" << endl;
    cin >> ch;

    if(ch == 'r')//if r is chosen it will ask you how many variants to produce per word
    {
        cout << "Select number of permutations per word(cannot be 0 or negative): ";
        cin >> pm;
    }

    randomizeCaseList(loc, ch, pm);
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

    loadFile(ifs, inputList);

    // append a random number to the new file to avoid overwriting
    string outName = appendName(fileLoc, choice);

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
            for(int p = 0; p != permut; ++p)//loop through as many times as permut
            ofs << randomizeUpperAndLowerCase(*it, permut) << endl;
        }
        cout << "Completed!" << endl;

        break;

    case 'u'://upper case only

        cout << "Setting all entries to upper case, please wait..." << endl;

        for(auto it = inputList.begin(); it != inputList.end(); ++it)
        {
            ofs << setAllToUpper(*it) << endl;
        }
        cout << "Completed!" << endl;
        break;

    case 'l'://lower case only

        cout << "Setting all entries to upper case, please wait..." << endl;

        for(auto it = inputList.begin(); it != inputList.end(); ++it)
        {
            ofs << setAllToLower(*it) << endl;
        }
        cout << "Completed!" << endl;
        break;

    case 'c':
        cout << "Capitalizing all entries' first letter, please wait..." << endl;

        for(auto it = inputList.begin(); it != inputList.end(); ++it)
        {
            ofs << setFirstLetterToUpper(setAllToLower(*it)) << endl;
        }

        cout << "Completed!" << endl;
        break;

    default:
        cout << "Improper values used.";
        break;
    }

}

string appendName(const string& fileLoc, const char& choice)
{
    string outName;
    int verNum = rand() % 9999;

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

    else if(choice == 'c')
    {
        outName = fileLoc + "CapitalizedAll" + std::to_string(verNum) + ".txt";
    }

    return outName;
}

void loadFile(ifstream& ifs, vector<string>& inputList)
{
    string word;
    //load the file into memory
    while(ifs >> word)
    {
        if(word.size() > 3)
        inputList.push_back(word);
    }
    ifs.close();
}

string randomizeUpperAndLowerCase(const string& tmp, int permut)
{
    string localTmp = tmp;

    for(int i = 0; i != localTmp.size(); ++i)
    {
        if(rand()%2)
        {
            localTmp[i] = toupper(localTmp[i]);
        }

        else
        {
            localTmp[i] = tolower(localTmp[i]);
        }
    }

    return localTmp;
}

string setAllToUpper(const string& tmp)
{
    string localTmp = tmp;

    //loop through each string
    for(int i = 0; i != localTmp.size(); ++i)
    {
        //Make everything Upper Case
        localTmp[i] = toupper(localTmp[i]);
    }
    return localTmp;
}

string setAllToLower(const string& tmp)
{
    string localTmp = tmp;

    //loop through each string
    for(int i = 0; i != localTmp.size(); ++i)
    {
        //Make everything Upper Case
        localTmp[i] = tolower(localTmp[i]);
    }
    return localTmp;
}

string setFirstLetterToUpper(const string& tmp)
{
    string localTmp = tmp;

    localTmp[0] = toupper(localTmp[0]);

    return localTmp;
}
