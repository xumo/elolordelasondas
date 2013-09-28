#include "xuKinectIn.h"


#define STRINGIFY(A) #A
//---------------------------------------
xuKinectIn::xuKinectIn(void)
{
	//Distancias en millímetros
	minDist = 500;
	maxDist = 3000;
	cotaInfDist = minDist;
	cotaSupDist = maxDist;
	threshold = 128;
	renderBlobs = false;
}

//---------------------------------------
xuKinectIn::~xuKinectIn(void)
{
}


//---------------------------------------
void xuKinectIn::setup()
{
	
	string shaderProgram = STRINGIFY(
                                    uniform sampler2DRect tex0;
                                    uniform sampler2DRect maskTex;

                                    void main (void){
                                        vec2 pos = gl_TexCoord[0].st;
                                         
                                        vec4 rTxt = texture2DRect(tex0, pos);
                                        //vec4 gTxt = texture2DRect(tex1, pos);
                                       // vec4 bTxt = texture2DRect(tex2, pos);
                                        vec4 mask = texture2DRect(maskTex, pos);
                                         
                                        vec4 color = vec4(0,0,0,255);
                                        //color = mix(color, rTxt, mask );
                                        //color = mix(color, gTxt, mask.g );
                                        //color = mix(color, bTxt, mask.b );
                                         color = rTxt * mask;
                                        gl_FragColor = color;
                                    }
                                    );
    
    //maskShader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
	maskShader.load("shaders/mixer");
	maskShader.linkProgram(); 



	kinect.init();
	kinect.setUseTexture(false);
	kinect.open();
	//kinect.addKinectListener(this, &chKinectEntrada::kinectConectado, &chKinectEntrada::kinectDesconectado);

	//kinectSource = &kinect;
	
	depthTextura.allocate(kinect.width, kinect.height, GL_RGB);
	videoTextura.allocate(kinect.width, kinect.height, GL_RGB);

	depthImage.allocate(kinect.width, kinect.height);
	fboPolys.allocate(kinect.width, kinect.height);
	fbo.allocate(kinect.width, kinect.height);
	fboGrid.allocate(kinect.width, kinect.height);
	
	fboGrid.begin();
	ofClear(0,0,0,0);
	int steps = 32;
	
	ofSetColor(255,255,255);

	for (int i = 0; i < steps; i++)
	{
		ofLine(0,i * kinect.height / steps , kinect.width ,  i * kinect.height / steps);
		ofLine(i * kinect.width  / steps , 0, i * kinect.width / steps, kinect.height); 
	}
	fboGrid.end();

	fbo.begin();
	ofClear(0,0,0,0);
	fbo.end();

}

//---------------------------------------
void xuKinectIn::update()
{
	kinect.setDepthClipping(minDist,maxDist);
	kinect.update();

	if(kinect.isFrameNew())
	{
		//std::cout<<"Esta abierto"<<std::endl;
		//depthTextura.loadData(kinectSource->getDepthPixels());
		videoTextura.loadData(kinect.getPixelsRef());
		depthImage.setFromPixels(kinect.getDepthPixelsRef());
		if(!renderBlobs)
		{
			return;
		}
		
		threshImage = depthImage;
		threshImage.threshold(threshold);

		contourFinderDepth.findContours(threshImage, 10,4000000,40,false, true);

		fboPolys.begin();
		ofClear(0,0,0,0);
		for(int i = 0; i < contourFinderDepth.nBlobs; i++)
		{
			//contourFinderDepth.blobs[i].draw(20, 340);
			renderBlob(&contourFinderDepth.blobs[i], 0,0);
		}

		fboPolys.end();
		

	}

		
		
		fbo.begin();
		ofPushMatrix();
		
		ofEnableAlphaBlending();
		ofClear(0, 0, 0,0);


		maskShader.begin();
		// Pass the video texture
		maskShader.setUniformTexture("tex0", fboGrid.getTextureReference() , 1 );
		// Pass the image texture
		//maskShader.setUniformTexture("tex1", logoImg, 2 );
		maskShader.setUniformTexture("maskTex", fboPolys.getTextureReference() , 2 );
    
		// We are using this image just as a frame where the pixels can be arrange
		// this could be a mesh also. 
		// Comment "shader.setUniformTexture("maskTex", maskFbo.getTextureReference() , 4 );" to se how there is two ways
		// of passing a texture to the shader
		// 
		//ofSetColor(255);
		fboGrid.draw(0,0);
    
		maskShader.end();
		ofPopMatrix();
		fbo.end();

}

//---------------------------------------
void xuKinectIn::draw()
{
	ofSetColor(255,255,255);
	videoTextura.draw(20,20,320,240);
	threshImage.draw(340,20,320,240);
	if(renderBlobs)
	{

		fboGrid.draw(680,20,320,240);
		fboPolys.draw(680,260,320,240);
		
		fbo.draw(680,520,320,240);
	
		depthImage.draw(20,260);
	}
}


void xuKinectIn::setRenderBlob(bool si)
{
	renderBlobs = si;
}

//---------------------------------------

void xuKinectIn::renderBlob(ofxCvBlob *blob, float x, float y )
{
	//blob->draw(20,340);
	//ofFbo  fbo;

	//fbo.allocate(kinect.width,kinect.height);

	//fbo.begin();
		//ofNoFill();
		ofSetHexColor(0xffFFFF);
		ofBeginShape();
		for (int i = 0; i < blob->nPts; i++){
				ofVertex( blob->pts[i].x, blob->pts[i].y);
		}
		ofEndShape(true);
		//Pintar un String
		// en centro del blob
		//blob->area.width;
		//blob->boundingRect.x;

		//ofSetHexColor(0xFFFFFF);
		//etiqueta.drawString(getMensaje(),blob->boundingRect.x, blob->centroid.y);


	//fbo.end();

	//fbo.draw(x, y);
	

	//delete fbo;
}

ofFbo * xuKinectIn::getSiluetas()
{
	return &fboPolys;
}

ofFbo * xuKinectIn::getMallado()
{
	return &fbo;
}

int xuKinectIn::getWidth()
{

	return kinect.width;
}

int xuKinectIn::getHeight()
{
	return kinect.height;
}

std::string xuKinectIn::getMensaje(){
	int n = (int)floor(ofRandom(mensajes.size()));
	return mensajes[n];
}

ofPoint	xuKinectIn::getRandomCentroid()
{

	if(contourFinderDepth.nBlobs>0)
	{
		ofxCvBlob blob = contourFinderDepth.blobs[(int)ofRandom(contourFinderDepth.nBlobs-1)];
		return ofPoint(blob.centroid.x, blob.centroid.y);
	}else
	{
		return ofPoint(-1);
	}

	
}

int xuKinectIn::getNumBlobs()
{
	return contourFinderDepth.nBlobs;
}

//---------------------------------------
void xuKinectIn::exit()
{
	if(videoTextura.bAllocated())
	{
			videoTextura.clear();
	}
	kinect.close();

}