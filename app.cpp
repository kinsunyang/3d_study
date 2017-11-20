#include "app.h"
#include "opengl/gl_renderer.h"

BaseApp::BaseApp(RENDERER_TYPE type)
{
	switch (type)
	{
	case RENDERER_TYPE::RENDERER_TYPE_OPENGL :
		m_renderer = new opengl::GLRenderer();
		break;
	default:
		break;
	}
}

BaseApp::~BaseApp()
{
	delete m_renderer;
}

void BaseApp::render()
{
	m_renderer->render();
	commit();
}
void BaseApp::commit()
{
	m_renderer->commit();
}