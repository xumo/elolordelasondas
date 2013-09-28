#include "xuMensaje.h"


xuMensaje::xuMensaje(string msg)
{
	//xuMensaje();
	pos.x = 100;
	pos.y = 100;
	vivo = true;
	tiempo = 0;
	tiempoMax = ofRandom(10000);
	etiqueta.loadFont("verdana.ttf", 30, true, true);
	etiqueta.setLineHeight(34.0f);
	etiqueta.setLetterSpacing(1.035);
	mensaje = msg;
	cout<<"iniciando con "<<msg<<endl;
}

xuMensaje::xuMensaje()
{
	mensaje = "";
	pos.x = 145;
	pos.y = 150;
	ofSet.x = 0;
	ofSet.y = 0;
	escala = 1;
	vivo = true;
	tiempo = 0;
	tiempoMax = ofRandom(10000);
	etiqueta.loadFont("verdana.ttf", 8, true, true);
	etiqueta.setLineHeight(34.0f);
	etiqueta.setLetterSpacing(1.035);
	
}

void xuMensaje::update()
{
	if(vivo)
	{
		if(ofGetElapsedTimeMillis() - tiempo > tiempoMax)
		{
			vivo =  false;
			cout<<"matar a mensaje"<<endl;
		}
	}
}

void xuMensaje::draw()
{
	if(vivo)
	{
		ofPushMatrix();
		ofScale(escala, escala, escala);
		ofTranslate(ofSet);
		etiqueta.drawString(mensaje,pos.x,pos.y);
		ofPopMatrix();
	}

}

void xuMensaje::setVivo(bool si)
{
	vivo = si;
	tiempo =  ofGetElapsedTimeMillis();
}

bool xuMensaje::getVivo()
{
	return vivo;
}

void xuMensaje::setMensaje(string msg)
{
	mensaje =  msg;
	vivo =  true;
}

void xuMensaje::setPos(ofPoint nPos)
{
	pos = nPos;
	pos.x -=100;

}

xuMensaje::~xuMensaje()
{
}