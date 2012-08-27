#ifndef CONECTOR_H_
#define CONECTOR_H_

class Component;
class Via;

/**
 * Clase que permite la conexion entre dos componentes
 */
class Connector {
private:
	Via* m_via;
	Component* m_father;
	bool m_isEntry;
	unsigned m_xRel;
	unsigned m_yRel;

public:
	Connector(Component* father, bool isEntrada, unsigned xRel,
			unsigned yRel, unsigned exitNumber = 0);
	virtual ~Connector();

	unsigned getXRel() const
    {
        return m_xRel;
    }

    unsigned getYRel() const
    {
        return m_yRel;
    }

	void setXRel( unsigned x)
    {
        m_xRel = x;
    }

    void setYRel(unsigned y)
    {
        m_yRel = y;
    }

    Via* getVia() const
    {
        return m_via;
    }

    void setVia(Via *via)
    {
        m_via = via;
    }

    Component *getFather() const
    {
        return m_father;
    }

    bool isEntry() const
    {
        return m_isEntry;
    }

};

#endif /* CONECTOR_H_ */
