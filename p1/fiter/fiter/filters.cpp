/*------------------------------------------------------------------------------------------*\
This file contains material supporting chapter 6 of the book:
OpenCV3 Computer Vision Application Programming Cookbook
Third Edition
by Robert Laganiere, Packt Publishing, 2016.

This program is free software; permission is hereby granted to use, copy, modify,
and distribute this source code, or portions thereof, for any purpose, without fee,
subject to the restriction that the copyright notice may not be remove
or altered from any source or altered source distribution.
The software is released on an as-is basis and without any warranties of any kind.
In particular, the software is not guaranteed to be fault-tolerant or free from failure.
The author disclaims all warranties with regard to this software, any use,
and any consequent failure, is purely the responsibility of the user.

Copyright (C) 2016 Robert Laganiere, www.laganiere.name
\*------------------------------------------------------------------------------------------*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <random>

// Add salt noise to an image function
void s_and_p(cv::Mat image, int n) {

	// C++11 random number generator
	std::default_random_engine generator;
	std::uniform_int_distribution<int> randomRow(0, image.rows - 1);
	std::uniform_int_distribution<int> randomCol(0, image.cols - 1);

	int i, j;
	for (int k = 0; k<n; k++) {

		// random image coordinate
		i = randomCol(generator);
		j = randomRow(generator);

		if (image.type() == CV_8UC1) { // gray-level image

									   // single-channel 8-bit image
			image.at<uchar>(j, i) = 255;

		}
		else if (image.type() == CV_8UC3) { // color image

											// 3-channel image
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;

			// or simply:
			// image.at<cv::Vec3b>(j, i) = cv::Vec3b(255, 255, 255);
		}
	}

	for (int k = 0; k<n; k++) {

		// random image coordinate
		i = randomCol(generator);
		j = randomRow(generator);

		if (image.type() == CV_8UC1) { // gray-level image

									   // single-channel 8-bit image
			image.at<uchar>(j, i) = 0;

		}
		else if (image.type() == CV_8UC3) { // color image

											// 3-channel image
			image.at<cv::Vec3b>(j, i)[0] = 0;
			image.at<cv::Vec3b>(j, i)[1] = 0;
			image.at<cv::Vec3b>(j, i)[2] = 0;
				
		}
	}
}

int main()
{
	// Read input image
	cv::Mat image= cv::imread("mumu1.jpg",1);
	if (!image.data)
		return 0; 

    // Display the image
	cv::namedWindow("Original Image");
	cv::imshow("Original Image",image);

	//define
	cv::Mat result;
	
	//Mean fiter
	/*
	// Blur the image with a mean filter 5x5
	cv::blur(image, result, cv::Size(5, 5));

	// Display the blurred image
	cv::namedWindow("Mean filtered Image (5x5)");
	cv::imshow("Mean filtered Image (5x5)", result);

	// Blur the image with a mean filter 9x9
	cv::blur(image, result, cv::Size(9, 9));

	// Display the blurred image
	cv::namedWindow("Mean filtered Image (9x9)");
	cv::imshow("Mean filtered Image (9x9)", result);
    
	// Blur the image with a mean filter 13x13
	cv::blur(image, result, cv::Size(13, 13));

	// Display the blurred image
	cv::namedWindow("Mean filtered Image (13x13)");
	cv::imshow("Mean filtered Image (13x13)", result);
	//*/
	
	//Gaussian fiter
	/*
	// Gaussian Blur the image
	cv::GaussianBlur(image,result,
		  cv::Size(5,5), // size of the filter
		  15);			 // parameter controlling the 
						 // shape of the Gaussian

    // Display the blurred image
	cv::namedWindow("Gaussian filtered Image (5x5)");
	cv::imshow("Gaussian filtered Image (5x5)",result);

	cv::GaussianBlur(image,result,cv::Size(9,9),15);

    // Display the blurred image
	cv::namedWindow("Gaussian filtered Image (9x9)");
	cv::imshow("Gaussian filtered Image (9x9)",result);

	cv::GaussianBlur(image, result, cv::Size(13, 13), 15);

	// Display the blurred image
	cv::namedWindow("Gaussian filtered Image (13x13)");
	cv::imshow("Gaussian filtered Image (13x13)", result);
	//*/
	//Get the gaussian kernel
	/*
	// Get the gaussian kernel (1.5)
	cv::Mat gauss= cv::getGaussianKernel(9,1.5,CV_32F);
		  
	// Display kernel values
	cv::Mat_<float>::const_iterator it= gauss.begin<float>();  
	cv::Mat_<float>::const_iterator itend= gauss.end<float>();  
	std::cout << "1.5 = [";
	for ( ; it!= itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	// Get the gaussian kernel (0.5)
	gauss= cv::getGaussianKernel(9,0.5,CV_32F);
		  
	// Display kernel values
	it= gauss.begin<float>();  
	itend= gauss.end<float>();  
	std::cout << "0.5 = [";
	for ( ; it!= itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	// Get the gaussian kernel (2.5)
	gauss= cv::getGaussianKernel(9,2.5,CV_32F);
		  
	// Display kernel values
	it= gauss.begin<float>();  
	itend= gauss.end<float>();  
	std::cout << "2.5 = [";
	for ( ; it!= itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	// Get the gaussian kernel (9 elements)
	gauss= cv::getGaussianKernel(9,-1,CV_32F);
		  
	// Display kernel values
	it= gauss.begin<float>();  
	itend= gauss.end<float>();  
	std::cout << "9 = [";
	for ( ; it!= itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	// Get the Deriv kernel (2.5)
	cv::Mat kx, ky;
    cv::getDerivKernels(kx,ky,2,2,7,true);
		  
	// Display kernel values
	cv::Mat_<float>::const_iterator kit= kx.begin<float>();  
	cv::Mat_<float>::const_iterator kitend= kx.end<float>();  
	std::cout << "[";
	for ( ; kit!= kitend; ++kit) {
		std::cout << *kit << " ";
	}
	std::cout << "]" << std::endl;
	//*/

	//Median fiter
	/*
	// Blur the image with a medianBlur filter 5x5
	cv::medianBlur(image, result, 5);

	// Display the blurred image
	cv::namedWindow("MedianBlur filtered Image (5x5)");
	cv::imshow("MedianBlur filtered Image (5x5)", result);

	// Blur the image with a medianBlur filter 9x9
	cv::medianBlur(image, result, 9);

	// Display the blurred image
	cv::namedWindow("MedianBlur filtered Image (9x9)");
	cv::imshow("MedianBlur filtered Image (9x9)", result);

	// Blur the image with a medianBlur filter 13x13
	cv::medianBlur(image, result, 13);

	// Display the blurred image
	cv::namedWindow("MedianBlur filtered Image (13x13)");
	cv::imshow("MedianBlur filtered Image (13x13)", result);
	//*/

	//Add noise
	/*
	// Process image with salt&pepper noise (denoise)
	s_and_p(image, 3000);

    // Display the S&P image
	cv::namedWindow("S&P Image");
	cv::imshow("S&P Image",image);
	cv::imwrite("Csalted.bmp", image);
	//*/

	//Read noise image
	///*
	//Read image with salt&pepper noise
	image = cv::imread("Csalted.bmp", 1);
	if (!image.data)
		return 0;

	// Display the S&P image
	cv::namedWindow("S&P Image");
	cv::imshow("S&P Image", image);
	//*/

	//Mean fiter
	///*
	// Blur the image with a mean filter 5x5
	cv::blur(image,result,cv::Size(5,5));
		
    // Display the blurred image
	cv::namedWindow("Mean filtered S&P Image (5x5)");
	cv::imshow("Mean filtered S&P Image (5x5)",result);

	// Blur the image with a mean filter 9x9
	cv::blur(image, result, cv::Size(9, 9));

	// Display the blurred image
	cv::namedWindow("Mean filtered S&P Image (9x9)");
	cv::imshow("Mean filtered S&P Image (9x9)", result);

	// Blur the image with a mean filter 13x13
	cv::blur(image, result, cv::Size(13, 13));

	// Display the blurred image
	cv::namedWindow("Mean filtered S&P Image (13x13)");
	cv::imshow("Mean filtered S&P Image (13x13)", result);
	//*/

	//Gaussian fiter
	///*
	// Gaussian Blur the image 5x5
	cv::GaussianBlur(image, result,	cv::Size(5, 5), 15);			 
						 
	// Display the blurred image
	cv::namedWindow("Gaussian filtered Image (5x5)");
	cv::imshow("Gaussian filtered Image (5x5)", result);

	// Gaussian Blur the image 9x9
	cv::GaussianBlur(image, result, cv::Size(9, 9), 15);

	// Display the blurred image
	cv::namedWindow("Gaussian filtered Image (9x9)");
	cv::imshow("Gaussian filtered Image (9x9)", result);

	// Gaussian Blur the image 13x13
	cv::GaussianBlur(image, result, cv::Size(13, 13), 15);

	// Display the blurred image
	cv::namedWindow("Gaussian filtered Image (13x13)");
	cv::imshow("Gaussian filtered Image (13x13)", result);
	//*/

	//Median fiter
	///*
	// Applying a median filter 5x5
	cv::medianBlur(image,result,5);
		
    // Display the blurred image
	cv::namedWindow("Median filtered Image (5x5)");
	cv::imshow("Median filtered Image (5x5)",result);

	// Applying a median filter 9x9
	cv::medianBlur(image, result, 9);

	// Display the blurred image
	cv::namedWindow("Median filtered Image (9x9)");
	cv::imshow("Median filtered Image (9x9)", result);

	// Applying a median filter 13x13
	cv::medianBlur(image, result, 13);

	// Display the blurred image
	cv::namedWindow("Median filtered Image (13x13)");
	cv::imshow("Median filtered Image (13x13)", result);
	//*/

	//Reduce image size
	/*
	// Reduce by 4 the size of the image (the wrong way)
	image= cv::imread("boldt.jpg",0);
	cv::Mat reduced(image.rows / 4, image.cols / 4, CV_8U);

	for (int i=0; i<reduced.rows; i++)
		for (int j=0; j<reduced.cols; j++)
			reduced.at<uchar>(i,j)= image.at<uchar>(i*4,j*4);

    // Display the reduced image
	cv::namedWindow("Badly reduced Image");
	cv::imshow("Badly reduced Image",reduced);

	cv::resize(reduced,reduced, cv::Size(), 4, 4, cv::INTER_NEAREST);

    // Display the (resized) reduced image
	cv::namedWindow("Badly reduced");
	cv::imshow("Badly reduced",reduced);

	cv::imwrite("badlyreducedimage.bmp",reduced);

	// first remove high frequency component
	cv::GaussianBlur(image, image, cv::Size(11,11), 1.75);
	// keep only 1 of every 4 pixels
	cv::Mat reduced2(image.rows/4, image.cols/4, CV_8U);
	for (int i=0; i<reduced2.rows; i++)
		for (int j=0; j<reduced2.cols; j++)
			reduced2.at<uchar>(i,j)= image.at<uchar>(i*4,j*4);

    // Display the reduced image
	cv::namedWindow("Reduced Image, original size");
	cv::imshow("Reduced Image, original size",reduced2);

	cv::imwrite("reducedimage.bmp",reduced2);

	// resizing with NN
	cv::Mat newImage;
	cv::resize(reduced2, newImage, cv::Size(), 4, 4, cv::INTER_NEAREST);

    // Display the (resized) reduced image
	cv::namedWindow("Reduced Image");
	cv::imshow("Reduced Image",newImage);

	// resizing with bilinear
	cv::resize(reduced2, newImage, cv::Size(), 4, 4, cv::INTER_LINEAR);

	// Display the (resized) reduced image
	cv::namedWindow("Bilinear resizing");
	cv::imshow("Bilinear resizing", newImage);
	
	// Creating an image pyramid
	cv::Mat pyramid(image.rows, image.cols + image.cols/2 + image.cols/4 + image.cols/8, CV_8U, cv::Scalar(255));
	image.copyTo(pyramid(cv::Rect(0, 0, image.cols, image.rows)));

	cv::pyrDown(image, reduced); // reduce image size by half
	reduced.copyTo(pyramid(cv::Rect(image.cols, image.rows/2, image.cols/2, image.rows/2)));
	cv::pyrDown(reduced, reduced2); // reduce image size by another half
	reduced2.copyTo(pyramid(cv::Rect(image.cols + image.cols/2, image.rows - image.rows/4, image.cols/4, image.rows/4)));
	cv::pyrDown(reduced2, reduced); // reduce image size by another half
	reduced.copyTo(pyramid(cv::Rect(image.cols + image.cols/2 + image.cols/4, image.rows - image.rows/8, image.cols/8, image.rows/8)));

    // Display the pyramid
	cv::namedWindow("Pyramid of images");
	cv::imshow("Pyramid of images", pyramid);
	*/
	
	
	cv::waitKey();
	return 0;
}
