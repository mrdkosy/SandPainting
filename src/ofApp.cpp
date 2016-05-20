#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // 画面基本設定
    ofSetFrameRate(60); //秒間60コマで描画
    ofSetBackgroundColor(255); //背景色を黒に
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    
    //shader
    shader.load("", "shader.frag");
    vertex = ofVec2f(ofGetWidth(), ofGetHeight());
    
    //video
    video.initGrabber(ofGetWidth(), ofGetHeight());
    isUpDate = false;
    
    //gui
    gui.setup();
    gui.add(min.setup("Light and shade", .2, 0., .6));
    isDraw = true;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    if(isUpDate) video.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255, 255);
    
    shader.begin();
    
    float coef[] = {
        1.0,  1.0,  1.0,
        1.0, -8.0,  1.0,
        1.0,  1.0,  1.0
    };
    
    shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    shader.setUniformTexture("_texture", video.getTexture(), 1);
    shader.setUniform1fv("coef", coef, 9);
    shader.setUniform1f("min", min);
    
    ofSetColor(255,255);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(0, 0);
    glVertex2d(0, 0);
    
    glTexCoord2d(vertex.x, 0);
    glVertex2d(vertex.x, 0);
    
    glTexCoord2d(0, vertex.y);
    glVertex2d(0, vertex.y);
    
    glTexCoord2d(vertex.x, vertex.y);
    glVertex2d(vertex.x, vertex.y);
    glEnd();
    
    shader.end();
    
    for(int i=0; i<powder.size(); i++){
        powder[i].draw();
    }
    
    if(isDraw) gui.draw();
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'u'){
        powder.clear();
        vector<Powder>().swap(powder);
        isUpDate = true;
    }
    if(key == 'd'){
        isDraw = !isDraw;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'u'){
        isUpDate = false;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    int num = 50;
    for (int i=0; i<num; i++) {
        Powder p;
        p.drop(ofPoint(x, y, 0));
        powder.push_back(p);
    }
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
