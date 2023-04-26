#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
//tạo của sổ SDL
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	//sử dụng SDL_CreateWindow để tạo ra cửa sổ

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// sử dụng SDL_CreateRenderer để tạo một bộ vẽ SDL cho cửa sổ với các tùy chọn cấu hình tốc độ phần cứng và bộ nhớ đệm
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
//dùng để tải texture từ đường dẫn file ảnh được truyền vào và trả về một con trỏ đến texture tương ứng
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);
	// sử dụng hàm IMG_LoadTexture của thư viện SDL_Image để tải texture

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::cleanUp()
//thoát cửa sổ giải phóng bộ nhớ
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
//xóa nội dung trên màn hình chủân bị cho nội dung mới
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
//hàm vẽ đối tượng kế thừa từ lớp Entity 
{
	SDL_Rect src; //chỉ định vị trí và kích thước của khung hình hiện tại của đối tượng
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;// xác định vị trí và kích thước của khung hình cần được vẽ lên màn hình
	dst.x = p_entity.getPos().x + (p_entity.getCurrentFrame().w - p_entity.getCurrentFrame().w*p_entity.getScale().x)/2;
	dst.y = p_entity.getPos().y + (p_entity.getCurrentFrame().h - p_entity.getCurrentFrame().h*p_entity.getScale().y)/2;
	dst.w = p_entity.getCurrentFrame().w*p_entity.getScale().x;
	dst.h = p_entity.getCurrentFrame().h*p_entity.getScale().y;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
	/*sử dụng để sao chép texture của đối tượng vào màn hình với các tham số như sau:

	renderer: là renderer để vẽ lên màn hình.
	p_entity.getTex(): là texture của đối tượng cần vẽ.
	&src: là con trỏ đến biến SDL_Rect src chứa thông tin về khung hình hiện tại của đối tượng.
	&dst: là con trỏ đến biến SDL_Rect dst chứa thông tin về vị trí và kích thước của khung hình cần vẽ lên màn hình.
	p_entity.getAngle(): là góc quay của đối tượng.
	0: là con trỏ đến trung tâm của texture, tương đương với trung tâm của khung hình vẽ.
	SDL_FLIP_NONE: là hướng flip của texture, trong trường hợp này là không flip*/
}

void RenderWindow::render(int x, int y, SDL_Texture* p_tex)
{
	SDL_Rect src;//lưu trữ kích thước của texture
	src.x = 0;
	src. y = 0;
	src.w;
	src.h;

	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);
	//xác định vị trí và kích thước của texture trên màn hình

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Thiết lập giá trị của dst.x và dst.y để đặt vị trí của texture trên màn hình
	dst.w = src.w;
	dst.h = src.h;
	//Thiết lập giá trị của dst.w và dst.h bằng với src.w và src.h để đảm bảo kích thước của texture trên màn hình giống với kích thước của texture ban đầu

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
	//sao chép texture lên màn hình với tham số renderer, p_tex, src và dst
}

void RenderWindow::render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
//vẽ một đoạn văn bản lên màn hình tại vị trí chỉ định
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		//tạo ra một surface chứa đoạn văn bản được chỉ định, với font và màu sắc được chỉ định
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		//tạo ra một texture từ surface vừa được tạo ra

		SDL_Rect src;
		// lưu trữ thông tin về kích thước và vị trí của một hình chữ nhật.
		src.x = 0;
		//tọa độ x tính từ góc trái trên
		src.y = 0;
		//tọa độ y tính từ góc trái trên
		src.w = surfaceMessage->w;
		//chiều rộng của hình chữ nhật, trong trường hợp này được thiết lập bằng chiều rộng của surfaceMessage
		src.h = surfaceMessage->h;
		//chiều cao của hình chữ nhật, trong trường hợp này được thiết lập bằng chiều cao của surfaceMessage
		
		//Biến surfaceMessage là một biến kiểu SDL_Surface*, chứa nội dung của đoạn văn bản được vẽ.

		SDL_Rect dst;
		//sử dụng để xác định vị trí và kích thước của hình chữ nhật mà đoạn văn bản sẽ được vẽ lên màn hình
		dst.x = p_x;
		// tọa độ x của hình chữ nhật, được truyền vào hàm render() dưới dạng đối số p_x
		dst.y = p_y;
		// tọa độ y của hình chữ nhật, được truyền vào hàm render() dưới dạng đối số p_y.
		dst.w = src.w;
		//chiều rộng của hình chữ nhật, được thiết lập bằng giá trị chiều rộng của biến src, tức là chiều rộng của surface chứa đoạn văn bản được vẽ
		dst.h = src.h;
		//chiều cao của hình chữ nhật, được thiết lập bằng giá trị chiều cao của biến src, tức là chiều cao của surface chứa đoạn văn bản được vẽ

		SDL_RenderCopy(renderer, message, &src, &dst);
		//để sao chép texture message lên màn hình tại vị trí và kích thước được xác định bởi biến dst
		//đối số đầu tiên của hàm SDL_RenderCopy() là renderer, đó là một con trỏ đến renderer mà đoạn văn bản sẽ được vẽ lên.
		//Đối số thứ hai của hàm SDL_RenderCopy() là message, đó là texture chứa đoạn văn bản được tạo ra từ surface bằng hàm SDL_CreateTextureFromSurface()
		//Đối số thứ ba và thứ tư là &src và &dst, tương ứng với con trỏ đến biến src và biến dst mà chúng ta đã thiết lập trước đó

		SDL_FreeSurface(surfaceMessage);
		//giải phóng surfaceMessage
	 	SDL_DestroyTexture(message);
}

void RenderWindow::renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
//hàm vẽ chữ giữa màn hình
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		//tạo ra một surface chứa đoạn văn bản được chỉ định 
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		//tạo ra một texture từ surface trên

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h; 

		SDL_Rect dst;
		dst.x = 640/2 - src.w/2 + p_x;
		dst.y = 480/2 - src.h/2 + p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(message);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
