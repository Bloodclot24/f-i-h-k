#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "model/Component.h"

class Attribute: public Component {

	virtual void initializeConnectors();
public:
	Attribute(const std::string & name = TARGET_ATTRIBUTE, int orientation = 0);

	Attribute(const Attribute &);
	Attribute& operator=(const Attribute&);

	virtual void serialize(XmlWriter & writer_rep, XmlWriter & writer_comp);

	virtual void deserialize(XmlReader & reader);

	virtual void removeFromDiagram(Diagram &diagram);

};

#endif /* ATTRIBUTE_H_ */
