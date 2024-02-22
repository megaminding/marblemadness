#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Avatar;
class Actor;

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
    void test();
  virtual void cleanUp();
    virtual void updateDisplayText();
    void handlemove(Actor* agentPointer, int ch);
    bool isValid(int x, int y);
    
//    void zapAllZappableActors(int x, int y)
//     {
//     for (p = actors.begin(); p != actors.end(); p++)
//     if (p->isAt(x,y) && p->isZappable())
//     p->zap();
//     }

private:
    Avatar* player;
    std::list<Actor*> actors;
    int m_bonusPoints;
};

#endif // STUDENTWORLD_H_
