#pragma once

#include "ofMain.h"

class BaseObject {
public:
    ofVec2f trans, scale;
    float    rot;
    bool    bSelected;
};

class Image : public BaseObject {
    
public:
    Image();
    void draw();
    
    ofImage image;
    bool loaded;
};


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void saveImage();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void deleteImage(Image *selectedImage);
    
    ofEasyCam cam;
    vector<Image *> images;
    vector<ofRectangle> imageRecs;
    Image *mainImage;
    ofImage screenGrab;
    ofVec3f mouse_last;
    int currentDepth;
    int mainImageDepth;
};

