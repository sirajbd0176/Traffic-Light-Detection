#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\core\core.hpp>
#include "opencv2/imgproc/types_c.h"
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include <conio.h>


using namespace std;
using namespace cv;

static void help()
{
	cout
		<< "------------------------------------------------------------------------------" << endl
		<< "This program shows how to write video files." << endl
		<< "You can extract the R or G or B color channel of the input video." << endl
		<< "Usage:" << endl
		<< "./video-write inputvideoName [ R | G | B] [Y | N]" << endl
		<< "------------------------------------------------------------------------------" << endl
		<< "Detect trafficlight  light and find the state of light---------------------------" << endl
		<< endl;
}
int main(int argc, char** argv)
{

	int redcount=0;
	int yellowcount = 0;

	/////////////load image start /////////////////////C:\Users\Mamone\Desktop\picture for TL
	string imageName("C:/Users/Mamone/Desktop/picture for TL/red.jpg");
	string imageNamery("C:/Users/Mamone/Desktop/picture for TL/red-yellow.jpg");
	string imageNamey("C:/Users/Mamone/Desktop/picture for TL/yellow.jpg");
	string imageNameg("C:/Users/Mamone/Desktop/picture for TL/green.jpg");
	if (argc > 1)
	{
		imageName = argv[1];
		imageNamery = argv[2];
		imageNamey = argv[3];
		imageNameg = argv[4];

	}
	Mat imagered, imageNamerry, imageNameY, imageNameG;
	imagered = imread(imageName.c_str(), IMREAD_COLOR); // Read the file
	imageNamerry = imread(imageNamery.c_str(), IMREAD_COLOR); // Read the file
	imageNameY = imread(imageNamey.c_str(), IMREAD_COLOR); // Read the file
	imageNameG = imread(imageNameg.c_str(), IMREAD_COLOR); // Read the file
	if (imagered.empty())                      // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
													//imshow("Display window", imagered);


													//waitKey(100);

													////////////////////////////////////load image end////////////////////

													///////////////***************Capter Start***********************////////////////////


	Mat image, src_gray;
	VideoCapture vcap;	// For Video Input

	bool WebCamFlag = true;	// Choosing video from Camera or files
	std::vector<KeyPoint> keypoints;

	/// Global Variables 1500---int DELAY_CAPTION = 1500;int DELAY_BLUR = 100;
	int DELAY_CAPTION = 30;
	int DELAY_BLUR = 30;
	int MAX_KERNEL_LENGTH = 1;//31;
	Mat vdst;

	if (WebCamFlag)

		vcap.open(0);	// Accesses webcamera 

	else
		vcap.open("scaleRotation.avi");//backSide //scaleRotation //illuminationVariation
									   // Utilizes video file in the same folder as source code, 
	if (!vcap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;

		return -1;
	}

	FeatureDetector* detector = NULL;

	while (1) {

		vcap >> image;
		imshow("Capture Vedio", image);
		char c = (char)waitKey(10);
		if (c == 27)
			break;
	}

	///////////////////////////Capture finish***************////////////////

	/*Reading from video file trt*/
	//VideoCapture cap("E:/LTVedio/TL1.mp4");
	//VideoCapture cap("E:/LTVedio/TL2.mp4");
	//VideoCapture cap("E:/LTVedio/TL-R.mp4");
	
	VideoCapture cap("E:/LTVedio/TL-R-Y.mp4");
	//VideoCapture cap("E:/LT Vedio/TL-G.mp4");
	//VideoCapture cap("E:/LT Vedio/Traffic.mp4");
	//open the video file for reading
	// if not success, exit program
	//display picture 

	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video file" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	//get the frames rate of the video
	double fps = cap.get(CAP_PROP_FPS);
	cout << "Frames per seconds : " << fps << endl;

	String window_name = " Traffic Light Detection";

	namedWindow(window_name, WINDOW_NORMAL); //create a window
	if(redcount>0)
	{
   level:
	{
		std::cout << "*****Red--Yellow" << std::endl;
		imshow("Display window", imageNamerry);
	}
	}

while (true)
	{
		Mat frame;
		// read a new frame from video 

		//Breaking the while loop at the end of the video

		bool bSuccess;
		if (bSuccess = cap.read(frame));

		else
		{
			cout << "Found the end of the video" << endl;
			break;
		}
		imshow(window_name, frame);

		// Transform it into the C++ cv::Mat format
		cv::Mat image(frame);
		/// << "\nHeight and Width: " << frame.size;

		int offset_x = 129;
		int offset_y = 129;

		cv::Rect roi;
		roi.x = offset_x;
		roi.y = offset_y;
		roi.width = frame.size().width - (offset_x * 2);
		double xx = frame.size().height - (offset_y * 2);
		roi.height = xx * .9;
		cv::Mat croppedImage = image(roi);

		//cv::Mat  hsv;
		//cv::cvtColor(croppedImage, hsv, CV_RGB2HSV);
		//cv::Mat dst;
		Mat gray;
		cvtColor(croppedImage, gray, COLOR_BGR2GRAY);//hsv
	//	medianBlur(gray, gray, 5);//5
		/// Reduce the noise so we avoid false circle detection
		GaussianBlur(gray, gray, Size(9, 9), 1, 1);//GaussianBlur( gray, gray, Size(9, 9),1,1 );
		vector<Vec3f> circles;
		HoughCircles(gray, circles, HOUGH_GRADIENT, 1,  //1
			gray.rows / 16,  //16 change this value to detect circles with different distances to each other/16
			100, 20, 20, 33 // change the last two parameters100,30,18,33
							// (min_radius & max_radius) to detect larger circles
		);

		for (size_t i = 0; i < circles.size(); i++)
		{
			Vec3i c = circles[i];
			Point center = Point(c[0], c[1]);//
											 // circle center
											 //******circle(croppedImage, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
											 // circle outline
											 //imshow(" zzzzzzzzzzzzzzzzblinking light", croppedImage);
			int radius = c[2];
			double area = 3.14*radius*radius;

			//if (25<radius && radius <30 && 2100 < area && area< 2650 20<radius && radius <35 &&)
			if (1900 <area && area< 2800)
			{
				//3
				circle(croppedImage, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
				//	imshow("Detecting Circle in orginal", croppedImage);
				//	cout << "CENTER Croped Image:----" << center << "center XXX  " << center.x << "center YYY  " << center.y;   ///<< "center rgb:-----" << center1<<"XX"<<center.x ;
				////Scalar intensity = croppedImage.at<uchar>(center.x, center.y);


				Point3_<uchar>* p = croppedImage.ptr<Point3_<uchar> >(center.y, center.x);

				int B = p->z; //R
				int G = p->y; //G
				int R = p->x;//B
				//imshow(" blinking light", croppedImage);
				imshow(" blinking light", croppedImage);
				int red, yellow, green;
				//if ((85<R&&R<160) && (85<G&&G<155) && (180 <= B && B <= 255))
			if ((30<R&&R<170) && (36<G&&G<145) && (180 <= B && B <= 255))
				///yellow  if ((0 < R&&R < 85) && (170 < G&&G < 215) && (180 <B&& B <= 255))
				{
					//cout << "1*Red" <<endl;

					///cout << "\033[1;31mbold red text\033[0m\n";
					//imshow("Red **Yellow Lighr is blinking", croppedImage);
					//system("color A1");
					std::cout << "*****Red" << std::endl;
					if ((redcount > 2) && (yellowcount > 2))// goto level;
					imshow("Display window", imagered);
					redcount++;
					//waitKey(2);
					//break;

				}

			int d;
				if ((24 < R&&R < 85) && (150 < G&&G < 215) && (180 <B&& B <= 255))
				{
					cout << "*****Yellow " << endl;
					//imshow("Yellow", croppedImage);
					//imshow("Display window", imageNamerry);Diff(2,5) => 3
					
					if (redcount >= yellowcount)
						d = redcount - yellowcount;
					else
						d = yellowcount - redcount;
					cout << d << endl;
					if ((redcount > 2) && (yellowcount > 2) && d<4) goto level;
						//&& diff(redcount,yellowcount)<3))) goto level;
					imshow("Display window", imageNameY);
					//waitKey(2);
					//break;
					yellowcount++;
				}

				if ((70 < R&&R <200) && (85 < G&&G < 230) && (0 <= B && B <= 60))
				{
					d = 0;
					redcount = 0;
					yellowcount = 0;
					cout << "****Green " << endl;
					imshow("Display window", imageNameG);
					///	imshow("Green Circle in orginal", croppedImage);
				}
			}
		}
		cout <<"rad:"<< redcount << "yellow"<< yellowcount<<endl;
		if (waitKey(10) == 27)
		{
			cout << "Esc key is pressed by user. Stoppig the video" << endl;
			break;
		}
	}

	return 0;

	cout << "Frame per seconds : " << fps << endl;

}
