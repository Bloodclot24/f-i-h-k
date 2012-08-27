#ifndef VISUALCOMPONENCOMPOSITEATTRIBUTE_H_
#define VISUALCOMPONENTCOMPOSITEATTRIBUTE_H_

#include "gui/Dibujar/AuxiliarDibujar.h"
#include "model/CompositeAttribute.h"
#include "model/Diagram.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "VisualComponentConector.h"

class VisualComponentCompositeAttribute: public VisualCompositeComponent{
public:
	VisualComponentCompositeAttribute( Diagram& diagram);

	VisualComponentCompositeAttribute(const VisualComponentCompositeAttribute& other);

	virtual ~VisualComponentCompositeAttribute() {
	}
	virtual VisualCompositeComponent* getCopy();

	virtual InfluenceArea getInfluenceArea();

	virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext);

    virtual void showProperties();
};

#endif /* VISUALCOMPONENTCOMPOSITEATTRIBUTE_H_ */
