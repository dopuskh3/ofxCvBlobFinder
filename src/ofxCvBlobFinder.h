/*

 FIXME:
  - add blob sorting by area
  
*/



#include "ofxOpenCv.h"
#include "ofxCvComplexBlob.h"


class ofxCvBlobFinder : private ofBaseDraws {

  public:
    ofxCvBlobFinder();
  
    virtual float getWidth(){ return _width; };
    virtual float getHeight(){ return _height; };
    void findBlobs(ofxCvGrayscaleImage img, bool find_hole);
    
    void setApproxFactor(float factor){ approxFactor = factor; }; 
    float getApproxFactor(){ return approxFactor; }; 
    

    virtual void  draw() {
      draw(0, 0, _width, _height);
    };

    virtual void  draw(float x, float y) {
      draw(x, y, _width, _height);
    };

    virtual void  draw(float x, float y, float w, float h);   //{ ofxCvContourFinder::draw(x, y, w, h);  };

    void reset();
    
    vector <ofxCvComplexBlob> blobz;


  private:
    int _width, _height;
    float approxFactor;
};

