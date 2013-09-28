#pragma once
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofMain.h"
#include <vector>
#include <math.h>  

class xuKinectIn
{
public:
	xuKinectIn(void);
	~xuKinectIn(void);

	void setup();
	void update();
	void draw();
	void exit();

	int getWidth();
	int getHeight();


	void setRenderBlob( bool si);

	std::string getMensaje();
	ofPoint		getRandomCentroid();
	int			getNumBlobs();

	ofFbo * getSiluetas();
	ofFbo * getMallado();

	//cotas para distancias de detección
	float  cotaInfDist,cotaSupDist; 
	int minDist, maxDist;
	int threshold;

	ofxKinect kinect;
	ofxBase3DVideo* kinectSource;

	ofTexture videoTextura;
	ofTexture depthTextura;

private:
	

	

	ofxCvGrayscaleImage depthImage;
	ofxCvGrayscaleImage threshImage;
	ofxCvContourFinder  contourFinderDepth;

	ofShader    maskShader;
	ofFbo		fboGrid, fbo, fboPolys;

	bool	renderBlobs;

	void renderBlob(ofxCvBlob *blob, float x = 0, float y = 0);

	ofTrueTypeFont	etiqueta;
	vector<std::string> mensajes;

};

