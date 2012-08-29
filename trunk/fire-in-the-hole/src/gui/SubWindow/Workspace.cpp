#include "gui/SubWindow/Workspace.h"
#include "gui/VisualComponents/VisualComponentEntity.h"
#include "gui/VisualComponents/VisualComponentCompositeAttribute.h"
#include "gui/VisualComponents/VisualComponentRelation.h"
#include "gui/VisualComponents/VisualComponentAttribute.h"
#include "gui/VisualComponents/VisualComponentSubdiagram.h"
#include "gui/VisualComponents/VisualComponentVia.h"
#include "gui/VisualComponents/VisualComponentForkVia.h"
#include "model/Utils.h"
#include "xml/XmlReader.h"
#include "gui/Tabs.h"
#include <iostream>
using namespace std;

Workspace::Workspace(Diagram* diagram, bool enableEvents) : DrawingAreaPlusPlus(enableEvents),
	m_diagram(diagram)
{
	if ( enableEvents)
		add_events(Gdk::ENTER_NOTIFY_MASK);

	m_refPageSetup = Gtk::PageSetup::create();
	m_refSettings = Gtk::PrintSettings::create();
	m_diagramOffsetX = 0;
	m_diagramOffsetY = 0;
}

Workspace::~Workspace() {

}

void Workspace::imprimirAPng(std::string archivo) {
	double sizeX, sizeY;
	getSize(sizeX, sizeY);

	Cairo::RefPtr<Cairo::Surface> ptrSurface = Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, sizeX+50, sizeY+50);
	Cairo::RefPtr<Cairo::Context> ptrContext = Cairo::Context::create(ptrSurface);

	//Blanquear.
	ptrContext->set_source_rgb(1, 1, 1);
	ptrContext->paint();

	ptrContext->save();

	prepareScreenContext(ptrContext);
	ptrContext->restore();

	ptrContext->set_source_rgb(1, 1, 1);
	ptrContext->fill();
	ptrContext->get_target()->write_to_png(archivo);
}

void Workspace::imprimirAPdf(std::string archivo) {
	Glib::RefPtr<Gtk::PrintOperation> print = Gtk::PrintOperation::create();
	print_or_preview(print);
	print->set_export_filename(archivo);

	try {
		print->run(Gtk::PRINT_OPERATION_ACTION_EXPORT,
				dynamic_cast<Gtk::Window&> (*get_toplevel()));
	} catch (const Gtk::PrintError& ex) {
		std::cerr << "An error occurred while trying to run a print operation:"
				<< ex.what() << std::endl;
	}
}

void Workspace::print_or_preview(Glib::RefPtr<Gtk::PrintOperation> print) {
	print->signal_draw_page().connect(sigc::mem_fun(this,
			&Workspace::on_draw_page));

	print->set_n_pages(2);

	print->set_track_print_status();
	print->set_default_page_setup(m_refPageSetup);
	print->set_print_settings(m_refSettings);
}

void Workspace::on_menu_file_page_setup() {
	Glib::RefPtr<Gtk::PageSetup> new_page_setup = Gtk::run_page_setup_dialog(
			dynamic_cast<Gtk::Window&> (*get_toplevel()), m_refPageSetup,
			m_refSettings);
	m_refPageSetup = new_page_setup;
}

void Workspace::on_menu_file_print_preview() {
	Glib::RefPtr<Gtk::PrintOperation> print = Gtk::PrintOperation::create();
	print_or_preview(print);
	try {
		print->run(Gtk::PRINT_OPERATION_ACTION_PREVIEW,
				dynamic_cast<Gtk::Window&> (*get_toplevel()));
	} catch (const Gtk::PrintError& ex) {
		std::cerr << "An error occurred while trying to run a print operation:"
				<< ex.what() << std::endl;
	}
}

void Workspace::on_menu_file_print() {
	Glib::RefPtr<Gtk::PrintOperation> print = Gtk::PrintOperation::create();
	print_or_preview(print);

	try {
		print->run(Gtk::PRINT_OPERATION_ACTION_PRINT_DIALOG,
				dynamic_cast<Gtk::Window&> (*get_toplevel()));
	} catch (const Gtk::PrintError& ex) {
		std::cerr << "An error occurred while trying to run a print operation:"
				<< ex.what() << std::endl;
	}
}

void Workspace::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context,
		int page_nr) {
	if (page_nr == 0) {
		double sizeX, sizeY, sizePageX, sizePageY;
		getSize(sizeX, sizeY);
		getPageSize(sizePageX, sizePageY);
		double scaleX = sizePageX / sizeX;
		double scaleY = sizePageY / sizeY;
		double lowest = scaleX < scaleY ? scaleX : scaleY;
		if (lowest < 1)
			context->get_cairo_context()->scale(lowest, lowest);
		prepareScreenContext(context->get_cairo_context());
	} else{
	}
}

void Workspace::on_load(XmlReader& reader, Tabs* tabs) {

	try{
		Utils utils;
		//setea atributos del diagram
		reader.setCurrentNode(reader.getRoot());
		m_diagram->setName(reader.getCurrentNodeProperty(TARGET_NAME));
		m_diagram->setSize(utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_SIZE_X)),
				utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_SIZE_Y)));

		std::map< unsigned, VisualCompositeComponent* > visualComponents;
		std::map< unsigned, std::vector<int> > idsComponentesEntradas;
		const char* nameComponente;
		xmlNode* nodoAnterior = reader.getCurrentNodeChild();
		reader.setCurrentNode(nodoAnterior);

		while(reader.getCurrentNode()){
			nameComponente = reader.getCurrentNodeName();

			VisualCompositeComponent* visualComponent = NULL;
			if(!strcmp(nameComponente, TARGET_ENTITY))
				visualComponent = new VisualComponentEntity( m_diagram);
			else if (!strcmp(nameComponente, TARGET_ATTRIBUTE))
				visualComponent = new VisualComponentAttribute( m_diagram);
			else if (!strcmp(nameComponente, TARGET_RELATION))
				visualComponent = new VisualComponentRelation( m_diagram);
			else if (!strcmp(nameComponente, TARGET_COMPOSITEATTRIBUTE))
				visualComponent = new VisualComponentCompositeAttribute( m_diagram);
			else if (!strcmp(nameComponente, TARGET_SUBDIAGRAM))
				visualComponent = new VisualComponentSubdiagram( m_diagram);
			else if (!strcmp(nameComponente, TARGET_VIA))
				visualComponent = new VisualComponentVia( m_diagram);
			else if (!strcmp(nameComponente, TARGET_FORK))
				visualComponent = new VisualComponentForkVia( m_diagram);

			if(visualComponent){
				visualComponent->load(reader, m_diagram);
				addVisualComponent(visualComponent);
				nodoAnterior = reader.getCurrentNode();
				int identificador = utils.convertToInt(reader.getCurrentNodeProperty(TARGET_ID));
				visualComponents[identificador] = visualComponent;

				std::vector<Views> views;
				std::vector<int> ids;
				xmlNode* nodoActual = reader.getCurrentNodeChild();
				while(nodoActual){
					reader.setCurrentNode(nodoActual);
					if(strcmp(reader.getCurrentNodeName(), TARGET_PUNTO) != 0 && strcmp(reader.getCurrentNodeName(), TARGET_OTHER_DIAGRAM) != 0)
						ids.push_back(utils.convertToInt(reader.getCurrentNodeProperty(TARGET_ID)));
					if(strcmp(reader.getCurrentNodeName(), TARGET_OTHER_DIAGRAM) == 0){
						Views view;
						view.name = reader.getCurrentNodeProperty(TARGET_NAME);
						view.id = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_ID));
						views.push_back(view);
					}
					nodoActual = reader.nextNode();
				}
				idsComponentesEntradas[identificador] =  ids;
				for(unsigned i = 0 ; i < views.size() ; i++) {
					Workspace* workspace = tabs->getWorkspace(views[i].name);
					visualComponent->addView(workspace->getVisualCompositeComponent(views[i].id));
				}
			}

			reader.setCurrentNode(nodoAnterior);
			nodoAnterior = reader.nextNode();
			reader.setCurrentNode(nodoAnterior);

		}
		//Conecta los componentes
		for(unsigned i = 0; i < idsComponentesEntradas.size(); i++){
			std::vector<int> ids = idsComponentesEntradas[i];
			VisualCompositeComponent* visualComponent = visualComponents[i];
			for (unsigned j = 0; j < ids.size(); j++) {
				if ( ids[j] == -1)
					continue;
				VisualComponentVia* visualVia = (VisualComponentVia*) visualComponents[ids[j]];
				VisualComponentConector* connector =(VisualComponentConector*) visualComponent->getChildren()[j];
				int x =(*((Via*)(visualVia->getComponent()))->getPoints().begin())->getX();
				int y =(*((Via*)(visualVia->getComponent()))->getPoints().begin())->getY();
				int delta = 10;
				if( connector->getX() - delta <= x && x <= connector->getX() + delta  &&
						connector->getY() - delta <= y && y <= connector->getY() + delta)
						visualVia->setStartConector(connector);
				else
						visualVia->setEndConector(connector);
				connector->setVia(visualVia);
			}
		}
	} catch (std::exception e) {
		throw std::runtime_error("Formato invalido del archivo xml");
	}
}


VisualCompositeComponent* Workspace::getVisualComponent(Component* comp){
	for ( unsigned i=0 ; i<m_visualComponentList.size(); i++){
		if ( m_visualComponentList[i]->getComponent() == comp)
			return m_visualComponentList[i];
	}
	return NULL;
}


void Workspace::store(XmlWriter& writer_rep, XmlWriter& writer_comp){
	Utils utils;
	updateDiagramSize();
	writer_rep.addCurrentNodeProperty(TARGET_NAME, m_diagram->getName().c_str());
	writer_rep.addCurrentNodeProperty(TARGET_SIZE_X, utils.convertToString(m_diagram->getSizeX()).c_str());
	writer_rep.addCurrentNodeProperty(TARGET_SIZE_Y, utils.convertToString(m_diagram->getSizeY()).c_str());

	writer_comp.addCurrentNodeProperty(TARGET_NAME, m_diagram->getName().c_str());

	m_diagram->startSerialization();
	for (std::vector<VisualCompositeComponent*>::iterator it = m_visualComponentList.begin(); it != m_visualComponentList.end(); ++it)
		(*it)->store(writer_rep, writer_comp, m_diagram);
	m_diagram->finalizeSerialization();

}

void Workspace::updateDiagramSize(){

	int maxX = 0, maxY = 0, minX = 0, minY = 0;
	if(m_visualComponentList.size() > 0) {
		maxX = minX = m_visualComponentList[0]->getX();
		maxY = minY = m_visualComponentList[0]->getY();
		for ( unsigned i=1 ; i<m_visualComponentList.size(); i++){

			 if(m_visualComponentList[i]->getX() + m_visualComponentList[i]->getSizeX()> maxX)
				 maxX = m_visualComponentList[i]->getX() + m_visualComponentList[i]->getSizeX();
			 else if(m_visualComponentList[i]->getX() < minX)
				 minX = m_visualComponentList[i]->getX();

			 if(m_visualComponentList[i]->getY() + m_visualComponentList[i]->getSizeY() > maxY)
				 maxY = m_visualComponentList[i]->getY() + m_visualComponentList[i]->getSizeY();
			 else if(m_visualComponentList[i]->getY() < minY)
				 minY = m_visualComponentList[i]->getY();
		}
	 }

	m_diagramOffsetX = minX;
	m_diagramOffsetY = minY;
	m_diagram->setSize(maxX - minX, maxY - minY);
}

Diagram* Workspace::getDiagram(){
	return m_diagram;
}

void Workspace::printErrorMessage(const Cairo::RefPtr<Cairo::Context>& ptrContext, const std::string& errorMessage, double wrap) {
    ptrContext->set_source_rgb(0, 0, 0);
    ptrContext->set_line_width(0.4);
    Glib::RefPtr<Pango::Layout> pangoLayout = Pango::Layout::create (ptrContext);

    Pango::FontDescription font_desc("sans 8");
    pangoLayout->set_font_description(font_desc);
    pangoLayout->set_width(Pango::SCALE * wrap);
    pangoLayout->set_wrap(Pango::WRAP_WORD_CHAR);

    pangoLayout->set_text("Ocurrio un error : " + errorMessage);
    pangoLayout->update_from_cairo_context(ptrContext);
    pangoLayout->add_to_cairo_context(ptrContext);
    ptrContext->fill();
}

void Workspace::validateDiagram(std::string archivo){

	  fstream filestr;
	  filestr.open(archivo.c_str(), std::fstream::out);

	  	if (filestr.is_open())
	  	  	m_diagram->validateDiagram(filestr);
	  	filestr.close();

}
