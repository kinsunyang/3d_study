#ifndef _BASE_APP_H_
#define _BASE_APP_H_

#include "renderer.h"

class BaseApp
{
public:
	BaseApp(RENDERER_TYPE type);
	// init
	virtual void run() = 0;
	// logic frame
	virtual void update() = 0;
	// render frame
	virtual void render();
	~BaseApp();
private:
	void commit();
protected:
	Renderer * m_renderer;	
};

#define REGISTER_APP_ENTRY(CLS_APP, RENDER_TYPE)	\
	CLS_APP * app = NULL;	\
	void _main_()					\
	{						\
		app = new CLS_APP(RENDER_TYPE);	\
		app->run();				\
	}	\
	void _update_()	\
	{\
		app->update();	\
	}	\
	void _render_()	\
	{\
		app->render();	\
	}
	
#endif
