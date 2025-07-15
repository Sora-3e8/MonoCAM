#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <sigc++/sigc++.h>
class camera_stream
{
  public:
    camera_stream(int id, int width, int height, int fps);

    cv::Mat frame;
    void start_stream();
    void stop_stream();

  private:
    int capture_fps;
    int capture_width;
    int capture_height;
    int device_id;
    bool _keep_frame_loop = false;
    cv::VideoCapture device;
    cv::Mat _frame;
    
    void frame_loop();

};
