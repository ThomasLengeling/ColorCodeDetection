#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  camWidth = 640; // try to grab at this size.
  camHeight = 480;

  // get back a list of devices.
  vector<ofVideoDevice> devices = vidGrabber.listDevices();

  for (int i = 0; i < devices.size(); i++) {
    if (devices[i].bAvailable) {
      // log the device
      ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
    } else {
      // log the device and note it as unavailable
      ofLogNotice() << devices[i].id << ": " << devices[i].deviceName
                    << " - unavailable ";
    }
  }

  vidGrabber.setDeviceID(0);
  vidGrabber.setDesiredFrameRate(60);
  // vidGrabber.setUseTexture(false);
  vidGrabber.setup(camWidth, camHeight);

  mImg.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
  imgDst.allocate(100, 100, OF_IMAGE_COLOR);

  ofSetVerticalSync(true);

  // gui
  gui.setup();
  gui.add(contrast.setup("contrast", 150, 10, 300));
  gui.add(brightness.setup("brightness", 140, 10, 300));

  mColorDetection = ColorDetection::create();
}

//--------------------------------------------------------------
void ofApp::update() {
  ofBackground(0);

  if (vidGrabber.isInitialized()) {
    vidGrabber.update();
    if (vidGrabber.isFrameNew()) {
      mImg.setFromPixels(vidGrabber.getPixels());
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofSetHexColor(0xffffff);
  mImg.draw(0, 0);

  // detectionTest();

  mColorDetection->processColor(vidGrabber.getPixels());

  auto imgVector = mColorDetection->getImgVec();

  int it = 0;
  for (auto const &imgItr : imgVector) {
    imgItr.draw(0, camHeight + it * 100, 100, 100);

    ofSetColor(0, 255, 0);
    ofDrawRectangle(100, camHeight + it * 100, 100, 100);

    it++;
  }

  // ofPixels crop;

  // vidGrabber.getPixelsRef().cropTo(crop, 100, 100, 200, 200);
  // crop.pasteInto(imgDst.getPixelsRef(), 0, camWidth);
  // imgDst.update();

  // ofColor(255, 0, 0);
  // ofDrawRectangle(100, 100, 200, 200);

  ofSetColor(0, 255, 0);
  for (int i = 0; i < camHeight / 50.0; i++) {
    ofDrawLine(0, 0 + 50 * i, camWidth, 0 + 50 * i);
  }

  ofDrawBitmapString(colorType, camWidth + 50, 75);

  gui.draw();
}

void ofApp::detectionTest() {

  cv::Mat imgOriginal = ofxCv::toCv(vidGrabber.getPixelsRef());
  cv::Mat imgThresholded = ofxCv::toCv(imgDst);
  cv::Mat imgHSV = ofxCv::toCv(imgDst);

  cv::cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV);

  /* HSV Color Code:
    Color               Hue      Saturation    Value
    Red     ...     163 - 179    161 - 228   116 - 169
    Orange  ...     0 - 12       112 - 227   134 - 255
    Yellow  ...     22 - 34      38 - 244    160 - 255
    Green   ...     45 - 108     39 - 153    92 - 255
    Blue    ...     92 - 135     62 - 176    32 - 126
    Purple  ...     109 - 139    58 - 148    43 - 87
    **Note: Color May Vary depending on lighting!
*/
  // red
  /*int iLowH = 163;
  int iLowS = 161;
  int iLowV = 116;
  int iHighH = 179;
  int iHighS = 228;
  int iHighV = 169;
*/
  // blue
  int iLowH = 92;
  int iLowS = 62;
  int iLowV = 32;
  int iHighH = 135;
  int iHighS = 176;
  int iHighV = 126;

  cv::inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV),
              cv::Scalar(iHighH, iHighS, iHighV), imgThresholded);

  // morphological opening (remove small objects from the foreground)
  cv::erode(imgThresholded, imgThresholded,
            cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
  cv::dilate(imgThresholded, imgThresholded,
             cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

  ofImage tmp0;
  ofImage tmp1;
  ofxCv::toOf(imgThresholded, tmp0);
  ofxCv::toOf(imgHSV, tmp1);

  tmp0.update();
  tmp1.update();
  tmp0.draw(camWidth, 0);
  tmp1.draw(0, camHeight);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  switch (key) {
  case 0:
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.setup(camWidth, camHeight);
    cout << "setup camera" << std::endl;
    break;
  default:
    /* code */
    break;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
