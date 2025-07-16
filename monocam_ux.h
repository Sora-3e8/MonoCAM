#include <opencv2/core/mat.hpp>
#include <gtkmm.h>
#include <bits/stdc++.h>
#include <string>


class CamWindow : public Gtk::Window
{ 

public:
    Gtk::Overlay overlay_layer;
    Gtk::Box overlay_container;
    Gtk::Button photo_button;
    Gtk::Button photovideo_switch;
    Gtk::Picture cam_view;
    Glib::RefPtr<Gdk::Pixbuf> image_nocam;
    CamWindow();

    void set_feed_source(cv::Mat *source);

  protected:
    void on_btn_clicked();
    bool update_feed();

  private:
    cv::Mat *image_source;
    Glib::RefPtr<Gdk::Pixbuf> image_buffer;


};

class SettingsWindow : public Gtk::Window
{
  public:
    SettingsWindow();
};
