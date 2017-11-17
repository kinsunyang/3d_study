#ifndef _WGL_CONTEXT_H_
#define _WGL_CONTEXT_H_

#include "opengl/gl_device_context.h"
#include <windows.h>

namespace opengl {

class WGLContext : public GLDeviceContext
{
public:
	WGLContext();
	~WGLContext();
	virtual void swapBuffers();
private:
	HDC m_hdc;
	HGLRC m_hglrc;
};

};
#endif
