#include "stdafx.h"
#include "Recognise.h"

// dinh nghia mau
const CvScalar WHITE  = CV_RGB(255, 255, 255);
const CvScalar RED    = CV_RGB(255, 0, 0);
const CvScalar GREEN  = CV_RGB(0, 255, 0);
const CvScalar BLUE   = CV_RGB(0, 0 ,255);

LPR_Recognise::LPR_Recognise()
{
	svm.load("svm.txt");
}

/* Phát hiện vùng chứa kí tự, trả về 1 vector chứa các ảnh kí tự
*
*/
vector<IplImage*> LPR_Recognise::CharacterDetection(IplImage *plate, bool show)
{
	vector<IplImage*> characters;
	vector<CvRect> rect;
	IplImage *resize, *rs_gray, *rs_binary, *character, *rs_clone;
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *contours = 0;
	double ratio, size, ratioWhite, numWhite;

	resize = cvCreateImage(cvSize(408 , 70 ), plate->depth, plate->nChannels);
	rs_clone = cvCreateImage(cvSize(408 , 70 ), plate->depth, plate->nChannels);
	rs_gray = cvCreateImage(cvSize(408, 70), plate->depth, 1);
	rs_binary = cvCreateImage(cvSize(408, 70), plate->depth, 1);

	cvResize(plate, resize);	
	cvCopy(resize, rs_clone);
	cvResize(plate, resize);	
	cvCopy(resize, rs_clone);
	cvCvtColor(resize, rs_gray, CV_RGB2GRAY);
	/*Nhị phân với ngưỡng động
	 * cvAdaptiveThreshold(src, dst, maxValue, adaptiveMethod, thresholdType, blockSize, C)
	 * blockSize - kích thước cửa sổ cho việc tính ngưỡng động
	 * C - thông số bù trừ khi ảnh có độ tương phản quá lớn
	 */
	cvAdaptiveThreshold(rs_gray, rs_binary, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 13, 2);
	cvFindContours(rs_binary, storage, &contours);


	while(contours)
	{
		CvRect  r = cvBoundingRect(contours, 0);

		ratio = (double)r.width/ (double)r.height; // tỉ lệ chiều cao / rộng
		size = r.width * r.height;
		cvSetImageROI(rs_binary, r);
		numWhite = cvCountNonZero(rs_binary); // số điểm trắng
		cvResetImageROI(rs_binary);
		ratioWhite = numWhite/ size;   // tỉ lệ điểm trắng

		if (ratio > 0.3 && ratio < 1.1 && size > 375 && 15 < r.width && r.width < 50
			&& 30 < r.height && r.height < 65 && 0.3 < ratioWhite && ratioWhite < 0.75 && r.x >2)
		{
			cvRectangle(rs_clone, cvPoint(r.x, r.y), cvPoint(r.x + r.width, r.y + r.height), RED, 2); 
			rect.push_back(r);
		}
		contours = contours->h_next;
	}

	//Sắp xếp lại các hình chữ nhật bao quanh kí tự
	for(int i = 0; i < rect.size() - 1; i++)
	{
		for(int j = i + 1; j < rect.size(); j++)
			if(rect[i].x > rect[j].x)
			{
				CvRect tg;
				tg = rect[i];
				rect[i] = rect[j];
				rect[j] = tg;
			}
	}

	//Cắt kí tự
	for(int i = 0; i < rect.size(); i++)
	{
		character = cvCreateImage(cvSize(rect[i].width, rect[i].height), 8, 3);
		cvSetImageROI(resize, rect[i]);
		cvCopy(resize, character, NULL);	
		cvResetImageROI(resize);
		characters.push_back(character);

		if (show)
		{
			char name[8];
			sprintf(name, "%d", i+1);
			cvShowImage(name, character);
		}
	}
	if (show)
	{
		cvShowImage("Characters", rs_clone);
	}
	
	return characters;
}

/*
	Nhận diện kí tự, sử dụng SVM
 */
char LPR_Recognise::CharacterRecognise(IplImage *character)
{
	IplImage *gray, *binary;

	gray = cvCreateImage(cvGetSize(character), 8, 1);
	binary = cvCreateImage(cvGetSize(character), 8, 1);
	cvCvtColor(character, gray, CV_RGB2GRAY);
	/*Nhị phân với ngưỡng động
	 * cvAdaptiveThreshold(src, dst, maxValue, adaptiveMethod, thresholdType, blockSize, C)
	 * blockSize - kích thước cửa sổ cho việc tính ngưỡng động
	 * C - thông số bù trừ khi ảnh có độ tương phản quá lớn
	 */
	cvAdaptiveThreshold(gray, binary, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 55, 5);
	
	Mat img_character(binary);
	char c = '*';
	if(img_character.empty())
		return c;

	vector<float> feature = calculate_feature(img_character);
	Mat m = Mat(number_of_feature, 1, CV_32FC1);
	
	for(size_t i = 0; i < feature.size(); ++i)
		m.at<float>(i, 0) = feature[i];

	float r = svm.predict(m);
	int ri = (int)r;
	
	if(ri >= 0 && ri <= 9)
		c = (char)(ri + 48); //ma ascii 0 = 48
	
	if(ri >= 10 && ri < 18)
		c = (char)(ri + 55); //ma accii A = 5, --> tu A-H
	
	if(ri >= 18 && ri < 22)
		c = (char)(ri + 55 + 2); //K-N, bo I,J
	
	if(ri == 22) c = 'P';
	
	if(ri == 23) c = 'S';
	
	if(ri >= 24 && ri < 27)
		c = (char)(ri + 60); //T-V,  
	
	if(ri >= 27 && ri < 30)
		c = (char)(ri + 61); //X-Z

	return c;
}
