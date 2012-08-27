#include "gui/SubWindow/AskDiagramName.h"
#include "gtkmm/stock.h"

const std::string LABEL_TEXT = "Ingrese el nombre del diagrama";

AskDiagramName::AskDiagramName() : m_label(LABEL_TEXT) {
	m_dialog.set_title("Nombre del diagrama");
	m_dialog.get_vbox()->pack_start( m_label, true, true , 5);
	m_dialog.get_vbox()->pack_start(m_nameEntry, true ,true, 5);

	m_dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	m_dialog.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	m_nameEntry.set_activates_default();
	m_dialog.set_response_sensitive(Gtk::RESPONSE_OK);
	m_dialog.set_default_response(Gtk::RESPONSE_OK);
}

AskDiagramName::~AskDiagramName() { }

std::string AskDiagramName::askName(){
	m_dialog.show_all();
	int res = m_dialog.run();
	if ( res == Gtk::RESPONSE_OK){
		return m_nameEntry.get_text();
	}
	return "";
}
