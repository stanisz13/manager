#include "logic.h"

void interactiveAddEntry()
{
    Entry toAdd = {};
    toAdd.number = MAX_ENTRIES - 1;

    cout<<"What's the name of the task?"<<endl;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    getline(cin, toAdd.name);

    cout<<"Till when does it have to be done?"<<endl;
    cin>>toAdd.deadline;

    cout<<"Describe it a little more"<<endl;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    getline(cin, toAdd.description);
    
    cout<<"How mamy times do you plan to study this topic?"<<endl;
    cin>>toAdd.estimatedLearnings;
   
    writeEntry(toAdd);
    cout<<"Done!\n"<<endl;
}

bool editEntry(const int index)
{
    vector<Entry> allEntries = getAllEntries();

    bool good = 0;
    for (int i = 0; i < allEntries.size(); ++i)
    {
        Entry ith = allEntries[i];
        if (ith.number == index)
            good = 1;
    }

    if (!good)
    {
        clearScreen();
        return 0;
    }
    
    for (int i = 0; i < allEntries.size(); ++i)
    {
        Entry& ith = allEntries[i];

        if (ith.number == index)
        {
            cout<<"What do you want to change about this entry?\n"<<endl;

            cout<<"1 - name of the task"<<endl;
            cout<<"2 - deadline"<<endl;
            cout<<"3 - description"<<endl;
            cout<<"4 - number of learning already done"<<endl;
            cout<<"5 - estimated number of learnings"<<endl;
            cout<<"6 - description of a particular learning session"<<endl;

            cout<<endl;
            int val;
            cin>>val;
            cout<<endl;
            clearScreen();
            
            if (val > 6)
            {
                return 0;
            }
    
            if (val == 1)
            {
                cout<<"Please type in the new name"<<endl;
                string name;
                cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
                getline(cin, name);
                ith.name = name;
            }

            if (val == 2)
            {
                cout<<"Please type in the new deadline"<<endl;
                string name;
                cin>>name;
                ith.deadline = name;
            }

            if (val == 3)
            {
                cout<<"Please type in the new description"<<endl;
                string name;
                cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
                getline(cin, name);
                ith.description = name;
            }

            if (val == 4)
            {
                cout<<"Please type in how many times have you studied this already"<<endl;
                int name;
                cin>>name;
                ith.doneLearnings = name;
            }

            if (val == 5)
            {
                cout<<"Please type in how many times do you plan to study this in total"<<endl;
                int name;
                cin>>name;
                ith.estimatedLearnings = name;
            }

            if (val == 6)
            {
                cout<<"All descriptions are:"<<endl;

                for (int j = 0; j<MAX_LEARNINGS; ++j)
                {
                    string jth = ith.descriptionsOfLearnings[j];
                    cout<<j+1<<": "<<jth<<endl;
                }

                cout<<"Which one do you wish do edit?"<<endl;
                int a;
                cin>>a;

                if (a > MAX_LEARNINGS)
                {
                    cout<<"Wrong number provided. Exiting..."<<endl;
                    return 0;
                }

                cout<<"Please type in the new description"<<endl;
                string b;
                cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
                getline(cin, b);

                allEntries[i].descriptionsOfLearnings[a-1] = b;
            }
        }

        if (ith.doneLearnings >= ith.estimatedLearnings)
        {
            ith.destroyed = 1;
        }
        else
        {
            ith.destroyed = 0;
        }
    }

    clearDataInFile(fileDataPath);
    clearScreen();
    cout<<"Success!\n\n"<<endl;
    writeAllEntries(allEntries);

    return 1;
}

bool deleteTask(const int index)
{
    vector<Entry> allEntries = getAllEntries();
    bool good = 0;
    
    for (int i = 0; i < allEntries.size(); ++i)
    {
        if (allEntries[i].number == index)
        {
            allEntries[i].destroyed = 1;
            good = 1;
        }
    }

    if (good == 0)
    {
        return 0;
    }
    
    clearDataInFile(fileDataPath);
    writeAllEntries(allEntries);

    return 1;
}

int newSession()
{
    vector<Entry> allEntries = getAllEntries();
   
    if (shortDrawAllUndone() == 0)
    {
        cout<<"You seem to have nothing to do. What a relief...\n\n"<<endl;
        return 2;
    }

    cout<<"The past you is really proud..."<<endl;
    cout<<"What task did you progress in?\n\n"<<endl;

    int v;
    cin>>v;
    clearScreen();

    bool res = 0;

    for (int i = 0; i<allEntries.size(); ++i)
    {
        Entry& ith = allEntries[i];
        if (ith.number == v)
        {
            res = 1;

            ith.doneLearnings ++;
            cout<<"Please specify what did you learn today\n\n"<<endl;

            string data;
            cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
            getline(cin, data);

            ith.descriptionsOfLearnings[ith.doneLearnings-1] = data;

            clearScreen();
            if (ith.doneLearnings  == ith.estimatedLearnings)
            {
                cout<<"Nice job, the task is now finished\n\n"<<endl;
                ith.doneLearnings = ith.estimatedLearnings;
                ith.destroyed = 1;

                break;
            }

            cout<<"Thanks, that's nice\n\n"<<endl;
        }
    }

    clearDataInFile(fileDataPath);
    writeAllEntries(allEntries);
    
    return res;
}

vector<TimeData> getAllTimes()
{
    vector<TimeData> allData;

    ifstream file(timesFilePath);
    
    string line;
 
    while(getline(file, line))
    {
        istringstream iss(line);
        string dateRead;
        unsigned minutes;

        iss>>dateRead>>minutes;

        TimeData toPB;
        toPB.date = dateRead;
        toPB.minutes = minutes;
        
        allData.push_back(toPB);
    }

    return allData;    
}

void writeAllTimes(vector<TimeData> allTimes)
{
    clearDataInFile(timesFilePath);
    ofstream file(timesFilePath, ios_base::app);
    
    for (int i = 0; i < allTimes.size(); ++i)
    {
        file << allTimes[i].date << allTimes[i].minutes <<'\n';
    }
}

void addTimeOfTheSession(const string date, const int t)
{
    vector<TimeData> allData = getAllTimes();

    for (int i = 0; i < allData.size(); ++i)
    {
        TimeData& now = allData[i];

        if (now.date == date)
        {
            now.minutes += t;

            writeAllTimes(allData);
            return;
        }
    }

    allData.push_back({date, t});

    writeAllTimes(allData);
}
