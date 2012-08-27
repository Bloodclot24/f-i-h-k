#ifndef VISUALCOMPONENT_H_
#define VISUALCOMPONENT_H_

#include "gui/Dibujar/InfluenceArea.h"
#include <cairomm-1.0/cairomm/cairomm.h>
#include "gui/Dibujar/AuxiliarDibujar.h"

/**
 * @brief Representa un component visual.
 * Un visual component es un elemento visual, el cual puede ser creado, movido, copiado, rotado, seleccionado, etc.
 */
class VisualComponent {

protected:
	bool m_selected;

public:

	VisualComponent(){
		m_selected = false;
	}

	virtual ~VisualComponent() { }

	/**
	 * Obtiene el area de influencia de este visualComponent.
	 * @return
	 */
	virtual InfluenceArea getInfluenceArea() = 0;

	//Eventos visuales
	/**
	 * Evento que se dispara al pedir dibujar.
	 * @param ptrContext
	 */
	virtual void on_expose(Cairo::RefPtr<Cairo::Context> ptrContext) = 0;

	/**
	 * Evento que se dispara para pedir un movimiento.
	 *
	 * @param mouseX
	 * @param mouseY
	 */
	virtual void on_move(int mouseX, int mouseY) = 0;

	virtual int getX() const = 0;
	virtual void setX(int x) = 0 ;
	virtual int getY() const = 0 ;
	virtual void setY(int y) = 0;


	/**
	 * @return el ancho del component.
	 */
	int getSizeX() {
		return getInfluenceArea().m_area[0].xf - getInfluenceArea().m_area[0].x0;
	}

	/**
	 * @return el largo del component.
	 */
	int getSizeY() {
		return getInfluenceArea().m_area[0].yf - getInfluenceArea().m_area[0].y0;
	}

	/**
	 * @return devuelve la mitad del ancho del component.
	 */
	int getXCenter() {
		return getSizeX() / 2;
	}

	/**
	 * @return devuelve la mitad del largo del component.
	 */
	int getYCenter() {
		return getSizeY() / 2;
	}


	virtual void setSelected(bool sel){
		m_selected = sel;
	}

	bool isSelected(){
		return m_selected;
	}

	virtual void draw(Cairo::RefPtr<Cairo::Context> ptrContext) = 0;
};

#endif /* VISUALCOMPONENT_H_ */
