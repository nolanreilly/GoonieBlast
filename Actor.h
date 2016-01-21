#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

class StudentWorld;

/* GraphObject functions for reference
 GraphObject(int imageID, int startX, int startY, Direction startDirection = none);
     void setVisible(bool shouldIDisplay);
     void getX() const;
     void getY() const;
     void moveTo(int x, int y);
     Direction getDirection() const; // Directions: none, up, down, left, right
     void setDirection(Direction d); // Directions: none, up, down, left, right
     unsigned int getID() const;
 */

class Actor: public GraphObject {
public:
    Actor(StudentWorld* world, int imageID, int x, int y, Direction dir) : GraphObject(imageID, x, y, dir), living(true), m_world(world)
    {
        setVisible(true);
    };
    
    virtual ~Actor()
    {};
    
    virtual void doSomething() = 0;
    StudentWorld* getWorldPtr() const
    {
        return m_world;
    }
    
    bool isAlive() const //true or false if the actor is alive
    {
        return living;
    }
    
private:
    bool living;
    StudentWorld* m_world;
};

//subclass for vulnerable objects (can be killed and deleted)
class vulnerable : public Actor {
public:
    vulnerable(StudentWorld* world, int health, int imageID, int x, int y, Direction dir) : Actor(world, imageID, x, y, dir)
    {
        m_health = health;
    };
    virtual void doSomething(); //declaration of a movable object being able to move
    bool movable(int x, int y); //determines whether a vulnerable object is movable
    
private:
    int m_health;
};

//subclass for invulnerable objects (can't die)
class invulnerable : public Actor {
public:
    invulnerable(StudentWorld* world, int imageID, int x, int y, Direction dir) : Actor(world, imageID, x, y, dir)
    {};
private:
};

class Player : public vulnerable {
public:
    Player(StudentWorld* world, int x, int y);
    int getAmmo() const;
private:
    int m_ammo;
};

class Wall : public invulnerable {
public:
    Wall(StudentWorld* world, int x, int y);
    ~Wall();
    virtual void doSomething();//nothing
    
private:
};

class Jewel : public Actor {
public:
    Jewel(StudentWorld* world, int x, int y) : Actor(world, IID_JEWEL, x, y, none) { };
    
    virtual void doSomething();
    virtual bool canOccupy() {
        return true;
    };
    virtual bool hittable() {
        return false;
    }
};


#endif // ACTOR_H_
