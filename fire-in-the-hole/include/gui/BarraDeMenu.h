#ifndef BARRADEMENU_H_
#define BARRADEMENU_H_

#include <gtkmm/menubar.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/main.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/stock.h>
#include <iostream>
#include "SubWindow/SubVentana.h"
#include <gtkmm/uimanager.h>
#include "gui/Handler/HandlerSelected.h"

class Tabs;
/**
 * Representa a la barra de menu (archivo / editar / etc).
 */
class BarraDeMenu {
private:
    SubVentana* subVentana;
    bool m_active;
    Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
    Glib::RefPtr<Gtk::UIManager> m_refUIManager;
	Tabs* m_tabs;
	HandlerSelected* handler;
	std::vector< VisualCompositeComponent* >* m_selection;

public:
	BarraDeMenu();

	virtual ~BarraDeMenu();
    Gtk::Widget *getMenuBar()
    {
        return m_refUIManager->get_widget("/MenuBar");
    }

    Gtk::Widget *getButtonBar()
    {
        return m_refUIManager->get_widget("/ToolBar");
    }

    Glib::RefPtr<Gtk::AccelGroup> getAccelGroup()
    {
        return m_refUIManager->get_accel_group();
    }

    void addActionGroup(Glib::RefPtr<Gtk::ActionGroup> actionGroup)
    {
        m_refUIManager->insert_action_group(actionGroup);
    }

    void setSubventana(SubVentana *subVentana);
    void on_menu_PageSetup();
    void on_menu_PrintPreview();
    void on_menu_Print();
    void on_menu_exportar_PNG();
    void on_menu_exportar_PDF();
    void on_menu_about();
    void on_menu_help();
    void on_publish_diagram();

    void deleteSelection();
    void copy();
    void cut();
    void createSubdiagram();
    void switchTabs(SubVentana* subVentanaAnterior);
    void exportSubdiagram();
    void showProperties();
    void validateDiagram();
    void setActive(bool act);

    Glib::RefPtr<Gtk::ActionGroup>& getRefActionGroup()
    {
        return m_refActionGroup;
    }

	void setTabs( Tabs* tabs) {
		m_tabs = tabs;
	}

	SubVentana* getSubVentana() {
		return subVentana;
	}

};

#endif /* BARRADEMENU_H_ */
