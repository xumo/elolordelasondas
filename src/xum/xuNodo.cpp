#include "xuNodo.h"

xuNodo::xuNodo()
{
	x = 0;
	y = 0;
	z = 0;
	peso = 0;
	tipo = 0;
	pos = ofPoint(0);
	vel = ofPoint(0);
	vivo = false;
	bound_x1 = 0;
	bound_x2 = 0;
	bound_y1 = 0;
	bound_y2 = 0;
	bound_z1 = 0;
	bound_z2 = 0;

}

xuNodo::~xuNodo()
{
}

void xuNodo::update()
{
	if(vivo)
	{
		pos +=vel;
		vivo = inBounds();
	}
}

void xuNodo::setNodo(ofPoint in_pos, ofPoint in_vel,  float in_peso, int in_tipo, bool in_vivo)
{
	pos = in_pos;
	vel = in_vel;
	peso = in_peso;
	tipo = in_tipo;
	vivo = in_vivo;
}

void xuNodo::setVel(ofPoint in_vel)
{
	vel = in_vel;

}

void xuNodo::reset()
{
	x = 0;
	y = 0;
	z = 0;
	peso = 0;
	tipo = 0;
	pos =  ofPoint(0);

}



int xuNodo::getTipo()
{
	return tipo;
}

float xuNodo::getPeso()
{
	return peso;
}

bool xuNodo::getVivo()
{
	return vivo;
}

void xuNodo::setBounds(float x1, float x2, float y1, float y2, float z1, float z2)
{
	bound_x1 = x1;
	bound_x2 = x2;
	bound_y1 = y1;
	bound_y2 = y2;
	bound_z1 = z1;
	bound_z2 = z2;
}

bool xuNodo::inBounds()
{
	if (pos.x < bound_x1 || pos.x > bound_x2 )
	{
		return false;
	}

	if (pos.y < bound_y1 || pos.y > bound_y2)
	{
		return false;
	}

	if (pos.z < bound_z1 || pos.z > bound_z2)
	{
		return false;
	}


	return true;
}