#ifndef VIEWMODIFYCOMPONENTINFOWIN_H_
#define VIEWMODIFYCOMPONENTINFOWIN_H_

#include "model/Component.h"
#include "gtkmm/dialog.h"
#include "gtkmm/frame.h"
#include "gtkmm/entry.h"
#include "gtkmm/label.h"
#include "gtkmm/box.h"

/**
 * @brief esta ventana despliega las propiedades del componente con el cual
 * fue creada (nombre y tipo).
 */

class ViewModifyComponentInfoWin : public Gtk::Dialog {
public:
	ViewModifyComponentInfoWin(Component* );
	virtual ~ViewModifyComponentInfoWin();
	virtual int run();

private:
	Gtk::Frame m_mainFrame ;
	Gtk::Label m_componentNameLabel, m_typeLabel;
	Gtk::Entry m_componentNameEntry;
	Gtk::HBox m_typeHbox, m_componentNameHbox;
	Gtk::VBox m_mainbox;
	Gtk::RadioButton* m_radioButtons[5];
	Gtk::HBox m_radioButtonHbox[3];
	Gtk::RadioButton::Group m_radio;
	Component* m_component;
};

#endif /* VIEWMODIFYCOMPONENTINFOWIN_H_ */
