#include <thread>
#include <chrono>
#include <iostream>
#include "mono_cap.h"


std::string OsName()
{
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}

camera_stream::camera_stream(int id=0, int width = 480, int height = 360, int fps = 30)
{
  device = cv::VideoCapture();
  device_index = id; 
  capture_width = width;
  capture_height = height;
  capture_fps = fps;
  cam_backend = (OsName() != "Linux") ? cv::CAP_ANY : cv::CAP_V4L2;
}

void camera_stream::start_stream()
{
  device.set(cv::CAP_PROP_FRAME_WIDTH,capture_width);
  device.set(cv::CAP_PROP_FRAME_HEIGHT,capture_height);
  device.set(cv::CAP_PROP_FPS,capture_fps);
  _keep_frame_loop = true;
  std::thread t_cam = std::thread(sigc::mem_fun(*this,&camera_stream::frame_loop));
  t_cam.detach();
}
void camera_stream::stop_stream()
{
  _keep_frame_loop = false;
  device.release();
}

void camera_stream::frame_loop()
{
  // This loop keeps running until told otherwise ==> awaits device
  while(_keep_frame_loop)
  {
    // Attempts to open camera by device_id 
    try { device.open(device_index,cv::CAP_V4L2); }
    catch(std::exception &e){ std::cout << "Could not open the device:" << '\n' << e.what() << std::endl; }
    
    // Starts if 
    while(device.isOpened())
    {
      device.read(_frame);
      if(_frame.empty()){ break; }
      else
      {
        cv::Mat mirrored;
        cv::flip(_frame,mirrored,1);
        cv::cvtColor(mirrored.clone(),frame, cv::COLOR_BGR2RGB);
      }
    }
  std::cout << "Device closed" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
 }
}
