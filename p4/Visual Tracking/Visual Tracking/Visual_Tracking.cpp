#include <stdio.h>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/bgsegm.hpp>
#include <iostream>
#include <cstring>

using namespace std;
using namespace cv;
int main() {
	// declares all required variables
	char filename[128];
	Rect2d roi_kcf, roi_mil, roi_tld, roi_boost, roi_medianflow;
	Mat frame;
	VideoWriter video_out;
	Size videoSize;
	int fps;
	// create a tracker object
	Ptr<Tracker> trackerKCF = Tracker::create("KCF");
	Ptr<Tracker> trackerMIL = Tracker::create("MIL");
	Ptr<Tracker> trackerBOOSTING = Tracker::create("BOOSTING");
	Ptr<Tracker> trackerTLD = Tracker::create("TLD");
	Ptr<Tracker> trackerMEDIANFLOW = Tracker::create("MEDIANFLOW");
	/*//check img file
	cv::Mat image; // create an empty image
	std::string name = "Jump/img/0001.jpg";
	// read the input image as a gray-scale image
	image = cv::imread(name, cv::IMREAD_GRAYSCALE);

	if (image.empty()) {  // error handling
						  // no image has been created...
						  // possibly display an error message
						  // and quit the application 
		std::cout << "Error reading image..." << std::endl;
		return 0;
	}
	*/

	// set input video
	std::string video = "Woman/img/%04d.jpg";
	VideoCapture cap(video);
	// get bounding box
	cap >> frame;
	roi_kcf = selectROI("tracker", frame);
	roi_mil = roi_kcf;
	roi_tld = roi_kcf;
	roi_boost = roi_kcf;
	roi_medianflow = roi_kcf;
	//videowriter setting
	videoSize = Size(frame.cols, frame.rows);
	fps = cap.get(CV_CAP_PROP_FPS);
	sprintf_s(filename, "Woman.avi");
	video_out.open(filename, CV_FOURCC('M', 'P', 'E', 'G'), fps, videoSize);

	// initialize the tracker
	trackerKCF->init(frame, roi_kcf);
	trackerMIL->init(frame, roi_mil);
	trackerTLD->init(frame, roi_tld);
	trackerBOOSTING->init(frame, roi_boost);
	trackerMEDIANFLOW->init(frame, roi_medianflow);
	// perform the tracking process
	printf("Start the tracking process, press ESC to quit.\n");
	for (;; ) {
		// get frame from the video
		cap >> frame;
		// stop the program if no more images
		if (frame.rows == 0 || frame.cols == 0)
			break;
		// update the tracking result and draw the tracked object
		trackerKCF->update(frame, roi_kcf);
		rectangle(frame, roi_kcf, Scalar(255, 0, 0), 2, 1); //KCF blue
		trackerMIL->update(frame, roi_mil);
		rectangle(frame, roi_mil, Scalar(0, 255, 0), 2, 1); //MIL green
		trackerTLD->update(frame, roi_tld);
		rectangle(frame, roi_tld, Scalar(0, 0, 255), 2, 1); //TLD red
		trackerBOOSTING->update(frame, roi_boost);
		rectangle(frame, roi_boost, Scalar(255, 255, 0), 2, 1); //BOOSTING sky blue
		trackerMEDIANFLOW->update(frame, roi_medianflow);
		rectangle(frame, roi_medianflow, Scalar(255, 0, 255), 2, 1); //MEDIANFLOW pink

														   // show image with the tracked object
		imshow("tracker", frame);
		//write
		video_out.write(frame);
		//quit on ESC button
		if (waitKey(1) == 27)break;
	}
	video_out.release();
	return 0;
}