#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

#include "Actor.h"
#include "StudentWorld.h"

using namespace std;
#include <iostream>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//virtual void doSomething()
// {
//    //If the player is in my line of sight, then
////        Fire my pea cannon in the direction of the player
////        Else if I can move in my current direction w/o hitting an obstacle, then
////        Move one square in my current direction
////        Else if I’m about to run into an obstacle, then
////        Reverse my direction, but don’t move during this tick
// studentWorldPtr->zapAllZappableActors(getX(), getY());
// }

class StudentWorld;
class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir = 0, double size = 1.0)
    : GraphObject(imageID, startX, startY, dir, size), m_removeOffScreen(false), m_active(true){
    }
    virtual bool isObstacle(){
        return false;
    }
    

    virtual bool removeOffScreen(){
        return m_removeOffScreen;
    }

    virtual ~Actor(){
        cout << "DELETED ACTOR";
    }
    virtual void doSomething(){
        cout << "dosomething called";
//        setVisible(true);
    }
    virtual bool isVisible(){
        if (!m_active){
            setVisible(false);
            return false;
        }
        return true;
    }
    
    virtual void makeVisible(){
       
            setVisible(true);
   
        }
       
    
 
   
private:
    bool m_removeOffScreen;
    bool m_active;

};

class hasHealth: public Actor
{
public:
    
    
    hasHealth(int imageID, double startX, double startY, int dir = 0, double size = 1.0)
            : Actor(imageID, startX, startY, dir, size), hit_points(20) {
        
        }
    virtual bool canPassThru(){
        return false;
    }
    


    int health(){
        return hit_points;
    }
private:
    int hit_points;

};

class Avatar: public hasHealth
{

//    iv. It must have a limited version of a doSomething() method that lets the
//    user pick a direction by hitting a directional key. If the av hits a
//    directional key during the current tick and the target square does not
//    contain a wall, it updates the player’s location to the target square and
//    the player’s direction. All this doSomething() method has to do is
//    properly adjust the player’s x,y coordinates and direction, and our
//    graphics system will automatically animate its movement it around the
//    maze!
    
public:
    
    Avatar(int imageID, double startX, double startY, int dir = 0, double size = 1.0, StudentWorld* world = nullptr)
    : hasHealth(imageID, startX, startY, dir, size), m_ammo(20), m_world(world) {
        
        }
    virtual bool isObstacle(){
        return false;
    }
    
    bool hasCollectedAllOfTheCrystalsOnTheLevel(){
        return true;
    }
    StudentWorld* getWorld() const{
        return m_world;
    }
    void setWorld(StudentWorld* world) {
        cout << "WORLD!" << world;
        m_world = world;
    }
    StudentWorld* getWorld() {
        return m_world;
    }
    virtual void doSomething() {
        int ch;
//        getWorld()->test();
//        if (getWorld()->getKey(ch))
//        {
//            setWorld(m_world);
//        }
       
    }
    bool checkIfCompletedCurrentLevel(){
        //    If the player steps onto the same square as an exit (after first collecting all
        //    of the crystals on the level), completing the current level, then the move()
        //    method should immediately:
        //    i. Increase the player’s score appropriately (by 2000 points for using
        //    the exit, and by the remaining bonus score for the level).
        //    ii. Return a value of GWSTATUS_FINISHED_LEVEL.
        return false;
    }
    
    
    
    int ammo(){
        return m_ammo;
    }
    
   
private:
    int m_ammo;
    StudentWorld* m_world;
};
class ThiefBot: public hasHealth
{
public:
    ThiefBot(int imageID, double startX, double startY, int dir = 0, double size = 1.0, StudentWorld* world = nullptr)
    : hasHealth(imageID, startX, startY, dir, size), m_ammo(20) {
    }
    virtual bool isObstacle(){
        return true;
    }
        
    private:
        int m_ammo;
        
};
class HorizRageBot: public ThiefBot
{
public:
    using ThiefBot::ThiefBot;

};
class VertRageBot: public ThiefBot
{
public:
    using ThiefBot::ThiefBot;

};
class MeanThiefBot: public ThiefBot
{
public:
    using ThiefBot::ThiefBot;

};
class RageThiefBot: public ThiefBot
{
public:
    using ThiefBot::ThiefBot;

};
class ThiefBotFactory: public Actor
{
public:
    virtual bool canPassThru(){
        return false;
    }
    virtual bool isObstacle(){
        return false;
    }
    

    using Actor::Actor;

};

class MeanThiefBotFactory: public ThiefBotFactory
{
public:
    virtual bool canPassThru(){
        return false;
    }
    

    using ThiefBotFactory::ThiefBotFactory;

};

class Peas: public Actor
{
public:
    virtual bool canPassThru(){
        return true;
    }
    


};

class Exits: public Actor
{
public:

    Exits(int imageID, double startX, double startY, int dir = 0, double size = 1.0)
    : Actor(imageID, startX, startY, dir, size), m_active(false) {}
        
    
    virtual void doSomething(){
        cout << "EXIT dosomething called";

    }
 
    virtual bool isVisible(){
        if (!m_active){
            setVisible(false);
            return false;
        }
        return true;
    }
  
   

private:
    bool m_active;

    

};
class Walls: public Actor
{
    virtual bool isObstacle(){
        return true;
    }
public:
    using Actor::Actor;

};
class Marbles: public Actor
{
public:
    virtual bool isObstacle(){
        return true;
    }
    using Actor::Actor;

};
class Pits: public Actor
{
public:
    virtual bool isObstacle(){
        return true;
    }
    using Actor::Actor;

};
class Crystals: public Actor
{
public:
    virtual bool canPassThru(){
        return true;
    }
    

    using Actor::Actor;

};

class ExtraLifeGoodies: public Actor
{
public:
    using Actor::Actor;

};
class RestoreHealthGoodies: public Actor
{
public:
    using Actor::Actor;

};
class AmmoGoodies: public Actor
{
public:
    using Actor::Actor;

};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
