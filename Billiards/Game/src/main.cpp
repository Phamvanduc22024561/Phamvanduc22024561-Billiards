#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include "RenderWindow.h"
#include "Entity.h"
#include "Ball.h"	
#include "Tile.h"
#include "Hole.h"

bool init()
//khởi tạo các thư viện cần thiết để chạy ứng dụng SDL
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	}
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	}
	if (!(TTF_Init()))
	{
		std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return true;
}

bool SDLinit = init();

RenderWindow window("Billiands", 640, 480);

SDL_Texture* ballTexture = window.loadTexture("res/gfx/ball.png");
SDL_Texture* holeTexture = window.loadTexture("res/gfx/hole.png");
SDL_Texture* pointTexture = window.loadTexture("res/gfx/point.png");
SDL_Texture* tileDarkTexture32 = window.loadTexture("res/gfx/tile32_dark.png");
SDL_Texture* tileDarkTexture64 = window.loadTexture("res/gfx/tile64_dark.png");
SDL_Texture* tileLightTexture32 = window.loadTexture("res/gfx/tile32_light.png");
SDL_Texture* tileLightTexture64 = window.loadTexture("res/gfx/tile64_light.png");
SDL_Texture* ballShadowTexture = window.loadTexture("res/gfx/ball_shadow.png");
SDL_Texture* bgTexture = window.loadTexture("res/gfx/bg.png");
SDL_Texture* uiBgTexture = window.loadTexture("res/gfx/UI_bg.png");
SDL_Texture* levelTextBgTexture = window.loadTexture("res/gfx/levelText_bg.png");
SDL_Texture* powerMeterTexture_FG = window.loadTexture("res/gfx/powermeter_fg.png");
SDL_Texture* powerMeterTexture_BG = window.loadTexture("res/gfx/powermeter_bg.png");
SDL_Texture* powerMeterTexture_overlay = window.loadTexture("res/gfx/powermeter_overlay.png");
SDL_Texture* logoTexture = window.loadTexture("res/gfx/logo.png");
SDL_Texture* click2start = window.loadTexture("res/gfx/click2start.png");
SDL_Texture* endscreenOverlayTexture = window.loadTexture("res/gfx/end.png");
SDL_Texture* splashBgTexture = window.loadTexture("res/gfx/splashbg.png");

Mix_Chunk* chargeSfx = Mix_LoadWAV("res/sfx/charge.mp3");
Mix_Chunk* swingSfx = Mix_LoadWAV("res/sfx/swing.mp3");
Mix_Chunk* holeSfx = Mix_LoadWAV("res/sfx/hole.mp3");


SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("res/font/font.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("res/font/font.ttf", 24);
//tải các tệp hình ảnh âm thanh để chạy

Ball balls[2] = {Ball(Vector2f(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 0), Ball(Vector2f(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 1)};
//tạo mảng balls
std::vector<Hole> holes = {Hole(Vector2f(0, 0), holeTexture), Hole(Vector2f(0, 0), holeTexture)};

std::vector<Tile> loadTiles(int level)
{
	std::vector<Tile> temp = {};
	switch (level)
	{
	case 0:
		temp.push_back(Tile(Vector2f(64 * 3, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 4, 64 * 3), tileDarkTexture64));

		temp.push_back(Tile(Vector2f(64 * 0, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 1, 64 * 3), tileDarkTexture64));

		temp.push_back(Tile(Vector2f(64 * 3 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 4 + 64 * 5, 64 * 3), tileLightTexture64));

		temp.push_back(Tile(Vector2f(64 * 0 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 1 + 64 * 5, 64 * 3), tileLightTexture64));
		break;
	case 1:
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 3), tileDarkTexture64));

		temp.push_back(Tile(Vector2f(64 * 4 + 64 * 5, 64 * 3), tileLightTexture64));
		break;
	case 2:
		temp.push_back(Tile(Vector2f(32 * 1 + 32 * 10 + 16, 32 * 5), tileLightTexture32));
		break;
	case 3:
		temp.push_back(Tile(Vector2f(32 * 4, 32 * 7), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 6, 32 * 3), tileDarkTexture32));

		temp.push_back(Tile(Vector2f(32 * 4 + 64 * 5, 32 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 6), tileLightTexture32));
		temp.push_back(Tile(Vector2f(32 * 6 + 32 * 10, 32 * 9), tileLightTexture32));
		break;
	case 4:
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 1), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 1, 32 * 3), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 5, 32 * 3), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 10), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 5, 32 * 12), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture32));

		//temp.push_back(Tile(Vector2f(32*4, 32*7), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 8, 32 * 7), tileDarkTexture64));

		temp.push_back(Tile(Vector2f(32 * 2 + 32 * 10, 32 * 2), tileLightTexture32));
		temp.push_back(Tile(Vector2f(32 * 5 + 32 * 10, 32 * 11), tileLightTexture32));

		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 1), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 8 + 32 * 10, 32 * 6), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 11), tileLightTexture64));
		break;
	case 5:
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 2), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 4, 64 * 2), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 6, 64 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 4), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 8, 64 * 4), tileLightTexture64));
		break;

	case 6:
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 3, 64 * 2), tileLightTexture64));
	case 7:
		temp.push_back(Tile(Vector2f(32 * 8 + 32 * 10, 32 * 6), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 11), tileLightTexture64));
	case 8:
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 4, 64 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 6, 64 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 4), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 8, 64 * 4), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 11, 64 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 11, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 11, 64 * 4), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 7), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 3, 64 * 7), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 4, 64 * 7), tileLightTexture64));
		break;

	case 9:
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 10), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 5, 32 * 12), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(64 * 11, 64 * 4), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 7), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 3, 64 * 7), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 4, 64 * 7), tileLightTexture64));

	}
	return temp;
}

int level = 0;
std::vector<Tile> tiles = loadTiles(level);

bool gameRunning = true;
bool mouseDown = false;
bool mousePressed = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;


SDL_Event event;

int state = 0; //0 = title screen, 1 = game, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();//, trả về thời điểm hiện tại theo đơn vị ticks.
Uint64 lastTick = 0;
double deltaTime = 0;

void loadLevel(int level)
{
	if (level > 9)
	{
		state = 2;
		return;
	}
	balls[0].setVelocity(0, 0);
	balls[1].setVelocity(0,0);
    balls[0].setScale(1, 1);
	balls[1].setScale(1, 1);
	balls[0].setWin(false);
	balls[1].setWin(false);

	tiles = loadTiles(level);

	switch (level)
	{
	case 0:
		balls[0].setPos(24 + 32 * 4, 24 + 32 * 11);
		balls[1].setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 11);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 2);
		holes.at(1).setPos(24 + 32 * 4 + 32 * 10, 22 + 32 * 2);
		break;
	case 1:
		balls[0].setPos(24 + 32 * 4, 24 + 32 * 11);
		balls[1].setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 11);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 2);
		holes.at(1).setPos(24 + 32 * 4 + 32 * 10, 22 + 32 * 2);
		break;
	case 2:
		balls[0].setPos(8 + 32 * 7, 8 + 32 * 10);
		balls[1].setPos(8 + 32 * 7 + 32 * 10, 8 + 32 * 10);

		holes.at(0).setPos(8 + 32 * 2, 6 + 32 * 5);
		holes.at(1).setPos(8 + 32 * 4 + 32 * 10, 6 + 32 * 3);
		break;
	case 3:
		balls[0].setPos(24 + 32 * 4, 24 + 32 * 5);
		balls[1].setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 4);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 1);
		holes.at(1).setPos(24 + 32 * 4 + 32 * 10, 22 + 32 * 11);
		break;
	case 4:
		balls[0].setPos(24 + 32 * 2, 24 + 32 * 12);
		balls[1].setPos(24 + 32 * 0 + 32 * 10, 24 + 32 * 5);

		holes.at(0).setPos(24 + 32 * 1, 22 + 32 * 1);
		holes.at(1).setPos(24 + 32 * 0 + 32 * 10, 22 + 32 * 7);
		break;
	case 5:
		balls[0].setPos(24 + 32 * 2, 24 + 32 * 6);
		balls[1].setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 6);

		holes.at(0).setPos(24 + 32 * 5, 22 + 32 * 2);
		holes.at(1).setPos(24 + 32 * 4 + 32 * 10 + 32, 22 + 32 * 2);
		break;
	case 6:
		balls[0].setPos(24 + 32 * 3, 24 + 32 * 2);
		balls[1].setPos(24 + 32 * 11, 24 + 32 * 9);

		holes.at(0).setPos(8 + 32 * 7, 6 + 32 * 3);

		holes.at(1).setPos(24 + 32 * 11, 24 + 32 * 2);
		break;
	case 7:
		balls[0].setPos(24 + 32 * 2, 24 + 32 * 3);
		balls[1].setPos(24 + 32 * 11, 24 + 32 * 10);

		holes.at(0).setPos(24 + 32 * 5, 24 + 32 * 6);
		holes.at(1).setPos(24 + 32 * 10, 24 + 32 * 10);
		break;
	case 8:
		balls[0].setPos(24 + 32 * 1, 24 + 32 * 5);
		balls[1].setPos(24 + 32 * 10, 24 + 32 * 5);

		holes.at(0).setPos(24 + 32 * 6, 24 + 32 * 1);
		holes.at(1).setPos(24 + 32 * 14, 24 + 32 * 5);
		break;
	case 9:
		balls[0].setPos(24 + 32 * 3, 24 + 32 * 2);
		balls[1].setPos(24 + 32 * 11, 24 + 32 * 10);

		holes.at(0).setPos(24 + 32 * 3, 24 + 32 * 3);
		holes.at(1).setPos(24 + 32 * 11, 24 + 32 * 2);
		break;

	}
}



const char* getStrokeText()
{
	int biggestStroke = 0;
	if (balls[1].getStrokes() > balls[0].getStrokes())
	{
		biggestStroke = balls[1].getStrokes();
	}
	else
	{
		biggestStroke = balls[0].getStrokes();
	}
	std::string s = std::to_string(biggestStroke);
	s = "STROKES: " + s;
	return s.c_str();
}

const char* getLevelText(int side)
{
	int tempLevel = (level + 1)*2 - 1;
	/*tính toán số thứ tự của lỗ bi và lưu trữ vào biến
	tạm thời tempLevel.Số thứ tự được tính bằng công thức
	(level + 1) * 2 - 1. Biến level ở đây có thể là một biến
	global hoặc thành viên của một lớp*/
	if (side == 1)
	/*kiểm tra nếu đối số đầu vào side có giá trị là 1
	thì tăng giá trị của tempLevel lên 1. Nếu side có giá
	trị khác 1, thì khối lệnh này sẽ bị bỏ qua*/
	{
		tempLevel++;
	}
	std::string s = std::to_string(tempLevel);
	//chuyển giá trị tempLever thành chuỗi
	s = "HOLE: " + s;
	//thêm chuỗi HOLE vào s
	return s.c_str();
	//trả về con trỏ ban đầu
}

void update()
//Hàm cập nhật các khung hình
{
	//đoạn mã sau cập nhật thời gian giữa các khung hình
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );

	mousePressed = false;
	//kiểm tra người chơi có dùng chuột không
	while (SDL_PollEvent(&event))
	//vòng lặp kiểm tra người dùng có bấm chuột không
	{
		switch(event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
				mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;
		}
	}

	if (state == 1)
	//nếu đang trong trạng thái chơi
	{
		for (Ball& b : balls)
		//vòng lặp cập nhật tất cả các thuộc tính của ball bằng  phương thức update
		{
			b.update(deltaTime, mouseDown, mousePressed, tiles, holes, chargeSfx, swingSfx, holeSfx);
		}
		if (balls[0].getScale().x < -1 && balls[1].getScale().x < -1)
		//nếu bóng vào lỗ thì biến level sẽ tăng thêm để hàm loadlever được gọi để tải màn chơi tiếp
 		{
        	level++;
			loadLevel(level);
    	}
	}
}

void graphics()
//vẽ các đối tượng để chơi game
{
	window.clear();
	//xóa màn hình trước khi vẽ đối tượng mới
	window.render(0, 0, bgTexture);
	//vẽ background lên cửa sổ
	for (Hole& h : holes)
	//vẽ lỗ trên cửa sổ bằng cách duyệt từng lỗ trong danh sách lỗ và vẽ nó lên cửa sổ
	{
		window.render(h);
	}
	for (Ball& b : balls)
	// vẽ bóng lên cửa sổ bằng cách duyệt từng quả bóng trong danh sách các quả bóng và vẽ nó lên cửa sổ
	{
		if (!b.isWin())
		//nếu bóng còn ở trên sân
		{
			window.render(b.getPos().x, b.getPos().y + 4, ballShadowTexture);
			//vẽ bóng đổ cho bóng
		}
		for (Entity& e : b.getPoints())
		//vẽ các gạch lên cửa sổ bằng cách duyệt từng gạch trong danh sách gạch và vẽ nó lên cửa sổ
		{
			window.render(e);
		}
		window.render(b);
	}
	for (Tile& t : tiles)
	//vẽ các gạch lên cửa sổ bằng cách duyệt từng gạch trong danh sách gạch và vẽ nó lên cửa sổ
	{ 
		window.render(t);
	}
	for (Ball& b : balls)
	//vẽ thanh điểm năng lượng và lớp vỏ trên thanh điểm năng lượng cho từng quả bóng bằng cách duyệt từng thanh điểm năng lượng và vẽ nó lên cửa sổ
	{
		for (Entity& e : b.getPowerBar())
		{
			window.render(e);
		}
		window.render(b.getPowerBar().at(0).getPos().x, b.getPowerBar().at(0).getPos().y, powerMeterTexture_overlay);
		//vẽ lớp vỏ trên thanh năng lượng
		
	}
	if (state != 2)
	//nếu khác trạng thái chiến thắng
	{
		window.render(640/4 - 132/2, 480 - 32, levelTextBgTexture);
		window.renderCenter(-160, 240 - 16 + 3, getLevelText(0), font24, black);
		window.renderCenter(-160, 240 - 16, getLevelText(0), font24, white);
		/*Vẽ background cho text "Level 1" tại vị trí (640/4 - 132/2, 480 - 32)
		bằng cách sử dụng hàm window.render với tham số là levelTextBgTexture và
		các tham số vị trí*/

		window.render(640/2 + 640/4 - 132/2, 480 - 32, levelTextBgTexture);
		window.renderCenter(160, 240 - 16 + 3, getLevelText(1), font24, black);
		window.renderCenter(160, 240 - 16, getLevelText(1), font24, white);
		/*Tương tự, vẽ background cho text "Level 2" tại vị trí (640/2 + 640/4 - 132/2, 480 - 32)
		và chữ "Level 2" với màu đen tại vị trí (160, 240 - 16 + 3) và với màu trắng tại vị trí (160, 240 - 16).*/

		window.render(640/2 - 196/2, 0, uiBgTexture);
		window.renderCenter(0, -240 + 16 + 3, getStrokeText(), font24, black);
		window.renderCenter(0, -240 + 16, getStrokeText(), font24, white);
		/*Vẽ background cho phần UI tại vị trí (640/2 - 196/2, 0) và vẽ chữ hiển thị số cú đánh tại vị trí
		(0, -240 + 16 + 3) với màu đen và vị trí (0, -240 + 16) với màu trắng. Các chữ được lấy bằng hàm getStrokeText(), với font size là 24*/
	}
	else
	{
		window.render(0, 0, endscreenOverlayTexture);
		//Vẽ hình nền cho giao diện kết thúc game bằng hàm window.render với tham số là endscreenOverlayTexture và vị trí (0, 0)
		window.renderCenter(0, 3 - 32, "YOU WON!", font48, black);
		window.renderCenter(0, -32, "YOU WON!", font48, white);
		//Vẽ chữ "YOU WON!" với màu đen tại vị trí (0, 3 - 32) và với màu trắng tại vị trí (0, -32) bằng hàm window.renderCenter với các tham số lần lượt là "YOU WON!", font48, black và white.
		window.renderCenter(0, 3 + 32, getStrokeText(), font32, black);
		window.renderCenter(0, 32, getStrokeText(), font32, white);
		//Vẽ chữ hiển thị số cú đánh tại vị trí (0, 3 + 32) với màu đen và vị trí (0, 32) với màu trắng. Các chữ được lấy bằng hàm getStrokeText(), với font size là 32.
	}
	window.display();
	//hiển thị toàn bộ
}

void titleScreen()
//hàm hiển thị tiêu đề cho game
{
	if (SDL_GetTicks() < 2000)
	//kiểm tra xem đã qua 2 giây từ khi game bắt đầu sử dụng hàm SDL_GetTicks
	{
		if (!swingPlayed)
		//kiểm tra xem tiêu đề đã đc phát chưa 
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			swingPlayed = true;
			//hàm sẽ phát hiệu ứng âm thanh bằng SDL_mixer và đặt biến swingPlayed thành true để đánh dấu
		}
		//Get our controls and events
		while (SDL_PollEvent(&event))
		//Nếu người dùng bấm nút "x" ở góc trên cùng bên trái của cửa sổ trò chơi, biến gameRunning được đặt thành false để thoát khỏi trò chơi
		{
			switch(event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			}
		}

		window.clear();
		//xóa nội dung trên cửa sổ
		window.render(0, 0, bgTexture);
		window.render(0, 0, splashBgTexture);
		window.renderCenter(0, 0 + 3, "WELCOME!", font32, black);
		window.renderCenter(0, 0, "WELCOME!", font32, white);
		//các hình ảnh và văn bản được hiển thị bằng cách sử dụng các hàm render() và renderCenter()
		window.display();
		//hiển thị toàn bộ nội dung game

	}
	else
	{
		if (!secondSwingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			secondSwingPlayed = true;
		}
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );

		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					Mix_PlayChannel(-1, holeSfx, 0);
					state = 1;
				}
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.render(320 - 160, 240 - 100 - 50 + 4*SDL_sin(SDL_GetTicks()*(3.14/1500)), logoTexture);
		window.render(0, 0, click2start);
		window.renderCenter(0, 240 - 48 + 3 - 16*5, "LEFT CLICK TO START", font32, black);
		window.renderCenter(0, 240 - 48 - 16*5, "LEFT CLICK TO START", font32, white);
		window.display();
	}
}
void game()
//à hàm chính của trò chơi, nó sẽ được gọi trong vòng lặp chính để chạy trò chơi
{
	if (state == 0)
	//kiểm tra biến state để xác định xem trò chơi đang ở trạng thái nào: nếu state bằng 0 thì sẽ chạy màn hình tiêu đề bằng hàm titleScreen()
	{
		titleScreen();
	}
	else
	//nếu state khác 0 thì sẽ chạy trạng thái chính của trò chơi bằng hai hàm update() và graphics().
	{
		update();
		graphics();
	}
}
int main(int argc, char* args[])
{
	loadLevel(level);
	//hàm được gọi để tải nội dung của màn chơi
	while (gameRunning)
	/*vòng lặp while và biến gameRunning được khởi
	tạo ban đầu là true, chương trình sẽ gọi hàm game()
	để chạy trò chơi cho đến khi biến gameRunning được đặt thành false*/
	{
		game();
	}

	window.cleanUp();
	TTF_CloseFont(font32);
	TTF_CloseFont(font24);
	SDL_Quit();
	TTF_Quit();
	return 0;
}