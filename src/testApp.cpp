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
	dataset.loadFile("conLuz.xml");
	
	calibration.init(&profCam.kinect,&dataset);
	calibration.enableKeys();
	calibration.enableChessboardMouseControl();

	rendererInited = false;
	//calibration.finalize();
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
	fboMensajes.allocate(anchoCamara,altoCamara);
	fboMensajes.begin();
	ofClear(0,0,0,0);
	fboMensajes.end();
	
	mensajes.push_back(new xuMensaje("Time-to-live exceeded."));
	mensajes.push_back(new xuMensaje("Someone else out there?"));
	mensajes.push_back(new xuMensaje("UNKNOWN PACKET"));
	mensajes.push_back(new xuMensaje("Client Hello"));
	mensajes.push_back(new xuMensaje("Server Hello"));
	mensajesPintados = 0;
	//mascaraTest.loadImage("mascara.png");
	//ofLoadImage(textTest,"mascara.png"); 

	ofsetMensajes.x = 0;
	ofsetMensajes.y = 0;


	gui.addTitle("Vistas");
	gui.addContent("Compuesto",fboMezcla);

	gui.addTitle("Mensajes");
	gui.addContent("",fboMensajes);
	gui.addSlider("Escala",escalaMensajes, 0.001,1.5);
	gui.addSlider("Offset x", ofsetMensajes.x,-200,200);
	gui.addSlider("Offset y", ofsetMensajes.y, -200,200); 

	gui.addTitle("Profundidad");
	gui.addSlider("Distancia minima mm", profCam.minDist,300,1000);
	gui.addSlider("Distancia maxima mm", profCam.maxDist,1100,4000);

	gui.addTitle("Paquetes");
	gui.addContent("Vista",fboUno);
	gui.addToggle("Cambiar vista", verFija);
	gui.addSlider("Velocidad",transito.velY,0.005,1.0);
	gui.addSlider("Tope de entrada",transito.maxCount, 5,500);
	gui.addSlider("Tiempo de espera", transito.timeMax, 50,1500);
	gui.addSlider("Escala", transito.escala,0.01,2);
	gui.addColorPicker("Uno",transito.colorUno);
	gui.addColorPicker("Uno",transito.colorDos);
	gui.addColorPicker("Uno",transito.colorTres);
	gui.addColorPicker("Uno",transito.colorCuatro);
	gui.addColorPicker("Uno",transito.colorCinco);
	gui.addColorPicker("Uno",transito.colorSeis);

	//gui.addContent("Produndidad",profCam.depthTextura);

	gui.loadFromXML();
	

}

//--------------------------------------------------------------
void testApp::update(){
    //profCam.update();
	updateScenes();
	//renderTransito();
	//depthcam.update();
	if(!calibration.isFinalized()) {
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
	
	


}

void testApp::updateScenes()
{
		profCam.update();
	    	
		renderTransito();
		
		bool deltaVivo;
		for (int i = 0; i < mensajes.size(); i++)
		{
			deltaVivo = mensajes[i]->getVivo();
			mensajes[i]->escala = escalaMensajes;
			mensajes[i]->ofSet = ofsetMensajes;
			mensajes[i]->update();
			if(deltaVivo != mensajes[i]->getVivo())
			{
				mensajesPintados--;
			}
		}

		if(mensajesPintados < profCam.getNumBlobs())
		{
			for (int i = 0; i < mensajes.size(); i++)
			{
				if(!mensajes[i]->getVivo())
				{
					mensajes[i]->setVivo(true);
					mensajes[i]->setPos(profCam.getRandomCentroid());
					mensajesPintados++;
					break;
				}
			}
		}

		fboMensajes.begin();
		ofClear(0,0,0,0);
		ofSetColor(255,255,255);
		for (int i = 0; i < mensajes.size(); i++)
		{
			mensajes[i]->draw();
		};
		fboMensajes.end();

		fboMezcla.begin();
		//ofPushMatrix();
		ofEnableAlphaBlending();
		ofClear(0, 0, 0,0);
		maskShader.begin();
		maskShader.setUniformTexture("tex0", fboUno.getTextureReference() , 1 );
		maskShader.setUniformTexture("maskTex",  profCam.getSiluetas()->getTextureReference() ,2 );
		maskShader.setUniformTexture("mensajesText",  fboMensajes.getTextureReference() ,3 );
		
		
		profCam.getSiluetas()->draw(0,0);
		//textTest.draw(0,0);
    	maskShader.end();
		
		//ofPopMatrix();
		fboMezcla.end(); 

}

//-1-------------------------------------------------------------
void testApp::draw(){
	ofBackground(255, 255, 255); //Set background color
	ofEnableAlphaBlending();
	//return;
	//profCam.getSiluetas()->draw(20,20);
	//profCam.draw();
	//depthcam.drawDepth(30,30);
	if(!calibration.isFinalized()) {
		calibration.drawStatusScreen(0,0,1024,768);
		calibration.drawChessboard(1024,0,1024,768);
	}
	
	if(calibration.isFinalized() && rendererInited) {
		//renderer.drawHueDepthImage();
		//fbo.draw(10,10);
		gui.show();
		renderer.drawImage(fboMezcla.getTextureReference());
	}
	//ofSetColor(255, 30, 30);

	//profCam.getSiluetas()->draw(20,20,320,240);
	//profCam.getMallado()->draw(360,20, 320,240);
	
	
	//fboUno.draw(0,0, 1024,768);
	//ofSetColor(255);
	//ofEnableAlphaBlending();
	//mascaraTest.draw(0,0,1024,768);
	//fboMezcla.draw(0,0);
	/*ofSetColor(255,0,0);
	for (int i = 0; i < mensajes.size(); i++)
	{
		mensajes[i]->draw();
	}*/
	//ofSetColor( 255, 255, 255 );
	//textTest.draw( 0, 0 ); //Draw texture
	//fboUno.draw(20,260,320,240);
	//profCam.draw();
	//ofSetColor(255,0,255);
	gui.draw();
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
}

void testApp::renderTransito()
{
	transito.update();

	fboUno.begin();
	ofClear(0,0,0,0);
	//ofPushMatrix();
	ofSetColor(255,255,255);

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
	ofDisableLighting();
	if (verFija)
	{
		cam.end();
	}else
	{
		camFija.end();
	}
	
	//ofPopMatrix();
	fboUno.end();

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
