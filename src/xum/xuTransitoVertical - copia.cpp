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
    maxNodos    = 256;
    velX        = 0;
    velY        = 0.01;
    velZ        = 0;
    maxY        = 15.0;
    minY        = - 2.0;
    addCount    = 0;
    addCountD   = 0;
    maxCount    = 10;
    timeMax     = 1500;
	tiempo		= ofGetElapsedTimeMillis();
	model.loadModel("dodecahedron.dae",false);
	model.loadModel("icosahedron.dae", false);
	model.loadModel("octahedron.dae",false);
	model.loadModel("tetrahedron.dae",false);
	//vboMesh = model.getMesh(0);
	vboUno = model.getMesh(0);
	vboDos = model.getMesh(1);
	vboTres = model.getMesh(2);
	vboCuatro = model.getMesh(3);
}

void xuTransitoVertical::update()
{
	//return;
	

    for(std::vector<vNodo>::iterator nod = nodosU.begin();nod!=nodosU.end();)
    {
        nod->x += velX;
        nod->y += velY;
        nod->z += velZ;
        
        if(nod->y>maxY || nod->y<minY)
        {
			if(nodosU.size()>2)
			{
				//nod = nodosU.erase(nod);
				
			}else
			{
				//nodosU.clear();
			}
        }else
        {
            nod++;
        }
        
    }
    
    for(std::vector<vNodo>::iterator nod = nodosD.begin();nod!=nodosD.end();nod++)
    {
        nod->x += velX;
        nod->y -= velY;
        nod->z += velZ;
        
        if(nod->y>maxY || nod->y<minY)
        {
            
			if(nodosD.size()>2)
			{
				//nod = nodosD.erase(nod);
			}else
			{
				//nodosD.clear();
			}
        }else
        {
           // nod++;
        }
        
    }
}

void xuTransitoVertical::draw()
{
    return;
   
    //ofSetColor(0,240,40);
	//ofSphere(1);
	//cout<<"nodos: "<<nodosU.size()<<endl;

	for(std::vector<vNodo>::iterator nod = nodosU.begin();nod!=nodosU.end();nod++)
    {
        if(nod->tipo!=NULL)
        {
            if (nod->tipo==1)
            {
               //ofSphere(nod->x, nod->y, nod->z,0.05 + nod->peso*0.0002);
				ofPushMatrix();
			ofTranslate(nod->x, nod->y, nod->z);
			ofScale(nod->peso*0.002, nod->peso*0.002, nod->peso*0.002);
			vboUno.draw();
			
			ofPopMatrix();
            }else if(nod->tipo == 2)
            {
               ofSetColor(255,255,50);
				ofBox(nod->x, nod->y, nod->z, 0.05 + nod->peso*0.0002);
			}else
            {
                
            }
            
        }      
    }
    
    return;
    for(std::vector<vNodo>::iterator nod = nodosD.begin();nod!=nodosD.end();nod++)
    {
        if (nod->tipo==1)
        {
			ofSetColor(40,200,200);
            ofSphere(nod->x, nod->y, nod->z,0.05 + nod->peso*0.0002);
        }else if(nod->tipo == 2)
        {
            ofSetColor(0,0,200);
			//ofSphere(nod->x, nod->y, nod->z,0.05 + nod->peso*0.0002);
			ofPushMatrix();
			ofTranslate(nod->x, nod->y, nod->z);
			ofScale(nod->peso*0.002, nod->peso*0.002, nod->peso*0.002);
			vboDos.draw();
			
			ofPopMatrix();
			//ci::gl::color(ci::Color(0.0,0.0,0.8));
            // ci::gl::drawSphere(ci::Vec3f(nod->x, nod->y, nod->z), 0.05 + nod->peso*0.0002);
            //ci::gl::drawStrokedCube(ci::Vec3f(nod->x, nod->y, nod->z), ci::Vec3f(0.1 , 0.1 , 0.1 ));
        }else
        {
            ofBox(nod->x, nod->y, nod->z,0.05 + nod->peso*0.0002);
            //ci::gl::drawStrokedCube(ci::Vec3f(nod->x, nod->y, nod->z), ci::Vec3f(0.05 + nod->peso*0.0002, 0.05 + nod->peso*0.0002, 0.05 + nod->peso*0.0002));
        }
    }
    
}

std::vector<vNodo> * xuTransitoVertical::getNodos()
{
    return &nodosU;
}

void xuTransitoVertical::addNodo(const vNodo  nodo, int u)
{
	
    float temp = ofGetElapsedTimeMillis()-tiempo;

	if(temp>timeMax)
    {
        tiempo = ofGetElapsedTimeMillis();
        if(addCount>=maxCount)
        {
            addCount = 0;
        }
            
        if(addCountD>=maxCount)
        {
            addCountD = 0;
        }
    }
    
    
    
    if(u==0)
    {
        if(nodosU.size()<maxNodos && addCount<maxCount && temp<timeMax)
        {
            nodosU.push_back(nodo);
			cout<<"::: Metiendo Nodo:::"<<endl;
            addCount++;
        }
            
    }else
    {
        if(nodosD.size()<maxNodos && addCountD<maxCount && temp<timeMax)
        {
            nodosD.push_back(nodo);
            addCountD++;
        }
    }
           
}