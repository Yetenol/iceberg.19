#ifndef Line_h
#define Line_h

#include "IO.h"
#include "Pilot.h"

class Line
{
public:
    Line();
    void update();
    bool isEnabled();
 private:
};

extern Line line;

#endif