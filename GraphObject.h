#ifndef GRAPHOBJ_H_
#define GRAPHOBJ_H_

#include <set>
#include <vector>
#include <cmath>
 
const int ANIMATION_POSITIONS_PER_TICK = 3;

inline int roundAwayFromZero(double r)
{
	double result =  r > 0 ? std::floor(r + 0.5) : std::ceil(r - 0.5);
	return int(result);
	 // If C99 is available, this can be return std::round(r);
}

class GraphObject
{
  public:

	enum Direction { none, up, down, left, right};

	GraphObject(int imageID, int startX, int startY, Direction dir = none, int sub_level = 0)
	 : m_imageID(imageID), m_visible(false), m_x(startX), m_y(startY),
	   m_destX(startX), m_destY(startY), m_brightness(1.0),
	   m_animationNumber(0), m_direction(dir), m_sub_level(sub_level)
	{
		getGraphObjects(m_sub_level).insert(this);
	}

	GraphObject(int sub_level)
	 : m_imageID(6), m_visible(false), m_x(0), m_y(0),
	   m_destX(0), m_destY(0), m_brightness(1.0),
	   m_animationNumber(0), m_direction(none), m_sub_level(sub_level)
	{
	}

	virtual ~GraphObject()
	{
		getGraphObjects(m_sub_level).erase(this);
	}

	void setVisible(bool shouldIDisplay)
	{
		m_visible = shouldIDisplay;
	}

	void setBrightness(double brightness)
	{
		m_brightness = brightness;
	}

	int getX() const
	{
		  // If already moved but not yet animated, use new location anyway.
		return roundAwayFromZero(m_destX);
	}

	int getY() const
	{
		  // If already moved but not yet animated, use new location anyway.
		return roundAwayFromZero(m_destY);
	}

	void moveTo(int x, int y)
	{
		m_destX = x;
		m_destY = y;
	}

	Direction getDirection() const
	{
		return m_direction;
	}

	void setDirection(Direction d)
	{
		m_direction = d;
	}

	  // The following should be used by only the framework, not the student

	bool isVisible() const
	{
		return m_visible;
	}

	unsigned int getID() const
	{
 		return m_imageID;
	}

	double getBrightness() const
	{
		return m_brightness;
	}

	unsigned int getAnimationNumber() const
	{
		return m_animationNumber;
	}

	void getAnimationLocation(double& x, double& y) const
	{
		x = m_x;
		y = m_y;
	}

	void animate()
	{
		m_animationNumber++;
		moveALittle(m_x, m_destX);
		moveALittle(m_y, m_destY);
	}

	static std::set<GraphObject*>& getGraphObjects(int sub_level)
	{
		static std::vector<std::set<GraphObject*> > graphObjects;
		if(graphObjects.size() == 0) {
			//GraphObject(int imageID, int startX, int startY, Direction dir = none, int sub_level = 0)
			for(int sublevel=0;sublevel<=5;sublevel++) {
				GraphObject* fake_obj = new GraphObject(sublevel);
				std::set<GraphObject*> obj;  obj.insert(fake_obj);
				graphObjects.push_back(obj);
			}
		}
		return graphObjects[sub_level];
	}

  private:
	static std::vector<std::set<GraphObject*> > graphObjects;
	static int  first_run;
	int			m_sub_level;
	int			m_imageID;
	bool		m_visible;
	double		m_x;
	double		m_y;
	double		m_destX;
	double		m_destY;
	double		m_brightness;
	int			m_animationNumber;
	Direction	m_direction;

	  // Prevent copying or assigning GraphObjects
	GraphObject(const GraphObject&);
	GraphObject& operator=(const GraphObject&);

	void moveALittle(double& from, double& to)
	{
		const double DISTANCE = 1.0 / ANIMATION_POSITIONS_PER_TICK;
		if (to - from >= DISTANCE)
			from += DISTANCE;
		else if (from - to >= DISTANCE)
			from -= DISTANCE;
		else
			from = to;
	}
};

#endif // GRAPHOBJ_H_
