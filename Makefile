all: MonoCAM

MonoCAM:
	g++ MonoCAM `pkg-config --cflags --libs gtkmm-4.0` `pkg-config --cflags --libs opencv4` -I main. main.h MonoCAM main.cpp 
