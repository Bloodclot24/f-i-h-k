#include "gui/SubWindow/ViewModifyAttributeInfoWin.h"
#include <iostream>
#include "gtkmm/stock.h"

ViewModifyAttributeInfoWin::ViewModifyAttributeInfoWin(Component* comp) :	m_mainFrame("Propiedades"), m_componentNameLabel("Nombre del atributo"),
			m_typeLabel("Expresión"), m_title("Tipos                                  Identificador"),
			m_radioButton1(m_radio, "Default"), m_radioButton2("primario"),
			m_radioButton3(m_radio, "Multivaluado"), m_radioButton4("secundario"),
			m_radioButton5(m_radio, "Derivado"), m_radioButton6("terciario")
{
	m_component = comp;

	set_title("Informacion del atributo");
	get_vbox()->pack_start(m_mainFrame, Gtk::PACK_EXPAND_WIDGET, 5);

	m_mainFrame.add(m_mainbox);

	m_mainbox.pack_start(m_componentNameHbox, Gtk::PACK_EXPAND_PADDING, 10);
	m_componentNameHbox.pack_start(m_componentNameLabel, Gtk::PACK_EXPAND_PADDING, 10);
	m_componentNameHbox.pack_start(m_componentNameEntry, Gtk::PACK_EXPAND_PADDING, 10);

	if (comp->getType() == 0)
		m_radioButton1.set_active();
	if (comp->getType() == 1)
		m_radioButton3.set_active();
	if (comp->getType() == 2)
		m_radioButton5.set_active();
	if (comp->getOptions()[0])
		m_radioButton2.set_active();
	if (comp->getOptions()[1])
		m_radioButton4.set_active();
	if (comp->getOptions()[2])
		m_radioButton6.set_active();

	m_mainbox.add(m_title);
	m_mainbox.pack_start(m_radioButton1Hbox, Gtk::PACK_EXPAND_PADDING, 10);
	m_mainbox.pack_start(m_radioButton2Hbox, Gtk::PACK_EXPAND_PADDING, 10);
	m_mainbox.pack_start(m_radioButton4Hbox, Gtk::PACK_EXPAND_PADDING, 10);
	m_radioButton1Hbox.pack_start(m_radioButton1, Gtk::PACK_EXPAND_PADDING, 10);
	m_radioButton1Hbox.pack_start(m_radioButton2, Gtk::PACK_EXPAND_PADDING, 10);
	m_radioButton2Hbox.pack_start(m_radioButton3, Gtk::PACK_EXPAND_PADDING, 10);
	m_radioButton2Hbox.pack_start(m_radioButton4, Gtk::PACK_EXPAND_PADDING, 10);
	m_radioButton4Hbox.pack_start(m_radioButton5, Gtk::PACK_EXPAND_PADDING, 10);
	m_radioButton4Hbox.pack_start(m_radioButton6, Gtk::PACK_EXPAND_PADDING, 10);
	m_radioButton1.set_group(m_radio);
	m_radioButton3.set_group(m_radio);
	m_radioButton5.set_group(m_radio);

	m_mainbox.add(m_radioButton1);
	m_mainbox.add(m_radioButton2);
	m_mainbox.add(m_radioButton3);
	m_mainbox.add(m_radioButton4);
	m_mainbox.add(m_radioButton5);
	m_mainbox.add(m_radioButton6);

	m_mainbox.pack_start(m_typeHbox, Gtk::PACK_EXPAND_PADDING, 10);
	m_typeHbox.pack_start(m_typeLabel, Gtk::PACK_EXPAND_PADDING, 10);
	m_typeHbox.pack_start(m_typeEntry, Gtk::PACK_EXPAND_PADDING, 10);

	m_typeEntry.set_text(m_component->getExpression());
	m_componentNameEntry.set_text(m_component->getName());

	add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
}

ViewModifyAttributeInfoWin::~ViewModifyAttributeInfoWin() {
}

int ViewModifyAttributeInfoWin::run(){

	show_all();
	int res = Gtk::Dialog::run();
	if ( res == Gtk::RESPONSE_OK){
		m_component->setName(m_componentNameEntry.get_text());
		m_component->setExpression(m_typeEntry.get_text());

		if ( m_radioButton1.get_active() )
			m_component->setType(0);
		if (m_radioButton3.get_active() )
			m_component->setType(1);
		if (m_radioButton5.get_active() )
			m_component->setType(2);

		m_component->getOptions()[0] = m_radioButton2.get_active();
		m_component->getOptions()[1] = m_radioButton4.get_active();
		m_component->getOptions()[2] = m_radioButton6.get_active();
	}
	return res;
}
