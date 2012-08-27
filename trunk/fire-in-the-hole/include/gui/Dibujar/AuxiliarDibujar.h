#ifndef AUXILIARDIBUJAR_H_
#define AUXILIARDIBUJAR_H_

#include <iostream>
#include <valarray>
#include <cairomm/context.h>
#include <gtkmm/widget.h>
#include "Defines.h"
#include "InfluenceArea.h"

/**
 * Clase auxiliar que contiene funciones genericas para dibujar.
 */
class Draw {
public:

	Draw() { };
	~Draw() { };

	/**
	 * Dibuja un highlight generico, rectangular, con un margen determinado.
	 *
	 * @param ptrContext
	 * @param x
	 * @param y
	 * @param tamanoX
	 * @param tamanoY
	 */
	void drawGenericHighlight(Cairo::RefPtr<Cairo::Context> ptrContext, double x, double y, double tamanoX, double tamanoY) {
		ptrContext->save();
		ptrContext->set_source_rgb(COLOR_HIGHLIGHT);
		ptrContext->set_line_width(ANCHO_DE_LINEA);
		ptrContext->rectangle(x - HIGHLIGHT, y - HIGHLIGHT, tamanoX + 2 * HIGHLIGHT, tamanoY + 2 * HIGHLIGHT);
		ptrContext->stroke();
		ptrContext->restore();
	}

	/**
	 * Escribe el name en el contexto indicado, con offset x, y, adiccionalmente lo centra.
	 *
	 * @param ptrContext
	 * @param x
	 * @param y
	 * @param name
	 * @param r
	 * @param g
	 * @param b
	 */
	void writeTextInContext(Cairo::RefPtr<Cairo::Context> ptrContext, int x, int y, const std::string& name, int r, int g, int b) {
		ptrContext->set_source_rgb(r, g, b);
		ptrContext->set_line_width(SIZE_TEXT);
		Glib::RefPtr<Pango::Layout> pangoLayout = Pango::Layout::create (ptrContext);

		Pango::FontDescription font_desc(FONT_DESCRIPTION);
		pangoLayout->set_font_description(font_desc);

		pangoLayout->set_text(name);
		ptrContext->move_to(x - pangoLayout->get_pixel_ink_extents().get_width() / 2, y - DISTANCE_OF_TEXT_FROM_COMPONENT);
		pangoLayout->update_from_cairo_context(ptrContext);
		pangoLayout->add_to_cairo_context(ptrContext);
		ptrContext->fill();
	}

};

#endif /* AUXILIARDIBUJAR_H_ */
