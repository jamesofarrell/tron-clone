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
                case SDLK_UP:  model->player1().turnLeft(); break;
                case SDLK_DOWN: model->player1().turnRight(); break;
                case SDLK_LALT:     model->player2().turnLeft(); break;
                case SDLK_SPACE:     model->player2().turnRight(); break;
                case SDLK_ESCAPE:     model->quit(); break;
                case SDLK_RETURN:     model->restartGame(); break;
			}
        }
        else if (ev.type == SDL_QUIT)
			model->quit();
}
