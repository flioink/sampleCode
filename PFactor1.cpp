#include <iostream>
#include <vector>

using namespace std;

void prime(int n)
{
    int z = 2;

    vector<int> st;

    while(z * z <= n)
    {
        if(n% z == 0)
        {
            cout << "i: " << z << endl;
            n /= z;
            st.push_back(z);

        }

        else
        {
            z++;
        }

    }

    if(n > 1)
    {
        cout << "Prime: " << n << endl;
        st.push_back(n);
    }

    for(auto& it: st)
    {
        cout << it << endl;
    }
}


int main()
{
    prime(24);


    return 0;
}

