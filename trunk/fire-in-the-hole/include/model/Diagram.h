#ifndef DIAGRAM_H_
#define DIAGRAM_H_
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "model/Component.h"
#include "model/Entity.h"
#include "model/CompositeAttribute.h"
#include "model/Relation.h"
#include "model/Via.h"
#include "model/Attribute.h"
#include <fstream>

class Diagram {

private:
	std::vector<Component*> m_components;

	std::string m_name, m_path;
	unsigned m_sizeX;
	unsigned m_sizeY;
	unsigned m_lastAttributeId;

	void serializeConnectedComponents(std::vector<Connector*> connectors, XmlWriter & writer);

public:
	Diagram(const std::string & name = "unnamed");

	virtual ~Diagram();

	std::string getName() { return m_name; }
	std::string getPath() { return m_path; }

	void setPath(const std::string & path) {
		m_path = path;
    }

    void addComponent(Component *component);
    void removeComponent(Component*);

//    void deserialize(XmlReader & reader);
//    void deserialize(const std::string & str);

    void validateDiagram(std::fstream & filestr);

	void serializeConnectedComponents(Component* component, XmlWriter & writer);
	int getId(Component* component);

	std::vector<Component*>* getComponents()
    {
        return &m_components;
    }

    unsigned getSizeX() const
    {
        return m_sizeX;
    }

    unsigned getSizeY() const
    {
        return m_sizeY;
    }

    void setSize(unsigned sizeX, unsigned sizeY)
    {
        m_sizeX = sizeX;
        m_sizeY = sizeY;
    }

    void setName(const std::string & name)
    {
        m_name = name;
    }
};

#endif /* DIAGRAMO_H_ */
