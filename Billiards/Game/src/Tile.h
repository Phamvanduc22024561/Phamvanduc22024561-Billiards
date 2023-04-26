#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "Math.h"

class Tile : public Entity
//Lớp Tile dùng để biểu diễn các viên gạch trong game và được kế thừa từ Entity
{
    public: 
    Tile(Vector2f p_pos, SDL_Texture* p_tex);
    
    private:
};