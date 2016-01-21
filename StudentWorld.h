#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <string>
#include <vector>

using namespace std;

class Actor;
class Player;
class Level;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
    {}
    
    virtual ~StudentWorld()//
    { cleanUp(); }

    virtual int init();
    virtual int move();
    virtual void cleanUp();
    virtual int getCurrentSubLevel();
    
    
    vector<Actor*> getActors()
    {
        return container;
    }
    
    Player* getPlayer()
    {
        return playerptr;
    }
    

        
private:
    vector<Actor*> container;
    Player* playerptr; //main pointer in program
    
};

#endif // STUDENTWORLD_H_
