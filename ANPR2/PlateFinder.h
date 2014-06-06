#ifndef PlateFinder_H
#define PlateFinder_H
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>
#include <iostream>

class LPR_PlateFinder 
{
	private:
		IplConvKernel* S1;
		IplConvKernel* S2;
		IplImage *plate; 
	public:
		LPR_PlateFinder();
		~LPR_PlateFinder();
		void WaveletEdge(IplImage *src_pyrdown, bool flag = false);
		IplImage* FindPlate(IplImage *src, bool show = false, int k = 1);
		int LPR_PlateFinder:: Count(IplImage *plate);
};
#endif