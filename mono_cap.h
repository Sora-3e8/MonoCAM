#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/hal/interface.h>
#include <sigc++/sigc++.h>
#include <opencv2/imgcodecs.hpp>
#include <mutex>

class camera_stream
{
  public:
    camera_stream(int id, int width, int height, int fps, bool mirror);
    void start_stream();
    void stop_stream();
    bool save_image(std::string filepath);
    cv::Mat frame;

  private:
    int capture_fps;
    int capture_width;
    int capture_height;
    int device_index;
    int cam_backend;
    bool mirror;
    bool _keep_frame_loop = false;
    cv::VideoCapture device;
    cv::Mat _frame;
    cv::Mat _frame2;
    std::mutex frame_mutex;
    void frame_loop();
};
