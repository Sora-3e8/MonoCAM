all: MonoCAM

#Dependencies:
deps:=  
deps+= `pkg-config --cflags --libs gtkmm-4.0`
deps+= `pkg-config --cflags --libs opencv4`

MonoCAM: clean
	g++ $(deps) monocam.cpp monocam_ux.h monocam_ux.cc -o build/MonoCAM
	cp build/MonoCAM $(PWD)/

clean:
	rm -f MonoCAM
	rm -r build/
	mkdir build


