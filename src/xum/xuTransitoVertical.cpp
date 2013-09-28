//
//  xuTransitoVertical.cpp
//  Sniffer
//
//  Created by Rodrigo Torres González on 03/07/13.
//
//

#include "xuTransitoVertical.h"

xuTransitoVertical::xuTransitoVertical()
{
    tiempo = ofGetElapsedTimeMillis();
}
xuTransitoVertical::~xuTransitoVertical()
{
    
}

void xuTransitoVertical::init()
{
    maxNodos    = 2000;
    velX        = 0;
    velY        = 0.01;
    velZ        = 0;
	minX		= -8;
	maxX		= 8;
    maxY        = 15.0;
    minY        = - 2.0;
	minZ		= -10;
	maxZ		= 1;
    addCount    = 0;
    addCountD   = 0;
    maxCount    = 50;
    timeMax     = 700;
	escala		= 1.0;
	tiempo		= ofGetElapsedTimeMillis();
	tiempoDos		= ofGetElapsedTimeMillis();
	modelUno.loadModel("solidos/dodecahedron.dae",false);
	modelDos.loadModel("solidos/icosahedron.dae", false);
	modelTres.loadModel("solidos/octahedron.dae",false);
	modelCuatro.loadModel("solidos/tetrahedron.dae",false);
	
	colorUno = ofFloatColor(ofColor(200,10,10));
	colorDos =  ofFloatColor(ofColor(30,30,200));
	colorTres =  ofFloatColor(ofColor(10,55,0));
	colorCuatro =  ofFloatColor(ofColor(200,140,10));
	colorCinco = ofFloatColor( ofColor(255,0,255));
	colorSeis = ofFloatColor( ofColor(0,255,255));

	colores.push_back(&colorUno);
	colores.push_back(&colorDos);
	colores.push_back(&colorTres);
	colores.push_back(&colorCuatro);
	colores.push_back(&colorCinco);
	colores.push_back(&colorSeis);

	vboUno = modelUno.getMesh(0);
	vboDos = modelDos.getMesh(0);
	vboTres = modelTres.getMesh(0);
	vboCuatro = modelCuatro.getMesh(0);

	nodosD.assign(maxNodos, xuNodo());
	nodosU.assign(maxNodos, xuNodo());


}

void xuTransitoVertical::update()
{
	for(std::vector<xuNodo>::iterator nod = nodosD.begin();nod!=nodosD.end();nod++)
    {
		nod->update();
    }

	for(std::vector<xuNodo>::iterator nod = nodosU.begin();nod!=nodosU.end();nod++)
    {
		nod->update();
    }
}

void xuTransitoVertical::draw()
{
	ofPushMatrix();
	for(std::vector<xuNodo>::iterator nod = nodosU.begin();nod!=nodosU.end();nod++)
    {
		if(nod->getTipo()!=NULL && nod->getVivo())
        {
			ofPushMatrix();
			ofTranslate(nod->pos);
			//ofRotateX(45);
			ofRotateY(160);
			float peso = nod->getPeso() == 0 ? 0.002 * escala :  log10f(0.002 * escala * nod->getPeso());
			ofScale(peso,peso, peso);

            if (nod->getTipo()==1)
            {
				ofSetColor(*tablaColor[nod->direccion]);
				vboCuatro.draw();
			}else if(nod->getTipo() == 2)
            {
				ofSetColor(*tablaColor[nod->direccion]);
				vboDos.draw();  
			}else
            {
				ofSetColor(*tablaColor[nod->direccion]);
				vboTres.draw();   
            }
            
			ofPopMatrix();
        }      
    }

	for(std::vector<xuNodo>::iterator nod = nodosD.begin();nod!=nodosD.end();nod++)
    {
		if(nod->getTipo()!=NULL && nod->getVivo())
        {
			ofPushMatrix();
			ofTranslate(nod->pos);
			float peso = nod->getPeso() == 0 ? 0.002 * escala :  log10f(0.002 * escala * nod->getPeso());
			ofScale(peso,peso, peso);

            if (nod->getTipo()==1)
            {
               //ofSphere(nod->x, nod->y, nod->z,0.05 + nod->peso*0.0002);
				ofSetColor(*tablaColor[nod->direccion]);
				vboDos.draw();
			}else if(nod->getTipo() == 2)
            {
				ofSetColor(*tablaColor[nod->direccion]);
				vboTres.draw();  
			}else
            {
				ofSetColor(*tablaColor[nod->direccion]);
				vboCuatro.draw();   
            }
            
			ofPopMatrix();
        } 
    }
    
	ofPopMatrix();
   
    
}

std::vector<xuNodo> * xuTransitoVertical::getNodos()
{
    return &nodosU;
}

int xuTransitoVertical::setVivo(std::vector<xuNodo> * vec_nodos,int in_tipo, float in_peso, ofPoint in_pos, ofPoint in_vel, string direccion)
{
	for(std::vector<xuNodo>::iterator nod = vec_nodos->begin();nod!= vec_nodos->end();nod++)
    {
		if(!nod->getVivo())
		{
			actualizarTabla(direccion);
			nod->direccion = direccion;
			nod->setBounds(minX, maxX, minY, maxY, minZ, maxX);
			nod->setNodo(in_pos, in_vel, in_peso, in_tipo, true);

			

			return 1;
		}
	}

	return 0;
}

void xuTransitoVertical::addNodo(int in_tipo, float in_peso, bool arriba,string direccion)
{
	float temp = ofGetElapsedTimeMillis()- tiempo;
	float temp2 = ofGetElapsedTimeMillis() - tiempoDos;

	if(temp>timeMax)
    {
        tiempo = ofGetElapsedTimeMillis();
        if(addCount>=maxCount)
        {
            addCount = 0;
        }     
    }

	if(temp2 > timeMax)
	{
		tiempoDos = ofGetElapsedTimeMillis();
		if(addCountD>=maxCount)
        {
            addCountD = 0;
        }
	}

	if(!arriba)
    {
        if(addCount<maxCount && temp<timeMax)
        {
            //nodosU.push_back(nodo);
			addCount += setVivo(&nodosU, in_tipo, in_peso, ofPoint(ofRandom(-7.0, 7.0), 14, ofRandom(-9,0)),ofPoint(velX,-velY, velZ), direccion);

			cout<<"::: Arriba:::"<<endl;
           
        }
            
    }else
    {
        if(addCountD<maxCount && temp2<timeMax)
        {
            //nodosD.push_back(nodo);
			cout<<"::: Abajo:::"<<endl;
			addCountD += setVivo(&nodosD, in_tipo, in_peso, ofPoint(ofRandom(-7.0, 7.0), -1, ofRandom(-9,0)),ofPoint(velX,velY, velZ), direccion);
            
        }
    }

}

void xuTransitoVertical::actualizarTabla(string dire)
{

	if(tablaColor.find(dire) == tablaColor.end())
	{
		//Todavia no hay ese color
		tablaColor[dire] =  colores[floor(ofRandom(colores.size()-1))];
	}

}

