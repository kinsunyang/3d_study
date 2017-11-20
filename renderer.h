#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "command_buffer.h"

enum RENDERER_TYPE {
	RENDERER_TYPE_NONE = 0,
	RENDERER_TYPE_OPENGL = 1,
	RENDERER_TYPE_METAL = 2,
	RENDERER_TYPE_VULKAN = 3,
};

enum CLEAR_TYPE {
	CLEAR_TYPE_COLOR = 1,
	CLEAR_TYPE_DEPTH = 2,
	CLEAR_TYPE_STENCIL = 4,
};

class CommandBase;
class CommandBuffer;
class Renderer
{
public:
	Renderer();
	~Renderer();
	virtual void commit() = 0;
	void render();
	// clear
	void clear(unsigned int flag, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float depth, unsigned int stencil);
	virtual void e_clear(CommandBase * cmd) = 0;
private:
	CommandBuffer *m_cmdBuffer;
};

#endif
