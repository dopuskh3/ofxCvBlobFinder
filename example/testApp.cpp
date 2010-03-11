#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {

  ofBackground(20, 20, 20);
  ofSetFrameRate(32);

  w = ofGetWidth();
  h = ofGetHeight();
  threshold = 110; 
  bGrab = true;
  
  vidGrabber.initGrabber(640, 480, false);
  inputImage.allocate(640, 480);
  inputImageGrey.allocate(640, 480);
 
}

//--------------------------------------------------------------
void testApp::update() {
  
  
  if(bGrab){
    vidGrabber.grabFrame();
    //1 - vidgrabber isNewFrame
    if(vidGrabber.isFrameNew()){
      // fill ofxCvColorImage with pixels 
      inputImage.setFromPixels(vidGrabber.getPixels(), 640, 480);
      inputImage.flagImageChanged();
    }
  }
  //3 - Put it in the blob detection
  inputImageGrey = inputImage;
  
  inputImageGrey.blurHeavily();
  inputImageGrey.threshold(threshold);
  inputImageGrey.invert();
  
  blobFinder.findBlobs(inputImageGrey, false);
  //blobFinder.findConvexBlobs(inputImageGrey);
  //blobFinder.findApproxBlobs(inputImageGrey);
  //blobFinder.findContours( inputImageGrey, 10, 1000000, 100, false, true);
  //blobFinder.computeConvexBlobs();
  //blobFinder.computeApproxBlobs();
}

//--------------------------------------------------------------
void testApp::draw() {
  ofSetColor(255, 255, 255);
  inputImageGrey.draw(0, 0);
  
  //1- draw blobsa
  //2- draw approx blobs
  //3- draw convex hull
  ofFill();
  blobFinder.draw( 640, 0);
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

  switch (key) {
    case 'g':
      break;
    case OF_KEY_UP:
      threshold = (threshold<255)?threshold+1:threshold;
      break;
    case OF_KEY_DOWN:
      
      threshold = (threshold>0)?threshold-1:threshold;
      break;
    case ' ':
      bGrab = ! bGrab;
  }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mouseReleased() {

}
