#include "gl_renderer.h"
namespace opengl {

GLRenderer::GLRenderer()
{
	m_context = new GLRenderContext();
}

GLRenderer::~GLRenderer()
{
	delete m_context;
}

void GLRenderer::e_clear(CommandBase * cmd)
{
	CommandClear * _cmd = (CommandClear *)cmd;
	unsigned int flag = _cmd->getClearFlag();
	GLuint glflag = 0;
	if(flag & CLEAR_TYPE_COLOR)
	{
		const Color4B &color = _cmd->getClearColor();
		glClearColor((GLclampf)(color.r/255.0), (GLclampf)(color.g/255.0), (GLclampf)(color.b/255.0), (GLclampf)(color.a/255.0));
		glflag |= GL_COLOR_BUFFER_BIT;
	}
	if(flag & CLEAR_TYPE_DEPTH)
	{
		glClearDepth(_cmd->getDepth());
		glflag |= GL_DEPTH_BUFFER_BIT;
	}
	if(flag & CLEAR_TYPE_STENCIL)
	{
		glClearStencil(_cmd->getStencil());
		glflag |= GL_STENCIL_BUFFER_BIT;
	}
	glClear(glflag);
}
void GLRenderer::commit()
{
	m_context->commit();
}
};
