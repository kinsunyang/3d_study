#include "gl_render_context.h"

#ifdef OS_WINDOWS
#include "win32/wgl_context.h"
#endif

namespace opengl {

GLRenderContext::GLRenderContext()
{
#ifdef OS_WINDOWS
	m_glDeviceContext = new WGLContext();
	GLuint flag = GL_COLOR_BUFFER_BIT;
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(flag);
#endif

}

GLRenderContext::~GLRenderContext()
{
	delete m_glDeviceContext;
}

void GLRenderContext::commit()
{
	m_glDeviceContext->swapBuffers();
}
};
