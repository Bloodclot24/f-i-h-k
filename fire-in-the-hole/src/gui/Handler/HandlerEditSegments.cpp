#include "gui/Handler/HandlerEditSegments.h"
#include "gui/Handler/HandlerDefault.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/VisualComponents/VisualComponentVia.h"

HandlerEditSegments::HandlerEditSegments( DrawingAreaPlusPlus* drawArea, VisualComponentVia* via, VisualComponentSegment* segment) :
Handler(drawArea){
	m_segment = segment;
	m_via = via;
	if(!m_segment->getStartPoint()->isMobile() || !m_segment->getEndPoint()->isMobile())
		creatSegments();
}

HandlerEditSegments::~HandlerEditSegments(){
	m_via->alignSegment(m_segment);
	m_drawArea->reDraw();
}

void HandlerEditSegments::on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent){
	if ( m_segment->isVertical()){
		m_segment->getStartPoint()->setX(event->x);
		m_segment->getEndPoint()->setX(event->x);
	} else {
		m_segment->getStartPoint()->setY(event->y);
		m_segment->getEndPoint()->setY(event->y);
	}

	m_drawArea->reDraw();
}

void HandlerEditSegments::on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){
	m_drawArea->setHandler( new HandlerDefault(m_drawArea));
}

void HandlerEditSegments::creatSegments(){
	if(m_segment->getStartPoint()->isMobile()){
		m_via->getChildren().pop_back(); // sacamos el ultimo segmento (m_segment).
		int startX = m_segment->getStartPoint()->getX(), startY = m_segment->getStartPoint()->getY();
		m_segment->getStartPoint()->setY(startY);
		int finalX = m_segment->getEndPoint()->getX(), finalY = m_segment->getEndPoint()->getY();

		int middleX = round((finalX - startX) / 2) + startX;
		Point* point1 = new Point(middleX, startY);
		Point* point2 = new Point(middleX, finalY);
		VisualComponentSegment* segment = new VisualComponentSegment(m_segment->getStartPoint(), point1, m_segment->isVertical());
		m_via->addChild(segment);
		VisualComponentSegment* segment1 = new VisualComponentSegment( point1, point2, !m_segment->isVertical());
		m_via->addChild(segment1);
		m_segment->setStartPoint(point2);
		m_via->addChild(m_segment);

		m_segment = segment;

	} else { // el otro es movible
		std::vector<VisualComponent*> segments(m_via->getChildren().size()-1);
		for(unsigned i=1; i<m_via->getChildren().size(); i++)
			segments[i-1] = m_via->getChildren()[i];
		m_via->getChildren().clear(); // sacamos el ultimo segmento (m_segment).

		int startX = m_segment->getStartPoint()->getX(), startY = m_segment->getStartPoint()->getY();
		m_segment->getEndPoint()->setY(startY);
		int finalX = m_segment->getEndPoint()->getX(), finalY = m_segment->getEndPoint()->getY();

		int middleX = round((finalX - startX) / 2) + startX;
		Point* point1 = new Point(middleX, startY);
		Point* point2 = new Point(middleX, finalY);
		m_via->addChild(m_segment);
		VisualComponentSegment* segment = new VisualComponentSegment(point1, point2, !m_segment->isVertical());
		m_via->addChild(segment);
		VisualComponentSegment* segment1 = new VisualComponentSegment( point2, m_segment->getEndPoint(), m_segment->isVertical());
		m_via->addChild(segment1);
		m_segment->setEndPoint(point1);

		m_segment = segment1;

		for(unsigned i=0; i< segments.size(); i++)
			m_via->getChildren().push_back(segments[i]);

	}

	//Se actualiza el model/
	Via* via = (Via*) m_via->getComponent();
	via->getPoints().clear();
	VisualComponentSegment* segment = NULL;
	for ( unsigned i=0 ; i<m_via->getChildren().size() ; i++){
		segment = (VisualComponentSegment*)m_via->getChildren()[i];
		via->addPointAtEnd(segment->getStartPoint());
	}
	via->addPointAtEnd(segment->getEndPoint());
}
