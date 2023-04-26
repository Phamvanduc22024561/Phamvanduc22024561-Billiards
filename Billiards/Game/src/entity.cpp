#include "Entity.h"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
//constructer của lớp Entity gồm vị trí vf con trỏ hình ảnh của bóng
:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	//khởi taọ vị trí x, y 
	currentFrame.w = 32;
	currentFrame.h = 32;
	//chiều cao và rộng của khung hình là 32
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
	//thông số kích thước rộng và cao đc truyền vào hàm lưu trữ trong currentFrame
}

SDL_Texture* Entity::getTex()
//sử dụng cho việc hiển thị hình ảnh của đối tượng Entity
{
	return tex;
}

void Entity::update(double deltaTime)
//cập nhật tgian
{

}

void Entity::setPos(float x, float y)
//cập nhật vị trí 
{
	pos.x = x;
	pos.y = y;
}

void Entity::setAngle(float p_angle)
//dùng để đặt giá trị cho biến angle
{
	angle = p_angle;
}

void Entity::setScale(float w, float h)
//hàm để vẽ đối tượng tỉ lệ tương ứng 
{
	scale.x = w;
	scale.y = h;
}

SDL_Rect Entity::getCurrentFrame()
//trả về kích thước và vị trí hiện tại của khung hình
{
	return currentFrame;
}
