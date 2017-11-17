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
private:

};

REGISTER_APP_ENTRY(TestApp, RENDERER_TYPE::RENDERER_TYPE_OPENGL)
