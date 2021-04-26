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
};

#endif
