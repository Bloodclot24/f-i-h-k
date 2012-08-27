#ifndef VIA_H_
#define VIA_H_

#include "model/Component.h"
#include "utils/Point.h"
#include <list>

class Via: public Component {

private:
	unsigned m_exitNumber; //ojo con esto
	std::list< Point*> m_points;

	virtual void initializeConnectors();

public:

	Via(unsigned exit = 0, const std::string & name = TARGET_VIA, int orientation = 0);

	Via(const Via &);
	Via& operator=(const Via&);

	virtual ~Via();

	virtual void serialize(XmlWriter & writer_rep, XmlWriter & writer_comp);

	virtual void deserialize(XmlReader & reader);

	unsigned getExitNumber() const
    {
        return m_exitNumber;
    }

    void setExitNumber(unsigned componentExit)
    {
        m_exitNumber = componentExit;
    }

    void setStartConnector( Connector* c){
    	m_startConnector = c;
    }

    void setEndConnector( Connector* c){
    	m_endConnector = c;
    }

    Connector* getStartConnector(){
    	return m_startConnector;
    }

    Connector* getEndConnector(){
    	return m_endConnector;
    }

    /*
     * agrega un punto en la posicion dada por el iterador.
     */
    void addPoint( Point* p, std::list< Point* >::iterator it);

    void addPointAtEnd( Point* point);

    void removePoint( Point* p);

    std::list< Point* >& getPoints();

    Connector* m_startConnector;
    Connector* m_endConnector;

    bool verifyConnectEntityRelation();
};

#endif /* VIA_H_ */
