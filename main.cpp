#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int N=30,M=20; // so luong hinh vuong trong cua so = 30x20
int size=16; // kich thuoc o vuong = 16.16
int chieuRong = size*N; // chieu rong cua cua so
int chieuCao = size*M; // chieu cao cua cua so

int dir,num=4; // huong cua Ran = chieu dai cua ran tinh theo o vuong

struct Ran 
{ int x,y;}  s[100]; // chieu dai toi da cua Ran la 199, mang de luu tru vi tri tung phan cua Ran

struct thucAn
{ int x,y;} f; // vi tri thuc an cua Ran

void Tick() // ham di chuyen cua Ran
 {
 	//di chuyen tung buoc cua Ran
    for (int i=num;i>0;--i)
     {s[i].x=s[i-1].x; s[i].y=s[i-1].y;}
// thay doi huong cua Ran
    if (dir==0) s[0].y+=1;// xuong
    if (dir==1) s[0].x-=1;// trai
    if (dir==2) s[0].x+=1;// phai  
    if (dir==3) s[0].y-=1;// len   

    if ((s[0].x==f.x) && (s[0].y==f.y)) // Ran an thuc an
     {num++; // tang kich thuoc len 1 o vuong sau khi an
	 f.x=rand()%N; 
	 f.y=rand()%M;
	 }
// Ran roi khoi cua so va den tu phia doi dien
    if (s[0].x>N) s[0].x=0;  if (s[0].x<0) s[0].x=N;
    if (s[0].y>M) s[0].y=0;  if (s[0].y<0) s[0].y=M;
 
    for (int i=1;i<num;i++)
     if (s[0].x==s[i].x && s[0].y==s[i].y)  num=i;// Ket thuc game khi Ran cham vao chinh no
 }

int main()
{  
    srand(time(0)); // ham thoi gian ngau nhien 

    RenderWindow window(VideoMode(chieuRong, chieuCao), "Ran San Moi");

    Texture t1,t2;
    t1.loadFromFile("images/white.png"); // Nen
    t2.loadFromFile("images/red.png"); // Ran va thuc an

    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Clock clock;
    float timer=0, delay=0.1;

    f.x=10;
    f.y=10; 
    
    while (window.isOpen()) // buffer window mo/ window an
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time; 

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)      
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) dir=1;   
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir=2;    
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir=3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir=0;

        if (timer>delay) {timer=0; Tick();}// sau moi 0.05 giay gia tri cua Ran va Thuc an duoc cap nhat

   // draw  //
    window.clear();

    for (int i=0; i<N; i++) 
      for (int j=0; j<M; j++) 
        { sprite1.setPosition(i*size, j*size);  window.draw(sprite1); } // nen

    for (int i=0;i<num;i++)
        { sprite2.setPosition(s[i].x*size, s[i].y*size);  window.draw(sprite2); }// tao Ran
   
    sprite2.setPosition(f.x*size, f.y*size);  window.draw(sprite2);//  tao thuc an

    window.display();
    }

    return 0;
}
