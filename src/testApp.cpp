#include "testApp.h"

bool rendererInited = false;
//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofEnableDepthTest();
	ofSetCircleResolution(64);
	ofSetSmoothLighting(true);
	ofEnableAlphaBlending();
	//depthcam.init();
	//depthcam.setUseTexture(false);
	//depthcam.open();
	//
	
	profCam.setup();
	profCam.setRenderBlob(true);
	//dataset.loadFile("conLuz.xml");
	
	/*calibration.init(&profCam.kinect,&dataset);
	calibration.enableKeys();
	calibration.enableChessboardMouseControl();

	rendererInited = false;
	*/
	/*cam.setPosition(0,70,100);
	cam.lookAt(ofVec3f(0,0,0));
	fbo.allocate(1024,768,GL_RGBA);
	fbo.begin();
	ofClear(0,0,0, 0);
    fbo.end();*/
	sniffer.transito = &transito;
	transito.init();
	sniffer.init();

	
	
	
	verFija = true;
	cam.setDistance(20);
	camFija.setPosition(0,7,10);
	camFija.lookAt(ofVec3f(0,7,0));
 
	 luzPuntual.setPointLight();
	 luzPuntual.setPosition(0,5,10);

	 luzDos.setDirectional();
	 luzDos.setPosition(-7,3, -5);

	 ofEnableAlphaBlending();
	
	maskShader.load("shaders/mixer");
	altoCamara = profCam.getHeight();
	anchoCamara = profCam.getWidth();
	fboMezcla.allocate(anchoCamara,altoCamara);
	fboUno.allocate(anchoCamara,altoCamara);
	fboUno.begin();
	ofClear(0,0,0,0);
	fboUno.end();
}

//--------------------------------------------------------------
void testApp::update(){
    profCam.update();
	updateScenes();
	//depthcam.update();
	/*if(!calibration.isFinalized()) {
		calibration.update();
	}

	if(calibration.isFinalized() && !rendererInited) {
		renderer.init(&profCam.kinect);
		renderer.setDrawArea(1024,0,1024,768);
		renderer.setProjectionMatrix(dataset.getMatrix());

		rendererInited = true;
	}
	
	if(calibration.isFinalized() && rendererInited) {
		
		renderer.update();
	}
	*/

}

void testApp::updateScenes()
{
	//profCam.update();
	    transito.update();

		fboUno.begin();
			ofClear(0,0,0,0);
			ofPushMatrix();
			ofSetColor(255,255,255);
		
			renderTransito();
			ofPopMatrix();
		fboUno.end();


		fboMezcla.begin();
		ofPushMatrix();
		ofEnableAlphaBlending();
		ofClear(0, 0, 0,0);
		maskShader.begin();
		maskShader.setUniformTexture("tex0", fboUno.getTextureReference() , 1 );
		maskShader.setUniformTexture("maskTex",  profCam.getSiluetas()->getTextureReference() ,2 );
        fboUno.draw(0,0);
    	maskShader.end();
		ofPopMatrix();
		fboMezcla.end(); 

}

//-1-------------------------------------------------------------
void testApp::draw(){
	ofClear(50,50,150);
	//return;
	//profCam.getSiluetas()->draw(20,20);
	//profCam.draw();
	//depthcam.drawDepth(30,30);
	/*if(!calibration.isFinalized()) {
		calibration.drawStatusScreen(0,0,1024,768);
		calibration.drawChessboard(1024,0,1024,768);
	}
	
	if(calibration.isFinalized() && rendererInited) {
		renderer.drawHueDepthImage();
		//fbo.draw(10,10);
		renderer.drawImage(fboMezcla.getTextureReference());
	}*/
	//ofSetColor(255, 30, 30);

	//profCam.getSiluetas()->draw(20,20,320,240);
	//profCam.getMallado()->draw(360,20, 320,240);
	
	//fboMezcla.draw(0,0, 1024,768);
	fboUno.draw(20,20,800,600);

	
	//fboUno.draw(20,260,320,240);
	//profCam.draw();
	//ofSetColor(255,0,255);
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
}

void testApp::renderTransito()
{

	
	if (verFija)
	{
		cam.begin();
		ofDrawGrid();
	}else
	{
		camFija.begin();
	}
	ofEnableLighting();
	luzPuntual.enable();
	luzDos.enable();

	transito.draw();
	luzDos.disable();
	luzPuntual.disable();
	if (verFija)
	{
		cam.end();
	}else
	{
		camFija.end();
	}

}

void testApp::exit()
{
	profCam.exit();
	//depthcam.close();
	sniffer.close();
	
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key==' ')
	{
		verFija = !verFija;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
