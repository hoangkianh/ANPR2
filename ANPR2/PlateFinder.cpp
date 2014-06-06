#include "stdafx.h"
#include "PlateFinder.h"
#include <iostream>
using namespace System;
/*
Chi tiết về các hàm được sử dụng xem tại:
http://opencv.willowgarage.com/documentation/c/index
*/
/* Custom Color */
const CvScalar RED   = CV_RGB(255, 0, 0);
const CvScalar GREEN = CV_RGB(0, 255, 0);
const CvScalar BLUE  = CV_RGB(0, 0, 255);
const CvScalar WHITE = CV_RGB(255, 255, 255);

LPR_PlateFinder::LPR_PlateFinder(){
	// Tạo cấu trúc sử dụng cho các phương pháp hình thái học ở phía dưới
	S1 = cvCreateStructuringElementEx(3, 1, 1, 0, CV_SHAPE_RECT, NULL);
	S2 = cvCreateStructuringElementEx(6, 1, 3, 0, CV_SHAPE_RECT, NULL);
	plate = NULL;
}
// Hàm hủy
LPR_PlateFinder::~LPR_PlateFinder(){
	if (plate)
	{
		S1 = NULL;
		S2 = NULL;
	}
}
/*
Tiền xử lý
+ 	Tách biên ngang, dọc; làm nổi bật vùng biển số
+	Nhị phân hóa ảnh đã được làm nổi bật vùng biển số
*/

void LPR_PlateFinder::WaveletEdge(IplImage *src, bool flag)
{
	int w = src->width;	// Chiều rộng ảnh gốc
	int h = src->height; // Chiều dài ảnh gốc
	IplImage *bothat	   = cvCreateImage(cvSize(w/2, h/2), IPL_DEPTH_8U, 1);	// Ảnh tạm thời
	IplImage *src_pyrdown  = cvCreateImage(cvSize(w/2, h/2), IPL_DEPTH_8U, 1);  // Ảnh gốc đã được giảm độ tương phản
	IplImage *temp2        = cvCreateImage(cvSize(w/2, h/2), IPL_DEPTH_8U, 1);
	IplImage *thresholded  = cvCreateImage(cvSize(w/2, h/2), IPL_DEPTH_8U, 1);  // ảnh nhị phân
	IplImage *mini_thresh  = cvCreateImage(cvSize(w/2, h/2), IPL_DEPTH_8U, 1);  // ảnh nhị phân thứ 2
	IplImage *dst          = cvCreateImage(cvSize(w/2, h/2), IPL_DEPTH_8U, 1);  // ảnh được làm rõ vùng chứa biển số

	cvPyrDown(src, src_pyrdown);   // Giảm độ tương phản

	cvMorphologyEx(src_pyrdown, bothat, temp2, S2, CV_MOP_BLACKHAT);  // Tìm các biên ngang của ảnh bằng phương pháp biến đổi hình thái học
	cvNormalize(bothat, bothat, 0, 255, CV_MINMAX);           // Lọc nhiễu

	/*
	Nhị phân hóa ảnh đã lọc biên, ở đây hàm cvAvg() dùng để tính giá trị trung bình của ảnh bothat
	Sau đó giá trị này trở thành thông số thresold (ngưỡng xám) để đưa vào hàm cvThresold
	Hàm cvAvg: http://opencv.willowgarage.com/documentation/c/core_operations_on_arrays.html?highlight=cvavg#avg
	Hàm cvThresold: http://opencv.willowgarage.com/documentation/c/imgproc_miscellaneous_image_transformations.html?highlight=threshold#cvThreshold
	*/
	cvThreshold(bothat, thresholded, (int)10*cvAvg(bothat).val[0], 255, CV_THRESH_BINARY);
	cvZero(dst);   // Xóa ảnh
	cvCopy(thresholded, mini_thresh);   // Copy ảnh

	/*
	-  Trong vòng lặp này, ảnh bothat sẽ được lọc để xóa các vùng không có khả năng là biển sô
	bằng cách trượt 1 hình chữ nhật trên khắp ảnh.
	-  Khu vực có khả năng là biển số sẽ được phát hiện theo mật độ pixel trong ảnh.
	-  Cứ mỗi lần đếm được 1 vùng thỏa mãn, thì cộng vào các số nonZero1, nonZero2, nonZero3, nonZero4
	*/
	int cnt;
	int nonZero1, nonZero2, nonZero3, nonZero4;
	CvRect rect;   // Hình chữ nhật trượt trên ảnh (có kích thước: cao 8, rộng 16)
	for (int i = 0; i < mini_thresh->width-32; i+=4)
	{
		for (int j = 0; j < mini_thresh->height-16; j+=4)
		{
			/*
			Hàm cvCountNonZero: 
			http://opencv.willowgarage.com/documentation/c/core_operations_on_arrays.html?highlight=cvcountnonzero#cvCountNonZero
			- Trả về số lượng các điểm ảnh khác 0 trong 1 mảng các điểm ảnh
			- Do ảnh đầu vào là ảnh nhị phân (mini_thresh) 
			nên những điểm ảnh có giá trị khác 0 đều là 255 (màu trắng)
			- Thực hiện đếm những điểm ảnh màu trắng trong hình chữ nhật 8 x 16.
			*/
			rect = cvRect(i, j, 16, 8);
			cvSetImageROI(mini_thresh, rect);
			nonZero1 = cvCountNonZero(mini_thresh);
			cvResetImageROI(mini_thresh);

			rect = cvRect(i+16, j, 16, 8);
			cvSetImageROI(mini_thresh, rect);
			nonZero2 = cvCountNonZero(mini_thresh);
			cvResetImageROI(mini_thresh);

			rect = cvRect(i, j+8, 16, 8);
			cvSetImageROI(mini_thresh, rect);
			nonZero3 = cvCountNonZero(mini_thresh);
			cvResetImageROI(mini_thresh);

			rect = cvRect(i+16, j+8, 16, 8);
			cvSetImageROI(mini_thresh, rect);
			nonZero4 = cvCountNonZero(mini_thresh);
			cvResetImageROI(mini_thresh);

			// Nếu các vùng nonZero1 -> nonZero4 có nhiều hơn 15 điểm ảnh (màu trắng) thì thực hiện tăng biến cnt
			cnt = 0;
			if (nonZero1 > 15) { cnt++;	}   
			if (nonZero2 > 15) { cnt++;	}
			if (nonZero3 > 15) { cnt++;	}
			if (nonZero4 > 15) { cnt++;	}
			// thực hiện khoanh vùng
			if (cnt > 2)
			{
				rect = cvRect(i, j, 32, 16);
				cvSetImageROI(dst, rect);
				cvSetImageROI(mini_thresh, rect);
				cvCopy(mini_thresh, dst);
				cvResetImageROI(dst);
				cvResetImageROI(mini_thresh);
			}
		}
	}
	/*
	- sau khi lọc ảnh, thực hiện các thao tác gọi là dilate (giãn ảnh) và erode (làm nhòe) ảnh dst để làm rõ hơn nữa vùng có khả năng là biển số
	- cvDilate: http://opencv.willowgarage.com/documentation/c/imgproc_image_filtering.html?highlight=cvdilate#cvDilate
	- cvErode:  http://opencv.willowgarage.com/documentation/c/imgproc_image_filtering.html?highlight=cverode#cvErode
	*/

	IplImage* dst_clone = cvCloneImage(dst);

	cvDilate(dst, dst, NULL, 2);
	cvErode (dst, dst, NULL, 2);
	cvDilate (dst, dst, S1, 9);
	cvErode (dst, dst, S1, 10);
	cvDilate (dst, dst);

	if (flag)
	{
		cvDestroyAllWindows();
		cvShowImage("Source", src);  // Hiện ảnh gốc
		cvShowImage("1", src);       // Hiện ảnh nguồn sau khi đã nâng chất lượng
		cvShowImage("2", bothat);                               // Hiện ảnh đã tách biên
		cvShowImage("3", mini_thresh);    // Hiện ảnh nhị phân mini_thresh
		cvShowImage("4", dst_clone);     // Hiện ảnh đã làm rõ vùng biển số (đây là ảnh nhị phân)
		cvShowImage("5", dst); 
	}


	cvPyrUp(dst, src);    // Tăng độ tương phản

	cvReleaseImage(&mini_thresh);
	cvReleaseImage(&bothat);
	cvReleaseImage(&temp2);
	cvReleaseImage(&dst);
	cvReleaseImage(&src_pyrdown);
	cvReleaseImage(&thresholded);
}
/*
Trên cơ sở hàm waveletEdge , thực hiện khoanh vùng các khu vực có thể là biển số
*/
IplImage* LPR_PlateFinder::FindPlate(IplImage *src, bool show, int k)
{
	IplImage *C1    = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);    // Ảnh được tách biên
	IplImage *imggray = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);  // Ảnh xám	
	IplImage *clone = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);

	cvCvtColor(src, imggray, CV_RGB2GRAY);
	cvMerge(imggray, imggray, imggray, NULL, clone);

	CvMemStorage *storageexx = cvCreateMemStorage(0);  // tạo khối nhớ để lưu trữ các vùng có khả năng là biển số
	CvSeq *contours = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), storageexx); // chuỗi các hình chữ nhật khoanh vùng biển số

	// Copy ảnh src vào C1
	cvCopy(imggray, C1);
	cvNormalize(C1, C1, 0, 255, CV_MINMAX);  // Lọc nhiễu
	WaveletEdge(C1, show);						 // Gọi hàm waveletEdge

	double scale = 0.5;	                     // Tỉ lệ này dùng để tạo ra ảnh có kích thước phù hợp
	IplImage *imgsmall   = cvCreateImage(cvSize(C1->width*scale, C1->height*scale), 8, 1);
	IplImage *colorplate = cvCreateImage(cvSize(C1->width*scale, C1->height*scale), 8, 3);

	cvResize(C1, imgsmall);					// resize lại ảnh C1 bằng với kích thước của imgsmall
	cvMerge(imgsmall, imgsmall, imgsmall, NULL, colorplate);   // trộn ảnh

	// Hàm cvFindCountors:
	// http://opencv.willowgarage.com/documentation/python/imgproc_structural_analysis_and_shape_descriptors.html#findcontours
	// Tìm các nét trên ảnh imgsmall

	cvFindContours(imgsmall, storageexx, &contours, sizeof(CvContour),
		CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));  

	int xmin, ymin, xmax, ymax, rto, wdth, hgth, _rect;
	int count1;
	double ratio;
	CvRect rect;
	IplImage** plateArr = new IplImage *[5];
	int j = 0;

	for (int i = 0; i < 5; i++)
	{
		plateArr[i] = NULL;
	}

	while (contours)
	{
		count1 = contours->total;         // số lượng pixel trong 1 đường
		CvPoint *PointArray = new CvPoint[count1];  // mảng các điểm ảnh
		cvCvtSeqToArray(contours, PointArray, CV_WHOLE_SEQ);  // convert chuỗi sang 1 mảng các điểm ảnh

		for (int i = 0; i < count1; i++)
		{
			PointArray[i].x /= scale;
			PointArray[i].y /= scale;
			/*
			Với mỗi bộ các cạnh tìm được (đã được convert sang mảng các pixel) ta thực hiện tìm các hình chữ nhật trong đó
			Tọa độ các đỉnh của hình chữ nhật:
			+ Tọa độ đỉnh trên - bên trái: (xmin, ymin)
			+ Tọa độ đỉnh dưới - bên phải: (xmax, ymax)
			*/
			if(i == 0)
			{
				xmin = xmax = PointArray[i].x;  // Khởi gán các giá trị xmin, xmax, ymin, ymax
				ymin = ymax = PointArray[i].y;
			}

			if (PointArray[i].x > xmax)     xmax = PointArray[i].x;
			else
				if(PointArray[i].x < xmin)  xmin = PointArray[i].x;
			if(PointArray[i].y > ymax)      ymax = PointArray[i].y;
			else
				if(PointArray[i].y < ymin)  ymin = PointArray[i].y;
		}
		/*chiều rộng và dài của hình chữ nhật*/
		wdth = xmax - xmin;
		hgth = ymax - ymin;
		_rect = wdth*hgth;
		// vẽ ra hình chữ nhật (màu đỏ)
		cvRectangle(colorplate, cvPoint(xmin*scale, ymin*scale),
			cvPoint(xmin*scale + wdth*scale, ymin*scale + hgth*scale), RED);

		if(_rect != 0) rto = (C1->width*C1->height) / _rect; 
		else rto = 1000;

		if ((wdth == 0) && (hgth == 0))	ratio = 0;
		else ratio = (double)wdth/hgth;  // tỷ lệ chiều rộng trên chiều cao

		if (30 < rto && rto < 270)
		{
			// vẽ ra những hình chữ nhật (màu xanh lá) thỏa mãn điều kiện: 30 < rto < 270.
			// các hình chữ nhật này có thể được vẽ đè lên những hình màu đỏ ở trên.
			cvRectangle(colorplate,cvPoint(xmin*scale,ymin*scale),   
				cvPoint(xmin*scale+wdth*scale,ymin*scale+hgth*scale), GREEN);
			if(2.6<ratio && ratio<7)
			{
				// Nếu hình chữ nhật (màu xanh lá) nào thỏa mãn các điều kiện trên thì vẽ màu xanh dương
				// như vậy những hình chữ nhật màu xanh dương sẽ có khả năng là biển số cao nhất.
				cvRectangle(colorplate,cvPoint(xmin*scale,ymin*scale),
					cvPoint(xmin*scale+wdth*scale,ymin*scale+hgth*scale), BLUE); 
				if(80<wdth && wdth<250 && 25<hgth &&  hgth<150)
				{
					rect = cvRect(xmin, ymin, wdth, hgth);  //   Hình chữ nhật khoanh vùng biển số

					// Vẽ hình chữ nhật [hình rect ở trên]
					cvRectangle(clone,cvPoint(rect.x,rect.y),
						cvPoint(rect.x+rect.width,rect.y+rect.height), RED, 3);

					// Ảnh kết quả
					plate = cvCreateImage(cvSize(rect.width, rect.height), 8, 3);
					cvSetImageROI(src, rect);
					cvCopy(src, plate, NULL);	
					cvResetImageROI(src);

					int cnt = Count(plate);
					if (cnt >= 5)
					{
						plateArr[j] = plate;
						j++;
					}
				}
			}
		}
		delete []PointArray;

		contours = contours->h_next;
	} // end while


	if (plateArr[0])
	{
		double w = plateArr[0]->width;
		int flag;
		for (int i = 1; i < 4; i++)
		{
			if (plateArr[i] && plateArr[i]->width < w)
			{
				flag = i;
			}
		}

		plateArr[0] = plateArr[flag];
	}

	if (show)
	{
		cvShowImage("Plate 1", plate);
		cvShowImage("Imgsmall", imgsmall);
		cvShowImage("Colorplate", colorplate);	
	}

	cvReleaseImage(&C1);
	cvReleaseImage(&imgsmall);
	cvReleaseImage(&colorplate);
	delete []contours;

	return (k == 1) ? plateArr[0] : clone;
}


//Đếm các vùng có khả năng là kí tự
int LPR_PlateFinder:: Count(IplImage *plate)
{
	int i = 0;
	IplImage *resize, *rs_gray, *rs_binary;

	resize = cvCreateImage(cvSize(408 , 70 ), plate->depth, plate->nChannels);
	rs_gray = cvCreateImage(cvSize(408, 70), plate->depth, 1);
	rs_binary = cvCreateImage(cvSize(408, 70), plate->depth, 1);	
	
	cvResize(plate, resize);	
	cvCvtColor(resize, rs_gray, CV_RGB2GRAY);
	cvAdaptiveThreshold(rs_gray, rs_binary, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 13, 2);
	//cvShowImage("adaptive", rs_binary_clone);
	
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *contours = 0;
	
	cvFindContours(rs_binary, storage, &contours);
	
	while(contours)
	{
		CvRect  r = cvBoundingRect(contours, 0);
		if(r.width > 15 && r.width < 50 && r.height > 40 && r.height <65 && r.width * r.height > 1000)
		{
			//cvRectangle(resize, cvPoint(r.x, r.y), cvPoint(r.x + r.width, r.y + r.height), GREEN, 2); 
			i++;
		}
		contours = contours->h_next; 
	}
	//cvShowImage("Bounding", resize);
	return i;
}