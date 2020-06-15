#include "screen.h"
#include "os.h"

#if defined(IS_MACOSX)
	#include <ApplicationServices/ApplicationServices.h>
#elif defined(USE_X11)
	#include <X11/Xlib.h>
	#include "xdisplay.h"
#endif

MMSignedSize getMainDisplaySize(void)
{
#if defined(IS_MACOSX)
	CGDirectDisplayID displayID = CGMainDisplayID();
	return MMSignedSizeMake(CGDisplayPixelsWide(displayID),
	                  CGDisplayPixelsHigh(displayID));
#elif defined(USE_X11)
	Display *display = XGetMainDisplay();
	const int screen = DefaultScreen(display);

	return MMSignedSizeMake((int32_t)DisplayWidth(display, screen),
	                  (int32_t)DisplayHeight(display, screen));
#elif defined(IS_WINDOWS)
	return MMSignedSizeMake((int32_t)GetSystemMetrics(SM_CXSCREEN),
	                  (int32_t)GetSystemMetrics(SM_CYSCREEN));
#endif
}

bool pointVisibleOnMainDisplay(MMSignedPoint point)
{
	MMSignedSize displaySize = getMainDisplaySize();
	return point.x < displaySize.width && point.y < displaySize.height;
}
