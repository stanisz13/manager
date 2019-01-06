#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <vector>

#include "file.h"

using namespace std;

void clearScreen();

void shortDrawEntry(const Entry& entry);

void drawEntry(const Entry& entry);

bool drawEntry(const int index);

bool shortDrawAllDone();

bool shortDrawAllUndone();

bool drawAllEntries();

bool shortDrawAllEntries();


#endif
