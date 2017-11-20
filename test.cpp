#include "app.h"
#include "renderer.h"
#include "common/log.h"

extern LogFile g_log;

class TestApp : public BaseApp
{
public:
	TestApp(RENDERER_TYPE type) : BaseApp(type)
	{

	}

	void run()
	{
		g_log.debug("start app");
	}
	virtual void update()
	{
		m_renderer->clear(CLEAR_TYPE::CLEAR_TYPE_COLOR, 255, 0, 0, 255, 0, 0);
	}
private:

};

REGISTER_APP_ENTRY(TestApp, RENDERER_TYPE::RENDERER_TYPE_OPENGL)
