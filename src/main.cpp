#include <iostream>
#include <algorithm>
#include <ctime>

#include "file.h"
#include "graphics.h"
#include "logic.h"

using namespace std;

inline string getTodaysDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string res = to_string(ltm->tm_mday) + "." + to_string(1 + ltm->tm_mon) + "." + to_string((1900 + ltm->tm_year)%100);
    return res;
}

inline void showDateAndTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    cout<<"Today is "<<getTodaysDate()<<endl;
    cout<<"It is "<<ltm->tm_hour<<":"<<ltm->tm_min<<" o'clock"<<endl;
}


int main()
{
    time_t beginning, ending;
    time(&beginning);
    
    clearScreen();
    
    cout<<"Welcome to your personalized planner!"<<endl;
           
    showDateAndTime();
    
    cout<<"What would you like to know?"<<endl;
    cout<<endl;
    
    while(true)
    {
        cout<<"1 <---- Show to-do list"<<endl;
        cout<<"11 <--- Show details of a task"<<endl;
        cout<<"2 <---- Add new entry"<<endl;
        cout<<"3 <---- Update progress"<<endl;
        cout<<"4 <---- Edit existing entry"<<endl;
        cout<<"5 <---- Delete entry"<<endl; //FLAG that done, dont erase. allow to see done tasks.
        cout<<"6 <---- List all done tasks"<<endl;
        cout<<"7 <---- List all tasks"<<endl;
        cout<<"8 <---- Clear screen"<<endl;
        cout<<"9 <---- Exit"<<endl;
        
        int v;
        cin>>v;
        clearScreen();
         
        sortEntriesByDeadline();
        
        if (v > 11 || v == 10 || v < 1)
        {
            cout<<"Wrong value provided\n\n"<<endl;
            continue;
        }

        if (v == 11)
        {
            if (shortDrawAllEntries() == 0)
            {
                cout<<"There is no record of you studying at all... Now that's something!\n\n"<<endl;
                continue;
            }
            
            cout<<"Which tasks concerns you?\n\n"<<endl;
            int h;
            cin>>h;
            clearScreen();
            if (drawEntry(h) == 0)
            {
                cout<<"Wrong value provided\n\n"<<endl;
                continue;
            }
        }
        
        if (v == 1)
        {
            if (shortDrawAllUndone() == 0)
            {
                cout<<"You seem to have nothing to do. What a relief...\n\n"<<endl;
            }
        }

        if (v == 2)
        {
            interactiveAddEntry();
        }

        if (v == 3)
        {
            if (newSession() == 0)
            {
                cout<<"Wrong value provided\n\n"<<endl;
                continue;
            }
        }
        
        if (v == 4)
        {
            if (shortDrawAllEntries() == 0)
            {
                cout<<"There is nothing to edit\n\n"<<endl;
                continue;
            }
            cout<<"Which entry do you wish to edit?"<<endl;
            int index;
            cin>>index;
            clearScreen();
            drawEntry(index);
            
            if (editEntry(index) == 0)
            {
                cout<<"Wrong value provided\n\n"<<endl;
                continue;
            }
        }

        if (v == 5)
        {
            if (shortDrawAllUndone() == 0)
            {
                cout<<"There is nothing to delete\n\n"<<endl;
                continue;
            }
            cout<<"Which entry do you wish to delete?"<<endl;
            int index;
            cin>>index;
            if (deleteTask(index) == 0)
            {
                cout<<"Wrong value provided\n\n"<<endl;                
            }
        }

        if (v == 6)
        {
            if (shortDrawAllDone() == 0)
            {
                cout<<"Seems like you haven't done much. Yet...\n\n"<<endl;
            }
        }

        if (v == 7)
        {
            if(shortDrawAllEntries() == 0)
            {
                cout<<"There is no record of you studying at all... Now that's something!\n\n"<<endl;
            }
        }

        if (v == 8)
        {
            showDateAndTime();
            cout<<"\n\n";
            continue;
        }
        
        if (v == 9)
        {
            cout<<"I hope it was productive :) See you next time\n\n"<<endl;
            break;
        }
    }

    time(&ending);
    float diftime = difftime(ending, beginning);
    cout<<"Your session lasted for "<<(long)diftime / 3600<<" hours and ";
    cout<<(long)diftime / 60<<" minutes\n\n"<<endl;

    addTimeOfTheSession(getTodaysDate(), (int)diftime / 60);
    return 0;
}
