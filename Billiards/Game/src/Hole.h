#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "Math.h"

class Hole : public Entity
//định nghĩa lớp Hole là lớp kế thừa của Entity
{
    public: 
    Hole(Vector2f p_pos, SDL_Texture* p_tex);
    private:
};