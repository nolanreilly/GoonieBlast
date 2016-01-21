#ifndef LEVEL_H_
#define LEVEL_H_

#include "GameConstants.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

class Level
{
public:

	enum MazeEntry {
		gate0 = 0, gate1 = 1, gate2 = 2, gate3 = 3, gate4 = 4, gate5 = 5,
		empty, exit, player, horiz_snarlbot, vert_snarlbot,
		kleptobot_factory, wall, hostage,
		jewel, restore_health, extra_life, ammo
	};
	enum LoadResult {
		load_success, load_fail_file_not_found, load_fail_bad_format,
		load_sublevel_success, load_sublevel_fail_file_not_found, load_sublevel_fail_bad_format
	};

	Level(std::string assetDir)
	 : m_pathPrefix(assetDir)
	{
		for (int y = 0; y < VIEW_HEIGHT; y++)
			for (int x = 0; x < VIEW_WIDTH; x++)
				m_maze[y][x] = empty;

		if (!m_pathPrefix.empty())
			m_pathPrefix += '/';
	}

	LoadResult loadLevel(std::string filename, unsigned int subLevel = 0)
	{

		std::ifstream levelFile((m_pathPrefix + filename).c_str());
		if (!levelFile) 
			return subLevel ? load_sublevel_fail_file_not_found : load_fail_file_not_found;

		  // get the maze

		std::string line;
		bool foundExit = false;
		bool foundPlayer = false;

		for (int y = VIEW_HEIGHT-1; std::getline(levelFile, line); y--)
		{
			if (y < 0)	// too many maze lines?
			{
				if (line.find_first_not_of(" \t\r") != std::string::npos) 
					return subLevel? load_sublevel_fail_bad_format : load_fail_bad_format;  // non-blank line
	
				char dummy;
				if (levelFile >> dummy) 	 // non-blank rest of file 
					return subLevel ? load_sublevel_fail_bad_format : load_fail_bad_format;
				break;
			}

			if (line.size() < VIEW_WIDTH  ||  line.find_first_not_of(" \t\r", VIEW_WIDTH) != std::string::npos)
				return subLevel? load_sublevel_fail_bad_format : load_fail_bad_format;
				
			for (int x = 0; x < VIEW_WIDTH; x++)
			{
				MazeEntry me;
				switch (tolower(line[x]))
				{
					case ' ':  me = empty;						break;
					case 'x':  me = exit; foundExit = true;		break;
					case '@':  me = player; foundPlayer = true; break;
					case 'h':  me = horiz_snarlbot;				break;
					case 'v':  me = vert_snarlbot;				break;
					case 'f':  me = kleptobot_factory;			break;
					case '#':  me = wall;						break;
					case '*':  me = jewel;						break;
					case 'r':  me = restore_health;				break;
					case 'e':  me = extra_life;					break;
					case 'a':  me = ammo;						break;
					case 't':  me = hostage;					break; 
					default:   
						if( isdigit(line[x]) )
							me = MazeEntry(line[x]-'0');
						else
							return subLevel? load_sublevel_fail_bad_format : load_fail_bad_format;
				}
				if(subLevel == 0)
					m_maze[y][x] = me;
				m_submaze[subLevel][y][x] = me;
			}
		}

		if ( (!foundExit && subLevel == 0) || !foundPlayer || !edgesValid(subLevel))
			return subLevel? load_sublevel_fail_bad_format : load_fail_bad_format;
		return subLevel? load_sublevel_success : load_success;
	}

	MazeEntry getContentsOf(unsigned int x, unsigned int y, int subLevel) const
	{
		return (x < VIEW_WIDTH && y < VIEW_HEIGHT) ? m_submaze[subLevel][y][x] : empty;
	}

private:

	MazeEntry	m_maze[VIEW_HEIGHT][VIEW_WIDTH]; // current maze
	MazeEntry	m_submaze[MAX_SUB_LEVEL][VIEW_HEIGHT][VIEW_WIDTH]; // saved sub mazes

	std::string m_pathPrefix;

	bool edgesValid(int subLevel) const
	{
		for (int y = 0; y < VIEW_HEIGHT; y++)
			if (m_submaze[subLevel][y][0] != wall || m_submaze[subLevel][y][VIEW_WIDTH-1] != wall)
				return false;
		for (int x = 0; x < VIEW_WIDTH; x++)
			if (m_submaze[subLevel][0][x] != wall || m_submaze[subLevel][VIEW_HEIGHT-1][x] != wall)
				return false;

		return true;
	}
};

#endif // LEVEL_H_
