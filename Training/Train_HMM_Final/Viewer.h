/***************************************************************
*                                                              
*   Author:Steven Cooper                                       
*   Project:Computer Vision for Interactive Applications                       
*   Version: 1.0 Date: 03/11/2013 details: Creation of Viewer Class
*	Version: 1.1 Date: 17/12/2013 details: Added Display Mode to Viewer class with functions
*	Version: 1.2 Date: 19/01/2014 details: Added More Display Modes to Viewer class with functions
*                                                              
***************************************************************/

#ifndef _PATH_VIEWER_H_

#define _PATH_VIEWER_H_
#include <OpenNI.h>
#include <vector>

#define MAX_DEPTH 700

using namespace std;

enum DisplayMode
{
	HAND_DETECTION = 0,
	PATH = 1,
	RGB_HAND_DETECTION = 2,
	RGB_PATH = 3
};

class PathViewer
{
public:
	PathViewer(const char* strSampleName, openni::Device& device, openni::VideoStream& depth, openni::VideoStream& color);
	~PathViewer();

	virtual openni::Status init(int argc, char **argv);
	virtual openni::Status run();	//Does not return

protected:
	virtual void display();
	virtual void displayPostDraw(){};	// Overload to draw over the screen image
	virtual void displayHandDetection();
	virtual void displayPath();
	virtual void displayRGBHandDetection();
	virtual void displayRGBPath();

	virtual void onKey(unsigned char key, int x, int y);

	virtual openni::Status initOpenGL(int argc, char **argv);
	void initOpenGLHooks();

	openni::VideoFrameRef		m_depthFrame;
	openni::VideoFrameRef		m_colorFrame;

	openni::Device&			m_device;
	openni::VideoStream&			m_depthStream;
	openni::VideoStream&			m_colorStream;
	openni::VideoStream**		m_streams;
	DisplayMode viewerMode;

private:
	PathViewer(const PathViewer&);
	PathViewer& operator=(PathViewer&);

	static PathViewer* ms_self;
	static void glutIdle();
	static void glutDisplay();
	static void glutKeyboard(unsigned char key, int x, int y);

	float			m_pDepthHist[MAX_DEPTH];
	char			m_strSampleName[ONI_MAX_STR];
	unsigned int		m_nTexMapX;
	unsigned int		m_nTexMapY;
	openni::RGB888Pixel*	m_pTexMap;

	int			m_width;
	int			m_height;

};


#endif