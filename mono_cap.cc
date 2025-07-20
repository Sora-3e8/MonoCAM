#include <thread>
#include <chrono>
#include <iostream>
#include "mono_cap.h"
#include "app_utils.h"

camera_stream::camera_stream(int id=0, int width = 480, int height = 360, int fps = 60)
{
  device = cv::VideoCapture();
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
  std::thread t_cam = std::thread(sigc::mem_fun(*this,&camera_stream::frame_loop));
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
    save_success =  cv::imwrite(filepath,_frame);
  }
  catch(std::exception &e){std::cout << "Saving file error: " << "\n\t" << e.what() << std::endl; }
  
  return save_success;
}

void camera_stream::frame_loop()
{
  // This loop keeps running until told otherwise ==> awaits device
  while(_keep_frame_loop)
  {
    // Attempts to open camera by device_id 
    try 
    {
      std::cout << "Trying to open device" << std::endl;
      device.open(device_index,cam_backend);
    }
    catch(std::exception &e){ }
    
    // Starts if 
    while(device.isOpened())
    {
      bool frame_valid = false;
      try {device.read(_frame); frame_valid = (_frame.empty()==false); }
      catch(std::exception &e){frame_valid = false;}

      if(frame_valid)
      {
        cv::Mat mirrored;
        cv::flip(_frame,mirrored,1);
        cv::cvtColor(mirrored.clone(),frame, cv::COLOR_BGR2RGB);
      }
      else
      {
        frame=cv::Mat();
        try{device.release();}catch(std::exception &e){};
      }
      
    }
  std::cout << "Device closed" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
 }
}
