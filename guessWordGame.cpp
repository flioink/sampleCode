#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

string& punctStrip(string& s);

int main()
{

    srand(time(nullptr));
    ifstream ifs("orgasmatron.txt");

    vector<string> vec;
    string line;

    while(ifs >> line)
    {
        vec.push_back(punctStrip(line));
    }


    size_t rn = vec.size();
    size_t rWord;
    string word;
    char ct;
do{
    do{
     rWord = rand()% rn;
     word = vec[rWord];
    }while(word.size() <= 4);

    size_t guess = 7;
    string answer(word.size(), '_');
    system("cls");
    cout << answer << endl;

    while(guess--)
    {
        cout << "(" << guess + 1<< ")tries left." <<"Enter a letter: ";
        char ch;
        cin >> ch;
        if(ch == '1')break;

        for(size_t pos = 0; pos != word.size(); ++pos)
        {
            if(word[pos] == ch)
            {
                answer[pos] = word[pos];

            }
        }
        system("cls");
        cout << answer << endl;
        if(answer == word) break;
    }

    if(answer != word)
    {
        cout << "Can you guess the word now? Write it here: ";
        cin >> answer;
    }
    if(answer == word)
    {
        cout << "Outstanding, you win! '" << word << "' is the right answer!" << endl;
    }
    else
    {
        cout << "Nice try, but the answer is: " << word << endl;
    }

    cout << "Try again? Press 'y' to continue or 'q' to quit: ";
    cin >> ct;

}while(ct != 'q');

}

string& punctStrip(string& s)
{
    for(auto& it: s)
    {
        it = tolower(it);
    }

    for(size_t i = 0, len = s.size(); i < len;)
    {
        if(ispunct(s[i]))
        {
            s.erase(i--, 1);
            len = s.size();
        }
        else
        {
            ++i;
        }
    }

    return s;
}
