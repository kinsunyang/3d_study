#ifndef _GL_DEVICE_CONTEXT_H_
#define _GL_DEVICE_CONTEXT_H_

namespace opengl {

class GLDeviceContext
{
 public:
	//GLDeviceContext();
	//~GLDeviceContext();
	virtual void swapBuffers() = 0;
};	

};

#endif
