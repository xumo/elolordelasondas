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
    maxNodos    = 1024;
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
	tiempo		= ofGetElapsedTimeMillis();
	tiempoDos		= ofGetElapsedTimeMillis();
	modelUno.loadModel("dodecahedron.dae",false);
	modelDos.loadModel("icosahedron.dae", false);
	modelTres.loadModel("octahedron.dae",false);
	modelCuatro.loadModel("tetrahedron.dae",false);
	
	colorUno = ofColor(200,10,10);
	colorDos = ofColor(30,30,200);
	colorTres = ofColor(10,55,0);
	colorCuatro = ofColor(200,140,10);

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
			float peso = nod->getPeso() == 0 ? 0.002 :  log10f(0.002 * nod->getPeso());
			ofScale(peso,peso, peso);

            if (nod->getTipo()==1)
            {
				ofSetColor(colorUno);
				vboCuatro.draw();
			}else if(nod->getTipo() == 2)
            {
				ofSetColor(colorDos);
				vboDos.draw();  
			}else
            {
				ofSetColor(colorUno);
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
			float peso = nod->getPeso() == 0 ? 0.002 :  log10f(0.002 * nod->getPeso());
			ofScale(peso,peso, peso);

            if (nod->getTipo()==1)
            {
               //ofSphere(nod->x, nod->y, nod->z,0.05 + nod->peso*0.0002);
				ofSetColor(colorCuatro);
				vboDos.draw();
			}else if(nod->getTipo() == 2)
            {
				ofSetColor(colorTres);
				vboTres.draw();  
			}else
            {
				ofSetColor(colorCuatro);
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

int xuTransitoVertical::setVivo(std::vector<xuNodo> * vec_nodos,int in_tipo, float in_peso, ofPoint in_pos, ofPoint in_vel)
{
	for(std::vector<xuNodo>::iterator nod = vec_nodos->begin();nod!= vec_nodos->end();nod++)
    {
		if(!nod->getVivo())
		{
			nod->setBounds(minX, maxX, minY, maxY, minZ, maxX);
			nod->setNodo(in_pos, in_vel, in_peso, in_tipo, true);
			return 1;
		}
	}

	return 0;
}

void xuTransitoVertical::addNodo(int in_tipo, float in_peso, bool arriba)
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
			addCount += setVivo(&nodosU, in_tipo, in_peso, ofPoint(ofRandom(-7.0, 7.0), 14, ofRandom(-9,0)),ofPoint(velX,-velY, velZ));

			cout<<"::: Arriba:::"<<endl;
           
        }
            
    }else
    {
        if(addCountD<maxCount && temp2<timeMax)
        {
            //nodosD.push_back(nodo);
			cout<<"::: Abajo:::"<<endl;
			addCountD += setVivo(&nodosD, in_tipo, in_peso, ofPoint(ofRandom(-7.0, 7.0), -1, ofRandom(-9,0)),ofPoint(velX,velY, velZ));
            
        }
    }

}



