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


void randomizeCaseList(ifstream& ifs, char choice, int permut);

int main()
{
     srand(time(nullptr));

    ifstream ifs("D:\\DL\\caps\\names.txt");

    if(ifs.is_open())
    {
        randomizeCaseList(ifs, 'u', 15);
    }
     else
    {
        cout << "Error reading file";
    }
}



void randomizeCaseList(ifstream& ifs, char choice, int permut)
{
    //container for the words from input file
    vector<string> inputList;
    string word;

    //load the file into memory
    while(ifs >> word)
    {
        if(word.size() > 3)
        inputList.push_back(word);

    }

    // append a random number to the new file to avoid overwritting
    int verNum = rand() % 9999;

    string outName;

    if(choice == 'r')//append it to whichever version u use
    {
        outName = "D:\\DL\\caps\\randomizedUpperLowerList" + std::to_string(verNum) + ".txt";
    }
    else if(choice == 'u')
    {
        outName = "D:\\DL\\caps\\upperCasedList" + std::to_string(verNum) + ".txt";
    }
    else if(choice == 'l')
    {
        outName = "D:\\DL\\caps\\lowerCasedList" + std::to_string(verNum) + ".txt";
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

