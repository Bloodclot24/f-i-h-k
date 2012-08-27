#ifndef RELATION_H_
#define RELATION_H_

#include "model/Component.h"

class Relation: public Component {

	virtual void initializeConnectors();
public:
	Relation(const std::string & name = TARGET_RELATION, int orientation = 0);

	Relation(const Relation &);
	Relation& operator=(const Relation&);

	virtual void serialize(XmlWriter & writer_rep, XmlWriter & writer_comp);

	virtual void update();
};

#endif /* RELATION_H_ */
