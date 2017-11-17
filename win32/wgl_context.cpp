#include "wgl_context.h"
#include "platform.h"
#include "common/log.h"

extern PlatformData g_platData;
extern LogFile g_log;
namespace opengl {
WGLContext::WGLContext()
{
	HDC hdc = GetDC(g_platData.hWnd);
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd  
		1,                              // version number  
		PFD_DRAW_TO_WINDOW |            // support window  
		PFD_SUPPORT_OPENGL |            // support OpenGL  
		PFD_DOUBLEBUFFER,               // double buffered  
		PFD_TYPE_RGBA,                  // RGBA type  
		32,                             // 32-bit color depth  
		0, 0, 0, 0, 0, 0,               // color bits ignored  
		0,                              // no alpha buffer  
		0,                              // shift bit ignored  
		0,                              // no accumulation buffer  
		0, 0, 0, 0,                     // accum bits ignored  
		32,      // 32-bit z-buffer      
		8,       // 8-bit stencil buffer  
		0,                              // no auxiliary buffer  
		PFD_MAIN_PLANE,                 // main layer  
		0,                              // reserved  
		0, 0, 0                         // layer masks ignored  
	};
	int pfmt = ChoosePixelFormat(hdc, &pfd);
	if(!pfmt)
	{
		ReleaseDC(g_platData.hWnd, hdc);
		g_log.fatal("ChoosePixelFormat Error");
		return;
	}
	int ret = SetPixelFormat(hdc, pfmt, &pfd);
	if(!ret)
	{
		ReleaseDC(g_platData.hWnd, hdc);
		g_log.fatal("SetPixelFormat Error");
		return;
	}

	HGLRC hglrc = wglCreateContext(hdc);
	if(!hglrc)
	{
		ReleaseDC(g_platData.hWnd, hdc);
		g_log.fatal("wglCreateContext Error");
		return;
	}
	
	ret = wglMakeCurrent(hdc, hglrc);
	if(!ret)
	{
		wglDeleteContext(hglrc);
		ReleaseDC(g_platData.hWnd, hdc);
		g_log.fatal("wglMakeCurrent Error");
		return;
	}
	m_hdc = hdc;
	m_hglrc = hglrc;
}

WGLContext::~WGLContext()
{
	if(m_hglrc)
		wglDeleteContext(m_hglrc);
	if(m_hdc)
		ReleaseDC(g_platData.hWnd, m_hdc);

}

void WGLContext::swapBuffers()
{
	SwapBuffers(m_hdc);
}
};
