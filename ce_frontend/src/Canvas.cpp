//- Centhra Engine -
#include <CE/Base.h>
#include <CE/AppFrontend.h>
#include <CE/Canvas.h>

#ifdef _WIN32
	//- Windows -
	#include <windows.h>
#endif

//- Standard Library -
#include <string>

//- OpenGL -
#include <GL/gl.h>

#if CE_FRONTEND_USEXLIB
	//- Xlib -
	#include <X11/Xlib.h>
	#include <GL/glx.h>

	#if CE_FRONTEND_USEXCB
		//- XCB -
		#include <X11/Xlib-xcb.h>
		#include <xcb/xcb.h>
	#endif
#endif

using namespace std;

namespace ce
{
	int g_glxVersionMajor = 0, g_glxVersionMinor = 0;

	LRESULT CALLBACK WindowProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
	{
		Canvas *canvas = (Canvas *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if(canvas)
		{
			AppFrontend *app = canvas->getApp();

			Event event;
			event.base.canvas = canvas;

			switch(wMsg)
			{
				case WM_DESTROY:
					PostQuitMessage(0);
					return app->quit();
				case WM_KEYDOWN:
					event.type = KeyDown;
					event.key.keyCode = wParam;
					event.key.state = 1;
					app->onEvent(event);
					break;
				case WM_KEYUP:
					event.type = KeyUp;
					event.key.keyCode = wParam;
					event.key.state = 0;
					app->onEvent(event);
					break;
			}
		}

		return DefWindowProc(hWnd, wMsg, wParam, lParam);
	}

	Canvas *Canvas::create(int width, int height, const char *title)
	{
		AppFrontend *app = (AppFrontend *)App::getCurrent();

		if(!app)
		{
			error("[Error] Canvas::create - There are no Apps running.\n");
			return 0;
		}

		#if CE_FRONTEND_USEXLIB
			Display *xDisplay = (Display *)app->getXDisplay();
			int xDefaultScreen = app->getXDefaultScreen();
			GLXContext glxContext;
			GLXWindow glxWindow;

			//- TODO: Investigate why the Visual Info fails to be received when these int's aren't defined. -
			int glxVersionMajor = 0, glxVersionMinor = 0;
			if(!glXQueryVersion(xDisplay, &g_glxVersionMajor, &g_glxVersionMinor))
			{
				error("[Error] glxQueryVersion failed.\n");
				return 0;
			}

			#if CE_FRONTEND_USEXCB
				xcb_connection_t *xcbConnection = (xcb_connection_t *)app->getXCBConnection();
				xcb_screen_t *screen = 0;
				xcb_screen_iterator_t screen_iter = xcb_setup_roots_iterator(xcb_get_setup(xcbConnection));
				for(int screen_num = xDefaultScreen; screen_iter.rem && screen_num > 0; --screen_num, xcb_screen_next(&screen_iter));
				screen = screen_iter.data;

				xcb_window_t xcbWindow;
			#else
				Window xWindow;
			#endif

			if(g_glxVersionMajor >= 1 && g_glxVersionMinor >= 3 && 0)
			{
				int fbNumConfig;
				GLXFBConfig *fbConfig = glXChooseFBConfig(xDisplay, xDefaultScreen, 0, &fbNumConfig);

				if(!fbConfig || !fbNumConfig)
				{
					error("[Error] Canvas::create - glXChooseFBConfig failed.\n");
					return 0;
				}

				glxContext = glXCreateNewContext(xDisplay, fbConfig[0], GLX_RGBA_TYPE, 0, GL_TRUE);
				if(!glxContext)
				{
					error("[Error] Window::create - glXCreateNewContext failed.\n");
					return 0;
				}

				#if CE_FRONTEND_USEXCB
					int visualID = 0;
					glXGetFBConfigAttrib(xDisplay, fbConfig[0], GLX_VISUAL_ID , &visualID);

					xcb_colormap_t colormap = xcb_generate_id(xcbConnection);
					xcbWindow = xcb_generate_id(xcbConnection);

					xcb_create_colormap(xcbConnection, XCB_COLORMAP_ALLOC_NONE, colormap, screen->root, visualID);

					uint32_t eventmask = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE;
					uint32_t valuelist[] = { eventmask, colormap, 0 };
					uint32_t valuemask = XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;

					xcb_create_window(xcbConnection, XCB_COPY_FROM_PARENT, xcbWindow, screen->root, 0, 0, width, height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, visualID, valuemask, valuelist);

					if(!xcbWindow)
					{
						glXDestroyContext(xDisplay, glxContext);

						error("[Error] Window::create - xcb_create_window failed.\n");
						return 0;
					}

					xcb_map_window(xcbConnection, xcbWindow);
					glxWindow = glXCreateWindow(xDisplay, fbConfig[0], xcbWindow, 0);

					if(!glxWindow)
					{
						xcb_destroy_window(xcbConnection, xcbWindow);
						glXDestroyContext(xDisplay, glxContext);

						error("[Error] Window::create - glXCreateWindow failed.\n");
						return 0;
					}

					if(!glXMakeContextCurrent(xDisplay, glxWindow, glxWindow, glxContext))
					{
						xcb_destroy_window(xcbConnection, xcbWindow);
						glXDestroyContext(xDisplay, glxContext);

						error("[Error] Window::create - glXMakeContextCurrent failed.\n");
						return 0;
					}
				#else
					XVisualInfo *xVisualInfo = glXGetVisualFromFBConfig(xDisplay, fbConfig[0]);

					if(!xVisualInfo)
					{
						error("[Error] Window::create - glXChooseVisual failed.\n");
						return 0;
					}

					Colormap xColormap = XCreateColormap(xDisplay, RootWindow(xDisplay, xVisualInfo->screen), xVisualInfo->visual, AllocNone);

					XSetWindowAttributes swa;
					swa.colormap = xColormap;
					swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask; 
					xWindow = XCreateWindow(xDisplay, RootWindow(xDisplay, xVisualInfo->screen), 0, 0, width, height, 0, xVisualInfo->depth, InputOutput, xVisualInfo->visual, CWColormap | CWEventMask, &swa);
					
					if(!xWindow)
					{
						glXDestroyContext(xDisplay, glxContext);

						error("[Error] Window::create - XCreateWindow failed.\n");
						return 0;
					}

					XMapWindow(xDisplay, xWindow);
					glxWindow = glXCreateWindow(xDisplay, fbConfig[0], xWindow, 0);

					if(!glxWindow)
					{
						XDestroyWindow(xDisplay, xWindow);
						glXDestroyContext(xDisplay, glxContext);

						error("[Error] Window::create - glXCreateWindow failed.\n");
						return 0;
					}

					if(!glXMakeContextCurrent(xDisplay, glxWindow, glxWindow, glxContext))
					{
						XDestroyWindow(xDisplay, xWindow);
						glXDestroyContext(xDisplay, glxContext);

						error("[Error] Window::create - glXMakeContextCurrent failed.\n");
						return 0;
					}
				#endif
			}
			else
			{
				#if CE_FRONTEND_USEXCB
					xcb_visualtype_t *xcbVisualInfo = NULL;

					for(xcb_depth_iterator_t depth_iter = xcb_screen_allowed_depths_iterator(screen); depth_iter.rem; xcb_depth_next(&depth_iter))
						for(xcb_visualtype_iterator_t visual_iter = xcb_depth_visuals_iterator(depth_iter.data); visual_iter.rem; xcb_visualtype_next (&visual_iter))
							if(screen->root_visual == visual_iter.data->visual_id)
							{
								xcbVisualInfo = visual_iter.data;
								break;
							}

					if(!xcbVisualInfo)
					{
						//- TODO: Fix this error message. -
						error("[Error] Window::create - xcb find visual failed.\n");
						return 0;
					}

					//- TODO: Investigate if this is bad practice. -
					XVisualInfo xVisualInfo;
					xVisualInfo.bits_per_rgb = xcbVisualInfo->bits_per_rgb_value;
					xVisualInfo.blue_mask = xcbVisualInfo->blue_mask;
					xVisualInfo.c_class = xcbVisualInfo->_class;
					xVisualInfo.colormap_size = xcbVisualInfo->colormap_entries;
//					xVisualInfo.depth;
					xVisualInfo.green_mask = xcbVisualInfo->green_mask;
					xVisualInfo.red_mask = xcbVisualInfo->red_mask;
//					xVisualInfo.screen;
//					xVisualInfo.visual;
					xVisualInfo.visualid = xcbVisualInfo->visual_id;

					xcb_colormap_t colormap = xcb_generate_id(xcbConnection);
					xcbWindow = xcb_generate_id(xcbConnection);

					glxContext = glXCreateContext(xDisplay, &xVisualInfo, 0, GL_TRUE);
					if(!glxContext)
					{
						error("[Error] Window::create - glXCreateNewContext failed.\n");
						return 0;
					}

					xcb_create_colormap(xcbConnection, XCB_COLORMAP_ALLOC_NONE, colormap, screen->root, xcbVisualInfo->visual_id);

					uint32_t eventmask = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE;
					uint32_t valuelist[] = { eventmask, colormap, 0 };
					uint32_t valuemask = XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;

					xcb_create_window(xcbConnection, XCB_COPY_FROM_PARENT, xcbWindow, screen->root, 0, 0, width, height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, xcbVisualInfo->visual_id, valuemask, valuelist);

					if(!xcbWindow)
					{
						glXDestroyContext(xDisplay, glxContext);

						error("[Error] Window::create - xcb_create_window failed.\n");
						return 0;
					}

					xcb_map_window(xcbConnection, xcbWindow);

					if(!glXMakeCurrent(xDisplay, xcbWindow, glxContext))
					{
						xcb_destroy_window(xcbConnection, xcbWindow);
						glXDestroyContext(xDisplay, glxContext);

						error("[Error] Window::create - glXMakeCurrent failed.\n");
						return 0;
					}
				#else
					Window xRootWindow = DefaultRootWindow(xDisplay);

					GLint attributeList[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER };
					XVisualInfo *xVisualInfo = glXChooseVisual(xDisplay, 0, attributeList);

					if(!xVisualInfo)
					{
						error("[Error] Window::create - glXChooseVisual failed.\n");
						return 0;
					}

					glxContext = glXCreateContext(xDisplay, xVisualInfo, 0, GL_TRUE);
					if(!glxContext)
					{
						error("[Error] Window::create - glXCreateNewContext failed.\n");
						return 0;
					}

					Colormap xColormap = XCreateColormap(xDisplay, xRootWindow, xVisualInfo->visual, AllocNone);

					XSetWindowAttributes swa;
					swa.colormap = xColormap;
					swa.border_pixel = 0;
					swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;

					xWindow = XCreateWindow(xDisplay, xRootWindow, 0, 0, width, height, 0, xVisualInfo->depth, InputOutput, xVisualInfo->visual, CWColormap | CWEventMask, &swa);

					if(!xWindow)
					{
						glXDestroyContext(xDisplay, glxContext);

						error("[Error] Window::create - glXCreateWindow failed.\n");
						return 0;
					}

					XMapWindow(xDisplay, xWindow);

					if(!glXMakeCurrent(xDisplay, xWindow, glxContext))
					{
						XDestroyWindow(xDisplay, xWindow);
						glXDestroyContext(xDisplay, glxContext);

						error("[Error] Window::create - glXMakeCurrent failed.\n");
						return 0;
					}
				#endif
			}
		#endif

		Canvas *canvas = new Canvas();
		canvas->m_app = app;

		#if CE_FRONTEND_USEWIN
			HINSTANCE hInstance = (HINSTANCE)app->getHInstance();

			WNDCLASS windowClass;
			windowClass.style = CS_HREDRAW | CS_VREDRAW;
			windowClass.lpfnWndProc = WindowProc;
			windowClass.cbClsExtra = 0;
			windowClass.cbWndExtra = 0;
			windowClass.hInstance = hInstance;
			windowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
			windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			windowClass.lpszMenuName = "";
			windowClass.lpszClassName = "ceApp";

			if(!RegisterClass(&windowClass))
			{
				delete canvas;
				error("[Error] Window::create - RegisterClass failed\n");
				return 0;
			}

			HWND hWnd = CreateWindow("ceApp", title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);
			if(!hWnd)
			{
				delete canvas;
				error("[Error] Window::create - CreateWindow failed\n");
				return 0;
			}

			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)canvas);

			HDC hDC = GetDC(hWnd);

			PIXELFORMATDESCRIPTOR pfd;
			ZeroMemory(&pfd, sizeof(pfd));
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 16;
			pfd.iLayerType = PFD_MAIN_PLANE;
			int format = ChoosePixelFormat(hDC, &pfd);
			SetPixelFormat(hDC, format, &pfd);

			HGLRC hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);

			ShowWindow(hWnd, SW_SHOWNORMAL);
			UpdateWindow(hWnd);
		#endif

		#if CE_FRONTEND_USEXLIB
			canvas->m_glxContext = glxContext;
			canvas->m_glxWindow = glxWindow;
			#if CE_FRONTEND_USEXCB
				xcb_change_property(xcbConnection, XCB_PROP_MODE_REPLACE, xcbWindow, WM_NAME, STRING, 8, strlen(title), title);
				canvas->m_xcbWindow = xcbWindow;
				app->m_canvasMap[xcbWindow] = canvas;
			#else
				XStoreName(xDisplay, xWindow, title);
				canvas->m_xWindow = xWindow;
				app->m_canvasMap[xWindow] = canvas;
			#endif
		#endif

		#if CE_FRONTEND_USEWIN
			canvas->m_windowHandle = hWnd;
			canvas->m_deviceContextHandle = hDC;
			canvas->m_glRenderingContextHandle = hRC;
			app->m_canvasMap[hWnd] = canvas;
		#endif
		
		return canvas;
	}

	Canvas::Canvas()
	{
		m_app = 0;
		m_lastRenderTimeMS = 0;

		#if CE_FRONTEND_USEXLIB
			#if CE_FRONTEND_USEXCB
				m_xcbWindow = 0;
				m_glxContext = 0;
				m_glxWindow = 0;
			#else
				m_xWindow = 0;
			#endif
		#endif

		#if CE_FRONTEND_USEWIN
			m_windowClass = "";
			m_windowHandle = 0;
			m_deviceContextHandle = 0;
			m_glRenderingContextHandle = 0;
		#endif
	}
	Canvas::~Canvas()
	{
		#if CE_DISPLAY_USEXLIB
			Display *xDisplay = (Display *)m_app->getXDisplay();

			glXDestroyContext(xDisplay, (GLXContext *)m_glxContext);
			glXDestroyWindow(xDisplay, m_glxWindow);

			#if CE_DISPLAY_USEXCB
				app->m_canvasMap.erase(m_xcbWindow);
				xcb_connection_t *xcbConnection = (xcb_connection_t *)m_app->getXCBConnection();
				xcb_destroy_window(xcbConnection, m_xcbWindow);
			#else
				app->m_canvasMap.erase(m_xWindow);
				XDestroyWindow(xDisplay, m_xWindow);
			#endif
		#endif

		#if CE_FRONTEND_USEWIN
			m_app->m_canvasMap.erase(m_windowHandle);

			HINSTANCE hInstance = (HINSTANCE)m_app->getHInstance();

			wglMakeCurrent((HDC)m_deviceContextHandle, NULL);
			wglDeleteContext((HGLRC)m_glRenderingContextHandle);
            ReleaseDC((HWND)m_windowHandle, (HDC)m_deviceContextHandle);

			UnregisterClass(m_windowClass.c_str(), hInstance);

			CloseWindow((HWND)m_windowHandle);
			DestroyWindow((HWND)m_windowHandle);
		#endif
	}
	AppFrontend *Canvas::getApp() const
	{
		return m_app;
	}
	void Canvas::render()
	{
		unsigned long time = m_app->getRunTimeMS();
		if((time - m_lastRenderTimeMS) > 15)
		{
			m_lastRenderTimeMS = time;

			glClearColor(0.2f, 0.4f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			#if CE_FRONTEND_USEXLIB
				Display *xDisplay = (Display *)m_app->getXDisplay();

				#if CE_FRONTEND_USEXCB
					glXSwapBuffers(xDisplay, (g_glxVersionMajor >= 1 && g_glxVersionMinor >= 3 && 0) ? m_glxWindow : m_xcbWindow);
				#else
					glXSwapBuffers(xDisplay, (g_glxVersionMajor >= 1 && g_glxVersionMinor >= 3 && 0) ? m_glxWindow : m_xWindow);
				#endif
			#endif

			#if CE_FRONTEND_USEWIN
				SwapBuffers((HDC)m_deviceContextHandle);
			#endif
		}
	}
	bool Canvas::onEvent(Event &event)
	{
		print("%i %i\n", this, event.base.canvas);

		switch(event.type)
		{
			case KeyDown:
				print("Down: %i %i\n", event.key.keyCode, event.key.state);
				break;
			case KeyUp:
				print("Up: %i %i\n", event.key.keyCode, event.key.state);
				break;
		}

		return true;
	}
}
