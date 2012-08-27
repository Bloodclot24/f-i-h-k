#include "gui/VisualComponents/VisualComponentVia.h"
#include "gui/VisualComponents/VisualComponentConector.h"
#include "gui/VisualComponents/VisualComponentSegment.h"
#include "model/Utils.h"
#include "model/Fork.h"
#include "gui/SubWindow/ViewModifyComponentInfoWin.h"

VisualComponentVia::VisualComponentVia(Diagram& diagram) :
VisualCompositeComponent(diagram){
	m_component = new Via();
	initialize();
}

VisualComponentVia::VisualComponentVia(VisualComponentConector* start, Diagram& diagram, VisualComponentConector* end) :
VisualCompositeComponent(diagram){
	m_component = new Via();
	setStartConector(start);
	setEndConector(end);
	m_component->setX(m_startConector->getX());
	m_component->setY(m_startConector->getY());
	createSegments();
	initialize();
}

VisualComponentVia::VisualComponentVia(const VisualComponentVia& other) : VisualCompositeComponent(other.m_diagram) {
	m_component = new Via(*(Via*)other.m_component);
	initialize();
	initializeSegments();
}

VisualComponentVia::~VisualComponentVia(){
	if ( m_startConector != NULL)
		m_startConector->setVia(NULL);
	if ( m_endConector != NULL)
		m_endConector->setVia(NULL);
}

void VisualComponentVia::setStartConector( VisualComponentConector* connector){
	m_startConector = connector;
	Via* via = (Via*) m_component;
	connector != NULL ? via->setStartConnector(connector->getConnector()) : via->setStartConnector(NULL);
}

void VisualComponentVia::setEndConector( VisualComponentConector* connector){
	m_endConector = connector;
	Via* via = (Via*) m_component;
	connector != NULL ? via->setEndConnector(connector->getConnector()) : via->setEndConnector(NULL);
}

InfluenceArea VisualComponentVia::getInfluenceArea() {
	std::vector<InfluenceArea> areas;
	for (std::vector<VisualComponent*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		areas.push_back((*it)->getInfluenceArea());
	return InfluenceArea(areas);
}

void VisualComponentVia::on_move(int x, int y){
	//Si ambas puntas de la via estan seleccionadas hay que mover everything.
	if (!(m_startConector->getParent()->isSelected() && m_endConector->getParent()->isSelected()))
		return;

	int deltaX = x - m_component->getX();
	int deltaY = y - m_component->getY();
	m_component->setX(x);
	m_component->setY(y);
	VisualComponentSegment* lastSeg = NULL;
	for (std::vector<VisualComponent*>::iterator it = m_children.begin(); it != m_children.end(); ++it){
		lastSeg = (VisualComponentSegment*) (*it);
		lastSeg->getStartPoint()->setX(lastSeg->getStartPoint()->getX() + deltaX);
		lastSeg->getStartPoint()->setY(lastSeg->getStartPoint()->getY() + deltaY);
	}
	if ( lastSeg != NULL){
		lastSeg->getEndPoint()->setX(lastSeg->getEndPoint()->getX() + deltaX);
		lastSeg->getEndPoint()->setY(lastSeg->getEndPoint()->getY() + deltaY);
	}
}

void VisualComponentVia::extend(){
	if ( m_startConector->getParent()->isSelected() && m_endConector->getParent()->isSelected())
		return;

	Point* newPoint;
	Point* alignPoint;
	int x, y;
	if ( m_startConector->getParent()->isSelected()){
		newPoint = ((VisualComponentSegment*)m_children[0])->getStartPoint();
		alignPoint = ((VisualComponentSegment*)m_children[0])->getEndPoint();
		x = m_startConector->getX() + m_startConector->getXCenter();
		y = m_startConector->getY() + m_startConector->getYCenter();
	} else {
		newPoint = ((VisualComponentSegment*)m_children[m_children.size()-1])->getEndPoint();
		alignPoint = ((VisualComponentSegment*)m_children[m_children.size()-1])->getStartPoint();
		x = m_endConector->getX() + m_endConector->getXCenter();
		y = m_endConector->getY() + m_endConector->getYCenter();
	}

	alignPoints(newPoint, alignPoint, x, y);
}

void VisualComponentVia::alignPoints( Point* newPoint, Point* alignPoint, int x, int y){
	if (newPoint->getY() == alignPoint->getY())
		alignPoint->setY(y);
	newPoint->setX(x);
	newPoint->setY(y);
}

void VisualComponentVia::alignSegment( VisualComponentSegment* editedSegment) {
	VisualComponentSegment* anteriorAnterior = NULL;
	VisualComponentSegment* posteriorPosterior = NULL;
	VisualComponentSegment* anterior = NULL;
	VisualComponentSegment* posterior = NULL;
	//si son los de los extremos no se editan
	for(int i = 1; i < (int)m_children.size() - 1; i++){
		if(m_children[i] == editedSegment){
			if(i - 2 >= 0)
				anteriorAnterior = (VisualComponentSegment*) m_children[i - 2];
			if(i + 2 < (int)m_children.size())
				posteriorPosterior = (VisualComponentSegment*) m_children[i + 2];
			anterior = (VisualComponentSegment*) m_children[i - 1];
			posterior = (VisualComponentSegment*) m_children[i + 1];
			break;
		}
	}

	bool entro = false;

	if(anteriorAnterior != NULL && anterior->getLength() < 6) {
		entro = true;
		Via* via = (Via*) m_component;
		via->removePoint(anterior->getStartPoint());
		via->removePoint(editedSegment->getStartPoint());
		posterior->isVertical() ? posterior->getStartPoint()->setY(anteriorAnterior->getEndPoint()->getY()) :
			posterior->getStartPoint()->setX(anteriorAnterior->getEndPoint()->getX());
		anteriorAnterior->setEndPoint(posterior->getStartPoint());
		removeChild(anterior);
		removeChild(editedSegment);
		delete anterior->getStartPoint();
		delete editedSegment->getStartPoint();
		delete anterior;
		delete editedSegment;
		editedSegment = anteriorAnterior;
	}

	if(posteriorPosterior != NULL && posterior->getLength() < 6 && !entro) {
		Via* via = (Via*) m_component;
		via->removePoint(editedSegment->getStartPoint());
		via->removePoint(posterior->getStartPoint());
		anterior->isVertical() ? posteriorPosterior->getStartPoint()->setX(anterior->getEndPoint()->getX()) :
			posteriorPosterior->getStartPoint()->setY(anterior->getEndPoint()->getY());
		anterior->setEndPoint(posteriorPosterior->getStartPoint());
		removeChild(posterior);
		removeChild(editedSegment);
		delete posterior->getStartPoint();
		delete editedSegment->getStartPoint();
		delete posterior;
		delete editedSegment;
	}
}

void VisualComponentVia::createSegments(){
	Via* via = (Via*) m_component;

	int startX = m_startConector->getX() + m_startConector->getXCenter();
	int startY = m_startConector->getY() + m_startConector->getYCenter();
	int	finalX = m_endConector->getX() + m_endConector->getXCenter();
	int finalY = m_endConector->getY() + m_endConector->getYCenter();


	int middleX = round((finalX - startX) / 2) + startX;
	Point* point0 = new Point(startX, startY);
	point0->setMobile(false);
	Point* point1 = new Point(middleX, startY);
	Point* point2 = new Point(middleX, finalY);
	Point* point3 = new Point(finalX, finalY);
	point3->setMobile(false);
	if(m_startConector->isEditable() && m_endConector->isEditable()) {
	VisualComponentSegment* segment = new VisualComponentSegment(point0, point1, false );
	addChild(segment);
	segment = new VisualComponentSegment( point1, point2, true); // m_component->getCardinality());
	addChild(segment);
	segment = new VisualComponentSegment( point2, point3, false);
	addChild(segment);

	//Se agregan los puntos al model/.
	via->addPointAtEnd(point0);
	via->addPointAtEnd(point1);
	via->addPointAtEnd(point2);
	via->addPointAtEnd(point3);
	} else { //esto es para que se dibujen diagonales las lineas que unen los atributos
		VisualComponentSegment* segment = new VisualComponentSegment(point0, point3, false);
		addChild(segment);
		//Se agregan los puntos al model/.
		via->addPointAtEnd(point0);
		via->addPointAtEnd(point3);
	}
}

void VisualComponentVia::showProperties(){
	if(m_startConector->isEditable() && m_endConector->isEditable()) {
		ViewModifyComponentInfoWin dialog(m_component);
		dialog.run();
	}
	return;
}

void VisualComponentVia::initializeSegments(){
	Via* via = (Via*)m_component;

	std::list< Point*> points = via->getPoints();
	Point* firstPoint = (*points.begin());

	std::list< Point*>::iterator it = points.begin();
	++it;
	bool isVertical = false;
	for ( ; it!=points.end() ; ++it ){
		VisualComponentSegment* segment = new VisualComponentSegment(firstPoint, (*it), isVertical);
		isVertical = !isVertical;
		firstPoint = (*it);
		addChild(segment);
	}
}


void VisualComponentVia::load(XmlReader& reader, Diagram & diagram){
	VisualCompositeComponent::load(reader, diagram);
	initializeSegments();
}

void VisualComponentVia::invertConnections(){ }

VisualCompositeComponent* VisualComponentVia::getCopy(Diagram & diagram){
	Diagram & origen = m_diagram;
	m_diagram = diagram;
	VisualCompositeComponent* comp = new VisualComponentVia(*this);
	m_diagram = origen;
	return comp;
}

void VisualComponentVia::setSelected(bool sel){
	m_selected = sel;
	for( unsigned i=0 ; i<m_children.size() ; i++){
		m_children[i]->setSelected(sel);
	}
}

void VisualComponentVia::draw(Cairo::RefPtr<Cairo::Context> ptrContext){
	Via* via = (Via*) m_component;
	ptrContext->save();

	VisualCompositeComponent::draw( ptrContext);
	Draw draw;
	std::list< Point* >::iterator it = via->getPoints().begin();
	Point* point1 = (*++it);
	Point* point2 = (*++it);
	draw.writeTextInContext(ptrContext,  (point1->getX() + point2->getX() ) / 2 + 14,
			( point1->getY() + point2->getY() ) / 2 - 2 , via->getTypes()[via->getType()], COLOR_IN_TEXT);
	if(via->getName() != "rol")
		draw.writeTextInContext(ptrContext,  (point1->getX() + point2->getX() ) / 2 + 18,
				( point1->getY() + point2->getY() ) / 2 + 12 , via->getName(), COLOR_IN_TEXT);
}
