#ifndef POINT_H_
#define POINT_H_

class Point {

public:

	Point(int x = 0, int y = 0, bool mobile = true){
		m_x = x;
		m_y = y;
		m_mobile = mobile;
	}

	virtual ~Point(){ }

	int getX() const
    {
        return m_x;
    }

    void setX(int x)
    {
        m_x = x;
    }

	int getY() const
    {
        return m_y;
    }

    void setY(int y)
    {
        m_y = y;
    }

    void setMobile(bool in){
    	m_mobile = in;
    }

    bool isMobile(){
    	return m_mobile;
    }

private:
	int m_x, m_y;
	bool m_mobile;
};

#endif /* POINT_H_ */
