#ifndef VISUALCOMPONENTSEGMENT_H_
#define VISUALCOMPONENTSEGMENT_H_

#include "model/Via.h"
#include "gui/VisualComponents/VisualComponent.h"
#include "utils/Point.h"

class VisualComponentVia;

class VisualComponentSegment : public VisualComponent{
private:
	bool m_isVertical;
    Point* m_startPoint;
    Point* m_endPoint;

public:
	VisualComponentSegment(Point* start, Point* end, bool isVertical);

	virtual ~VisualComponentSegment();

	virtual InfluenceArea getInfluenceArea();
	virtual void on_expose(Cairo::RefPtr<Cairo::Context> ptrContext);
	virtual void on_move(int mouseX, int mouseY);

	virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext);

	virtual int getX() const;
	virtual void setX(int x);
	virtual int getY() const;
	virtual void setY(int y);

	bool isVertical();
	bool isMobile();
	int getLength();
    Point *getStartPoint() const
    {
        return m_startPoint;
    }

    void setStartPoint(Point *startPoint)
    {
        m_startPoint = startPoint;
    }

    Point *getEndPoint() const
    {
        return m_endPoint;
    }

    void setEndPoint(Point *endPoint)
    {
         m_endPoint = endPoint;
    }

};

#endif /* VISUALCOMPONENTSEGMENT_H_ */
