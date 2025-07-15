#include <thread>
#include <chrono>
#include <iostream>
#include "mono_cap.h"

camera_stream::camera_stream(int id=NULL, int width=NULL, int height=NULL, int fps = NULL)
{
  device = cv::VideoCapture();
  device_id = (id == NULL) ? id : device_id;
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
    try { device.open(device_id,cv::CAP_ANY); }
    catch(std::exception &e){ std::cout << "Could not open the device:" << '\n' << e.what() << std::endl; }
    
    // Starts if 
    while(device.isOpened())
    {
      device.read(_frame);
      if(frame.empty()){ break; }
      else
      {
        cv::cvtColor(_frame.clone(),frame, cv::COLOR_BGR2RGB);
      }
    }
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
 }
}
