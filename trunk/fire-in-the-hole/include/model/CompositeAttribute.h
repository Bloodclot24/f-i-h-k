#ifndef COMPOSITEATTRIBUTE_H_
#define COMPOSITEATTRIBUTE_H_

#include "model/Component.h"

class CompositeAttribute: public Component {

	virtual void initializeConnectors();
public:
	CompositeAttribute(const std::string & name = TARGET_COMPOSITEATTRIBUTE, int orientation = 0);

	CompositeAttribute(const CompositeAttribute &);
	CompositeAttribute& operator=(const CompositeAttribute&);

	virtual void serialize(XmlWriter & writer_rep, XmlWriter & writer_comp);

	virtual void deserialize(XmlReader & reader);

	virtual void update();
};

#endif /* COMPOSITEATTRIBUTE_H_ */
