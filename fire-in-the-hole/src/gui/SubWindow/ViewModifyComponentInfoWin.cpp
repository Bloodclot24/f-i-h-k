#include "gui/SubWindow/ViewModifyComponentInfoWin.h"
#include <iostream>
#include "gtkmm/stock.h"

ViewModifyComponentInfoWin::ViewModifyComponentInfoWin(Component* comp) :	m_mainFrame("Propiedades"),
		m_componentNameLabel("Nombre del componente"),	m_typeLabel("Tipos")
{
	m_component = comp;

	set_title("Informacion del componente");
	get_vbox()->pack_start(m_mainFrame, Gtk::PACK_EXPAND_WIDGET, 5);

	m_mainFrame.add(m_mainbox);

	m_mainbox.pack_start(m_componentNameHbox, Gtk::PACK_EXPAND_PADDING, 10);
	m_mainbox.pack_start(m_typeHbox, Gtk::PACK_EXPAND_PADDING, 10);

	m_componentNameHbox.pack_start(m_componentNameLabel, Gtk::PACK_EXPAND_PADDING, 10);
	m_componentNameHbox.pack_start(m_componentNameEntry, Gtk::PACK_EXPAND_PADDING, 10);

	for(unsigned i = 0; i < m_component->getTypes().size(); i++)
		m_radioButtons[i] = new Gtk::RadioButton(m_radio, m_component->getTypes()[i]);

	m_radioButtons[m_component->getType()]->set_active();
	m_mainbox.add(m_typeLabel);

	for(unsigned i = 0; i < m_component->getTypes().size(); i++) {
		if(i % 2 == 0)
			m_mainbox.pack_start(m_radioButtonHbox[i/2], Gtk::PACK_EXPAND_PADDING, 10);
		m_radioButtonHbox[i/2].pack_start(*m_radioButtons[i], Gtk::PACK_EXPAND_PADDING, 10);
		m_mainbox.add(*m_radioButtons[i]);
	}
	m_componentNameEntry.set_text(m_component->getName());
	add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
}

ViewModifyComponentInfoWin::~ViewModifyComponentInfoWin() {
	for(unsigned i = 0; i < m_component->getTypes().size(); i++)
		delete m_radioButtons[i];
}

int ViewModifyComponentInfoWin::run(){

	show_all();
	int res = Gtk::Dialog::run();
	if ( res == Gtk::RESPONSE_OK){
		m_component->setName(m_componentNameEntry.get_text());

		for(unsigned i = 0; i < m_component->getTypes().size(); i++)
			if ( m_radioButtons[i]->get_active() )
				m_component->setType(i);
	}
	return res;
}
