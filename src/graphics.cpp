#include "graphics.h"

void clearScreen()
{
    for (int i = 0; i<40; ++i)
    {
        cout<<"\n";
    }
    cout<<endl;
}

void shortDrawEntry(const Entry& entry)
{
    if (entry.destroyed == 0)
    {
        cout<<"#"<<entry.number<<endl;
        cout<<"---"<<entry.name<<"---"<<endl;
        cout<<"This task is scheduled till "<<entry.deadline<<endl;
        cout<<"This task involves:"<<endl;
        cout<<entry.description<<endl;
        cout<<endl;
        cout<<endl;
    }

    else
    {
        cout<<"#"<<entry.number<<endl;
        cout<<"---"<<entry.name<<"---"<<endl;
        cout<<"(!)This task is already done\n"<<endl;
        cout<<"This task was scheduled till "<<entry.deadline<<endl;
        cout<<"This task involved:"<<endl;
        cout<<entry.description<<endl;
        cout<<endl;
        cout<<endl;
    }
}

void drawEntry(const Entry& entry)
{
    if (entry.destroyed == 0)
    {
        cout<<"#"<<entry.number<<endl;
        cout<<"---"<<entry.name<<"---"<<endl;
        cout<<"This task is scheduled till "<<entry.deadline<<endl;
        cout<<"This task involves:"<<endl;
        cout<<entry.description<<endl;
        cout<<"\nThe learning progress is as follows:"<<endl;
        cout<<entry.doneLearnings<<'/'<<entry.estimatedLearnings<<endl;
        cout<<"\nThe descriptions of your sessions:"<<endl;
        for(int i = 0; i<entry.doneLearnings; ++i)
        {
            if (entry.descriptionsOfLearnings[i].empty() == 0)
                cout<<i+1<<": "<<entry.descriptionsOfLearnings[i]<<endl; 
        }

        cout<<endl;
        cout<<endl;
    }

    else
    {
        cout<<"#"<<entry.number<<endl;
        cout<<"---"<<entry.name<<"---"<<endl;
        cout<<"(!)This task is already done\n"<<endl;
        cout<<"This task was scheduled till "<<entry.deadline<<endl;
        cout<<"This task involved:"<<endl;
        cout<<entry.description<<endl;
        cout<<"The learning progress was as follows:"<<endl;
        cout<<entry.doneLearnings<<'/'<<entry.estimatedLearnings<<endl;
        cout<<"The descriptions of your sessions:"<<endl;
        for(int i = 0; i<entry.doneLearnings; ++i)
        {
            if (entry.descriptionsOfLearnings[i].empty() == 0)
                cout<<i+1<<": "<<entry.descriptionsOfLearnings[i]<<endl; 
        }
        cout<<endl;
        cout<<endl;
    }
}

bool drawEntry(const int index)
{
    vector<Entry> allEntries = getAllEntries();

    bool res = 0;
    
    for (int i = 0; i <allEntries.size(); ++i)
    {
        if (allEntries[i].number == index)
        {
            res = 1;

            drawEntry(allEntries[i]);
            return 1;
        }
    }

    return 0;
}


bool shortDrawAllDone()
{
    vector<Entry> allEntries = getAllEntries();

    bool good = 0;

    for (int i = allEntries.size() - 1; i >= 0; --i)
    {
        Entry now = allEntries[i];
        if (now.destroyed == 1)
        {
            shortDrawEntry(now);
            good = 1;
        }
    }

    return good;
}

bool shortDrawAllUndone()
{
    vector<Entry> allEntries = getAllEntries();

    bool good = 0;

    for (int i = allEntries.size() - 1; i >= 0; --i)
    {
        Entry now = allEntries[i];
        if (now.destroyed == 0)
        {
            shortDrawEntry(now);
            good = 1;
        }
    }

    return good;
}

bool drawAllEntries()
{
    vector<Entry> allEntries = getAllEntries();

    if (allEntries.size() == 0)
        return 0;
    
    for (int i = allEntries.size() - 1; i >= 0; --i)
    {
        Entry now = allEntries[i];
        drawEntry(now);
    }

    return 1;
}

bool shortDrawAllEntries()
{
    vector<Entry> allEntries = getAllEntries();

    if (allEntries.size() == 0)
        return 0;
    
    for (int i = allEntries.size() - 1; i >= 0; --i)
    {
        Entry now = allEntries[i];
        shortDrawEntry(now);
    }

    return 1;
}
