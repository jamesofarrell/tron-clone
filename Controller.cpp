//
// Created by JULIA BALAJAN on 30/12/2016.
//

#include "Controller.h"
#include "Model.h"

Controller::Controller(Model *model) : model(model) {}

void Controller::handleEvents() {
	SDL_Event ev;
	
    while(SDL_PollEvent(&ev))
        if (ev.type == SDL_KEYDOWN) {
            switch(ev.key.keysym.sym) {
                case SDLK_UP:  model->player1().direction = UP; break;
                case SDLK_DOWN: model->player1().direction = DOWN; break;
                case SDLK_LEFT: model->player1().direction = LEFT; break;
                case SDLK_RIGHT: model->player1().direction = RIGHT; break;
                case SDLK_SPACE:  model->player2().direction = UP; break;
                case SDLK_LALT: model->player2().direction = DOWN; break;
                case SDLK_LSHIFT: model->player2().direction = LEFT; break;
                case SDLK_LCTRL: model->player2().direction = RIGHT; break;
                case SDLK_ESCAPE:     model->quit(); break;
                case SDLK_RETURN:     model->restartGame(); break;
			}
        }
        else if (ev.type == SDL_QUIT)
			model->quit();
}
