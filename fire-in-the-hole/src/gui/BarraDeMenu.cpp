#include "gui/BarraDeMenu.h"
#include <gtkmm/stock.h>
#include "gui/Handler/HandlerSelected.h"
#include "gui/SubWindow/AskDiagramName.h"
#include "gui/VisualComponents/VisualComponentSubdiagram.h"
#include "model/Diagram.h"
#include "gui/Handler/HandlerDefault.h"
#include "gui/About.h"
#include "utils/Settings.h"
#include "gui/Tabs.h"

BarraDeMenu::BarraDeMenu() {
	m_active = false;
	m_refActionGroup = Gtk::ActionGroup::create();
	subVentana = NULL;

	m_refActionGroup->add( Gtk::Action::create("MenuFile", "_File") );
	m_refActionGroup->add( Gtk::Action::create("PageSetup", Gtk::Stock::PROPERTIES), sigc::mem_fun(this, &BarraDeMenu::on_menu_PageSetup));
	m_refActionGroup->add( Gtk::Action::create("PrintPreview", Gtk::Stock::PRINT_PREVIEW), sigc::mem_fun(this, &BarraDeMenu::on_menu_PrintPreview));
	m_refActionGroup->add( Gtk::Action::create("Print", Gtk::Stock::PRINT), Gtk::AccelKey("<control>P"), sigc::mem_fun(this, &BarraDeMenu::on_menu_Print));
	m_refActionGroup->add( Gtk::Action::create("ExportarPdf", Gtk::Stock::DND, "Export to PDF"), sigc::mem_fun(this, &BarraDeMenu::on_menu_exportar_PDF));
	m_refActionGroup->add( Gtk::Action::create("ExportarPng", Gtk::Stock::FILE, "Export to PNG"), sigc::mem_fun(this, &BarraDeMenu::on_menu_exportar_PNG));
	m_refActionGroup->add( Gtk::Action::create("Quit", Gtk::Stock::QUIT), sigc::ptr_fun(&Gtk::Main::quit));

	m_refActionGroup->add( Gtk::Action::create("MenuEdit", "_Edit"));
	m_refActionGroup->add( Gtk::Action::create("Options", "_Options"));
	m_refActionGroup->add( Gtk::Action::create("Copy", Gtk::Stock::COPY), sigc::mem_fun(*this, &BarraDeMenu::copy));
	m_refActionGroup->add( Gtk::Action::create("Cut", Gtk::Stock::CUT), sigc::mem_fun(*this, &BarraDeMenu::cut));
	m_refActionGroup->add( Gtk::Action::create("Properties", Gtk::Stock::PROPERTIES), sigc::mem_fun(*this, &BarraDeMenu::showProperties));
	m_refActionGroup->add( Gtk::Action::create("Validate", Gtk::Stock::CONNECT,"Validate"), sigc::mem_fun(*this, &BarraDeMenu::validateDiagram));

	m_refActionGroup->add( Gtk::Action::create("Borrar", Gtk::Stock::CANCEL, "Delete"), sigc::mem_fun(*this, &BarraDeMenu::deleteSelection));
	m_refActionGroup->add( Gtk::Action::create("CrearSubdiagrama", Gtk::Stock::CONVERT, "Create Subdiagram"), sigc::mem_fun(*this, &BarraDeMenu::createSubdiagram));
	m_refActionGroup->add( Gtk::Action::create("ExportarSubdiagrama", Gtk::Stock::NETWORK, "Export Subdiagram"), sigc::mem_fun(*this, &BarraDeMenu::exportSubdiagram));

	m_refActionGroup->add( Gtk::Action::create("MenuHelp", "_Help"));
	m_refActionGroup->add( Gtk::Action::create("About", Gtk::Stock::ABOUT), sigc::mem_fun(*this, &BarraDeMenu::on_menu_about));
	m_refActionGroup->add( Gtk::Action::create("Help", Gtk::Stock::HELP), sigc::mem_fun(*this, &BarraDeMenu::on_menu_help));

	m_refUIManager = Gtk::UIManager::create();
	Glib::ustring ui_info =
	    "<ui>"
	    "  <menubar name='MenuBar'>"
	    "    <menu action='MenuFile'>"
	    "      <menuitem action='New'/>"
	    "      <menuitem action='Open'/>"
		"	   <menuitem action='Save'/>"
		"	   <menuitem action='SaveAs'/>"
		"	   <menuitem action='Close'/>"
		"      <separator/>"
		"      <menuitem action='NewProyect'/>"
		"      <menuitem action='OpenProyect'/>"
		"      <menuitem action='CloseProyect'/>"
	    "      <separator/>"
		"	   <menuitem action='RenombrarDiagrama'/>"
		"	   <menuitem action='PageSetup'/>"
		"      <separator/>"
		"	   <menuitem action='PrintPreview'/>"
		"	   <menuitem action='Print'/>"
		"	   <menuitem action='ExportarPdf'/>"
		"	   <menuitem action='ExportarPng'/>"
		"      <separator/>"
	    "      <menuitem action='Quit'/>"
	    "    </menu>"
	    "    <menu action='MenuEdit'>"
		"      <menuitem action='Copy'/>"
		"      <menuitem action='Cut'/>"
		"      <menuitem action='Borrar'/>"
		"      <separator/>"
		"      <menuitem action='CrearSubdiagrama'/>"
		"      <menuitem action='ExportarSubdiagrama'/>"
	    "    </menu>"
	    "    <menu action='Options'>"
	    "      <menuitem action='Properties'/>"
		"      <menuitem action='Validate'/>"
		"    </menu>"
		"    <menu action='MenuHelp'>"
		"	   <menuitem action='About'/>"
		"	   <menuitem action='Help'/>"
		"    </menu>"
	    "  </menubar>"
	    "  <toolbar  name='ToolBar'>"
	    "    <toolitem action='New'/>"
		"    <toolitem action='Open'/>"
	    "    <toolitem action='Save'/>"
		"	   <toolitem action='Print'/>"
		"      <separator/>"
		"      <toolitem action='Copy'/>"
		"      <toolitem action='Cut'/>"
		"      <toolitem action='Borrar'/>"
		"      <separator/>"
		"      <toolitem action='Properties'/>"
		"      <toolitem action='CrearSubdiagrama'/>"
		"      <toolitem action='ExportarSubdiagrama'/>"
		"      <separator/>"
		"		<toolitem action='Validate'/>"
		"      <toolitem action='Properties'/>"
		"      <separator/>"
		"	   <toolitem action='Help'/>"
		"      <separator/>"
	    "  </toolbar>"
	    "</ui>";

	m_refUIManager->add_ui_from_string(ui_info);
	m_refUIManager->insert_action_group(m_refActionGroup);
}

BarraDeMenu::~BarraDeMenu() { }

void BarraDeMenu::setSubventana(SubVentana* subVentana) {
	this->subVentana = subVentana;
}

void BarraDeMenu::on_menu_PageSetup() {
	if (subVentana != NULL)
		subVentana->getWorkspace()->on_menu_file_page_setup();
}

void BarraDeMenu::on_menu_PrintPreview() {
	if (subVentana != NULL)
		subVentana->getWorkspace()->on_menu_file_print_preview();
}

void BarraDeMenu::on_menu_Print() {
	if (subVentana != NULL)
		subVentana->getWorkspace()->on_menu_file_print();
}

void BarraDeMenu::on_menu_exportar_PNG() {
	if (subVentana != NULL) {
		Gtk::FileChooserDialog fileChooser("Elegir nombre", Gtk::FILE_CHOOSER_ACTION_SAVE);
		fileChooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		fileChooser.add_button("Select", Gtk::RESPONSE_OK);
		int resultado = fileChooser.run();
		if (resultado == Gtk::RESPONSE_OK) {
			subVentana->getWorkspace()->imprimirAPng(fileChooser.get_filename());
		}
	}
}

void BarraDeMenu::on_menu_exportar_PDF() {
	if (subVentana != NULL) {
		Gtk::FileChooserDialog fileChooser("Elegir nombre", Gtk::FILE_CHOOSER_ACTION_SAVE);
		fileChooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		fileChooser.add_button("Select", Gtk::RESPONSE_OK);
		int resultado = fileChooser.run();
		if (resultado == Gtk::RESPONSE_OK) {
			subVentana->getWorkspace()->imprimirAPdf(fileChooser.get_filename());
		}
	}
}

void BarraDeMenu::deleteSelection(){
	if ( !m_active)
		return ;

	HandlerSelected* han = dynamic_cast< HandlerSelected* >(subVentana->getWorkspace()->getHandler());
	if ( han != NULL)
		han->deleteSelection(m_tabs);
}

void BarraDeMenu::showProperties(){
	if ( !m_active)
		return ;

	HandlerSelected* han = dynamic_cast< HandlerSelected* >(subVentana->getWorkspace()->getHandler());
	if ( han != NULL)
		han->showProperties();
}

void BarraDeMenu::validateDiagram(){

	std::string filename;
	std::string anho;
	std::string mes;
	std::string dia;
	std::string hora;

	struct tm *tiempo;
	time_t fecha_sistema;
	time(&fecha_sistema);
	filename = ctime(&fecha_sistema);
	anho=filename.substr(20,4);
	mes=filename.substr(4,3);
	dia=filename.substr(8,2);
	filename = subVentana->getWorkspace()->getDiagram()->getName() + "_" + dia + mes + anho + ".html";

	if (subVentana != NULL) {
		Gtk::FileChooserDialog fileChooser("Choose file name validation", Gtk::FILE_CHOOSER_ACTION_SAVE);
		fileChooser.set_current_name(filename);
		fileChooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		fileChooser.add_button("Select", Gtk::RESPONSE_OK);
		int resultado = fileChooser.run();
		if (resultado == Gtk::RESPONSE_OK) {
			subVentana->getWorkspace()->validateDiagram(fileChooser.get_filename());
		}
	}
}

void BarraDeMenu::copy(){
	if ( !m_active)
		return ;

	HandlerSelected* han = dynamic_cast< HandlerSelected* >(subVentana->getWorkspace()->getHandler());
	if ( han != NULL)
		han->copy();
}

void BarraDeMenu::cut(){
	if ( !m_active)
		return ;

	HandlerSelected* han = dynamic_cast< HandlerSelected* >(subVentana->getWorkspace()->getHandler());
	if ( han != NULL)
		han->cut();
}

/**
void BarraDeMenu::createSubdiagram(){
	if ( !m_active)
		return ;
	handler = dynamic_cast< HandlerSelected* >(subVentana->getWorkspace()->getHandler());
	m_selection = handler->duplicateSelection(false);
	m_tabs->setActive(true);
}
*/

void BarraDeMenu::switchTabs(SubVentana* subVentanaAnterior) {
	if ( !m_active)
		return ;

	int size = m_selection->size();
//	int size1 = handler->getSelection()->size();
	handler->setSelection(m_selection);
	handler->setDarea(subVentana->getWorkspace());
	handler->copy(true);
	for(int i = 0; i < handler->getSelection()->size(); i++)
		subVentana->getWorkspace()->getDiagram()->addComponent((*handler->getSelection())[i]->getComponent());
	handler->setDarea(subVentanaAnterior->getWorkspace());
	handler->createSubdiagram();
	subVentana->getWorkspace()->setHandler(new HandlerDefault(subVentana->getWorkspace()));
	subVentanaAnterior->getWorkspace()->setHandler(new HandlerDefault(subVentanaAnterior->getWorkspace()));
	m_tabs->setActive(false);
}

void BarraDeMenu::exportSubdiagram(){
	if ( !m_active)
		return ;

	HandlerSelected* han = dynamic_cast< HandlerSelected* >(subVentana->getWorkspace()->getHandler());

	SubVentana* subVentanaAnterior = subVentana;
	m_tabs->on_menu_open();
	han->setDarea(subVentana->getWorkspace());
	han->copy(true);
	for(int i = 0; i < han->getSelection()->size(); i++)
		subVentana->getWorkspace()->getDiagram()->addComponent((*han->getSelection())[i]->getComponent());
	han->setDarea(subVentanaAnterior->getWorkspace());
	han->createSubdiagram();
	subVentana->getWorkspace()->setHandler(new HandlerDefault(subVentana->getWorkspace()));
	subVentanaAnterior->getWorkspace()->setHandler(new HandlerDefault(subVentanaAnterior->getWorkspace()));
}

void BarraDeMenu::createSubdiagram(){
	if ( !m_active)
		return ;

	HandlerSelected* han = dynamic_cast< HandlerSelected* >(subVentana->getWorkspace()->getHandler());
	SubVentana* subVentanaAnterior = subVentana;

	m_tabs->agregarSubVentana();

	han->setDarea(subVentana->getWorkspace());
	han->copy(true);
	for(int i = 0; i < han->getSelection()->size(); i++)
		subVentana->getWorkspace()->getDiagram()->addComponent((*han->getSelection())[i]->getComponent());
	han->setDarea(subVentanaAnterior->getWorkspace());
	han->createSubdiagram();
	subVentana->getWorkspace()->setHandler(new HandlerDefault(subVentana->getWorkspace()));
	subVentanaAnterior->getWorkspace()->setHandler(new HandlerDefault(subVentanaAnterior->getWorkspace()));
}

void BarraDeMenu::setActive(bool act){
	m_active = act;
}

void BarraDeMenu::on_menu_about() {
	About about;
	about.run();
}

void BarraDeMenu::on_menu_help() {
	system(("xdg-open " + Settings::getInstance().getValue("HelpPath")).c_str());
}
