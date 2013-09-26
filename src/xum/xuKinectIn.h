#pragma once
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofMain.h"


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
	ofFbo * getSiluetas();
	ofFbo * getMallado();

	//cotas para distancias de detección
	float minDist, maxDist, cotaInfDist,cotaSupDist; 
	int threshold;

	ofxKinect kinect;
	ofxBase3DVideo* kinectSource;

private:
	

	ofTexture videoTextura;
	ofTexture depthTextura;

	ofxCvGrayscaleImage depthImage;
	ofxCvGrayscaleImage threshImage;
	ofxCvContourFinder  contourFinderDepth;

	ofShader    maskShader;
	ofFbo		fboGrid, fbo, fboPolys;

	bool	renderBlobs;

	void renderBlob(ofxCvBlob *blob, float x = 0, float y = 0);
};

