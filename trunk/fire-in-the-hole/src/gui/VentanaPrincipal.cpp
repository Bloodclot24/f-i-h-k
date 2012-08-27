#include "gui/VentanaPrincipal.h"

VentanaPrincipal::VentanaPrincipal() {
	set_title(TITULO);
	tabs = new Tabs(barraDeMenu);
	barraDeHerramientas.setTabs(tabs);
	barraDeMenu.setTabs(tabs);

	separadorPrincipal.pack_start(*barraDeMenu.getMenuBar(), false, false, 0);
	separadorPrincipal.pack_start(*barraDeMenu.getButtonBar(), false, false, 0);
	separadorPrincipal.pack_start(separadorTabsAndButtons, true, true, 0);
	separadorTabsAndButtons.pack_start(barraDeHerramientas, false, false, 0);
	separadorTabsAndButtons.pack_start(*tabs, true, true, 0);

	add(separadorPrincipal);
	add_accel_group(barraDeMenu.getAccelGroup()); //Agrega los shortcuts a esta ventana.
	signal_key_release_event().connect(sigc::mem_fun(this, &VentanaPrincipal::on_asd_key_release_event));
	signal_key_press_event().connect(sigc::mem_fun(this, &VentanaPrincipal::on_asd_key_press_event));
	show_all();
	maximize();
}

VentanaPrincipal::~VentanaPrincipal() {
		delete tabs;
}

bool VentanaPrincipal::on_asd_key_release_event(GdkEventKey* event) {
	tabs->on_key_release_event(event);
	return false; //Detener la propagacion
}

bool VentanaPrincipal::on_asd_key_press_event(GdkEventKey* event){
	tabs->on_key_press_event(event);
	return false;
}
