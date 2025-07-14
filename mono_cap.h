#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class camera_stream
{
  public:
    camera_stream(int id, int width, int height, int fps);
    
    void start_stream();
    void stop_stream();
  private:
    bool _keep_frame_loop = false;
    int capture_fps;
    int capture_width;
    int capture_height;
    int device_id;
    cv::VideoCapture device;
    
    void frame_loop();

};
