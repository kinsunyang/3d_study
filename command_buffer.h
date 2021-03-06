#ifndef _COMMAND_BUFFER_H_
#define _COMMAND_BUFFER_H_

#include "renderer.h"
#include "common/utils.h"
#include <map>

enum COMMAND_TYPE {
	COMMAND_BEGIN = 1,
	COMMAND_CLEAR = 1,
	COMMAND_END,
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

class CommandAllocatorBase
{
public :
	CommandAllocatorBase() : m_tail(0)
	{
	}
	void clear()
	{
		m_tail = 0;
	}
protected:
	int m_tail;
};
template<class T>
class CommandAllocator : public CommandAllocatorBase
{
public:
	CommandAllocator()
	{
		m_buffer = new T * [8];
		m_capacity = 8;
		memset(m_buffer, 0, sizeof(m_buffer));
		m_size = 0;
	}
	~CommandAllocator()
	{
		int index = 0;
		while(index != m_size)
		{
			delete m_buffer[index];
			index++;
		}

		delete [] m_buffer;
	}

	T * get()
	{
		T * cmd = m_buffer[m_tail];
		if(!cmd)
		{
			if(m_size == m_capacity)
			{
				int old_capacity = m_capacity;
				m_capacity *= 2;
				T ** tmp = new T * [m_capacity];
				memcpy(tmp, m_buffer, old_capacity);
				delete[] m_buffer;
				m_buffer = tmp;
			}
			cmd = new T();
			m_buffer[m_tail] = cmd;
			m_tail++;
			m_size++;
		}
		return cmd;
	}
private :
	T ** m_buffer;
	int m_size;
	int m_capacity;
};
class CommandBuffer
{
public:
	CommandBuffer();
	~CommandBuffer();
	CommandBase * getCommand(COMMAND_TYPE type);
	friend class Renderer;
	void clear() ;
private:
	CommandBase ** m_buffer;
	CommandAllocatorBase * m_alloc[COMMAND_END];
	const int m_size;
	int m_tail;
};
#endif
