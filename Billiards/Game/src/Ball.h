#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "Hole.h"
#include "Tile.h"

#include "Entity.h"
#include "Math.h"
//Khi báo thư viện

class Ball : public Entity
//Khởi tạo lớp ball kế thừa từ lớp Entity, lớp ball là lớp có các thuộc tính bên dưới
{
public:
	Ball(Vector2f p_pos, SDL_Texture* p_tex, SDL_Texture* p_pointTex, SDL_Texture* p_powerMTexFG, SDL_Texture* p_powerMTexBG, int p_index);
    /*Hàm khởi tạo của lớp Ball, với các đối số lần lượt là vị trí ban đầu của quả bóng, các hình ảnh được sử dụng để vẽ quả bóng và
    các thành phần khác, và chỉ số của quả bóng*/
    Vector2f& getVelocity()//Hàm trả về vector vận tốc của quả bóng
	{
		return velocity;
	}
    Vector2f& getInitialMousePos()
    //trả về một tham chiếu đến vector initialMousePos - là vị trí ban đầu của chuột
	{
		return initialMousePos;
	}
    std::vector<Entity> getPoints()
    //trả về một vector chứa các đối tượng Entity - đại diện cho các điểm trên đường đi của quả bóng
	{
		return points;
	}
    std::vector<Entity> getPowerBar()
    //trả về một vector chứa các đối tượng Entity - đại diện cho các thanh cung cấp năng lượng của quả bóng
	{
		return powerBar;
	}
    int getStrokes()
    //trả về số lần bắn bóng của người chơi
    {
        return strokes;
    }
    bool isWin()
    // trả về giá trị boolean cho biết liệu người chơi đã chiến thắng hay chưa
    {
        return win;
    }
    void setWin(bool p_win);//thiết lập giá trị boolean cho biết liệu người chơi đã chiến thắng hay chưa
    void setInitialMousePos(float x, float y);// thiết lập giá trị vector vị trí ban đầu của chuột
    void setVelocity(float x, float y);// thiết lập giá trị vector tốc độ của quả bóng
    void setLaunchedVelocity(float x, float y);//thiết lập giá trị vector tốc độ ban đầu của quả bóng
    void update(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Tile> tiles, std::vector<Hole> holes,Mix_Chunk* chargeSfx, Mix_Chunk* swingSfx, Mix_Chunk* holeSfx);
    /*cập nhật trạng thái của quả bóng theo thời gian và các sự kiện chuột và bàn phím*/
private:
    Vector2f velocity;//Vector 2D đại diện cho vận tốc hiện tại của ball trong trò chơi
    Vector2f target;//Vector 2D đại diện cho vị trí mục tiêu của ball
    Vector2f launchedVelocity;//Vector 2D đại diện cho vận tốc của ball khi nó được phóng ra
    float velocity1D;//Số thực đại diện cho độ lớn của vector vận tốc hiện tại
    float launchedVelocity1D;//Số thực đại diện cho độ lớn của vector vận tốc được phóng ra
    Vector2f initialMousePos;//Vector 2D đại diện cho vị trí ban đầu của con chuột khi được nhấn
    bool canMove = true;// Boolean cho biết liệu ball có thể di chuyển hay không
    bool playedSwingFx = true;// Boolean cho biết liệu âm thanh hoạt động đã được phát hay chưa
    int index;//Số nguyên đại diện cho chỉ mục của ball trong trò chơi
    int strokes = 0;//Số nguyên đại diện cho số lần đánh trong trò chơi
    int dirX = 1;//Số nguyên cho biết hướng di chuyển trên trục x
    int dirY = 1;//Số nguyên cho biết hướng di chuyển trên trục y
    bool win = false;//Boolean cho biết liệu trò chơi đã thắng hay chưa
    double friction = 0.001;//Số thực đại diện cho ma sát của bề mặt mà đối tượng đang di chuyển trên đó
    std::vector<Entity> points;//Vector của các đối tượng Entity đại diện cho các điểm trong trò chơi
    std::vector<Entity> powerBar;// Vector của các đối tượng Entity đại diện cho thanh công suất trong trò chơi
};