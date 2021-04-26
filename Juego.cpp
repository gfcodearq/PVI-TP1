#include "Juego.h"

using namespace std;
using namespace sf;

Juego::Juego(Vector2i resol, string tit)
{
	wnd = new RenderWindow(VideoMode(800, 600), tit);
	wnd->setFramerateLimit(60);		
	evento = new Event;	
	gameloop();
}

void Juego::gameloop()
{
	while (1)
	{
		cargar_recursos();
		procesar_eventos();
		dibujar();
	}
}

void Juego::procesar_eventos()
{
	while (wnd->pollEvent(*evento))
	{
		Event e;
		while(wnd->pollEvent(e)) {
			if(e.type == Event::Closed)
				wnd->close();	
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				anim->Play("run");
				anim->FlipX(true);
				anim->move(-2, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				anim->Play("run");
				anim->FlipX(false);
				anim->setPosition(anim->getPosition().x + 2, anim->getPosition().y);
			}
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				anim->Play("stairs");
				anim->FlipY(true);
				anim->setPosition(anim->getPosition().x, anim->getPosition().y - 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				anim->Play("falls of");
				anim->FlipY(false);
				anim->setPosition(anim->getPosition().x, anim->getPosition().y + 4);
			}
			if (Keyboard::isKeyPressed(Keyboard::I)) {
				anim->Play("idle");
			}
			if (Keyboard::isKeyPressed(Keyboard::Z)) {
				anim->setScale(anim->getScale().x + 1.f, anim->getScale().x + 1.f);
			}
			if (Keyboard::isKeyPressed(Keyboard::X)) {
				anim->setScale(anim->getScale().x - 1.f, anim->getScale().x - 1.f);
			}
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				anim->setRotation(anim->getRotation() + 1.f);
			}
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
			anim->setRotation(anim->getRotation() - 1.f);
			}
		}		
	}
}

void Juego::cargar_recursos()
{
	anim = new Afichmation ("spritesheet.png", true, 26, 30); 
	//Afichmation anim("spritesheet.png", true, 26, 30);
	anim->Add("idle", {0, 1, 2, 1, 0}, 8, false);
	anim->Add("run", {3, 4, 5, 4}, 8, true);
	anim->Add("falls of", {6}, 8, true);
	anim->Add("stairs", {7, 8}, 8, true);
	anim->Play("idle");	
	anim->setScale(Vector2f(2.f, 2.f));	
}

void Juego::dibujar()
{
	anim->Update();
	wnd->clear(Color(255,255,255,255));	
	anim->Draw();
	wnd->display();
}

