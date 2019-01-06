#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

const string fileDataPath = "data/data.txt";
const int MAX_LEARNINGS = 10;
const int MAX_ENTRIES = 100*100;

/*
#123
NAME OF ENTRY
DEADLINE (dd.mm.yy)
DESCRIPTION
NUMBER OF DONE LEARNINGS
NUMBER OF ESTIMATED LEARNINGS
IS DESTROYED
DESCRIPTION OF WHAT WAS LEARNED DURING 1st SESSION
DESCRIPTION OF WHAT WAS LEARNED DURING 2nd SESSION
.
.
.
%%%
*/

struct Entry
{
    int number;
    string name;
    string deadline;
    string description;
    int doneLearnings;
    int estimatedLearnings;
    bool destroyed; 
    string descriptionsOfLearnings[MAX_LEARNINGS];
};

vector<Entry> getAllEntries();

void writeEntry(const Entry& entry);

void writeAllEntries(vector<Entry>& allEntries);

void sortEntriesByDeadline();

void clearDataInFile(const string path);

int dateToInt(const string s);

#endif
