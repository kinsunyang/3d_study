#include "gl_render_context.h"

#ifdef OS_WINDOWS
#include "win32/wgl_context.h"
#endif

namespace opengl {

GLRenderContext::GLRenderContext()
{
#ifdef OS_WINDOWS
	m_glDeviceContext = new WGLContext();
	
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
