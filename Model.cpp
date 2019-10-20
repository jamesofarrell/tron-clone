//
// Created by JULIA BALAJAN on 30/12/2016.
//

#include "Model.h"
#include "Includes.h"

Model::Model() : player_1(1 , Field::HEIGHT / 2, RIGHT, RED), player_2(Field::WIDTH - 2, Field::HEIGHT / 2, LEFT, GREEN),
                 controller(this), view(&field)
{
    field.matrix[player_1.pos.y][player_1.pos.x] = PLAYER_1;
    field.matrix[player_2.pos.y][player_2.pos.x] = PLAYER_2;
}

Player &Model::player1() {
	return player_1;
}

Player &Model::player2() {
	return player_2;
}


void Model::loop() {
    controls_current_time = SDL_GetTicks();
    if ((controls_current_time - controls_last_time) > controls_wait_time) {
		controller.handleEvents();
        controls_last_time = controls_current_time;
    }

    movement_current_time = SDL_GetTicks();
    if ((movement_current_time - movement_last_time) > movement_wait_time) {
		updatePlayer(player_1);
		updatePlayer(player_2);
        movement_last_time = movement_current_time;
    }

    current_ticks = SDL_GetTicks();
    int delay = 1000 / max_fps - current_ticks + last_ticks;

    if(delay > 0)
        SDL_Delay(delay);

    view.draw();

    last_ticks = current_ticks;
}

void Model::endGame() {
	if (winner == RED) red_wins++;
	else if (winner == GREEN) green_wins++;
    view.draw_end_screen(winner,red_wins,green_wins);
    SDL_Event ev;
    while(SDL_WaitEvent(&ev)){
        if (ev.type == SDL_KEYDOWN) {
            switch(ev.key.keysym.sym) {
                case SDLK_ESCAPE:     game_over_flag=true;return;
                case SDLK_RETURN:     restartGame();return;
                        }
        }
        else if (ev.type == SDL_QUIT) {
               game_over_flag=true;
	       return;
	}
    }

}

void Model::restartGame() {
    game_over_flag=false;
    winner=NONE;
    std::fill_n(&field.matrix[0][0], Field::WIDTH * Field::HEIGHT, NOTHING);
    player_1.pos.x=1;
    player_1.pos.y=Field::HEIGHT/2;
    player_1.direction = RIGHT;
    player_2.pos.x=Field::WIDTH - 2;
    player_2.pos.y=Field::HEIGHT/2;
    player_2.direction = LEFT;
    field.matrix[player_1.pos.y][player_1.pos.x] = PLAYER_1;
    field.matrix[player_2.pos.y][player_2.pos.x] = PLAYER_2;
}

void Model::quit() {
	game_over_flag = true;
}

bool Model::isGameOver() const {
    return game_over_flag;
}

void Model::updatePlayer(Player &p) {
	Coord trail = p.tick();
    field.matrix[trail.y][trail.x] =
		p.getTeam() == RED ? RED_TRAIL : GREEN_TRAIL;
	
	checkCollision(p);
	
    field.matrix[p.pos.y][p.pos.x] =
		p.getTeam() == RED ? PLAYER_1 : PLAYER_2;
}

void Model::checkCollision(Player &p) {
	Objects cell = field.matrix[p.pos.y][p.pos.x];
    if (cell == RED_TRAIL || cell == GREEN_TRAIL || cell == PLAYER_1 || cell == PLAYER_2 ) {
		if(game_over_flag) {
				winner = NONE;
		} else {
        	game_over_flag = true;
			winner = p.getTeam() == RED ? GREEN : RED;
		}
    }
}

