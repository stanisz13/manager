#include "file.h"

Entry getEntry(const int indexOfEntry)
{
    Entry res = {};
    
    ifstream file(fileDataPath);

    string line;
    while(getline(file, line))
    {
        if (line[0] == '#')
        {
            istringstream iss(line);
            char dump;
            int number;
            iss >> dump >> number;


            if (number == indexOfEntry)
            {
                string nameOfEntry;
                getline(file, nameOfEntry);

                string deadline;
                getline(file, deadline);
                
                string description;
                getline(file, description);
                
                int estimatedLearnings;
                int doneLearnings;
                string lineLearnings;
                getline(file, lineLearnings);

                istringstream learningsSS(lineLearnings);
                learningsSS >> doneLearnings >> estimatedLearnings;

                res.number = number;
                res.name = nameOfEntry;
                res.deadline = deadline;
                res.description = description;
                res.estimatedLearnings = estimatedLearnings;
                res.doneLearnings = doneLearnings;

                string flags;
                getline(file, flags);
                istringstream flagsSS(flags);
                flagsSS >> res.destroyed;
                
                for (int i = 0; i < doneLearnings; ++i)
                {
                    string ithDescription;
                    getline(file, ithDescription);

                    res.descriptionsOfLearnings[i] = ithDescription;
                }
            }
        }
    }

    return res;
}

vector<Entry> getAllEntries()
{
    vector<Entry> allEntries;

    Entry entryRead;

    for (int i = 1; i<=MAX_ENTRIES; ++i)
    {
        entryRead = getEntry(i);
        if (entryRead.number != 0)
        {
            allEntries.push_back(entryRead);
        }
    }

    return allEntries;
}

void writeEntry(const Entry& entry)
{    
    ofstream file(fileDataPath, ios_base::app);

    file << "#";
    file << entry.number <<'\n';
    file << entry.name << '\n';
    file << entry.deadline << '\n';
    file << entry.description << '\n';
    file << entry.doneLearnings<<' ' <<entry.estimatedLearnings<<'\n';
    file << entry.destroyed << '\n';
    for (auto&& i : entry.descriptionsOfLearnings)
    {
        file << i <<'\n';
    }
    file << "%%%\n";
}

int dateToInt(const string s)
{
    return s[6]*100000 + s[7] * 10000 + s[3] * 1000 + s[4] * 100 + s[0] * 10 + s[1];
}

bool deadlineCmp(const Entry& a, const Entry& b)
{
    string da = a.deadline;
    string db = b.deadline;

    int va = dateToInt(da);
    int vb = dateToInt(db);
        
    if (va < vb)
        return 1;
    return 0;
}

void clearDataInFile(const string path)
{
    ofstream ofs;
    ofs.open(path, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}


void writeAllEntries(vector<Entry>& allEntries)
{
    for (int i = 0; i < allEntries.size(); ++i)
    {
        allEntries[i].number = i + 1;
        writeEntry(allEntries[i]);
    }
}

void sortEntriesByDeadline()
{
    vector<Entry> allEntries = getAllEntries();
    
    sort(allEntries.begin(), allEntries.end(), deadlineCmp);

    clearDataInFile(fileDataPath);

    writeAllEntries(allEntries);
}
