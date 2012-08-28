#include "gui/Tabs.h"
#include "gui/SubWindow/AskDiagramName.h"
#include <gtkmm-2.4/gtkmm/messagedialog.h>
#include "model/Diagram.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include "utils/Settings.h"

Tabs::Tabs(BarraDeMenu& barraDeMenu) : barraDeMenu(barraDeMenu) {

	set_show_tabs(true);
	set_show_border(true);
	set_scrollable(true);
	signal_switch_page().connect(sigc::mem_fun(this, &Tabs::on_switch_page_fake));
	Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup = Gtk::ActionGroup::create();
	m_refActionGroup->add( Gtk::Action::create("NewProyect", Gtk::Stock::NEW, "New Proyect"), sigc::mem_fun(this, &Tabs::on_menu_new_proyect));
	m_refActionGroup->add( Gtk::Action::create("New", Gtk::Stock::NEW, "New Diagram"), sigc::mem_fun(this, &Tabs::on_menu_new));
	m_refActionGroup->add( Gtk::Action::create("OpenProyect", Gtk::Stock::OPEN, "Open Proyect"), sigc::mem_fun(this, &Tabs::on_menu_open_proyect));
	m_refActionGroup->add( Gtk::Action::create("Open", Gtk::Stock::OPEN, "Open Diagram"), sigc::mem_fun(this, &Tabs::on_menu_open));
	m_refActionGroup->add( Gtk::Action::create("Save", Gtk::Stock::SAVE, "Save Diagram"), sigc::mem_fun(this, &Tabs::on_menu_save));
	m_refActionGroup->add( Gtk::Action::create("SaveAs", Gtk::Stock::SAVE_AS, "SaveAs Diagram"), sigc::mem_fun(this, &Tabs::on_menu_save_as));
	m_refActionGroup->add( Gtk::Action::create("CloseProyect", Gtk::Stock::CLOSE, "Close Proyect"), sigc::mem_fun(this, &Tabs::on_menu_close_proyect));
	m_refActionGroup->add( Gtk::Action::create("Close", Gtk::Stock::CLOSE, "Close Diagram"), sigc::mem_fun(this, &Tabs::on_menu_close));
	m_refActionGroup->add( Gtk::Action::create("RenombrarDiagrama", Gtk::Stock::EDIT, "Rename Diagram"), sigc::mem_fun(this, &Tabs::on_name_change));

	barraDeMenu.addActionGroup(m_refActionGroup);
	m_active = false;
}

Tabs::~Tabs() {
	for (unsigned i = 0; i < subVentanas.size(); ++i)
		delete subVentanas[i];
}

void Tabs::agregarSubVentana(Diagram* diagram) {
	Diagram* diagramDefault;
	if (diagram == NULL) {
		AskDiagramName dialog("Nombre del diagrama");
		std::string diagramName = dialog.askName();
		if (diagramName.size() == 0)
			return;
		diagramDefault = new Diagram();
		diagramDefault->setName(diagramName);
	} else {
		diagramDefault = diagram;
	}
	SubVentana* subVentanaDefault = new SubVentana(*diagramDefault, get_allocation());
	subVentanas.push_back(subVentanaDefault);
	append_page(*subVentanaDefault, subVentanaDefault->getDiagram()->getName());
	show_all();
	set_current_page(subVentanas.size() - 1);

	subVentanaDefault->getWorkspace()->setActions(barraDeMenu.getRefActionGroup());
	barraDeMenu.setActive(true); // habilita los eventos del menu.
}

void Tabs::removerSubVentanaActual() {
	int paginaActual = get_current_page();
	remove_page(paginaActual);
	delete subVentanas[paginaActual];
	subVentanas.erase(subVentanas.begin() + paginaActual);
	if (get_n_pages() > 0)
		barraDeMenu.setSubventana(subVentanas[get_current_page()]);
	else
		barraDeMenu.setActive(false);
}

void Tabs::on_switch_page_fake(GtkNotebookPage* page, guint page_num) {
	SubVentana* subventanaAnterior = barraDeMenu.getSubVentana();
	barraDeMenu.setSubventana(subVentanas[page_num]);
	if(m_active)
		barraDeMenu.switchTabs(subventanaAnterior);
}

void Tabs::on_menu_close() {
	if ( get_n_pages () < 1)
		return;
	removerSubVentanaActual();
}

void Tabs::on_menu_new() {
	agregarSubVentana();
}

void Tabs::on_menu_new_proyect() {
	on_menu_close_proyect();
	AskDiagramName dialog("Nombre del proyecto");
	m_proyectName = dialog.askName();
	std::string proyectPath = Settings::getInstance().getValue("DiagramsPath") + m_proyectName;
	mkdir(proyectPath.c_str(), 0777);
	agregarSubVentana();
}

void Tabs::on_menu_open_proyect() {
	on_menu_close_proyect();
	AskDiagramName dialog("Nombre del proyecto");
	m_proyectName = dialog.askName();
	std::string proyectPath = Settings::getInstance().getValue("DiagramsPath") + m_proyectName;

	DIR * directorio;
	struct dirent * ent;

	if ((directorio = opendir(proyectPath.c_str())) == NULL) {
		printf("No puedo abir el directorio \n");
		return;
	}
	for (int i = 0; (ent = readdir(directorio)) != NULL; i++) {
		std::string archivo = proyectPath + "/" + ent->d_name;
		if(archivo.find("-rep") == archivo.length() - 4 ) {
			XmlReader reader(archivo.c_str());
			Diagram* circ = new Diagram();
			agregarSubVentana(circ);
			subVentanas.back()->getWorkspace()->on_load(reader);
			set_tab_label_text(*subVentanas.back(), circ->getName());
		}
	}
	closedir(directorio);
}

void Tabs::on_menu_close_proyect() {
	while ( get_n_pages () >= 1)
		removerSubVentanaActual();
}

void Tabs::on_menu_open() {
	Gtk::FileChooserDialog fileChooser("Elegir nombre", Gtk::FILE_CHOOSER_ACTION_OPEN);
	fileChooser.resize(600,450);
	fileChooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fileChooser.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	int resultado = fileChooser.run();
	if (resultado == Gtk::RESPONSE_OK) {
		XmlReader reader(fileChooser.get_filename().c_str());
		Diagram* circ = new Diagram();
		agregarSubVentana(circ);
		subVentanas.back()->getWorkspace()->on_load(reader);
		set_tab_label_text(*subVentanas.back(), circ->getName());
	}
}

void Tabs::save_as() {
	Gtk::FileChooserDialog fileChooser("Elegir name", Gtk::FILE_CHOOSER_ACTION_SAVE);
	fileChooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fileChooser.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
	int resultado = fileChooser.run();
	if (resultado == Gtk::RESPONSE_OK) {
		Diagram* diagram = subVentanas[get_current_page()]->getDiagram();
		std::cout<<"cantidad: "<<diagram->getComponents()->size()<<" diagrama "<< diagram->getName()<<std::endl;
		std::string path = fileChooser.get_filename();
		diagram->setPath(path);
		XmlWriter writer_rep("diagram");
		XmlWriter writer_comp("diagram");
		subVentanas[get_current_page()]->getWorkspace()->store(writer_rep, writer_comp);
		writer_rep.saveFile((path + "-rep").c_str());
		writer_comp.saveFile((path + "-comp").c_str());
	}
}

void Tabs::on_menu_save() {
	if ( get_n_pages () < 1)
		return;

	Diagram* diagram = subVentanas[get_current_page()]->getDiagram();
	std::string path = diagram->getPath();
	if (path.length() == 0)
		save_as();
	else {
		XmlWriter writer_rep("diagram");
		XmlWriter writer_comp("diagram");
		std::cout<<"cantidad: "<<diagram->getComponents()->size()<<std::endl;
		subVentanas[get_current_page()]->getWorkspace()->store(writer_rep, writer_comp);
		writer_rep.saveFile((path + "-rep").c_str());
		writer_comp.saveFile((path + "-comp").c_str());
	}
}

void Tabs::on_menu_save_as() {
	if (get_n_pages () > 0)
		save_as();
}

bool Tabs::on_key_release_event(GdkEventKey* event) {
	if (get_n_pages () > 0)
		subVentanas[get_current_page()]->getWorkspace()->on_key_release_event(event);
	return false;
}

bool Tabs::on_key_press_event(GdkEventKey* event){
	if (get_n_pages () > 0)
		subVentanas[get_current_page()]->getWorkspace()->on_key_press_event(event);
	return false;
}

Workspace* Tabs::getCurrentWorkspace(){
	if ( get_n_pages () < 1)
		return NULL;
	return subVentanas[get_current_page()]->getWorkspace();
}

void Tabs::on_name_change() {
	Workspace* currentWorkspace = getCurrentWorkspace();
	if ( currentWorkspace != NULL){
		AskDiagramName dialog("Nombre del diagrama");
		std::string diagramName = dialog.askName();
		if ( diagramName != ""){
			currentWorkspace->getDiagram()->setName(diagramName);
			Gtk::Label* label = (Gtk::Label*)get_tab_label(*subVentanas[get_current_page()]);
			label->set_text(diagramName);
		}
	}
}
