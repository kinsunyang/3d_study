#ifndef _COMMAND_BUFFER_H_
#define _COMMAND_BUFFER_H_

#include "renderer.h"
#include "common/utils.h"
#include <vector>

enum COMMAND_TYPE {
	COMMAND_CLEAR = 1,
};
class Renderer;
class CommandBase
{
public:
	CommandBase(COMMAND_TYPE type) : m_type(type) {};
	~CommandBase() {}
	virtual void execute(Renderer *renderer) = 0;
	COMMAND_TYPE getType() { return m_type;}
private:
	COMMAND_TYPE m_type;
};

class CommandClear : public CommandBase
{
public:
	CommandClear(unsigned int flag, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float depth, unsigned int stencil) : 
		CommandBase(COMMAND_CLEAR),
		m_flag(flag),
		m_color(r, g, b, a),
		m_depth(depth),
		m_stencil(stencil)
	{}
	CommandClear() :
		CommandBase(COMMAND_CLEAR),
		m_flag(1),
		m_color(0,0,0,255),
		m_depth(0.0),
		m_stencil(0)
	{}

	void execute(Renderer * renderer);
	unsigned int getClearFlag() { return m_flag; }
	void setClearFlag(unsigned int flag) {m_flag = flag;}
	float getDepth() { return m_depth; }
	void setDepth(float depth) {m_depth = depth;}
	unsigned int getStencil() {return m_stencil;}
	void setStencil(unsigned int stencil) {m_stencil = stencil;}
	const Color4B & getClearColor() {return m_color;}
	void setClearColor(const Color4B & color) {m_color = color;}
private:
	unsigned int m_flag;
	Color4B m_color;
	float m_depth;
	unsigned int m_stencil;
};

class CommandBuffer
{
public:
	CommandBase * getCommand(COMMAND_TYPE type);
	friend class Renderer;
	void clear() {m_buffer.clear();}
private:
	std::vector<CommandBase *> m_buffer;
};
#endif
