#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "TextureShape.h"

// ------------------------------------------------- App
class testApp : public ofBaseApp {
	
public:
	
  void setup();
  void update();
  void draw();
  
  void keyPressed(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  
  ofxBox2d box2d;
  vector< ofPtr<ofxBox2dRect> > bricks;
  vector< ofPtr<ofxBox2dRect> > paddles;
  vector< ofPtr<ofxBox2dCircle> > balls;
  float brickWidth;
  float brickHeight;  
  float brickGap;
  int numPlayers;
  float ballRadius;
  float paddleWidth;
  float paddleHeight;
};
