# README #

PSMoveFreepieBridge is a client for [PSMoveService](https://github.com/cboulay/PSMoveService) that takes the location and rotation data of a controller and passes it into [FreePIE](https://andersmalmgren.github.io/FreePIE/).

Releases can be found on the [Downloads](https://bitbucket.org/hawkinse/psmovefreepiebridge/downloads) page.

# Usage #
1. Start PSMoveService

2. Start PSMoveFreepieBridge.

3. Enter the number of controllers you wish to track and press enter.

4. For each controller, enter the controller ID you wish to track and press Enter. This can be found using PSMoveConfigTool.

5. Open FreePIE, File>Open the included freepie example script

6. Script>Run

# VRidge Users #
* If using with Riftcat VRidge for head tracking purposes, make sure to set Tracking source to either "Phone orientation and FreeTrack position" or "FreeTrack orientation and position" in the desktop app's settings. 
* If using with a Google Cardboard headset and you can't get rotation to work at all, it is likely because your headset contains a magnet based button. Either mount your PS Move controller on the side opposing the button, or remove the magnet.

# Freepie IO mapping #

freePieIO[0] = position and rotational data

If tracking single controller:

freePieIO[1].x/y/z = Accelerometer data

freePieIO[1].pitch/roll/yaw = Gyroscope data

freePieIO[2].x/y/z = Magnetometer data

If tracking multiple controllers, each index is for a different controller.

If tracking less than four controllers, button and trigger data can also be read from freePieIO[3]. Trigger data is stored in the orientation values (yaw/pitch/roll) while button presses are in the location values (x/y/z). Button data is stored as individual bits:

Bit 0 - Square

Bit 1 - Triangle

Bit 2 - Cross

Bit 3 - Circle

Bit 4 - Move

Bit 5 - PS

Bit 6 - Start

Bit 7 - Select

# Release Changelog #

### Release 15 ###
* Update PSMoveService to 0.9 alpha 8.7.1

### Release 14 ###
* Add support for PSMoveService Virtual Controllers.
* Example FreePIE script no longer attempts to adjust orientation for Riftcat VRidge. VRidge should now work properly with actual values.

### Release 13 ###
* Add support for PSMoveService Virtual HMDs.

### Release 12 ###
* Migrate to the new C API used by PSMoveService.

### Release 11 ###
* Add -x command line argument which stops PSMoveFreepieBridge from keeping the window open when finished.

### Release 10 ###
* Add command line argument support.
* Add example batch file demonstrating command line arguments to track the third controller with default bulb color.

### Alpha 9 ###
* Better handling for changes in available controllers. This includes no longer exiting when a controller is added or dropped by PSMoveService, and controllers used for tracking are handled properly when re-added.
* Console window no longer closes when disconnecting from client if not closed by the user. This will allow the output to be used in diagnosing potential issues.

### Alpha 8 ###
* Button support brought back, this time for up to three controllers
* Mouse example script updated to use new button support instead of FreePIE Joystick.
* Standard example script should now handle controller rotation better in Riftcat VRidge.

### Alpha 7 ###
* Added ability to set the bulb color of the tracked controllers

### Alpha 6 ###
* Fix compatibility with PSMoveService alpha 5

### Alpha 5 ###
* Add support for up to 4 controllers. Note that tracking more than one controller disables raw sensor data access.
* Compatible with PSMoveService alpha 4.2 through alpha 4.6.

### Alpha 4 ###
* Remove button support. FreePIE can already read PS Move button input using joystick[0].
* Add support for raw sensor data.
* Update example mouse control script to use joystick and gyroscope movement.
* Compatible with PSMoveService alpha 4.2 through alpha 4.6.

### Alpha 3 ###
* Add button support
* Add an example mouse control script
* Compatible with PSMoveService alpha 4.2 through alpha 4.6.

### Alpha 2 ###
* Fix 360 degree movement on yaw and pitch axis. However, only one axis can be used at a time without issues.
* Disable roll and pitch in example FreePIE script. If PSMoveFreepieBridge is being used for head tracking, yaw is the most important axis.
* Compatible with PSMoveService alpha 4.2 through alpha 4.6.

### Alpha 1 ###
* Initial Release
* Compatible with PSMoveService alpha 4.2 through alpha 4.6.