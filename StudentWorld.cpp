#include "StudentWorld.h"
#include "Level.h"
#include "Actor.h"
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
    int mainlev = 0;
    string mainlev_string = to_string(mainlev);
    if(mainlev < 10)
        mainlev_string += '0';
    
    string curLevel;
    if(getCurrentSubLevel() != 0)
    {
        string sublev_string = to_string(getCurrentSubLevel());
        curLevel = "level" + mainlev_string + '-' + sublev_string + ".dat";
    }
    else
        curLevel = "level" + mainlev_string + ".dat";
     //formatting for level string's main levels and sublevels
    
    Level lev(assetDirectory()); //create level object
    
    Level::LoadResult result = lev.loadLevel(curLevel); //load level
    if (result	==	Level::load_fail_file_not_found	||
        result	==	Level:: load_fail_bad_format)
    {
        return -1;
        // cerr << "something bad happened" << endl;
    }
    
    if(curLevel == "level99.dat")
        return GWSTATUS_PLAYER_WON;

    if(curLevel[0] != 'l' || curLevel[1] != 'e' || curLevel[2] != 'v' || curLevel[3] != 'e' || curLevel[4] != 'l' || !isdigit(curLevel[5]) || !isdigit(curLevel[6]) || curLevel[7] != '.' || curLevel[8] != 'd' || curLevel[9] != 'a' || curLevel[10] != 't' || curLevel.length() != 11)
        //no hotfix yet for sublevels
    {
        return GWSTATUS_LEVEL_ERROR; //FIX THIS
    }
    
    for (int i = 0; i < VIEW_WIDTH; i++)
    {
        for (int j = 0; j < VIEW_HEIGHT; j++)
        {
            Level::MazeEntry item =	lev.getContentsOf(i, j, getCurrentSubLevel());
            
            switch (item)
            {
                case Level::player:
                {
                    playerptr = new Player(this, i, j);
                    container.push_back(playerptr); //new
                    break;
                }
                case Level::wall:
                {
                    Wall* wallptr = new Wall(this, i, j);
                    container.push_back(wallptr);
                    break;
                }
                case Level::empty:
                default:
                    break;
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    
    
    for(int i = 0; i < container.size(); i++)
    {
        if (container[i]->isAlive())
            container[i]->doSomething();
    }
 
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
    
    for(int i = 0; i < container.size(); i++)
    {
        delete container[i];
    }
    
    /*delete m_player;
    
    vector<Actor*>::iterator first = container.begin();
    while (first != container.end())
    {
        vector<Actor*>::iterator second = first;
        first = container.erase(first);
        delete *second; //double for/iterate through vector
    }*/
}

int StudentWorld::getCurrentSubLevel() //no sublevels yet
{
    return 0;
}


/*
void setDisplayText()
{
    int score = getCurrentScore();
    int level = getCurrentGameLevel(); // (e.g. 03)
    int subLevel = getCurrentSubLevel(); // (e.g. 01. 00 is for main level)
    unsigned int timeLimit = getCurrentTimeLimit();
    int livesLeft = getNumberOfLivesThePlayerHasLeft();
    // Next, create a string from your statistics, of the form:
    // Score: 0000100 Level: 03-01 Lives: 3 Health: 70% Ammo: 216 TimeLimit: 34
    string s = someFunctionToFormatThingsNicely(score, level, sublevel,
                                                lives, health, ammo, bonus);
   
    // Finally, update the display text at the top of the screen with your
    // newly created stats
    setGameStatText(s); // calls our provided GameWorld::setGameStatText
}
*/



