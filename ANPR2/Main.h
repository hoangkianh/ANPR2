#ifndef Main_H
#define Main_H

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>
#include "PlateFinder.h"
#include "Recognise.h"

class LPR_Main
{
	protected:
		IplImage *src;	
		IplImage *plate;
		int pointer;
		int globallettercount;
		bool isplateblack;
		LPR_PlateFinder pf;
		LPR_Recognise rc;
	public:		
		bool show_in_find_plate;
		bool show_in_recognise;

		LPR_Main();
		~LPR_Main();	
		IplImage*  Crop_Plate(IplImage *src, int k = 1);
		string Recognise(IplImage *plate);
};
#endif