//
// Created by JULIA BALAJAN on 30/12/2016.
//

#ifndef TRON_MODEL_H
#define TRON_MODEL_H

#include "Includes.h"
#include "Player.h"
#include "Field.h"
#include "Controller.h"
#include "View.h"

class Model {
public:
    void loop();
    void endGame();
	
	void quit();
	void restartGame();
	
    Model();

    bool isGameOver() const;
	
	Player &player1();
	Player &player2();
    int green_wins = 0;
    int red_wins = 0;

private:
    Player player_1,
           player_2;

    Field field;

    bool game_over_flag = false;

    Team winner;

    Controller controller;
    View view;
    constexpr static int max_fps = 60;
    int last_ticks = 0;
    int current_ticks;

    int movement_last_time = SDL_GetTicks();
    int movement_current_time;
    static constexpr int movement_wait_time = 50;

    int controls_last_time = SDL_GetTicks();
    int controls_current_time;
    static constexpr int controls_wait_time = 100;

    void updatePlayer(Player &p);
    void checkCollision(Player &p);
};


#endif //TRON_MODEL_H
