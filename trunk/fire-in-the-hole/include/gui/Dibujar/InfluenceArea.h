#ifndef INFLUENCEAREA_H_
#define INFLUENCEAREA_H_

#include "InfluenceRectangle.h"
#include <vector>

/**
 * @brief Representa a un area de influencia.
 */
class InfluenceArea {
public:
	InfluenceArea(const InfluenceRectangle& influenceRectangle);
	InfluenceArea(const std::vector<InfluenceRectangle>& influenceRectangles);
	InfluenceArea(std::vector<InfluenceArea>& influenceArea);
	virtual ~InfluenceArea();

	/**
	 * Indica si el punto es afectado por esta area de influencia.
	 *
	 * @param x
	 * @param y
	 * @return
	 */
	bool touch(int x, int y);

	/**
	 * Indica si las areas de influencia tienen algun tipo de contacto.
	 *
	 * @param influenceArea
	 * @return
	 */
	bool touch(InfluenceArea& influenceArea);

	/**
	 * Anade el rectangulo al area de influencia.
	 *
	 * @param influenceRectangle
	 */
	void addRectangle(InfluenceRectangle& influenceRectangle);

	std::vector<InfluenceRectangle> m_area;
};

#endif /* INFLUENCEAREA_H_ */
