#ifndef COMPONENTE_H_
#define COMPONENTE_H_
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "xml/XmlReader.h"
#include "xml/XmlWriter.h"
#include "model/Connector.h"
#include "model/Utils.h"
#include <algorithm>
//#include <conio.h>

class Diagram;
class Attribute;
class Entity;

/**
 * Clase correspondiente a todos los elementos que puede contener
 * un diagrama.
 */
class Component {

private:
	int m_type;
	unsigned m_tamanio;

protected:
	std::string m_name;
	std::vector<Connector*> m_entryConnectors;
	std::vector<Connector*> m_exitConnectors;
	unsigned m_posX, m_posY;
	std::vector<Attribute*> m_attributes;
	std::vector<Entity*> m_entities;
	std::vector<bool> m_options;
	std::vector<std::string> m_types;
	std::string m_expression;

	/**
	 * Agrega un conector a la coleccion de conectores
	 * @param xRel posicion en x del conector
	 * @param yRel posicion en y del conector
	 * @param isEntry
	 * @param exitNumber
	 */
	void addConnector(unsigned xRel, unsigned yRel, bool isEntry, unsigned exitNumber = 0);

	/**
	 * Inicializa los conectores
	 */
	virtual void initializeConnectors() = 0;

public:

	Component(const std::string & name = "", int type = 0);

	Component(const Component &);
	Component& operator=(const Component&);

	virtual ~Component();

	/**
	 * Persiste los datos del componente
	 * @param writer
	 */
	virtual void serialize(XmlWriter & writer_rep, XmlWriter & writer_comp);

	/**
	 * Levanta y deja en un estado consistente la instancia a partir
	 * del xml que contiene el reader
	 * @param reader
	 */
	virtual void deserialize(XmlReader & reader);

	/**
	 * Se agrega a si mismo a la coleccion que corresponda en el diagrama
	 * @param diagram
	 */
    virtual void addToDiagram(Diagram* diagram);

    /**
     * Se busca en la coleccion del diagram que le corresponda y se remueve
     * de la misma
     * @param diagram
     */
    virtual void removeFromDiagram(Diagram* diagram);

    virtual void update() {
    }

    /**
     * Valida cada componente con el diagrama
     * en el que se encuentra
     * @param diagram
     */
    virtual void validate(std::fstream & filestr,bool &valido);

	std::vector<Connector*>* getAttributeConnectors()
    {
        return &m_entryConnectors;
    }

	std::vector<Connector*>* getExitConnectors()
    {
        return &m_exitConnectors;
    }

	std::vector<bool>& getOptions()
    {
        return m_options;
    }

	std::vector<std::string>& getTypes()
    {
        return m_types;
    }

	std::string getName() const
    {
        return m_name;
    }

	void setName(const std::string & name)
    {
        m_name = name;
    }

    int getType() const
    {
        return m_type;
    }

    void setType(int type)
    {
        m_type = type;
    }

	std::string getExpression() const
    {
        return m_expression;
    }

	void setExpression(const std::string & exp)
    {
		m_expression = exp;
    }

    void setX(unsigned x);
    void setY(unsigned y);
    unsigned getX() const;
    unsigned getY() const;

    std::vector<Attribute*>* getAtrributes(){
		return &m_attributes;
    }

    bool isIqual(Component& other) {
    	std::cout<<"/other  " << other.m_name << "/"<< other.m_type << "/"<< other.m_posX << "/"<< other.m_posY << "/";
    	std::cout<<"/this  " << m_name << "/"<< m_type << "/"<< m_posX << "/"<< m_posY << "/";
    	return other.m_name == m_name && other.m_type == m_type &&
    			other.m_posX == m_posX && other.m_posY == m_posY;
    }
};

#endif /* COMPONENTE_H_ */
