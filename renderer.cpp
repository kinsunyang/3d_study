#include "renderer.h"

Renderer::Renderer()
{
	m_cmdBuffer = new CommandBuffer();
}

Renderer::~Renderer()
{
	delete m_cmdBuffer;
}

void Renderer::clear(unsigned int flag, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float depth, unsigned int stencil)
{
	CommandClear *cmd = (CommandClear *)m_cmdBuffer->getCommand(COMMAND_CLEAR);
	cmd->setClearFlag(flag);
	cmd->setClearColor(Color4B(r,g,b,a));
	cmd->setDepth(depth);
	cmd->setStencil(stencil);
}

void Renderer::render()
{
	std::vector<CommandBase *>::const_iterator it = m_cmdBuffer->m_buffer.begin();
	while(it != m_cmdBuffer->m_buffer.end())
	{
		(*it)->execute(this);
		it++;
	}

	m_cmdBuffer->clear();
}