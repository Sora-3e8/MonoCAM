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

  try
  {
    device.open(device_id,cv::CAP_ANY);
  }
  catch(std::exception &e)
  {
    std::cout << "Could not open the device:" << '\n' << e.what() << std::endl;
  }
  frame_loop();
}
void camera_stream::stop_stream()
{
  
}

void camera_stream::frame_loop()
{
  while(_keep_frame_loop)
  {
  
  }
}



