#include "Actor.h"
#include "StudentWorld.h"
#include "Level.h"
#include <vector>
#include <iostream>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


Player::Player(StudentWorld* world, int x, int y) : vulnerable(world, 20, IID_PLAYER, x, y, right)
{
    m_ammo = 0;
};

int Player::getAmmo() const
{
    return m_ammo;
}

Wall::Wall(StudentWorld* world, int x, int y) : invulnerable(world, IID_WALL, x, y, none)
{};

Wall::~Wall()
{};

void Wall::doSomething()
{}; //wall does nothing

bool vulnerable::movable(int x, int y)
{
    if (x >= VIEW_WIDTH || y >= VIEW_HEIGHT || x < 0 || y < 0)
        return false;
    
    vector<Actor*> vec = getWorldPtr()->getActors();
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i]->getX() == x && vec[i]->getY() == y)
        {
            if (vec[i]->getID() == IID_WALL)
            {
                return false;
            }
        }
    }
        
    return true; //how to search the vector for walls?
}

void vulnerable::doSomething() {
    if (!isAlive())
    {
        cerr << "You are dead" << endl;
        return;
    }
    
    int key;
    if (getWorldPtr()->getKey(key))
    {
        int x = getX();
        int y = getY();
        
        switch (key)
        {
            case KEY_PRESS_LEFT:
            {
                setDirection(left);
                if (movable(x-1, y))
                {
                    moveTo(x-1, y);
                }
                break;
            }
            case KEY_PRESS_RIGHT:
            {
                setDirection(right);
                if (movable(x+1, y))
                {
                    moveTo(x+1, y);
                }
                break;
            }
            case KEY_PRESS_UP:
            {
                setDirection(up);
                if (movable(x, y+1))
                {
                    moveTo(x, y+1);
                }
                break;
            }
            case KEY_PRESS_DOWN:
            {
                setDirection(down);
                if (movable(x, y-1))
                {
                    moveTo(x, y-1);
                }
                break;
            }

            case KEY_PRESS_ESCAPE:
                break;
        }
    }
}

void Jewel::doSomething() {
    if (! isAlive()) {
        return;
    }
    
    // if Player is on the same square as the Jewel
    if (getX() == getWorldPtr()->getPlayer()->getX() && getY() == getWorldPtr()->getPlayer()->getY()) {
        getWorldPtr()->increaseScore(50);
        getWorldPtr()->playSound(SOUND_GOT_GOODIE);
       // getWorldPtr()->getPlayer()->incJewels();
      //  setDead();
    }
}


