#ifndef ENTITY_H_
#define ENTITY_H_

#include "model/Component.h"

class Entity: public Component {
private:
	virtual void initializeConnectors();
public:

	Entity(const std::string & name = TARGET_ENTITY, int orientation = 0);

	Entity(const Entity &);
	Entity& operator=(const Entity&);

	virtual void serialize(XmlWriter & writer_rep, XmlWriter & writer_comp);

	virtual void update();

};

#endif /* ENTITY_H_ */
