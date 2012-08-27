#ifndef VISUALCOMPONENTSUBDIAGRAM_H_
#define VISUALCOMPONENTSUBDIAGRAM_H_

#include "model/Subdiagram.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
class Diagram;

class VisualComponentSubdiagram: public VisualCompositeComponent{
private:
	std::vector< VisualCompositeComponent* >* m_components;
	std::string m_xml;
	void crear();
public:

	VisualComponentSubdiagram( Diagram& diagram, const std::string & xml = "");

	VisualComponentSubdiagram( Diagram* diagram, Diagram* sourceDiagram, const std::string & name, std::vector< VisualCompositeComponent* >* components, bool source);

	VisualComponentSubdiagram(const VisualComponentSubdiagram& other);

	virtual ~VisualComponentSubdiagram() {
	}

	virtual VisualCompositeComponent* getCopy(Diagram & diagram);

	virtual InfluenceArea getInfluenceArea();

	virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext);

	virtual void load(XmlReader& reader, Diagram & diagram);

	Subdiagram* getSubdiagram(){
		return (Subdiagram *) m_component;
	}

	void setXml(const std::string &xml){
		m_xml = xml;
	}

	virtual void showProperties();
};

#endif /* VISUALCOMPONENTChip_H_ */
