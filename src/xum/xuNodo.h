#pragma once
#include "ofMain.h"

class xuNodo
{
public:
	xuNodo();
	~xuNodo();

	void update();
	void setNodo(ofPoint in_pos,ofPoint in_vel, float in_peso, int in_tipo, bool vivo);
	void setVel(ofPoint in_vel);
	void reset();
	ofPoint  getPos();
	int		getTipo();
	float	getPeso();
	bool	getVivo();
	bool	inBounds();
	void	setBounds(float x1, float x2, float y1, float y2, float z1, float z2);

	ofPoint pos;

	string direccion;
private:
	float	x;
	float	y;
	float	z;
	float	peso;
	float	escala;
	int		tipo;
	bool	vivo;
	
	ofPoint vel;
	float	bound_x1, bound_x2, bound_y1, bound_y2, bound_z1, bound_z2;


};

