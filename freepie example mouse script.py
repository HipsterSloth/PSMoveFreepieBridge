def update():
	#define globals
	global lastX
	global lastY
	global cursorScale
	
	#bind left mouse to trigger button
	#Right mouse to Move button
	#Middle mouse to Square
	mouse.leftButton = freePieIO[3].yaw == 1
	mouse.rightButton = int(freePieIO[3].x) & 0b00010000 > 0
	mouse.middleButton = int(freePieIO[3].x) & 0b00000001 > 0
	
	#Mouse movement using position data
	#mouse.deltaX = (freePieIO[0].x - lastX) * cursorScale
	#mouse.deltaY = -1 * (freePieIO[0].y - lastY) * cursorScale
	#lastX = freePieIO[0].x
	#lastY = freePieIO[0].y
	
	#Mouse movement using Gryoscope
	mouse.deltaX = -1 * freePieIO[1].yaw
	mouse.deltaY = -1 * freePieIO[1].pitch
	lastX = 0
	lastY = 0
	
if starting:
	lastX = freePieIO[0].x
	lastY = freePieIO[0].y
	cursorScale = 10
	freePieIO[0].update += update