/*

 FIXME:
   - add convexity deffects use

   
*/

#ifndef OFXCVCOMPLEXBLOB_H
#define OFXCVCOMPLEXBLOB_H

#include "ofxOpenCv.h"

typedef  struct ofxCvConvexityDefects_s {
   ofPoint start;
   ofPoint end;
   ofPoint defect;
   float length;
} ofxCvConvexityDefect;

class ofxCvComplexBlob
{
  
  private:
    
    bool bApproxModified;
    bool bHullModified; 
 
  public:
    CvSeq *points; 
    vector<ofPoint> ofPoints;
    
    CvSeq *convexHull;
    vector<ofPoint> ofConvexPoints;
    
    CvSeq *approxChain;
    vector<ofPoint> ofApproxPoints;
    
    float approxFactor; 
    
    
    #define BLOB_AREA_APPROX 1
    #define BLOB_AREA 2
    #define BLOB_AREA_HULL 3
    
   //------------------------------------------------------------------------------------
    ofxCvComplexBlob(CvSeq *point_list);
    ofxCvComplexBlob(vector<ofPoint> of_points);
    vector<ofPoint> getPoints();
    vector<ofPoint> getHullPoints();
    void setApproxFactor(float approx);
    vector<ofPoint> getApproxPoints();
    float getArea();
    float getPerimeter();
    ofRectangle getBoundingBox();
    vector<ofxCvConvexityDefect> getConvexityDefects();
    void clear();
    
    int operator -(ofxCvComplexBlob b){
      return getArea() - b.getArea(); }
  
};

#endif // OFXCVCOMPLEXBLOB_H
