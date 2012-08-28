#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/VisualComponents/VisualCompositeComponent.h"
#include "gui/Handler/Handler.h"
#include "gui/Handler/HandlerDefault.h"
#include "gui/VisualComponents/VisualComponentSegment.h"

#define LEFT_CLICK 1
#define RIGHT_CLICK 3

#define DRAWING_AREA_SIZE 1024 * 4, 1024 * 4

DrawingAreaPlusPlus::DrawingAreaPlusPlus(bool editable) {
	//Pido al X Server los eventos necesarios.
	m_editable = editable;

	set_size_request(DRAWING_AREA_SIZE);

	add_events(Gdk::POINTER_MOTION_MASK);
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::BUTTON_RELEASE_MASK);
	add_events(Gdk::KEY_PRESS_MASK);
	add_events(Gdk::KEY_RELEASE_MASK);
	m_handler = new HandlerDefault(this);

	m_selectionRectangle = NULL;
	m_connectingLine = NULL;

}

DrawingAreaPlusPlus::~DrawingAreaPlusPlus(){
	if ( m_handler != NULL)
		delete m_handler;
	for( unsigned i=0 ; i<m_visualComponentList.size() ; i++)
		delete m_visualComponentList[i];
}

void DrawingAreaPlusPlus::addVisualComponent(
		VisualCompositeComponent* visualComponent) {
	m_visualComponentList.push_back(visualComponent);
}

void DrawingAreaPlusPlus::removeVisualComponent(
		VisualCompositeComponent* visualComponent) {
	for (std::vector<VisualCompositeComponent*>::iterator it =
			m_visualComponentList.begin(); it != m_visualComponentList.end(); ++it)
		if ((*it) == visualComponent) {
			m_visualComponentList.erase(it);
			return;
		}
}

void DrawingAreaPlusPlus::reDraw() {
	queue_draw();
	show_all();
}

bool DrawingAreaPlusPlus::on_motion_notify_event(GdkEventMotion* event) {
	if ( m_editable)
		m_handler->on_motion_notify_event(event, getTouchedVisualComponent(event->x, event->y));
	return true;
}

bool DrawingAreaPlusPlus::on_button_press_event(GdkEventButton* event) {
	if ( m_editable){
		if ( event->button == LEFT_CLICK)
			m_handler->on_left_click_press_event(event, getTouchedVisualComponent(event->x, event->y));
		else if ( event->button == RIGHT_CLICK)
			m_handler->on_right_click_press_event(event, getTouchedVisualComponent(event->x, event->y));
	}
	return true;
}

bool DrawingAreaPlusPlus::on_button_release_event(GdkEventButton* event) {
	if ( m_editable){
		if ( event->button == LEFT_CLICK)
			m_handler->on_left_click_release_event(event, getTouchedVisualComponent(event->x, event->y));
		else if ( event->button == RIGHT_CLICK)
			m_handler->on_right_click_release_event(event, getTouchedVisualComponent(event->x, event->y));
	}
	return true;
}



bool DrawingAreaPlusPlus::on_expose_event(GdkEventExpose* event) {
	prepareScreenContext(get_window()->create_cairo_context());
	return true;
}

void DrawingAreaPlusPlus::prepareScreenContext(const Cairo::RefPtr<
		Cairo::Context> ptrContext) {
	//Blanquear Pantalla.
	ptrContext->set_source_rgb(1, 1, 1);
	ptrContext->paint();

	//Dibujar cuadriculado
	ptrContext->save();
	ptrContext->set_source_rgb(0.75, 0.75, 0.75); //gris
	ptrContext->set_line_width(ANCHO_DE_CUADRICULADO);
	std::valarray< double > dashes(2);
	dashes[0] = ANCHO_DE_CUADRICULADO; //Linea visible.
	dashes[1] = CUADRICULADO; //Linea no visible.
	ptrContext->set_dash(dashes, 0.0);
	int longXADibujar = get_allocation().get_width() - 2 * CUADRICULADO; //Sin el primero ni el ultimo.
	for (int y = CUADRICULADO; y < get_allocation().get_height(); y+= CUADRICULADO) {
		ptrContext->move_to(CUADRICULADO, y);
		ptrContext->rel_line_to(longXADibujar, 0);
		ptrContext->stroke();
	}
	ptrContext->restore();

	if (m_connectingLine != NULL)
		m_connectingLine->on_expose(ptrContext);
	for (std::vector<VisualCompositeComponent*>::reverse_iterator it =
			m_visualComponentList.rbegin(); it != m_visualComponentList.rend(); ++it)
		(*it)->on_expose(ptrContext);
	if ( m_selectionRectangle != NULL)
		drawSelection(ptrContext, *m_selectionRectangle);
}


VisualCompositeComponent* DrawingAreaPlusPlus::getTouchedVisualComponent(int x, int y){
	VisualCompositeComponent* visualComponent = NULL;
	for (std::vector<VisualCompositeComponent*>::iterator it =
			m_visualComponentList.begin(); it != m_visualComponentList.end(); ++it)
		if ((*it)->getInfluenceArea().touch(x, y))
			return (*it);

	return visualComponent;
}

void DrawingAreaPlusPlus::getTouchedVisualComponents(
		InfluenceArea& influenceArea,
		std::vector<VisualCompositeComponent*>& ret) {
	for (std::vector<VisualCompositeComponent*>::iterator it =
			m_visualComponentList.begin(); it != m_visualComponentList.end(); ++it)
		if ((*it)->getInfluenceArea().touch(influenceArea))
			ret.push_back(*it);
}

bool DrawingAreaPlusPlus::on_key_release_event(GdkEventKey* event) {
	if ( m_editable){
		int x,y;
		get_pointer(x,y);
		m_handler->on_key_release_event(event, getTouchedVisualComponent(x, y));
	}
	return true;
}

bool DrawingAreaPlusPlus::on_key_press_event(GdkEventKey* event, Tabs* tabs){
	if ( m_editable){
		int x,y;
		get_pointer(x,y);
		m_handler->on_key_press_event(event, getTouchedVisualComponent(x, y), tabs);
	}
	return true;
}

void DrawingAreaPlusPlus::setHandler(Handler* han){
	if ( m_handler != NULL)
		delete m_handler;
	m_handler = han;
}

Handler* DrawingAreaPlusPlus::getHandler(){
	return m_handler;
}

void DrawingAreaPlusPlus::setSelectionRectangle(InfluenceRectangle* rect){
	if ( m_selectionRectangle != NULL)
		delete m_selectionRectangle;
	m_selectionRectangle = rect;
}


void DrawingAreaPlusPlus::setActions(Glib::RefPtr<Gtk::ActionGroup>& actionGroup) {
	  m_UIManager = Gtk::UIManager::create();
	  m_UIManager->insert_action_group(actionGroup);

	  Glib::ustring ui_info =
	        "<ui>"
	        "  <popup name='PopupMenu'>"
				"      <menuitem action='Copy'/>"
				"      <menuitem action='Cut'/>"
				"      <menuitem action='Borrar'/>"
				"      <separator/>"
			    "      <menuitem action='Properties'/>"
				"      <separator/>"
				"      <menuitem action='CrearSubdiagrama'/>"
				"      <menuitem action='ExportarSubdiagrama'/>"
	        "  </popup>"
	        "</ui>";

	  m_UIManager->add_ui_from_string(ui_info);
}

Glib::RefPtr<Gtk::UIManager>& DrawingAreaPlusPlus::getUIManager(){
	return m_UIManager;
}

void DrawingAreaPlusPlus::setConnectingLine(VisualComponentSegment* line){
	if ( m_connectingLine != NULL){
		 // porque el delete de segment no borra los puntos del mismo
		delete m_connectingLine->getStartPoint();
		delete m_connectingLine->getEndPoint();
		delete m_connectingLine;
	}
	m_connectingLine = line;
}

VisualComponentSegment* DrawingAreaPlusPlus::getConnectingLine(){
	return m_connectingLine;
}

/**
 * Dibuja la seleccion mientras se esta ingresando.
 *
 * @param ptrContext
 * @param rectanguloDeInfluencia
 */
void DrawingAreaPlusPlus::drawSelection(const Cairo::RefPtr<Cairo::Context> ptrContext, InfluenceRectangle& rectanguloDeInfluencia) {
	ptrContext->save();
	ptrContext->set_source_rgb(0,0,0); //negro.
	ptrContext->set_line_width(ANCHO_DE_LINEA_SELECCION);
    std::valarray< double > dashes(2);
    dashes[0] = 1; //Linea visible.
    dashes[1] = 1; //Linea no visible.
	ptrContext->set_dash(dashes, 0.0);
	ptrContext->rectangle(rectanguloDeInfluencia.x0, rectanguloDeInfluencia.y0, rectanguloDeInfluencia.xf - rectanguloDeInfluencia.x0, rectanguloDeInfluencia.yf - rectanguloDeInfluencia.y0);
	ptrContext->stroke();
	ptrContext->restore();
}
