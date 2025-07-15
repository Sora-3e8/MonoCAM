#include <iostream>
#include <gtkmm/application.h>
#include "monocam_ux.h"
#include "mono_cap.h"

std::shared_ptr<Gtk::Application> app = NULL;
CamWindow* cam_window = NULL;
std::shared_ptr<camera_stream> cam = NULL;

// Default camera parameters
const int default_cam_index = 0;
const int default_cam_width = 480;
const int default_cam_height = 360;
const int default_cam_fps = 30;


void on_activate()
{
  cam_window = new CamWindow();
  cam_window->present();
  app->add_window(*cam_window);
  cam = std::make_shared<camera_stream>(default_cam_index, default_cam_width, default_cam_height,default_cam_fps);
  cam->start_stream();
}

int main(int argc, char* argv[])
{
  app = Gtk::Application::create("org.Sora3e8.MonoCAM");
  app->signal_activate().connect(&on_activate);
  app->run(argc,argv);
  cam->stop_stream();
  std::cout << "Program exiting..." << std::endl;

  // Release memory
  delete cam_window;
  cam_window = nullptr;

  // Release memory
  
  return 0;
}
