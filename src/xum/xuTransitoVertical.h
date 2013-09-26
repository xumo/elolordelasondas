#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include <math.h>

#include "xuEstructuras.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include  "xuNodo.h"

class xuTransitoVertical
{
public:
	xuTransitoVertical(void);
	~xuTransitoVertical(void);
	void    init();
    void    update();
    void    draw();
	//void	render();
   // void    addNodo(vNodo nodo, int u);
	void	addNodo(int in_tipo, float in_peso, bool arriba);
	int	setVivo(std::vector<xuNodo> * vec_nodos, int in_tipo, float in_peso, ofPoint in_pos, ofPoint in_vel);

    std::vector<xuNodo> * getNodos();
    float velX, velY, velZ,minX, maxX, maxY, minY, minZ, maxZ;
	ofColor		colorUno, colorDos, colorTres, colorCuatro;
private:
    //std::vector<vNodo> nodosU;
    //std::vector<vNodo> nodosD;

	std::vector<xuNodo> nodosU;
    std::vector<xuNodo> nodosD;



    int maxNodos, addCount, addCountD,maxCount;
    
    float timeUp, timeDown, timeMax;
    float addRate;
	float tiempo, tiempoDos;

	ofxAssimpModelLoader modelUno, modelDos, modelTres, modelCuatro;
	ofVboMesh	vboMesh, vboUno, vboDos, vboTres, vboCuatro;


};

