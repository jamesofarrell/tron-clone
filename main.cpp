#include "Model.h"

#include <SDL2/SDL_timer.h>

int main() {
    Model model;
    while (!model.isGameOver()) {
    	while (!model.isGameOver()) {
    	    model.loop();
    	}
    	model.endGame();
    }
    return 0;
}
