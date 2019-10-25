#include "ofApp.h"
using namespace std;
using std::vector;

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth = 480;
    camHeight = 360;
    ofBackground(0, 0, 0);
    
    scales.push_back(5);
    scales.push_back(10);
    scales.push_back(20);
    scales.push_back(40);
    
    fontsizes.push_back(7);
    fontsizes.push_back(14);
    fontsizes.push_back(28);
    fontsizes.push_back(56);
    
    poetx = 0;
    poety = 0;
    
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(camWidth, camHeight);
    
    hsb.allocate(camWidth, camHeight);
    bri.allocate(camWidth, camHeight);
    rgb.allocate(camWidth, camHeight);
    hue.allocate(camWidth, camHeight);
    sat.allocate(camWidth, camHeight);
    
    finalImage.allocate(camWidth, camHeight);
    ofTrueTypeFontSettings settings("FZXIANGSU15.ttf", fontsize);
    settings.antialiased = true;
    settings.contours = true;
    settings.addRanges(ofAlphabet::Chinese);
    settings.addRanges(ofAlphabet::Latin);
    
    myfont.load(settings);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    
    
    if(vidGrabber.isFrameNew()) {
        rgb.setFromPixels(vidGrabber.getPixels());
        hsb = rgb;
        hsb.convertRgbToHsv();
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        int briTemp = 0;
        for (int i = 0; i < camWidth; i+=scale) {
            for (int j = 0; j < camHeight; j+=scale) {
                for (int w = i; w < i + scale; w++) {
                    for (int h = j; h < j + scale; h++) {
                        briTemp += bri.getPixels()[(h*camWidth)+w];
                    }
                }
                for (int w_ = i; w_ < i + scale; w_++) {
                    for (int h_ = j; h_ < j + scale; h_++) {
                        finalImage.getPixels()[(h_*camWidth)+w_] = briTemp / (scale * scale);
                    }
                }
                briTemp = 0;
            }
        }
    }
    finalImage.flagImageChanged();
    strings.clear();
    
    
    if ((finalImage.getPixels()[0] < 30) && (finalImage.getPixels()[-1] < 30) && (finalImage.getPixels()[camWidth/scale] < 30)) yinyangTimer += 1;
    
    
    /*
    if (poetTimer > 100) {
        poetTimer = 0;
        poetx = ofRandom(strings.size() - 1);
        poety = poetx+1;
    }*/
    
    if (yinyangTimer >= 40) {
        yinyang = -yinyang;
        yinyangTimer = 0;
    }
    for (int i = 0; i < camWidth*camHeight; i ++)  {
        if (yinyang > 0) {
            if (finalImage.getPixels()[i] == 0) strings.push_back(" ");
            else if (finalImage.getPixels()[i] < 30) strings.push_back("山");
            else if (finalImage.getPixels()[i] < 60) strings.push_back("水");
            else if (finalImage.getPixels()[i] < 90) strings.push_back("无");
            else if (finalImage.getPixels()[i] < 115) strings.push_back("路");
            else if (finalImage.getPixels()[i] < 145) strings.push_back("重");
            else if (finalImage.getPixels()[i] < 175) strings.push_back("复");
            //else if (finalImage.getPixels()[i] < 190) strings.push_back("7");
            //else if (finalImage.getPixels()[i] < 200) strings.push_back("8");
            else strings.push_back("疑");
        } else {
            if (finalImage.getPixels()[i] == 0) strings.push_back(" ");
            else if (finalImage.getPixels()[i] < 30) strings.push_back("一");
            else if (finalImage.getPixels()[i] < 60) strings.push_back("又");
            else if (finalImage.getPixels()[i] < 90) strings.push_back("村");
            else if (finalImage.getPixels()[i] < 115) strings.push_back("花");
            else if (finalImage.getPixels()[i] < 145) strings.push_back("明");
            else if (finalImage.getPixels()[i] < 175) strings.push_back("暗");
            //else if (finalImage.getPixels()[i] < 190) strings.push_back("7");
            //else if (finalImage.getPixels()[i] < 200) strings.push_back("8");
            else strings.push_back("柳");
        }
    }
    //strings[poetx] = "陆";
    //strings[poety] = "游";
    //poetTimer += 1;
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < camWidth; i+=scale) {
        for (int j = 0; j < camHeight; j+=scale) {
            myfont.drawString(strings[j*camWidth + i], (camWidth*2-scale*2)-(i*2), (j*2)+scale*2);
            //myfont.drawStringAsShapes(strings[j*camWidth + i], i*2, (j*2)+scale);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //rescaling
    if (key == 'q') {
        if (scale_index == 0) ;
        else {
            scale_index -= 1;
        }
    } else if (key == 'e') {
        if (scale_index == 3) ;
        else {
            scale_index += 1;
        }
    }
    scale = scales[scale_index];
    
    //reload new fontsize
    fontsize = fontsizes[scale_index];
    ofTrueTypeFontSettings settings("FZXIANGSU15.ttf", fontsize);
    settings.antialiased = true;
    settings.contours = true;
    settings.addRanges(ofAlphabet::Chinese);
    settings.addRanges(ofAlphabet::Latin);
    myfont.load(settings);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
