#ifndef _RENDERER_H_
#define _RENDERER_H_

enum RENDERER_TYPE {
	RENDERER_TYPE_NONE = 0,
	RENDERER_TYPE_OPENGL = 1,
	RENDERER_TYPE_METAL = 2,
	RENDERER_TYPE_VULKAN = 3,
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	virtual void commit() = 0;
private:
};

#endif
