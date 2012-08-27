#ifndef VISUALCOMPONENTENTITY_H_
#define VISUALCOMPONENTENTITY_H_

#include "gui/Dibujar/AuxiliarDibujar.h"
#include "model/Entity.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/VisualComponents/VisualComponentConector.h"

class VisualComponentEntity: public VisualCompositeComponent{

public:
	VisualComponentEntity(Diagram& diagram);

	VisualComponentEntity(const VisualComponentEntity& other);

	virtual ~VisualComponentEntity() {
	}

	virtual VisualCompositeComponent* getCopy();

	virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext);

	virtual InfluenceArea getInfluenceArea();
};

#endif /* VISUALCOMPONENTENTITY_H_ */
