#include "gui/Dibujar/InfluenceRectangle.h"
InfluenceRectangle::InfluenceRectangle(int x0, int y0, int xf, int yf) {
	if (x0 > xf) { //Entonces el rectangulo es inverso en X
		this->x0 = xf;
		this->xf = x0;
	} else {
		this->x0 = x0;
		this->xf = xf;
	}
	if (y0 > yf) {//Entonces el rectangulo es inverso en Y
		this->y0 = yf;
		this->yf = y0;
	} else {
		this->y0 = y0;
		this->yf = yf;
	}
}

bool InfluenceRectangle::touch(int x, int y) {
	if ((x0 <= x) && (xf >= x) && (y0 <= y) && (yf >= y))
		return true;
	return false;
}

bool InfluenceRectangle::touch(InfluenceRectangle& otroRectangulo) {
	if (xf < otroRectangulo.x0) //Entonces este rectangulo esta a la izquierda del otro.
		return false;
	else if (x0 > otroRectangulo.xf) //Entonces este rectangulo esta a la derecha del otro.
		return false; //Si no llega hasta aca, entonces se tocan en algun punto de las Xs.
	else if (yf < otroRectangulo.y0) //Entonces este rectangulo esta arriba del otro.
		return false;
	else if (y0 > otroRectangulo.yf) //Entonces este rectangulo esta abajo del otro.
		return false;
	return true;
}
