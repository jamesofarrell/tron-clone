//
// Created by JULIA BALAJAN on 30/12/2016.
//

#ifndef TRON_PLAYER_H
#define TRON_PLAYER_H

#include "Includes.h"
#include "Coord.h"

class Player {
public:
    void changeDirection(Dir new_dir);
    Dir getDirection() const;

	void turnLeft();
	void turnRight();
	
    Team getTeam() const;
	
	Coord tick();

    Player(int x, int y, Dir ndir, Team nteam);

    Coord pos;
    Dir direction = UP;
private:
    Team team;
};


#endif //TRON_PLAYER_H
