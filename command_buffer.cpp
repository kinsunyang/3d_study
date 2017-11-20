#include "command_buffer.h"

void CommandClear::execute(Renderer * renderer)
{
	renderer->e_clear(this);
}

CommandBase * CommandBuffer::getCommand(COMMAND_TYPE type)
{
	CommandBase * cmd = 0;
	switch(type)
	{
	case COMMAND_TYPE::COMMAND_CLEAR :
		cmd = new CommandClear();
		break;
	}

	m_buffer.push_back(cmd);

	return cmd;
}
