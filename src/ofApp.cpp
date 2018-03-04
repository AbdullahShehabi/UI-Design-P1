#include "ofApp.h"

Image::Image()
{
    trans.x = 0;
    trans.y = 0;
    scale.x = 1.0;
    scale.y = 1.0;
    rot = 0;
    bSelected = false;
    loaded = false;
}

void Image::draw() {
    if (loaded) {
        image.draw(trans.x, trans.y);
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    
    cam.setDistance(200);
    cam.disableMouseInput();
    cam.disableRotation();
    
    ofSetColor(211, 211, 211);
    currentDepth = -1;
    mainImageDepth = -1;
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    cam.begin();
    ofPushMatrix();
    ofSetColor(255, 255, 255, 255);
    
    for (int i = images.size() - 1; i >= 0; i--) {
        if (images[i]->bSelected) {
            imageRecs[i].set(images[i]->trans.x, images[i]->trans.y, images[i]->image.getWidth(), images[i]->image.getHeight());
            ofSetColor(255, 0, 0);
            ofNoFill();
            ofSetLineWidth(3.0);
            ofDrawRectangle(imageRecs[i]);
        } else {
            ofSetColor(255, 255, 255, 255);
            imageRecs[i].set(images[i]->trans.x, images[i]->trans.y, images[i]->image.getWidth(), images[i]->image.getHeight());
            ofSetColor(0, 0, 0);
            ofNoFill();
            ofDrawRectangle(imageRecs[i]);
        }
        ofSetColor(255, 255, 255, 255);
        images[i]->draw();
    }
    
    ofPopMatrix();
//    cam.end();
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//    cout << "mouse( " << x << "," << y << ")" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (images.size() == 0) return;
    
    ofVec2f mouse = ofVec2f(x, y);
    ofVec2f delta = mouse - mouse_last;
    if (mainImage->bSelected) {
         mainImage->trans += delta ;
    }
    
    mouse_last = mouse;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouse_last = ofPoint(x, y);
    for (int i = imageRecs.size(); i >= 0; i--) {
        if (imageRecs[i].inside(x, y)) {
            mainImage->bSelected = false;
            mainImage = images[i];
            mainImage->bSelected = true;
        } else {
            mainImage->bSelected = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

void ofApp::keyPressed(int key) {
    switch (key) {
        case 'C':
        case 'c':
            break;
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
        case 'H':
        case 'h':
            break;
        case 'r':
            break;
        case 's':
            break;
        case 'u':
            break;
        case ' ':
            break;
        case OF_KEY_UP:
            cout << mainImageDepth;
            if (mainImageDepth < images.size()-1 && mainImageDepth + 1 != images.size()) {
                images[mainImageDepth] = images[mainImageDepth+1];
                images[mainImageDepth+1] = mainImage;
                mainImageDepth += 1;
                this->draw();
            }
            break;
        case OF_KEY_DOWN:
            cout << mainImageDepth;
            if (mainImageDepth > 0 && mainImageDepth - 1 != -1) {
                images[mainImageDepth] = images[mainImageDepth-1];
                images[mainImageDepth-1] = mainImage;
                mainImageDepth -= 1;
                this->draw();
            }
            break;
        case OF_KEY_LEFT:
            break;
        case OF_KEY_RIGHT:
            break;
        case OF_KEY_ALT:
            break;
        case OF_KEY_CONTROL:
            break;
        case OF_KEY_SHIFT:
            break;
        case OF_KEY_DEL:
            break;
    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    switch (key) {
        case ' ':
            break;
        case OF_KEY_LEFT:
            break;
        case OF_KEY_RIGHT:
            break;
        case OF_KEY_ALT:
            break;
        case OF_KEY_CONTROL:
            break;
        case OF_KEY_SHIFT:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
//
// Function to save image
//
void ofApp::saveImage() {
    screenGrab.grabScreen(0,0, ofGetWidth(), ofGetHeight());
    screenGrab.save("snapshot.jpg");
}

void ofApp::deleteImage(Image *selectedImage) {
    if (selectedImage != nullptr) {
        for (int i = 0; i <= images.size(); i++) {
            if (images[i] == selectedImage) {
                images.erase(images.begin() + i);
                delete selectedImage;
                selectedImage = NULL;
            }
        }
        
    }
}

//--------------------------------------------------------------
//
// Simple file drag and drop implementation.
//
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
    Image *newImage = new Image();
    if (newImage->image.load(dragInfo.files[0]) == false) {
        cout << "Can't load image: " << dragInfo.files[0] << endl;
    } else {
        newImage->loaded = true;
        images.push_back(newImage);
        mainImage = newImage;
        mainImage->bSelected = true;
        ofRectangle border;
        imageRecs.push_back(border);
        currentDepth += 1;
        mainImageDepth = currentDepth;
    }
}

