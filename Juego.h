#ifndef JUEGO_H
#define JUEGO_H


#include "SFML\Graphics.hpp"
#include "Animation.h"
#include "Afichmation.h"

//Declaracion de constantes
const int POSICION_TERRENO_Y = 460;
const int MAX_ASCENSO_SALTO_Y = 200;

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
	void controlar_salto(Event *event);
	void controlar_desplazamiento();
private:
	RenderWindow* wnd;
	Event* evento;
	Event* event;
	Afichmation* anim;	
	Texture* tex_background;
	Sprite* spr_background;
	Texture* tex_bloque;
	Sprite* spr_bloque;
	bool teclaSaltoPresionada = false; //boleano que verifica si la tecla de salto esta activada
	bool enAscenso = false; //booleano para verificar que el personaje sube
	bool saltoEnProceso = true; //booleano para verificar que el salto esta en proceso
	bool sentidoDerecha = false; //boleano para verificar si va en sentido derecha
};

#endif
