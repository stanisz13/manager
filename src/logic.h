#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>

#include "graphics.h"
#include "file.h"

using namespace std;

struct TimeData
{
    string date;
    int minutes;
};

const string timesFilePath = "data/times.txt";

void interactiveAddEntry();

bool editEntry(const int index);

bool deleteTask(const int index);

int newSession();

void addTimeOfTheSession(const string date, const int t);

#endif
