#include <iostream>
#include <gtkmm/application.h>
#include <opencv2/imgcodecs.hpp>
#include "app_utils.h"
#include "monocam_ux.h"
#include "mono_cap.h"
#include <ctime>

std::shared_ptr<Gtk::Application> app;
CamWindow *cam_window;
std::shared_ptr<camera_stream> cam;

// Default camera parameters
const int default_cam_index = 0;
const int default_cam_width = 480;
const int default_cam_height = 360;
const int default_cam_fps = 30;

// Default image save folder under $HOMEDIR
const std::string default_savepath = "Pictures/";
const std::string default_filextension = ".png";
// Triggers on application launch
void on_activate()
{
  load_resources();

  // Creates new window
  cam_window = new CamWindow();
  cam_window->present();
  app->add_window(*cam_window);

  // Initializes camera with default config
  cam = std::make_shared<camera_stream>(default_cam_index, default_cam_width, default_cam_height,default_cam_fps);
  
  // Provides pointer to the cam_window to know where to read new frames from
  cam_window->set_feed_source(&cam->frame);

  // Starts the camera device loop
  cam->start_stream();
}

void CamWindow::on_btn_clicked()
{ 
  //Returns if saving image failed or succeeded
  std::string timecode = apputils::datetime("%d-%m-%Y-%H-%M");
  std::string file_path = apputils::osutils::HOMEDIR()+"/"+default_savepath+timecode+default_filextension;
  bool save_success = cam->save_image(file_path);
  std::cout << ( (save_success==true) ? "Image saved:" : "Failed to save image path: ") << file_path << std::endl;
}

int main(int argc, char* argv[])
{
  app = Gtk::Application::create("org.Sora3e8.MonoCAM");
  app->signal_activate().connect(&on_activate);
  app->run(argc,argv);
  cam->stop_stream();

  // Release memory
  delete cam_window;
  cam_window = nullptr;
  // Release memory
  
  return 0;
}
