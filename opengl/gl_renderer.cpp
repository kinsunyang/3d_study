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

void GLRenderer::commit()
{
	m_context->commit();
}
};
