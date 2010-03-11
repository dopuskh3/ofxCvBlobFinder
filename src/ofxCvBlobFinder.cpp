
#ifndef OFXCVBLOBFINDER_H
#define OFXCVBLOBFINDER_H

#include "ofxCvBlobFinder.h"

//--------------------------------------------------------------------------------
bool sort_blob_func( ofxCvComplexBlob a, ofxCvComplexBlob b){ 
  return a.getArea() > b.getArea();  
}


//----------------------------------------------------------------------------------
ofxCvBlobFinder::ofxCvBlobFinder()
{
    approxFactor = 0.005;
}

//----------------------------------------------------------------------------------
void ofxCvBlobFinder::findBlobs(ofxCvGrayscaleImage image, bool find_holes) {

    CvMemStorage *stor = cvCreateMemStorage();
    IplImage *img = image.getCvImage();
    CvSeq *contours;

    // CV_RETR_EXTERNAL to not find holes
    int mode = (find_holes)?CV_RETR_LIST:CV_RETR_EXTERNAL;
    
    cvFindContours(img, stor, &contours, sizeof(CvContour), mode, CV_CHAIN_APPROX_SIMPLE);

    blobz.clear();
    while (contours) {
        ofxCvComplexBlob b =  ofxCvComplexBlob(contours);
        b.setApproxFactor(approxFactor);
        b.getApproxPoints();
        b.getHullPoints();
        blobz.push_back( b );
        contours = contours->h_next;
    }
    
    // sort blobs 
    sort(blobz.begin(),  blobz.end(), sort_blob_func); 
}


//----------------------------------------------------------------------------------
void ofxCvBlobFinder::draw(float x, float y, float w, float h) {

    // draw blobs
    //ofxCvContourFinder::draw(x, y, w, h);
    // scale blob
    float scalex = 0.0f;
    float scaley = 0.0f;

    if (_width != 0) {
        scalex = w / _width;
    }
    else {
        scalex = 1.0f;
    }

    if (_height != 0) {
        scaley = h / _height;
    }
    else {
        scaley = 1.0f;
    }


    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    // apply transformation
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(scalex, scaley, 0.0);


#define DRAW_BLOB_VECTOR(points) do{ \
        ofBeginShape(); \
        for(int i = 0; i < (points).size(); i++){ \
          ofVertex((points[i]).x, (points[i]).y); \
        } \
        ofEndShape(true); \
      } while(0)

    ofNoFill();
    for (int j = 0; j < blobz.size(); j++) {
        ofSetColor(0xFF0000);
        DRAW_BLOB_VECTOR( blobz[j].getPoints());

        ofSetColor(0x00FF00);
        DRAW_BLOB_VECTOR(blobz[j].getHullPoints());

        ofSetColor(0x0000FF);
        DRAW_BLOB_VECTOR( blobz[j].getApproxPoints());

        ofSetColor(0x00ffae);
        ofRectangle c = blobz[j].getBoundingBox();
        
        
        // draw bounding box
        ostringstream s; 
        s << j << "Area = " << blobz[j].getArea();
        
        ofDrawBitmapString(s.str(), c.x, c.y);
        ofRect(c.x, c.y, c.width, c.height);
        
        // get convexity defects
        vector<ofxCvConvexityDefect> cd = blobz[j].getConvexityDefects();
        ofSetColor(0x00effe);
        for(int i=0; i < cd.size(); i++){
          ofLine(cd[i].start.x, cd[i].start.y, cd[i].end.x, cd[i].end.y);
          ofCircle(cd[i].defect.x, cd[i].defect.y, 2);
          float angle = atan2f( ( (float) (cd[i].end.y - cd[i].start.y) ) , ( (float) (cd[i].end.x - cd[i].start.x)));
          float x = cd[i].defect.x - sinf(angle) * cd[i].length; 
          float y = cd[i].defect.y + cosf(angle) * cd[i].length;
          ofSetColor(0xF0F0F0);
          ofLine(cd[i].defect.x, cd[i].defect.y, x, y);
        }
    }

    glPopMatrix();
}

void ofxCvBlobFinder::reset() {
    blobz.clear();
}

#endif
