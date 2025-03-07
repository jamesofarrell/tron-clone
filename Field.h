//
// Created by JULIA BALAJAN on 31/12/2016.
//

#ifndef TRON_FIELD_H
#define TRON_FIELD_H

#include "Includes.h"

class Field {
public:
    static constexpr int SCREEN_WIDTH = 320;
    static constexpr int SCREEN_HEIGHT = 240;
    static constexpr short TILESIZE = 4;

    static constexpr int WIDTH = SCREEN_WIDTH / TILESIZE;
    static constexpr int HEIGHT = SCREEN_HEIGHT / TILESIZE;

    Field();
    Objects matrix[HEIGHT][WIDTH];
};


#endif //TRON_FIELD_H
