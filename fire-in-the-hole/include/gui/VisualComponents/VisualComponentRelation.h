#ifndef VISUALCOMPONENTRELATION_H_
#define VISUALCOMPONENTRELATION_H_

#include "model/Relation.h"
#include "gui/VisualComponents/VisualCompositeComponent.h"
#include "model/Diagram.h"

class VisualComponentRelation: public VisualCompositeComponent{
public:
	VisualComponentRelation( Diagram& diagram);

	VisualComponentRelation(const VisualComponentRelation& other);

	virtual ~VisualComponentRelation() {
	}

	virtual VisualCompositeComponent* getCopy(Diagram & diagram);

	virtual InfluenceArea getInfluenceArea();

	virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext);

};

#endif /* VISUALCOMPONENTRELATION_H_ */
