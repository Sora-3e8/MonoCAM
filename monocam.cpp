#include "monocam_ux.h"
#include <gtkmm/application.h>
#include <iostream>

std::shared_ptr<Gtk::Application> app = NULL;
CamWindow* cam_window = NULL;

void on_activate()
{
  cam_window = new CamWindow();
  cam_window->present();
  app->add_window(*cam_window); 
}

int main(int argc, char* argv[])
{
  app = Gtk::Application::create("org.Sora3e8.MonoCAM");
  app->signal_activate().connect(&on_activate);
  app->run(argc,argv);
  std::cout << "Got past here!" << std::endl;

  // Release memory
  delete cam_window;
  cam_window = nullptr;
  // Release memory

  return 0;
}
