#ifndef SUBDIAGRAM_H_
#define SUBDIAGRAM_H_

#include <list>
#include "model/Component.h"

class Subdiagram: public Component {
private:

public:
	Subdiagram(const std::string & name = TARGET_SUBDIAGRAM);

	Subdiagram(const Subdiagram &);
	Subdiagram& operator=(const Subdiagram&);

	virtual void serialize(XmlWriter & writer_rep, XmlWriter & writer_comp);

	virtual void deserialize(XmlReader & reader);

	/**
	 * Se agrega a la coleccion de subdiagramas en el diagrama pasado como parametro
	 * @param diagram
	 */
	virtual void addToDiagram(Diagram* diagram);

	/**
	 * Remueve su instancia de la coleccion de subdiagramas en el diagrama
	 */
	virtual void removeFromDiagram(Diagram* diagram);

/*    std::string getIP() const
    {
        return m_ip;
    }

    unsigned getPort() const
    {
        return m_port;
    }

*/    unsigned getSizeX() const
    {
        return 0; //m_sizeX;
    }

    unsigned getSizeY() const
    {
        return 0; //m_sizeY;
    }
/*
    void setSize(unsigned sizeX, unsigned sizeY)
    {
        m_sizeX = sizeX;
        m_sizeY = sizeY;
    }

    unsigned getAttributeNumber() const {
    	return m_AttributeNumber;
    }

	void setIp( const std::string &ip){
		m_ip = ip;
	}

	void setPort( unsigned port){
		m_port = port;
	}
*/
	virtual void initializeConnectors() {}

};

#endif /* SUBDIAGRAM_H_ */
