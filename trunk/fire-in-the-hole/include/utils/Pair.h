
#ifndef PAIR_H_
#define PAIR_H_

template< typename T1 , typename T2 >
class Pair {

public:

	Pair(){};
	Pair( T1 t1 , T2 t2 ){
		setT1(t1);
		setT2(t2);
	}
	virtual ~Pair(){};
	T1 getT1() const
    {
        return m_t1;
    }

    void setT1(T1 t1)
    {
        m_t1 = t1;
    }

    T2 getT2() const
    {
        return m_t2;
    }

    void setT2(T2 t2)
    {
        m_t2 = t2;
    }

    T1 m_t1;
	T2 m_t2;
};

#endif /* PAIR_H_ */
