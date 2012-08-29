#ifndef VISUALCOMPONENTCONECTOR_H_
#define VISUALCOMPONENTCONECTOR_H_

#include "gui/VisualComponents/VisualComponent.h"
#include "model/Diagram.h"
class VisualComponentVia;
class VisualCompositeComponent;

class VisualComponentConector: public VisualComponent {
private:
    bool m_isEntry;
	int m_number;
	Diagram* m_diagram;
	Connector* m_connector;
	VisualComponentVia* m_via;
	VisualCompositeComponent* m_parent;

public:
    VisualComponentConector(VisualCompositeComponent *parent, Connector *connector, int nro, bool esEntrada, Diagram* diagram);
    virtual ~VisualComponentConector();
    virtual InfluenceArea getInfluenceArea();
    virtual void on_expose(Cairo::RefPtr<Cairo::Context> ptrContext);
    virtual void on_move(int mouseX, int mouseY);
    VisualCompositeComponent *getParent();
    virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext);
    bool isEditable();
    virtual int getX() const;
    virtual void setX(int x);
    virtual int getY() const;
    virtual void setY(int y);
    VisualComponentVia *getVia() const;
    void setVia(VisualComponentVia *via);
    Connector *getConnector() const
    {
        return m_connector;
    }

    void setConnector(Connector *connector)
    {
        m_connector = connector;
    }

};

#endif /* VISUALCOMPONENTCONECTOR_H_ */
