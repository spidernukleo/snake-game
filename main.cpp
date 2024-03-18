#include "funzioni.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

int diff=0, pos=0;

void gioco(){
	int size=1, game=1, dir, nextdir, win=0;
	float speed=0.1;
	//struttura dello snake, con posizione iniziale al centro
	struct {
		int x=250;
		int y=250;
	}p[144];
	//creazione finestra e creazione vari elementi 
	RenderWindow finestra(VideoMode(600,600), "Snake Game!", Style::Close);
	Event event;
	Sprite snake, apple;
	Texture restart;
	restart.loadFromFile("Resources/restart.png");
	Sprite button1;
	button1.setTexture(restart);
	Texture tx1, tx2;
	tx1.loadFromFile("Resources/snake.png");
	tx2.loadFromFile("Resources/apple.png");
	snake.setTexture(tx1);
	apple.setTexture(tx2);
	snake.setColor(Color::Blue);
	apple.setPosition(50*(rand()%12), 50*(rand()%12));
	Font f1;
	f1.loadFromFile("Resources/COMIC.TTF");
	Text text2;
	text2.setFont(f1);
	Text text1;
	nextdir=rand()%4;
	text1.setFont(f1);
	text1.setPosition(210,250);
	text2.setString("Premi il bottone per ricominciare");
	button1.setPosition(250, 330);
	text2.setPosition(70,280);
	text1.setString("Points: 1");
	SoundBuffer wav1;
	wav1.loadFromFile("Resources/crunch.wav");
	Sound crunch;
	crunch.setBuffer(wav1);
	//gestire gli eventi
	while(finestra.isOpen()){
		Vector2f pos = finestra.mapPixelToCoords(Mouse::getPosition(finestra));
		while(finestra.pollEvent(event)){
			if(event.type==Event::Closed)
				finestra.close();
			if(event.type==Event::KeyPressed){
				//controllare il tasto premuto per la direzione
				if(event.key.code == Keyboard::Down && dir!=1)
					nextdir=0;
				if(event.key.code == Keyboard::Up && dir!=0)
					nextdir=1;
				if(event.key.code == Keyboard::Right && dir!=3)
					nextdir=2;
				if(event.key.code == Keyboard::Left && dir!=2) //AGGGIUNGERE QUALCHE FEATURE E POI FINITO
					nextdir=3;
				if(event.key.code == Keyboard::Escape)
					finestra.close();
				if(event.key.code == Keyboard::Return)
					if(game==0){
						finestra.close();
						menu();
					}
			}
			if(event.type==Event::MouseButtonPressed){
				if(button1.getGlobalBounds().contains(pos)){
					game=1;
					finestra.close();
					menu();
				}
			}
		}
		finestra.clear(Color(118, 209, 48));
		if(game==1){
			//applica la posizione a tutti gli elementi dell'array cioe lo snake
			for(int i=size;i>0;i--){ 
				p[i].x=p[i-1].x;
				p[i].y=p[i-1].y;
			}
			//handle movment in base alla direzione
			if(nextdir==0) p[0].y+=50;
			if(nextdir==1) p[0].y-=50;
			if(nextdir==2) p[0].x+=50;
			if(nextdir==3) p[0].x-=50;
			dir=nextdir;
			//gestire bordi e difficoltà
			if(diff==0){
				if(p[0].x>=600) p[0].x=0; 
				if(p[0].y>=600) p[0].y=0;
				if(p[0].x<0) p[0].x=600;
				if(p[0].y<0) p[0].y=600;
			}
			if(diff==1){
				if(p[0].x>=600 || p[0].y>=600 || p[0].x<0 || p[0].y<0){
					game=0;
					win=0;
				}
			}
			//gestire mela e allungamento serpente
			Vector2f posmela=apple.getPosition(); //prendi posizione della mela per poi vedere x e y
			if(posmela.y==p[0].y&&posmela.x==p[0].x){
				crunch.play();
				int xmelarandom=50*(rand()%12), ymelarandom=50*(rand()%12);
				size++;
				for(int i=0;i<size;i++)
					if(p[i].x==xmelarandom&&p[i].y==ymelarandom){
						xmelarandom=50*(rand()%12);
						ymelarandom=50*(rand()%12);
					}
				apple.setPosition(xmelarandom, ymelarandom);
				finestra.setTitle("Points: "+std::to_string(size));
			}
			//disegna il serpente nella sua posizione per ogni elemento i e la mela
			for(int i=0;i<size;i++){
				snake.setPosition(p[i].x, p[i].y);
				finestra.draw(snake);
			}
			finestra.draw(apple);
			for(int i=1;i<size;i++)
				if(p[0].x==p[i].x&&p[0].y==p[i].y){
					game=0;
					sleep(seconds(1));
				}
			//controlla se vinto
			if(size==144){
				game=0;
				win=1;
			}
			//gestisci fps
			finestra.display();
			sleep(seconds(speed));
		}
		if(game==0){
			if(win==0) text1.setString("HAI PERSO :(");
			if(win==1) text1.setString("HAI VINTO :)");
			finestra.draw(text1);
			finestra.draw(text2);
			finestra.draw(button1);
			finestra.display();
		}
	}	
}

void menu(){
	RenderWindow menu(VideoMode(300,300), "Snake Game!", Style::Close);
	Event event;
	//loading textures
	Texture tx1, tx2, tx3, tx4, tx5;
	tx1.loadFromFile("Resources/text1.png");
	tx2.loadFromFile("Resources/text2.png");
	tx3.loadFromFile("Resources/text3.png");
	tx4.loadFromFile("Resources/text4.png");
	tx5.loadFromFile("Resources/text5.png");
	//making sprites and adding textures
	Sprite s1, s2, s3, s4, s5;
	s1.setTexture(tx1);
	s2.setTexture(tx2);
	s3.setTexture(tx3);
	s4.setTexture(tx4);
	s5.setTexture(tx5);
	if(diff==0){
		s4.setColor(Color::Red);
		s5.setColor(Color::White);
	}
	if(diff==1){
		s5.setColor(Color::Red);
		s4.setColor(Color::White);
	}
	//setting sprites position
	s1.setPosition(50, 50);
	s2.setPosition(120, 100);
	s3.setPosition(85, 220);
	s4.setPosition(20, 150);
	s5.setPosition(200, 150);
	while(menu.isOpen()){
		Vector2f pos = menu.mapPixelToCoords(Mouse::getPosition(menu)); //ottieni posizione mouse in coordinate ad ogni frame
		while(menu.pollEvent(event)){
			if(event.type==Event::Closed)
				menu.close();
			//check ogni click se sta nei vari boottoni
			if(event.type==Event::MouseButtonPressed){
				if(s1.getGlobalBounds().contains(pos)){
					menu.close();
					gioco();
				}
				if(s2.getGlobalBounds().contains(pos)) menu.close();
				if(s4.getGlobalBounds().contains(pos)){
					s4.setColor(Color::Red);
					s5.setColor(Color::White);
					diff=0;
				}
				if(s5.getGlobalBounds().contains(pos)){
					s5.setColor(Color::Red);
					s4.setColor(Color::White);
					diff=1;
				}
			}
			if(event.type==Event::KeyPressed){
				if(event.key.code==Keyboard::Escape){
					menu.close();
				}
				if(event.key.code==Keyboard::Left){
					diff=0;
					s4.setColor(Color::Red);
					s5.setColor(Color::White);
				}
				if(event.key.code==Keyboard::Right){
					s4.setColor(Color::White);
					s5.setColor(Color::Red);
					diff=1;
				}
				if(event.key.code==Keyboard::Return){
					menu.close();
					gioco();					
				}
			}
		}
		menu.clear();
		//drawing and displaying things
		menu.draw(s1);
		menu.draw(s2);
		menu.draw(s3);
		menu.draw(s4);
		menu.draw(s5);
		//displaya tutto nella finestra
		menu.display();
	}
}


int main(){
	menu();
}
