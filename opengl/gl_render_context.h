#ifndef _GL_RENDER_CONTEXT_H_
#define _GL_RENDER_CONTEXT_H_

#ifdef OS_WINDOWS
#include <windows.h>
#endif

#include "gl_device_context.h"
#include <gl/GL.h>

namespace opengl {

class GLRenderContext
{
public:
	GLRenderContext();
	~GLRenderContext();
	void commit();
private:
	GLDeviceContext * m_glDeviceContext;
};

};

#endif
