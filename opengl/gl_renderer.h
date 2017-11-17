#ifndef _GL_RENDERER_H_
#define _GL_RENDERER_H_

#include "renderer.h"
#include "gl_render_context.h"

namespace opengl {

class GLRenderer : public Renderer
{
public:
	GLRenderer();
	~GLRenderer();
	virtual void commit();
private:
	GLRenderContext * m_context;
};

};

#endif
