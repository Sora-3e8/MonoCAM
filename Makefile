all: precompile

precompile:
	glib-compile-resources --sourcedir resources --generate-source resources.gresource.xml
	glib-compile-resources --sourcedir resources --generate-header resources.gresource.xml
