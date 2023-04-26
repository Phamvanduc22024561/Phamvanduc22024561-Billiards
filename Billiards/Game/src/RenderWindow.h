#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Entity.h"

class RenderWindow 
//Lớp đại diện cho 1 cửa sổ hiển thị (window) và trình vẽ (renderer) của SDL
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	//hàm tạo của lớp RenderWindow, nhận vào 3 tham số là tiêu đề của cửa sổ (p_title) và kích thước của cửa sổ (p_w, p_h)
	SDL_Texture* loadTexture(const char* p_filePath);
	//tải texture từ file (p_filePath) và trả về con trỏ đến texture được tải lên
	void cleanUp();//giải phóng bộ nhớ
	void clear();//xóa nội dung hiển thị của cửa sổ
	void render(Entity& p_entity);//phương thức vẽ một đối tượng Entity lên cửa sổ, nhận vào tham số là một tham chiếu (&) đến đối tượng Entity cần vẽ
	void render(int x, int y, SDL_Texture* p_tex);
	//vẽ một texture (p_tex) lên cửa sổ với tọa độ (x, y) được chỉ định
	void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
	void renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
	//vẽ một chuỗi ký tự (p_text) lên cửa sổ với tọa độ (p_x, p_y) được chỉ định, font chữ (font) và màu chữ (textColor).
	void display();//hiển thị nội dung đã vẽ lên cửa sổ
private:
	SDL_Window* window;//con trỏ mà RenderWindow quản lí
	SDL_Renderer* renderer;//con trỏ đến bộ vẽ được sử dụng để vẽ hình ảnh trên cửa sổ
};