#include "command_buffer.h"

void CommandClear::execute(Renderer * renderer)
{
	renderer->e_clear(this);
}
CommandBuffer::CommandBuffer() : m_size(4096), m_tail(0)
{
	m_buffer = new CommandBase * [m_size];
	memset(m_alloc, 0, sizeof(m_alloc));
}
CommandBuffer::~CommandBuffer()
{
	for(int i = 0; i < COMMAND_END; i ++)
	{
		CommandAllocatorBase * alloc = m_alloc[i];
		if(alloc)
		{
			delete alloc;
		}
	}
	delete [] m_buffer;
}
CommandBase * CommandBuffer::getCommand(COMMAND_TYPE type)
{
	CommandAllocatorBase * alloc = m_alloc[type];

#define GET_ONE_CMD(cls)	\
	{\
		CommandAllocator<cls> * real_alloc = 0;	\
		if(!alloc)	\
		{\
			real_alloc = new CommandAllocator<cls>();	\
			m_alloc[type] = real_alloc;	\
		}\
		else \
		{\
			real_alloc = (CommandAllocator<CommandClear> *)alloc;	\
		}\
		cmd = real_alloc->get();	\
	}


	CommandBase * cmd = 0;
	switch(type)
	{
	case COMMAND_TYPE::COMMAND_CLEAR :
		GET_ONE_CMD(CommandClear);
		break;
	default:
		break;
	}
#undef GET_ONE_CMD

	if(cmd)
	{
		m_buffer[m_tail] = cmd;
		m_tail++;
	}

	return cmd;
}

void CommandBuffer::clear()
{
	int i = COMMAND_BEGIN;
	while(i != COMMAND_END)
	{
		m_alloc[i]->clear();
		i++;
	}
	m_tail = 0;
}
