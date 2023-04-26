#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.h"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
	// hàm tạo lớp Entity với các tham số là vị trí (vector 2D) và texture (SDL_Texture*) của đối tượng
	Vector2f& getPos()//trả về vị trí của đối tượng (kiểu tham chiếu)
	{
		return pos;
	}
	float getAngle()//trả về góc xoay của đối tượng
	{
		return angle;
	}
	Vector2f getScale()//trả về tỷ lệ kích thước của đối tượng (vector 2D)
	{
		return scale;
	}
	void setPos(float x, float y);// thiết lập vị trí mới cho đối tượng với tham số là tọa độ x và y
	void setScale(float w, float h);// thiết lập tỷ lệ kích thước mới cho đối tượng với tham số là chiều rộng và chiều cao
	void setAngle(float angle);// thiết lập góc xoay mới cho đối tượng với tham số là góc
	SDL_Texture* getTex();// trả về texture của đối tượng
	void update(double deltaTime);//cập nhật trạng thái của đối tượng với tham số là thời gian trôi qua
	SDL_Rect getCurrentFrame();// trả về khung hình hiện tại của đối tượng (SDL_Rect)
private:
	Vector2f pos;// vị trí của đối tượng (kiểu vector 2D)
	float angle = 0;// góc xoay của đối tượng (mặc định là 0)
	Vector2f scale = Vector2f(1, 1);//tỷ lệ kích thước của đối tượng (kiểu vector 2D) với giá trị mặc định là (1, 1) (tức không thay đổi kích thước)
	SDL_Rect currentFrame;// khung hình hiện tại của đối tượng (kiểu SDL_Rect)
	SDL_Texture* tex;// texture của đối tượng (kiểu con trỏ đến SDL_Texture)
};