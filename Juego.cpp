#include "Juego.h"

using namespace std;
using namespace sf;

Juego::Juego(Vector2i resol, string tit)
{
	wnd = new RenderWindow(VideoMode(800, 600), tit);
	wnd->setFramerateLimit(60);		
	evento = new Event;	
	event = new Event;
	gameloop();
}

void Juego::gameloop()
{
	cargar_recursos();//esto debería llamarse en el constructor
	controlar_salto(event);
	while (wnd->isOpen())
	{
		anim->Update();
		procesar_eventos();
		
		controlar_desplazamiento();			
		dibujar();
	}
}

void Juego::procesar_eventos()
{
	
	//había doble pollEvent (es una cola de eventos de ventana, no se requiere hacer doble control de la cola)
		while(wnd->pollEvent(*evento)) {
			if(evento->type == Event::Closed)
				wnd->close();
		}		
		//Se chequea si se presionó la tecla de salto y si el proceso aún no inició
		if (teclaSaltoPresionada && !saltoEnProceso) {
			saltoEnProceso = true;
			enAscenso = true;
		}
//		
		//Bloque que maneja el salto y su descenso a través del eje 'y'.
		if (saltoEnProceso) {
			
			//Se controla cuando se llega al maximo de altura de salto
			if (anim->getPosition().y <= POSICION_TERRENO_Y - MAX_ASCENSO_SALTO_Y) {
				enAscenso = false;
			}
			
			//Se ejecuta el movimiento hacia arriba o abajo en eje 'y'
			if (enAscenso) {
				anim->setPosition(anim->getPosition().x, anim->getPosition().y - 1);
			}
			else {
				anim->setPosition(anim->getPosition().x, anim->getPosition().y + 1);
			}
			
			//Se controla cuando el personaje vuelve a tocar el eje 'y' del terreno
			if (anim->getPosition().y >= POSICION_TERRENO_Y) {
				saltoEnProceso = false; //Permite que finalize un ciclo de salto y que comienze uno nuevo
				anim->setPosition(anim->getPosition().x, POSICION_TERRENO_Y); //Se fuerza la posicion del personaje en la linea de terreno
			}
	
		}
}

void Juego::cargar_recursos()	
{
	//Carga el fondo 
	tex_background = new Texture;
	tex_background->loadFromFile("mundo_fondo.jpg");
	spr_background = new Sprite;
	spr_background->setTexture(*tex_background);
	
	anim = new Afichmation ("spritesheet.png", true, 208, 249); 
	//Afichmation anim("spritesheet.png", true, 26, 30);
	anim->Add("idle", {0, 1, 2, 1, 0}, 8, true);
	anim->Add("run", {3, 4, 5, 4}, 8, true);
	anim->Add("falls of", {6}, 8, true);
	anim->Add("stairs", {7, 8}, 8, true);
	anim->Add("jump", { 12,13, 14 }, 8, true);
	anim->Add("collide", { 15 }, 8, false);	
	anim->Play("idle");	
	anim->setScale(Vector2f(.5f, .5f));
	anim->setPosition(50,460);
}


void Juego::dibujar()
{
	wnd->clear(Color(255,255,255,255));	
	wnd->draw(*spr_background);
	wnd->draw(*anim);
	wnd->display();
}

void Juego::controlar_salto(Event *event)
{
	if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Space) {
		teclaSaltoPresionada = true;
	}
	else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Space) {
		teclaSaltoPresionada = false;
	}
}

void Juego::controlar_desplazamiento()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		anim->FlipX(false);
		anim->setPosition(anim->getPosition().x - 1, anim->getPosition().y);
		if (!saltoEnProceso) //si no esta saltando que pueda caminar caso contrario que siga saltando
			anim->Play("run");
		else
			anim->Play("jump");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		anim->FlipX(true); 
		anim->setPosition(anim->getPosition().x + 1, anim->getPosition().y);
		if (!saltoEnProceso) //si no esta saltando que pueda caminar caso contrario que siga saltando
			anim->Play("run");
		else
			anim->Play("jump");
	}
	else if (saltoEnProceso) { // si el salto esta en proceso que salte sino que siga como estaba
		anim->Play("jump");
	}
	else {
		anim->Play("idle");
	}
//	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//	{
//		anim->Play("jump");
//		anim->move(0,-10);
//	}
}
