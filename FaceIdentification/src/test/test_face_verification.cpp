/*
*
* This file is part of the open-source SeetaFace engine, which includes three modules:
* SeetaFace Detection, SeetaFace Alignment, and SeetaFace Identification.
*
* This file is part of the SeetaFace Identification module, containing codes implementing the
* face identification method described in the following paper:
*
*
*   VIPLFaceNet: An Open Source Deep Face Recognition SDK,
*   Xin Liu, Meina Kan, Wanglong Wu, Shiguang Shan, Xilin Chen.
*   In Frontiers of Computer Science.
*
*
* Copyright (C) 2016, Visual Information Processing and Learning (VIPL) group,
* Institute of Computing Technology, Chinese Academy of Sciences, Beijing, China.
*
* The codes are mainly developed by Jie Zhang(a Ph.D supervised by Prof. Shiguang Shan)
*
* As an open-source face recognition engine: you can redistribute SeetaFace source codes
* and/or modify it under the terms of the BSD 2-Clause License.
*
* You should have received a copy of the BSD 2-Clause License along with the software.
* If not, see < https://opensource.org/licenses/BSD-2-Clause>.
*
* Contact Info: you can send an email to SeetaFace@vipl.ict.ac.cn for any problems.
*
* Note: the above information must be kept whenever or wherever the codes are used.
*
*/

#include<iostream>
using namespace std;
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#ifdef _WIN32
#pragma once
#include <opencv2/core/version.hpp>

#define CV_VERSION_ID CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) \
  CVAUX_STR(CV_SUBMINOR_VERSION)

#ifdef _DEBUG
#define cvLIB(name) "opencv_" name CV_VERSION_ID "d"
#else
#define cvLIB(name) "opencv_" name CV_VERSION_ID
#endif //_DEBUG

#pragma comment( lib, cvLIB("core") )
#pragma comment( lib, cvLIB("imgproc") )
#pragma comment( lib, cvLIB("highgui") )

#endif //_WIN32

#if defined(__unix__) || defined(__APPLE__)

#ifndef fopen_s

#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL

#endif //fopen_s

#endif //__unix

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "face_identification.h"
#include "recognizer.h"
#include "face_detection.h"
#include "face_alignment.h"

#include "math_functions.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace seeta;

#define TEST(major, minor) major##_##minor##_Tester()
#define EXPECT_NE(a, b) if ((a) == (b)) std::cout << "ERROR: "
#define EXPECT_EQ(a, b) if ((a) != (b)) std::cout << "ERROR: "

#ifdef _WIN32
std::string DATA_DIR = "../../data/";
std::string MODEL_DIR = "../../model/";
#else
std::string DATA_DIR = "./data/";
std::string MODEL_DIR = "./model/";
#endif

std::string IMAGE_DIR = "images/compare_im/";

int main(int argc, char* argv[]) {
  // Initialize face detection model
  seeta::FaceDetection detector("./build/seeta_fd_frontal_v1.0.bin");
  detector.SetMinFaceSize(40);
  detector.SetScoreThresh(2.f);
  detector.SetImagePyramidScaleFactor(0.8f);
  detector.SetWindowStep(4, 4);

  std::cout<<"this is right, sizeof(detector->facial_detector) is" << sizeof(detector.impl_)<<std::endl;
  // Initialize face alignment model 
  seeta::FaceAlignment point_detector((MODEL_DIR + "seeta_fa_v1.1.bin").c_str());

   std::cout<<"Initialize is right, sizeof(point_detector) is " << sizeof(point_detector.facial_detector)<<std::endl;

  // Initialize face Identification model 
  FaceIdentification face_recognizer((MODEL_DIR + "seeta_fr_v1.0.bin").c_str());
  std::cout<<"sizeof(face_recognizer) is " << sizeof(face_recognizer.recognizer) << std::endl;
  std::string test_dir = DATA_DIR + "test_face_recognizer/";
  std::cout<<"test_dir is "<<test_dir<<std::endl;
  //load image
  char * filename1 = argv[1];
  char* filename2 = argv[2];
  //cv::Mat gallery_img_color = cv::imread(test_dir + IMAGE_DIR + argv[1], 1);
  cv::Mat gallery_img_color = cv::imread(filename1,1);
  if(!gallery_img_color.data)
  {
    cout << "Cannot Open!!" << endl;
  }

  /*show */
  //cv::namedWindow("test");
  //cv::imshow("test", gallery_img_color);
  //cv::waitKey(0);
  //cv::destroyWindow("test");

  cv::Mat gallery_img_gray;
  cv::cvtColor(gallery_img_color, gallery_img_gray, CV_BGR2GRAY);
  std::cout<<"get gray img1"<<std::endl;

  //cv::Mat probe_img_color = cv::imread(test_dir + IMAGE_DIR + argv[2], 1);
  cv::Mat probe_img_color = cv::imread(filename2,1);
  if(!probe_img_color.data)
  {     
    cout << "Cannot Open!!" << endl;
  } 
  cv::Mat probe_img_gray;
  cv::cvtColor(probe_img_color, probe_img_gray, CV_BGR2GRAY);
  std::cout<<"get gray img2"<<std::endl;

  ImageData gallery_img_data_color(gallery_img_color.cols, gallery_img_color.rows, gallery_img_color.channels());
  gallery_img_data_color.data = gallery_img_color.data;

  std::cout<<"gallery_img_data_color"<<std::endl;

  seeta::ImageData gallery_img_data_gray;
  gallery_img_data_gray.data = gallery_img_gray.data;
  gallery_img_data_gray.num_channels = gallery_img_gray.channels();
  gallery_img_data_gray.height = gallery_img_gray.rows;
  gallery_img_data_gray.width = gallery_img_gray.cols;
  std::cout<<"gallery_img_data_gray"<<std::endl;

  ImageData probe_img_data_color(probe_img_color.cols, probe_img_color.rows, probe_img_color.channels());
  probe_img_data_color.data = probe_img_color.data;
  std::cout<<"probe_img_data_color"<<std::endl;

  seeta::ImageData probe_img_data_gray;
  probe_img_data_gray.data = probe_img_gray.data;
  probe_img_data_gray.num_channels = probe_img_gray.channels();
  probe_img_data_gray.height = probe_img_gray.rows;
  probe_img_data_gray.width = probe_img_gray.cols;
  std::cout<<"probe_img_data_gray"<<std::endl;

  // Detect faces
  std::cout<<"probe_img_data_gray " << probe_img_gray.cols << " " << probe_img_gray.rows<<" "<< probe_img_data_gray.num_channels<<std::endl;
  std::vector<seeta::FaceInfo> gallery_faces = detector.Detect(gallery_img_data_gray);
  std::cout<<"faceInfo "<<std::endl;
  int32_t gallery_face_num = static_cast<int32_t>(gallery_faces.size());
  std::cout<<"gallery_face_num "<<std::endl;

  for(int i = 0; i<gallery_faces.size(); i++) {
     std::cout << gallery_faces[i].roll << " "<< gallery_faces[i].pitch << " "
               << gallery_faces[i].yaw << std::endl;
     std::cout << gallery_faces[i].bbox.x << " " << gallery_faces[i].bbox.y << " "
               << gallery_faces[i].bbox.width << " " << gallery_faces[i].bbox.height<<std::endl;
  }
  std::vector<seeta::FaceInfo> probe_faces = detector.Detect(probe_img_data_gray);
  int32_t probe_face_num = static_cast<int32_t>(probe_faces.size());
  std::cout<<"detect faces" <<endl;

  if (gallery_face_num == 0 || probe_face_num==0)
  {
    std::cout << "Faces are not detected.";
    return 0;
  }

  // Detect 5 facial landmarks
  seeta::FacialLandmark gallery_points[5];
  point_detector.PointDetectLandmarks(gallery_img_data_gray, gallery_faces[0], gallery_points);
  for(int i  = 0; i<5;++i) {
    std::cout<<gallery_points[i].x<<" "<<gallery_points[i].y<<endl;
  }

  seeta::FacialLandmark probe_points[5];
  point_detector.PointDetectLandmarks(probe_img_data_gray, probe_faces[0], probe_points);
  for(int i  = 0; i<5;++i) {
    std::cout<< probe_points[i].x<<" "<< probe_points[i].y<<endl;
  }

  for (int i = 0; i<5; i++)
  {
    cv::circle(gallery_img_color, cv::Point(gallery_points[i].x, gallery_points[i].y), 2,
      CV_RGB(0, 255, 0));
    cv::circle(probe_img_color, cv::Point(probe_points[i].x, probe_points[i].y), 2,
      CV_RGB(0, 255, 0));
  }
  cv::imwrite("gallery_point_result.jpg", gallery_img_color);
  cv::imwrite("probe_point_result.jpg", probe_img_color);

  // Extract face identity feature
  float gallery_fea[2048] = {0.0};
  float probe_fea[2048] = {0.0};
  face_recognizer.ExtractFeatureWithCrop(gallery_img_data_color, gallery_points, gallery_fea);
  face_recognizer.ExtractFeatureWithCrop(probe_img_data_color, probe_points, probe_fea);

  // Caculate similarity of two faces
  float sim = face_recognizer.CalcSimilarity(gallery_fea, probe_fea);
  std::cout << sim <<endl;

  for(int i = 0; i<2048; i++) {
      std::cout<< gallery_fea[i]<<" ";
  }
  std::cout<<std::endl;
  for(int i = 0; i<2048; i++) {
      std::cout<< probe_fea[i]<<" ";
  }



  return 0;
}


