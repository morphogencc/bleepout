#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
  ofBackgroundHex(0x000000);
  ofSetLogLevel(OF_LOG_NOTICE);
  ofSetVerticalSync(true);
  ofDisableAntiAliasing();
  
  // Box2d
  box2d.init();
  box2d.createGround();
  box2d.setFPS(30.0);
  box2d.registerGrabbing();

  brickWidth = 100;
  brickHeight = 20;
  brickGap = 5;
  ballRadius = 10;
  paddleWidth = 150;
  paddleHeight = 25;
  numPlayers = 1;

  // set up wall
  bool oddRow = true;
  for(int i = 0; i < ofGetWidth() + brickWidth; i+= brickWidth + brickGap) {
    for(int j = 0; j < ofGetHeight()/3.0; j+= brickHeight + brickGap) {
      if(oddRow) {
	bricks.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
	//bricks.back().get()->setPhysics(3.0, 0.53, 0.1);
	bricks.back().get()->setup(box2d.getWorld(), i, j, brickWidth, brickHeight);
	oddRow = false;
      }
      else {
	bricks.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
	//bricks.back().get()->setPhysics(3.0, 0.53, 0.1);
	bricks.back().get()->setup(box2d.getWorld(), i - (brickWidth/2.0), j, brickWidth, brickHeight);
	oddRow = true;
      }
    }
  }

  // set up ball / paddle pairs
  for(int i = 0; i < numPlayers; i++) {
    balls.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
    balls.back().get()->setPhysics(3.0, 1.0, 0.0);
    balls.back().get()->setup(box2d.getWorld(), ofGetWidth()/2.0, ofGetHeight()/2.0, ballRadius);
    balls.back().get()->addImpulseForce(ofVec2f(ofRandom(0,ofGetWidth()), ofGetHeight()), ofVec2f(ofRandom(0,100), ofRandom(0,100)));

    paddles.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
    paddles.back().get()->setPhysics(3.0, 0.5, 0.9);
    paddles.back().get()->setup(box2d.getWorld(), ofGetWidth()/2.0, ofGetHeight() - paddleHeight, paddleWidth, paddleHeight);
  }
}

//--------------------------------------------------------------
void testApp::update() {
  box2d.update();

  //update paddles
  ofVec2f mouse(ofGetMouseX(), ofGetHeight());
  if(numPlayers == 1) {
    for(int i = 0; i < numPlayers; i++) {
      float dis = mouse.distance(paddles[i].get()->getPosition());
      if(dis > paddleWidth / 2.0) {
	paddles[i].get()->addAttractionPoint(mouse, 3.0);
      }
      else {
	paddles[i].get()->addRepulsionForce(mouse, 1.0);
      }
    }
  }
}

//--------------------------------------------------------------
void testApp::draw() {
  for (int i=0; i < bricks.size(); i++) {
    bricks[i].get()->draw();
  }
  for (int i=0; i < balls.size(); i++) {
    balls[i].get()->draw();
  }
  for (int i=0; i < paddles.size(); i++) {
    paddles[i].get()->draw();
  }
}


//--------------------------------------------------------------
void testApp::keyPressed(int key) {
  if(key == 'c') {
    paddles.clear();
  }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
}

