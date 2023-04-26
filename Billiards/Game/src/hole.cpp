#include "Hole.h"
#include "Entity.h"
#include "Math.h"
#include <SDL.h>

Hole::Hole(Vector2f p_pos, SDL_Texture* p_tex)
//constructer của lớp Hole gồm vị trí ban đầu và con trỏ texture của hole
:Entity(p_pos, p_tex)
{
}