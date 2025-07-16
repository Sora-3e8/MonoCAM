#include "monocam_ux.h"

// CamWindow: Gtk::Window init override
CamWindow::CamWindow()
{
  // Widget creation
  overlay_layer =  Gtk::Overlay();
  overlay_container = Gtk::Box();
  cam_view = Gtk::Picture();
  photo_button = Gtk::Button();
  // Widget creation
  
  // Load resources
  try
  {
    image_nocam = Gdk::Pixbuf::create_from_file("resources/images/no_camera.png");
  }
  catch(std::exception &e)
  {
    std::cout << "\tFailed to load resources with following Error:"<<std::endl<< e.what() <<std::endl;
  }
  // Load resources
  
  // Widget configuration
  overlay_container.set_orientation(Gtk::Orientation::VERTICAL);
  cam_view.set_hexpand(true);
  cam_view.set_vexpand(true);
  overlay_container.set_hexpand(false);
  overlay_container.set_vexpand(false);
  overlay_container.set_valign(Gtk::Align::END);
  photo_button.set_hexpand(false);
  photo_button.set_vexpand(false);
  photo_button.set_halign(Gtk::Align::CENTER);
  photo_button.set_label("Take image");
  photo_button.add_css_class("bottom");
  cam_view.set_pixbuf(image_nocam);
  // Widget configuration

  // Add widgets to the layout
  overlay_layer.set_child(cam_view);
  overlay_layer.add_overlay(overlay_container);
  overlay_container.append(photo_button);
  set_child(overlay_layer);
  photo_button.signal_clicked().connect(sigc::mem_fun(*this,&CamWindow::on_btn_clicked));
  //sigc::slot<bool> t_out = sigc::ptr_fun(&update_feed); 
  Glib::signal_timeout().connect(sigc::mem_fun(*this,&CamWindow::update_feed),16);
  // Add widgets to the layout
}

void CamWindow::set_feed_source(cv::Mat* source)
{
  image_source = source;
}

bool CamWindow::update_feed()
{
  if(image_source->empty() == false)
  {
    auto image_src = *image_source;
    image_buffer = Gdk::Pixbuf::create_from_data(image_src.data, Gdk::Colorspace::RGB,false, 8, image_src.cols, image_src.rows, image_src.step);
    cam_view.set_pixbuf(image_buffer);
   
  }
  return true;
}

void CamWindow::on_btn_clicked()
{
  std::cout << "Hi thewe 0w0." <<std::endl;
}


