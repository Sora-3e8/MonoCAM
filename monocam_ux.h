#include <opencv2/core/mat.hpp>
#include <gtkmm.h>
#include <bits/stdc++.h>
#include <string>
#include "mono_cap.h"

void load_resources();

class CamWindow : public Gtk::Window
{ 

public:
    Gtk::HeaderBar header;
    Gtk::Button settings_button;
    Gtk::Overlay overlay_layer;
    Gtk::Box overlay_container;
    Gtk::Button photo_button;
    Gtk::Button photovideo_switch;
    Gtk::Picture cam_view;
    Glib::RefPtr<Gdk::Pixbuf> image_nocam;
    CamWindow();
    ~CamWindow() override;

    void set_feed_source(camera_stream* cam);


  protected:
    void on_btn_clicked();
    bool update_feed();

  private:
    camera_stream* cam;
    Glib::RefPtr<Gdk::Pixbuf> image_buffer;

};

class SettingsWindow : public Gtk::Window
{
  public:
    SettingsWindow();
};
