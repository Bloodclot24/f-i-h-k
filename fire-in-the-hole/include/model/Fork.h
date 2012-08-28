#ifndef FORK_H_
#define FORK_H_
#include <vector>
#include "model/Component.h"

/**
 * Clase que permite la bifurcacion de una via
 */
class Fork : public Component {

	virtual void initializeConnectors();
public:
	Fork(const std::string & name = TARGET_FORK, int orientation = 0);

	Fork(const Fork &);
	Fork& operator=(const Fork&);

	virtual void serialize(XmlWriter & writer_rep, XmlWriter & writer_comp);

	virtual void update();
};

#endif /* FORK_H_ */
