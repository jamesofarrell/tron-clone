//
// Created by JULIA BALAJAN on 30/12/2016.
//

#include "View.h"
#include "Cleanup.h"
#include "Field.h"

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>

template <typename T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

namespace {
	void render_texture(SDL_Renderer *ren, SDL_Texture *tex, int x, int y, int w, int h) {
		SDL_Rect dst;
		dst.x = x;
		dst.y = y;
		dst.w = w;
		dst.h = h;
		SDL_RenderCopy(ren, tex, nullptr, &dst);
	}
	
	void render_texture(SDL_Renderer *ren, SDL_Texture *tex, int x, int y) {
		int w,
			h;
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		render_texture(ren, tex, x, y, w, h);
	}
	
	SdlTexPtr render_font(SDL_Renderer *ren, const std::string &file, const std::string &msg, SDL_Color color, int font_size) {
		TtfFontPtr font{TTF_OpenFont(file.c_str(), font_size)};
		if (!font)
			throwSdlError("TTF Open Font");
		
		SdlSurfPtr temp_surface{TTF_RenderText_Blended(font.get(), msg.c_str(), color)};
		if (!temp_surface)
			throwSdlError("TTF Render Font");
		
		SdlTexPtr tex{SDL_CreateTextureFromSurface(ren, temp_surface.get())};
		if (!tex)
			throwSdlError("Create Texture");
		
		return tex;
	}
}

View::View(Field *field)
    : SdlHandle(SDL_INIT_EVERYTHING)
    , ImgHandle(IMG_INIT_PNG | IMG_INIT_JPG)
    , field(field) {
    
    win.reset(SDL_CreateWindow("Tron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, field->SCREEN_WIDTH, field->SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
    if (!win)
        throwSdlError("Window Initialisation");

    ren.reset(SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED));
    if (!ren)
        throwSdlError("Renderer Initialisation");

    background.reset(IMG_LoadTexture(ren.get(), "Resources/background.jpg"));
    if (!background)
        throwSdlError("Texture");
}

void View::draw() {
    // Render background texture
    render_texture(ren.get(), background.get(), 0, 0);

    SDL_Rect draw_dst;
    draw_dst.w = Field::TILESIZE;
    draw_dst.h = Field::TILESIZE;

    for (int y = 0; y < field->HEIGHT; ++y)
        for (int x = 0; x < field->WIDTH; ++x) {
            switch(field->matrix[y][x]) {
                case PLAYER_1 :
                case RED_TRAIL :
                    // Set the draw color
                    SDL_SetRenderDrawColor(ren.get(), COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, SDL_ALPHA_OPAQUE);

                    // Set the position to draw
                    draw_dst.x = x * Field::TILESIZE;
                    draw_dst.y = y * Field::TILESIZE;

                    // Draw
                    SDL_RenderFillRect(ren.get(), &draw_dst);
                    break;
                case PLAYER_2 :
                case GREEN_TRAIL :
                    // Set the draw color
                    SDL_SetRenderDrawColor(ren.get(), COLOR_GREEN.r, COLOR_GREEN.g, COLOR_GREEN.b, SDL_ALPHA_OPAQUE);

                    // Set the position to draw
                    draw_dst.x = x * Field::TILESIZE;
                    draw_dst.y = y * Field::TILESIZE;

                    // Draw
                    SDL_RenderFillRect(ren.get(), &draw_dst);
                    break;
                case NOTHING :
                    break;
            }
        }

    SDL_RenderPresent(ren.get());
}

void View::draw_end_screen(Team winner,int red_wins, int green_wins) {
    std::string winner_text;
    std::string start_text = "start";
    std::string select_text = "exit";
    std::string realwinner_text = ToString(red_wins) + " : " + ToString(green_wins);

    SDL_Color winner_color;
    SDL_Color realwinner_color;
    SDL_Color start_color = {0,255,0};
    SDL_Color select_color = {255,0,0};
    SDL_Color bg_color = {0,0,0};

    if (red_wins == green_wins) realwinner_color = {255,255,0};
    else if (red_wins < green_wins) realwinner_color = {0,255,0};
    else realwinner_color = {255,0,0};

    if (winner == RED) {
        winner_text = "Red Won";
        winner_color = {255, 0, 0};
    }
    else if (winner == GREEN) {
        winner_text = "Green Won";
        winner_color = {0, 255, 0};
    }
    else {
        	winner_text = "Tie!";
        	winner_color = {255, 255, 0};
	}

    auto winner_texture_s = render_font(ren.get(), "Resources/pixelated.ttf", winner_text.c_str(), bg_color, 50);
    auto select_texture_s = render_font(ren.get(), "Resources/pixelated.ttf", select_text.c_str(), bg_color, 24);
    auto start_texture_s = render_font(ren.get(), "Resources/pixelated.ttf", start_text.c_str(), bg_color, 24);
    auto realwinner_texture_s = render_font(ren.get(), "Resources/pixelated.ttf", realwinner_text.c_str(), bg_color, 24);
    auto winner_texture = render_font(ren.get(), "Resources/pixelated.ttf", winner_text.c_str(), winner_color, 50);
    auto select_texture = render_font(ren.get(), "Resources/pixelated.ttf", select_text.c_str(), select_color, 24);
    auto start_texture = render_font(ren.get(), "Resources/pixelated.ttf", start_text.c_str(), start_color, 24);
    auto realwinner_texture = render_font(ren.get(), "Resources/pixelated.ttf", realwinner_text.c_str(), realwinner_color, 24);

    int w,h;
    SDL_QueryTexture(winner_texture.get(), nullptr, nullptr, &w, &h);

    SDL_Rect dst;
    dst.x = Field::SCREEN_WIDTH / 2 - w / 2 + 2;
    dst.y = Field::SCREEN_HEIGHT / 2 - h / 2 + 2;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(ren.get(), winner_texture_s.get(), nullptr, &dst);
    dst.x -= 2;
    dst.y -= 2;
    SDL_RenderCopy(ren.get(), winner_texture.get(), nullptr, &dst);

    SDL_QueryTexture(realwinner_texture.get(), nullptr, nullptr, &w, &h);
    dst.x = Field::SCREEN_WIDTH / 2 - w / 2 + 2;
    dst.y = Field::SCREEN_HEIGHT - h - 3;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(ren.get(), realwinner_texture_s.get(), nullptr, &dst);

    dst.x -= 2;
    dst.y -= 2;

    SDL_RenderCopy(ren.get(), realwinner_texture.get(), nullptr, &dst);

    SDL_QueryTexture(start_texture.get(), nullptr, nullptr, &w, &h);

    dst.x = Field::SCREEN_WIDTH - w - 1;
    dst.y = 5;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(ren.get(), start_texture_s.get(), nullptr, &dst);
    dst.x -= 2;
    dst.y -= 2;
    SDL_RenderCopy(ren.get(), start_texture.get(), nullptr, &dst);

    SDL_QueryTexture(select_texture.get(), nullptr, nullptr, &w, &h);

    dst.x = 5; 
    dst.y = 5;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(ren.get(), select_texture_s.get(), nullptr, &dst);
    dst.x -= 2;
    dst.y -= 2;
    SDL_RenderCopy(ren.get(), select_texture.get(), nullptr, &dst);

    SDL_RenderPresent(ren.get());
}
