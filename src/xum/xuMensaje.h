#pragma once
#include "ofMain.h"
#include <string>

using namespace std;

class xuMensaje
{
public:
	xuMensaje();
	xuMensaje(string msg);
	~xuMensaje();

	void	update();
	void	draw();

	void setVivo(bool si);
	void setMensaje(string msg);
	bool getVivo();
	void setPos(ofPoint nPos);
	
	ofPoint		pos, ofSet;
	float		escala;

private:
	float		tiempo;
	int			tiempoMax;
	
	bool vivo;
	string	mensaje;
	ofTrueTypeFont	etiqueta;
};

