#ifndef _UTILS_H_
#define _UTILS_H_

class Color4B
{
public:
	Color4B(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : 
		r(r), g(g), b(b), a(a)
	{}
	Color4B() :
		r(0), g(0), b(0), a(255)
	{}
	Color4B & operator = (const Color4B &rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		a = rhs.a;

		return *this;
	}

public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

#endif
