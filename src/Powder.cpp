#include "Powder.hpp"

void Powder::drop(ofPoint pos){
    float radius = ofRandom(20);
    float theta = ofRandom(TWO_PI);
    position = pos + ofPoint(radius*cos(theta), radius*sin(theta));
    speed = ofPoint( ofRandom(-.2, .2), ofRandom(.1, 1.)+.2 );
    
}
void
Powder::draw(){
    ofPushStyle();
    //update
    position += speed;
    
    //draw
    ofSetColor(ofRandom(255), ofRandom(255));
    ofDrawCircle(position, 1);
    ofPopStyle();
}
