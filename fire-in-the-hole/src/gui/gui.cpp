#include "../../include/gui/VentanaPrincipal.h"
#include <gtkmm/settings.h>
#include <fstream>

int main(int argc, char **argv) {
	Gtk::Main kit(argc, argv);
	//En caso de que tenga algun theme raro que no permita imgs por default.
	#ifdef GLIBMM_PROPERTIES_ENABLED
	Gtk::Settings::get_default()->property_gtk_button_images() = true;
	#endif //#GLIBMM_PROPERTIES_ENABLED

	VentanaPrincipal ventanaPrincipal;

	Gtk::Main::run(ventanaPrincipal);

	return 0;
}
