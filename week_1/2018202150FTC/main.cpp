#include "claw.h"




int main()
{
    using namespace std;
    set<string> urls;
    set<string> clawed;
    queue<string> tobe;
    string current;
    string content;
    tobe.push(root);
    while (tobe.empty() == false)
    {

        cout << "how many tobe" << tobe.size() << endl;
        current = tobe.front();

        tobe.pop();
        clawed.insert(current);
        content = get_content(current);

        parse(content, current, urls);
        set<string>::iterator it;
        for (it = urls.begin(); it != urls.end(); it++)
        {
            if (clawed.find(*it) == clawed.end())
            {
                cout << "get in the queue" << endl;
                tobe.push(*it);
                clawed.insert(*it); // new change;
            }
        }

    }
}
