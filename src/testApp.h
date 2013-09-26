#pragma once
#include "xum/xuSniffer.h"
#include "ofMain.h"
#include "xum/xuTransitoVertical.h"

#include "ofxReprojection.h"
#include "ofxKinect.h"
#include "xum/xuKinectIn.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void renderTransito();
		void updateScenes();
		
		ofFbo							fboMezcla, fboUno, fboDos;
		xuKinectIn						profCam;
		//ofxKinect depthcam;
		ofxReprojectionCalibration		calibration;
		ofxReprojectionCalibrationData	dataset;
		ofxReprojectionRenderer2D		renderer;
		
		xuSniffer						sniffer;
		xuTransitoVertical				transito;
		
		
		ofEasyCam						cam;
		ofCamera						camFija;

		bool							verFija;
		ofLight							luzPuntual, luzDos;
		ofShader    maskShader;

		int								altoCamara, anchoCamara;

		
};
