#ifndef VISUALCOMPONENTFORK_H_
#define VISUALCOMPONENTFORK_H_

#include "VisualCompositeComponent.h"

class VisualComponentForkVia: public VisualCompositeComponent {
public:

	VisualComponentForkVia(Diagram* diagram);

	VisualComponentForkVia(const VisualComponentForkVia& other);

	virtual ~VisualComponentForkVia();

	virtual VisualCompositeComponent* getCopy(Diagram* diagram);

	virtual InfluenceArea getInfluenceArea();

	virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext);
};

#endif /* VISUALCOMPONENTFORK_H_ */
