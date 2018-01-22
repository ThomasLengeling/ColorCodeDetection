#include "ColorDetection.h"

// reading all the pixels.
void ColorDetection::processColor(ofPixels pixels) {
  cv::Mat imgOriginal = ofxCv::toCv(pixels);
  cv::Mat imgHSV;

  cv::cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV);

  // white
  cv::Mat imgWhite;

  cv::inRange(imgHSV, cv::Scalar(iLowWhiteH, iLowWhiteS, iLowWhiteV),
              cv::Scalar(iHighWhiteH, iHighWhiteS, iHighWhiteV), imgWhite);

  // morphological opening (remove small objects from the foreground)
  cv::erode(imgWhite, imgWhite,
            cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
  cv::dilate(imgWhite, imgWhite,
             cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

  ofxCv::toOf(imgWhite, mImageColors.at(0));
  mImageColors.at(0).update();

  // black
  cv::Mat imgBlack;

  cv::inRange(imgHSV, cv::Scalar(iLowBlackH, iLowBlackS, iLowBlackV),
              cv::Scalar(iHighBlackH, iHighBlackS, iHighBlackV), imgBlack);

  // morphological opening (remove small objects from the foreground)
  cv::erode(imgBlack, imgBlack,
            cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
  cv::dilate(imgBlack, imgBlack,
             cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

  ofxCv::toOf(imgBlack, mImageColors.at(1));
  mImageColors.at(1).update();

  // red
  cv::Mat imgRed;

  cv::inRange(imgHSV, cv::Scalar(iLowRedH, iLowRedS, iLowRedV),
              cv::Scalar(iHighRedH, iHighRedS, iHighRedV), imgRed);

  // morphological opening (remove small objects from the foreground)
  cv::erode(imgRed, imgRed,
            cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
  cv::dilate(imgRed, imgRed,
             cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

  ofxCv::toOf(imgRed, mImageColors.at(2));
  mImageColors.at(2).update();

  // blue
  cv::Mat imgBlue;

  cv::inRange(imgHSV, cv::Scalar(iLowBlueH, iLowBlueS, iLowBlueV),
              cv::Scalar(iHighBlueH, iHighBlueS, iHighBlueV), imgBlue);

  // morphological opening (remove small objects from the foreground)
  cv::erode(imgBlue, imgBlue,
            cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
  cv::dilate(imgBlue, imgBlue,
             cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

  ofxCv::toOf(imgBlue, mImageColors.at(3));
  mImageColors.at(3).update();
}

// make the image detection smaller.
void ColorDetection::compress() {
  int i = 0;
  int components = imgDst.bpp / 8;
  for (auto const &imgItr : mImageColors) {
    ofPixels pix = imgItr->getPixels();
    for (int y = 0; y < image.height; y++) {
    }
  }
}
