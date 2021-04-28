#ifndef JUEGO_H
#define JUEGO_H


#include "SFML\Graphics.hpp"
#include "Animation.h"
#include "Afichmation.h"

using namespace sf;
using namespace std;

class Juego
{
public:
	Juego(Vector2i resol, string titulo);
	void gameloop();
	void procesar_eventos();
	void cargar_recursos();
	void dibujar();	
private:
	RenderWindow* wnd;
	Event* evento;
	Afichmation* anim;	
	Texture *text_background;
	Sprite *spr_background;
	Texture *text_bloque;
	Sprite *spr_bloque;
	bool teclaSaltoPresionada = false;
	bool enAscenso = false;
	bool saltoEnProceso = true;
	bool sentidoDerecha = false;
};

#endif
