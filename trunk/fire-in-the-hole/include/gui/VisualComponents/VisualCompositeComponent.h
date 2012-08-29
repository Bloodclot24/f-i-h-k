#ifndef VISUALCOMPOSITECOMPONENT_H_
#define VISUALCOMPOSITECOMPONENT_H_

#include "xml/XmlReader.h"
#include "xml/XmlWriter.h"
#include "model/Diagram.h"
#include "gui/VisualComponents/VisualComponent.h"
#include "model/Component.h"
#include "gui/VisualComponents/VisualComponent.h"
#include "gui/VisualComponents/VisualComponentConector.h"

/**
 * @brief Representa a un VisualComponent que esta compuesto por otros SubVisualComponent s.
 */
class VisualCompositeComponent : public VisualComponent{

public:

	VisualCompositeComponent(Diagram* diagram);

	VisualCompositeComponent(const VisualCompositeComponent &other);

	virtual ~VisualCompositeComponent();

	virtual void load(XmlReader& reader, Diagram* diagram);

	void store(XmlWriter& writer_rep, XmlWriter& writer_comp, Diagram* diagram);
    void on_expose(Cairo::RefPtr<Cairo::Context> ptrContext);
    void on_move(int mouseX, int mouseY);
    VisualComponent *getTouchedSubVisualComponent(int x, int y);
    virtual void showProperties();
    virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext);
    Component *getComponent()
    {
        return m_component;
    }

    virtual void setX(int x);
    virtual void setY(int y);
    virtual int getX() const;
    virtual int getY() const;
    Diagram* getDiagram();
    void addChild(VisualComponent *child);
    void addView(VisualCompositeComponent *view);

    std::vector<VisualComponent*>& getChildren()
    {
        return m_children;
    }

    std::vector<VisualCompositeComponent*>& getViews()
    {
        return m_views;
    }

    virtual VisualCompositeComponent *getCopy(Diagram* diagram)
    {
    	m_diagram = diagram;
        return NULL;
    }

protected:
    std::vector<VisualComponent*> m_children;
    std::vector< VisualCompositeComponent* > m_views;
    Component *m_component;
    Diagram* m_diagram;
    void initialize();
    void removeChild(VisualComponent *child);
    int getXRelativeToCenter(VisualComponent *subVisualComponentent)
    {
        return subVisualComponentent->getX() + subVisualComponentent->getXCenter() - getX() - getXCenter();
    }

    int getYRelativeToCenter(VisualComponent *subVisualComponentent)
    {
        return subVisualComponentent->getY() + subVisualComponentent->getYCenter() - getY() - getYCenter();
    }

    void setNewXRelativeToCenter(int xCenter, int xDelta, VisualComponent *subVisualComponentent)
    {
        subVisualComponentent->setX(xCenter + xDelta - subVisualComponentent->getXCenter());
    }

    void setNewYRelativeToCenter(int yCenter, int yDelta, VisualComponent* subVisualComponentent) {
		subVisualComponentent->setY(yCenter + yDelta - subVisualComponentent->getYCenter());
	}

//    void serializedAttributes(XmlWriter & xml, Diagram* diagram, Component* component);

    void update();

};

#endif /* VISUALCOMPOSITECOMPONENT_H_ */
