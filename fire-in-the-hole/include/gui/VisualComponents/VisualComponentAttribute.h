#ifndef VISUALCOMPONENTATTRIBUTE_H_
#define VISUALCOMPONENTATTRIBUTE_H_

#include "model/Attribute.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"

class Diagram;

class VisualComponentAttribute: public VisualCompositeComponent{
public:
	VisualComponentAttribute( Diagram* diagram);

	virtual ~VisualComponentAttribute() {
	}

	virtual VisualCompositeComponent* getCopy(Diagram* diagram);

	VisualComponentAttribute(const VisualComponentAttribute& other);

	virtual InfluenceArea getInfluenceArea();

	virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext);

    virtual void showProperties();
};

#endif /* VISUALCOMPONENTEntrada_H_ */
