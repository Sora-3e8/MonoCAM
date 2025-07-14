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

  protected:
    void on_btn_clicked();

};

class SettingsWindow : public Gtk::Window
{
  public:
    SettingsWindow();
};
