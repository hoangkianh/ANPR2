#ifndef RECOGNISE_H
#define RECOGNISE_H

#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include <opencv\ml.h>
#include <stdlib.h>
#include <iostream>
#include "feature.h"

using namespace std;
using namespace cv;

class LPR_Recognise
{
private:
	CvSVM svm;
public:
	LPR_Recognise();
	vector<IplImage *> CharacterDetection(IplImage *plate, bool show);
	char CharacterRecognise(IplImage *plate);
};
#endif