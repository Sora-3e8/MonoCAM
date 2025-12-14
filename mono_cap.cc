#include <thread>
#include <chrono>
#include <iostream>
#include "mono_cap.h"
#include "app_utils.h"




camera_stream::camera_stream(int id=0, int width = 480, int height = 360, int fps = 60, bool mirror = false)
{
  #ifdef __DEBUG__
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_INFO);
  #endif

  #ifndef __DEBUG__
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
  #endif
  device = cv::VideoCapture();
  this->mirror = mirror;
  device_index = id; 
  capture_width = width;
  capture_height = height;
  capture_fps = fps;
  cam_backend = (apputils::osutils::OSNAME() != "Linux") ? cv::CAP_ANY : cv::CAP_V4L2;
}

void camera_stream::start_stream()
{
  device.set(cv::CAP_PROP_FRAME_WIDTH,capture_width);
  device.set(cv::CAP_PROP_FRAME_HEIGHT,capture_height);
  device.set(cv::CAP_PROP_FPS,capture_fps);
  device.setExceptionMode(true);
  _keep_frame_loop = true;
  std::thread t_cam = std::thread(&camera_stream::frame_loop,this);
  t_cam.detach();
}

void camera_stream::stop_stream()
{
  _keep_frame_loop = false;
   device.release();
}

bool camera_stream::save_image(std::string filepath)
{
  bool save_success = false;
  try
  {
    save_success =  cv::imwrite(filepath,_frame2);
  }
  catch(std::exception &e){std::cout << "Saving file error: " << "\n\t" << e.what() << std::endl; }
  
  return save_success;
}

bool camera_stream::cam_available()
{
   cv::VideoCapture temp_camera(this->device_index, this->cam_backend);
   bool res = temp_camera.isOpened();
   temp_camera.release();
   return res;
}

void camera_stream::frame_loop()
{
  const std::lock_guard<std::mutex> lock(frame_mutex);
   
  // This loop keeps running until told otherwise ==> awaits device
  while(_keep_frame_loop)
  {
    if(cam_available())
    {
    // Attempts to open camera by device_id 
    try 
    {
      #ifdef __DEBUG__
        std::cout << "Trying to open device..." << std::endl;
      #endif
      device.open(device_index,cam_backend);
    }
    catch(std::exception &e)
    { 
      #ifdef __DEBUG__
        std::cout << "Opening device failed: " << e.what() << std::endl;
      #endif

    }

    // Starts if 
    while(device.isOpened())
    { 
   
      try {frame_valid = (device.read(_frame) && _frame.empty()==false); }
      catch(std::exception &e){
        frame_valid = false;
        device.release();
      }

      if(frame_valid)
      {
        if(mirror){cv::flip(_frame,_frame2,1);} else { _frame2 = _frame; }
        cv::cvtColor(_frame2,frame, cv::COLOR_BGR2RGB); 
      }
    } 
  device.release();
  #ifdef __DEBUG__
  std::cout << "Device closed" << std::endl;
  #endif
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

 }
}
