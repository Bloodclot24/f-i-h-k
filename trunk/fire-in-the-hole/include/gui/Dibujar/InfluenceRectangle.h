#ifndef RECTANGULODEINFLUENCIA_H_
#define RECTANGULODEINFLUENCIA_H_

#include <iostream>

class InfluenceRectangle {
public:
	int x0, y0, xf, yf;
	InfluenceRectangle(int x0, int y0, int xf, int yf);
	virtual ~InfluenceRectangle() { }
	bool touch(int x, int y);

	bool touch(InfluenceRectangle& otroRectangulo);
};

#endif /* RECTANGULODEINFLUENCIA_H_ */
