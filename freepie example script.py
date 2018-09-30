def update():
	freeTrack.pitch = -freePieIO[0].pitch
	freeTrack.roll =  freePieIO[0].roll
	freeTrack.yaw = freePieIO[0].yaw
	
	#Multiply by 10 for SteamVR use
	freeTrack.x = (freePieIO[0].x * 10)
	freeTrack.y = (freePieIO[0].y * 10)
	freeTrack.z = (freePieIO[0].z * 10)

	
if starting:
	freePieIO[0].update += update