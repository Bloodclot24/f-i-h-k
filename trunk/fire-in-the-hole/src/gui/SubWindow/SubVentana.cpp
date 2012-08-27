#include "gui/SubWindow/SubVentana.h"
#include "gtkmm/messagedialog.h"
#include <iostream>

#define LABEL_TABLA_LOGICA "Tabla logica"
#define LABEL_LISTA_ACCIONES "Lista de acciones"
#define ANCHO_DERECHA 100

SubVentana::SubVentana(Diagram& diagram, Gtk::Allocation allocation) :
	m_diagram(diagram), ajusteHorizontal(0, 0, allocation.get_width()), ajusteVertical(0, 0, get_height()),
			adaptador(ajusteHorizontal, ajusteVertical), workspace(diagram) {
	boxInicial.set_homogeneous(false);
	add(boxInicial);

	//Workspace a la izquierda.
	boxInicial.pack_start(scrollWorkspace, true, true, 0);
	scrollWorkspace.add(adaptador);
	adaptador.add(workspace);
	workspace.size_allocate(allocation);

	//Parte de la derecha.
	boxInicial.pack_start(boxHomogenea, false, true, 0);

	scrollWorkspace.add_events(Gdk::POINTER_MOTION_MASK );
	workspace.add_events(Gdk::POINTER_MOTION_MASK );
	scrollWorkspace.add_events(Gdk::BUTTON_PRESS_MASK );
	workspace.add_events(Gdk::BUTTON_PRESS_MASK );
	scrollWorkspace.add_events(Gdk::BUTTON_RELEASE_MASK );
	workspace.add_events(Gdk::BUTTON_RELEASE_MASK );
	scrollWorkspace.signal_motion_notify_event().connect(sigc::mem_fun(workspace, &DrawingAreaPlusPlus::on_motion_notify_event));
	show_all();
}
