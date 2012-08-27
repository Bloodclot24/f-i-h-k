#ifndef VISUALCOMPONENTVIA_H_
#define VISUALCOMPONENTVIA_H_

#include "../Dibujar/AuxiliarDibujar.h"
#include "model/Via.h"
#include "VisualCompositeComponent.h"
#include "gui/SubWindow/Workspace.h"
#include "utils/Point.h"

class VisualComponentConector;
class VisualComponentSegment;

/**
 * @brief Representa a una via compuesta por diferentes segmentos.
 * La misma cumple los siguientes invariantes:
 * - Esta compuesta de segmentos alternados entre (- | - | -, etc) o ( | - | - |, etc).
 * - Cada segmento esta parametrizado por : Un punto inicial, una longitud y un sentido ( | o -).
 * - Los segmentos estan encadenados de forma que cada uno tiene referencia al anterior y al siguiente, (pueden ser null en caso de ser un extremo).
 * - El punto inicial de cada segmento corresponde al punto final del segmento anterior (dado por punto inicial + longitud en direccion de sentido).
 */
class VisualComponentVia: public VisualCompositeComponent {

private:
    VisualComponentConector *m_startConector;
    VisualComponentConector *m_endConector;

	void initializeSegments();

public:

	VisualComponentVia(VisualComponentConector* start, Diagram& diagram, VisualComponentConector* end = NULL);

	VisualComponentVia(const VisualComponentVia& other);

	VisualComponentVia(Diagram& diagram);

	virtual ~VisualComponentVia();

	virtual void on_move(int x, int y);

	void createSegments();

	virtual InfluenceArea getInfluenceArea();

	virtual void load(XmlReader& reader, Diagram & diagram);

	void extend();

	void setStartConector( VisualComponentConector* connector);

	void setEndConector( VisualComponentConector* connector);
    void alignPoints(Point *newPoint, Point *alignPoint, int x, int y);
    void alignSegment(VisualComponentSegment *editedSegment);
    virtual void invertConnections();
    virtual VisualCompositeComponent *getCopy(Diagram & diagram);

    VisualComponentConector *getStartConector() const
    {
        return m_startConector;
    }

    VisualComponentConector *getEndConector() const
    {
        return m_endConector;
    }

	virtual void setSelected(bool sel);

	virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext);

	virtual void showProperties();

};

#endif /* VISUALCOMPONENTVia_H_ */

