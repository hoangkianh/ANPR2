#include "stdafx.h"
#include "Main.h"

const CvScalar BLACK = CV_RGB (0, 0, 0);
const CvScalar GREEN = CV_RGB (0, 0, 255);
const CvScalar BLUE  = CV_RGB (0, 255, 0);
const CvScalar RED   = CV_RGB (255, 0, 0);
const CvScalar CYAN  = CV_RGB (0, 255, 255);
const CvScalar WHITE = CV_RGB (255, 255, 255);

LPR_Main::LPR_Main(){
	src = NULL;
	plate = NULL;
	globallettercount = 0;
	show_in_find_plate = false;
	show_in_recognise = false;
}
LPR_Main::~LPR_Main(){
	if (src)
	{
		src = NULL;
		plate = NULL;
	}
}

/************************************************************************/
/*				TÌM BIỂN SỐ                                             */
/************************************************************************/


/*
 *	Cắt biển số từ ảnh gốc
 */
IplImage* LPR_Main::Crop_Plate(IplImage *src, int k){

	IplImage *resizeimg = cvCreateImage(cvSize(800, 600), src->depth, src->nChannels); // Ảnh resize

	cvResize(src, resizeimg, CV_INTER_LINEAR);

	plate = show_in_find_plate ? pf.FindPlate(resizeimg, true) : pf.FindPlate(resizeimg, false);

	IplImage* grayImg = pf.FindPlate(resizeimg, show_in_find_plate, 2);

	cvReleaseImage(&resizeimg);
	
	return (k == 1) ? plate : grayImg;
}

/************************************************************************/
/*					NHẬN DẠNG KÝ TỰ                                     */
/************************************************************************/
string LPR_Main::Recognise(IplImage *plate){
	// chia tách ký tự
	vector<IplImage *> cVector = show_in_recognise ? rc.CharacterDetection(plate, true) : rc.CharacterDetection(plate, false);
	
	// nhận dạng kí tự	
	vector <char> characters; // vector kí tự
	for (int i = 0; i < cVector.size(); i++)
	{
		characters.push_back(rc.CharacterRecognise(cVector.at(i)));
	}

	// ghép thành chuỗi
	string s = "";
	for (int i = 0; i < characters.size(); i++)
	{
		s.append(1, characters.at(i));
	}

	return s;
}
