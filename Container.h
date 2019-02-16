#ifndef Container_h
#define Container_h

#include "core.h"

#define INITIALISATION  0
#define UPDATE          1

class Container
{
  public:
    Container();
    void updateAll();
    virtual void update() = 0;

  private:
    void container(byte operation);
};

#endif