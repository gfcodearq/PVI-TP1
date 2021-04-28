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
	cargar_recursos();//esto debería llamarse en el constructor
	while (wnd->isOpen())
	{
		anim->Update();
		procesar_eventos();
		dibujar();
	}
}

void Juego::procesar_eventos()
{
	//había doble pollEvent (es una cola de eventos de ventana, no se requiere hacer doble control de la cola)
		while(wnd->pollEvent(*evento)) 
		{
			if(evento->type == Event::Closed)
				wnd->close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			anim->FlipX(false);
			anim->setPosition(anim->getPosition().x - 1, anim->getPosition().y);
			if (!saltoEnProceso)
				anim->Play("walking");
			else
				anim->Play("jump");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			anim->FlipX(true);
			anim->setPosition(anim->getPosition().x + 1, anim->getPosition().y);
			if (!saltoEnProceso)
				anim->Play("walking");
			else
				anim->Play("jump");
		}
		else if (saltoEnProceso) {
			anim->Play("jump");
		}
		else {
			anim->Play("idle");
		}		
}

void Juego::cargar_recursos()
{
	//cargo textura del fondo
	text_background = new Texture;
	text_background->loadFromFile("mundo_fondo.jpg");
	spr_background = new Sprite();
	spr_background->setTexture(*text_background);
	//cargo textureas del bloque
	text_bloque = new Texture;
	text_bloque->loadFromFile("bloque_pared.png");
	spr_bloque = new Sprite();
	spr_bloque->setTexture(*text_bloque);
	spr_bloque->setPosition(300,210);
	
	anim = new Afichmation ("spritesheet.png", true, 208, 249); 	
	anim->Add("idle", {0, 1, 2, 1, 0}, 8, true);
	anim->Add("walking", { 3, 4, 5, 6, 7, 8, 9, 10, 11, 10, 9, 8, 7, 6, 5, 4 }, 12, true);
	anim->Add("run", {3, 4, 5, 4}, 8, true);	
	anim->Add("jump", { 12, 13, 14 }, 8, false);
	anim->Add("collide", { 15 }, 8, false);	
	anim->Play("idle");	
	anim->setScale(Vector2f(.5f, .5f));	
	anim->setPosition(50,460);
}

void Juego::dibujar()
{
	wnd->clear(Color(255,255,255,255));	
	wnd->draw(*spr_background);
	wnd->draw(*spr_bloque);
	wnd->draw(*anim);	
	wnd->display();
}

