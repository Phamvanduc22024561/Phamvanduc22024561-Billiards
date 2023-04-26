#include "Ball.h"
#include "Entity.h"
#include "Math.h"
#include "Tile.h"
#include "Hole.h"

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


Ball::Ball(Vector2f p_pos, SDL_Texture* p_tex, SDL_Texture* p_pointTex, SDL_Texture* p_powerMTexFG, SDL_Texture* p_powerMTexBG, int p_index)
//Khởi tạo lớp ball gồm các thành phần như vị trí ban đầu, con trỏ để vẽ, vị trí trên màn, con trỏ tới thanh công suất, con trỏ đến nền của thanh công suất trên màn hình, chỉ số 
:Entity(p_pos, p_tex)
//khai báo để gọi phương thức khởi tạo của lớp Entity, truyền vào tham số p_pos và p_tex
{
    index = p_index;//gán giá trị của biến p_index vào biến index.
    points.push_back(Entity(Vector2f(-64, -64), p_pointTex));
    //thêm một phần tử mới vào cuối vector points, đó là một đối tượng của lớp Entity được khởi tạo bằng tham số Vector2f(-64, -64) và p_pointTex.
    powerBar.push_back(Entity(Vector2f(-64, -64), p_powerMTexBG));
    //thêm một đối tượng mới vào vector powerBar, được khởi tạo bằng tham số Vector2f(-64, -64) và p_powerMTexBG
    powerBar.push_back(Entity(Vector2f(-64, -64), p_powerMTexFG));
    // thêm một đối tượng mới vào vector powerBar, được khởi tạo bằng tham số Vector2f(-64, -64) và p_powerMTexFG.
}

void Ball::setVelocity(float x, float y)
//hàm set vận tốc
{
    velocity.x = x;
    velocity.y = y;
}

void Ball::setLaunchedVelocity(float x, float y)
//hàm dùng để thiết lập vận tốc ban đầu của quả bóng khi bắn
{
    launchedVelocity.x = x;
    launchedVelocity.y = y;
}

void Ball::setInitialMousePos(float x, float y)
// đặt tọa độ chuột ban đầu khi người chơi bắt đầu kéo quả bóng để phóng
{
    initialMousePos.x = x;
    initialMousePos.y = y;
}

void Ball::setWin(bool p_win)
//thiết lập trạng thái chiến thắng của quả bóng
{
    win = p_win;
}

void Ball::update(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Tile> tiles,std::vector<Hole> holes, Mix_Chunk* chargeSfx, Mix_Chunk* swingSfx, Mix_Chunk* holeSfx)
{   
    if (win)
    {
        if (getPos().x < target.x)
        //nếu tọa độ x của bóng nhỏ hơn tọa độ x của điểm cuối cùng thì tọa độ x của bóng sẽ tăng dần với vận tốc 0.1deltaTime
        {
            setPos(getPos().x += 0.1*deltaTime, getPos().y);
        }
        else if (getPos().x > target.x)
        //Nếu tọa độ x của bóng lớn hơn tọa độ x của điểm cuối cùng thì tọa độ x của bóng giảm dần với vận tốc 0.1deltaTime
        {
            setPos(getPos().x -= 0.1*deltaTime, getPos().y);
        }
        if (getPos().y < target.y)
        //Nếu tọa độ y của bóng nhỏ hơn tọa độ y của điểm cuối cùng thì tọa độ y của bóng tăng dần với vận tốc 0.1dentalTime
        {
            setPos(getPos().x, getPos().y += 0.1*deltaTime);
        }
        else if (getPos().y > target.y)
        //Nếu tọa độ y của bóng lớn hơn tọa độ y của điểm cuối cùng thì tọa độ y của bóng giảm dần với vận tốc 0.1dentalTime
        {
            setPos(getPos().x, getPos().y -= 0.1*deltaTime);
        }
        setScale(getScale().x - 0.001*deltaTime, getScale().y - 0.001*deltaTime);
        /*getScale() được gọi để trả về tỷ lệ hiện tại của đối tượng bóng theo trục x và y, và sau đó lệnh trừ 0.001*deltaTime
        được áp dụng để giảm tỷ lệ theo cùng một mức độ đối với cả hai trục
        setScale() được gọi để đặt lại tỷ lệ của đối tượng bóng với giá trị mới tính được*/
        return;
    }
    
    for (Hole h : holes)
    //Lặp qua tất cả các phần tử trong danh sách Hole
    {
        if (getPos().x + 4 > h.getPos().x && getPos().x + 16 < h.getPos().x + 20 && getPos().y + 4 > h.getPos().y && getPos().y + 16 < h.getPos().y + 20)
        //Nếu bóng va chạm với 1 lỗ
        {
            Mix_PlayChannel(-1, holeSfx, 0);//phát ra âm thanh holeSfx
            setWin(true);//đặt setWin thành true
            target.x = h.getPos().x ;
            target.y = h.getPos().y + 3;
            //đặt vị trí của bóng vào lỗ
        }
    }

    if (mousePressed && canMove)
    //khi bấm chuột biến canMove chuyển thành true
    {
        Mix_PlayChannel(-1, chargeSfx, 0);//phát âm thanh
        playedSwingFx = false;
        int mouseX = 0;
	    int mouseY = 0;
        //vị trí ban đầu của chuột đc lấy và lưu trữ
	    SDL_GetMouseState(&mouseX, &mouseY);//trạng thái chuột
        setInitialMousePos(mouseX, mouseY);//vị trí của chuột trên màn
    }
    if (mouseDown && canMove)//giữ chuột canMove chuyển true
    {
        
        int mouseX = 0;
	    int mouseY = 0;
        //lưu trữ vị trí ban đầu
	    SDL_GetMouseState(&mouseX, &mouseY);//trạng thái chuột
        setVelocity((mouseX - getInitialMousePos().x)/-150, (mouseY - getInitialMousePos().y)/-150);
        //hàm cập nhật vận tốc dựa theo vị trí ban đầu và vị trí hiện tại củ chuột 
        setLaunchedVelocity((mouseX - getInitialMousePos().x)/-150, (mouseY - getInitialMousePos().y)/-150);
        //hàm thiết lập vận tốc
        velocity1D = SDL_sqrt(SDL_pow(abs(getVelocity().x), 2) + SDL_pow(abs(getVelocity().y), 2));
        launchedVelocity1D = velocity1D;//gán vận tốc phóng

        points.at(0).setPos(getPos().x, getPos().y + 8 - 32);
        /*Dòng này truy cập vào phần tử đầu tiên của points sử dụng phương thức at() và
        thiết lập vị trí của nó bằng phương thức setPos().
        Vị trí được thiết lập bằng cách sử dụng phương thức getPos(), được giả định là trả về một đối tượng vector 2D hoặc tương tự với các tọa độ x và y.
        Tọa độ y được điều chỉnh bằng cách thêm 8 và trừ đi 32.*/
        points.at(0).setAngle(SDL_atan2(velocity.y, velocity.x)*(180/3.1415) + 90);
        /*tính góc của vector velocity so với trục hoành bằng hàm atan2(độ) sau đó cộng thêm 90 độ và lưu kết quả vào angle của phần tử đầu trong points sửu dụng hàm setAngle()*/

        dirX = velocity.x/abs(velocity.x);
        dirY = velocity.y/abs(velocity.y);
        //tính toán hướng đi của velocity trên mỗi trục 
        
        powerBar.at(0).setPos(getPos().x + 32 + 8, getPos().y - 32);
        powerBar.at(1).setPos(getPos().x + 32 + 8 + 4, getPos().y - 32 + 4 + 32 - 32*powerBar.at(1).getScale().y);
        //2 dòng trên để tính toán vị trí đặt của thanh lực
        //dòng 1 đặt cách bóng 32 đơn vị theo x và y cộng thêm 8 cho x để thanh lực ở bên phải của bóng
        //dòng 2 tại vị trí cách 32 theo x và y thì thêm 8 cho x và 4 cho y để thanh lực đưa lên góc phải trên của bóng
        if (velocity1D > 1)
        //đoạn code này để giới hạn giá trị của velocity1D max là 1
        {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }
        powerBar.at(1).setScale(1, velocity1D/1);
        //hàm sẽ cập nhật hiển thị thanh lực tùy theo khoảng cách mà người chơi kéo
    }
    else
    {
        if (!playedSwingFx)
        //kiểm tra xem đã phát âm thanh swing chưa
        {
            Mix_PlayChannel(-1, swingSfx, 0);
            //phát nhạc
            playedSwingFx = true;
            strokes++;
        }
        points.at(0).setPos(-64, -64);
        powerBar.at(0).setPos(-64, -64);
        powerBar.at(1).setPos(-64, -64);
        //làm cho các vật thể đếm không hiện trên màn hình
        canMove = false;//làm cho vật thể k di chuyển được
        setPos(getPos().x + getVelocity().x*deltaTime, getPos().y + getVelocity().y*deltaTime);
        //hàm cập nhật vị trí theo thời gian và vận tốc
        if (getVelocity().x > 0.0001 || getVelocity().x < -0.0001 || getVelocity().y > 0.0001 || getVelocity().y < -0.0001)
        //hàm tạo lực ma sát để dừng quả bóng
        {
            if (velocity1D > 0)
            {
                velocity1D -= friction*deltaTime;
            }
            else
            {
                velocity1D = 0;
            }
            velocity.x = (velocity1D/launchedVelocity1D)*abs(launchedVelocity.x)*dirX;
            velocity.y = (velocity1D/launchedVelocity1D)*abs(launchedVelocity.y)*dirY;


        }
        else
        //nếu bóng đứng yên 
        {
            setVelocity(0,0);//đặt lại tốc độ bóng
            int mouseX = 0;
	        int mouseY = 0;
            //đặt lại vị trí chuột
            SDL_GetMouseState(&mouseX, &mouseY);
            setInitialMousePos(mouseX, mouseY);
            //đặt vị trí ban đầu của chuột cho bóng
            canMove = true;//cho phép bóng có thể di chuyển
        }

        if (getPos().x + getCurrentFrame().w > 640/(2 - index))
        /*Nếu vị trí hiện tại của bóng cộng với chiều rộng của khung hình hiện tại lớn hơn 
        giá trị tính toán 640 chia cho 2 trừ đi giá trị biến index, tức là vượt quá giới hạn 
        bên phải của màn hình, thì đối tượng sẽ di chuyển ngược lại theo trục x với vận tốc
        đảo chiều và cập nhật lại hướng di chuyển của đối tượng theo trục x (dirX) là âm*/
        {
            setVelocity(-abs(getVelocity().x), getVelocity().y);
            dirX = -1;
        }
        else if (getPos().x < 0 + (index*320))
        //hàm kiểm tra va chạm vs giới hạn phải trái của màn hình nếu va chạm vận tốc sẽ được đặt là giá trị tuyệt đối của vạn tốc hiện tại với chiều ngược lại và hướng cũng đc thay đổi ngược lại
        {
            setVelocity(abs(getVelocity().x), getVelocity().y);
            dirX = 1;
        }
        else if (getPos().y + getCurrentFrame().h > 480)
        //kiểm tra bóng có va chạm với đáy màn hình không
        {
            setVelocity(getVelocity().x, -abs(getVelocity().y));
            dirY = -1;
        }
        else if (getPos().y < 0)
        //kiểm tra va chạm với bên trên màn hình
        {
            setVelocity(getVelocity().x, abs(getVelocity().y));
            dirY = 1;
        }

        for (Tile& t : tiles)
        //vòng lặp duyệt từng phần tử trong mảng tiles,kiểm tra va chạm giữa bóng và vật thể
	    { 
		    float newX = getPos().x + getVelocity().x*deltaTime;
            float newY = getPos().y;
            if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h - 3)
            {
                setVelocity(getVelocity().x*-1, getVelocity().y);
                dirX *= -1;
            }

            newX = getPos().x;
            newY = getPos().y + getVelocity().y*deltaTime;
            if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h - 3)
            {
                setVelocity(getVelocity().x, getVelocity().y*-1);
                dirY *= -1;
            }
	    }
    }
    
}