#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
using namespace std;
using std::vector;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
		
    int camWidth, camHeight, grayScale;
    int yinyang = 1;
    int yinyangTimer = 0;
    int poetx, poety;
    int poetTimer = 0;
    int scale = 10;
    int scale_index = 1;
    int fontsize = 14;
    vector<int> scales;
    vector<int> fontsizes;
    vector<string> strings;
    
    string poet = "陆游";
    
    ofVideoGrabber vidGrabber;
    ofxCvColorImage rgb, hsb;
    ofxCvGrayscaleImage bri, hue, sat, finalImage;
    ofTrueTypeFont myfont;
};
