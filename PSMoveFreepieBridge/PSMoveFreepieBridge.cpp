#include "stdafx.h"
#include "FreepieMoveClient.h"

void prompt_arguments(eDeviceType &deviceType, int32_t &deviceCount, int* deviceIDs, PSMTrackingColorType* bulbColors, int32_t &triggerAxis, std::string &hostAddress) {

	std::string psmServerAddress;
	std::cout << "Host Address (default=localhost): ";
	std::getline(std::cin, psmServerAddress);
	if (psmServerAddress.length() > 0)
	{
		hostAddress = psmServerAddress;
	}

	int rawDeviceType= 0;
	std::cout << "1) HMD " << std::endl;
	std::cout << "2) Controllers " << std::endl;
	std::cout << "Which device type do you want to track: ";
	std::cin >> rawDeviceType;

	if (rawDeviceType == (int)_deviceTypeHMD)
	{
		deviceType= _deviceTypeHMD;
		deviceCount= 1;
	}
	else
	{
		deviceType= _deviceTypeController;

		std::cout << "How many controllers do you want to track (1-4)? Note that more than 1 disables raw sensor data access and 4 disables button access: ";
		std::cin >> deviceCount;
	}

	for (int i = 0; i < deviceCount; i++)
	{
		int deviceID = 0;
		std::cout << "Enter the ID of the device you wish to use: ";
		std::cin >> deviceID;

		PSMTrackingColorType bulbColor = PSMTrackingColorType_MaxColorTypes;

		if (deviceType == _deviceTypeController)
		{
			char customColorChoice;
		    std::cout << "Do you want to use a custom bulb color for this controller (y/n)? ";
			std::cin >> customColorChoice;
			if (customColorChoice == 'Y' || customColorChoice == 'y') {
				std::cout << "Color Options:\n";
				std::cout << "  0 - Magenta\n";
				std::cout << "  1 - Cyan\n";
				std::cout << "  2 - Yellow\n";
				std::cout << "  3 - Red\n";
				std::cout << "  4 - Green\n";
				std::cout << "  5 - Blue\n";
				std::cout << "Enter the number of the desired color from the above list: ";

				int32_t intBulbColor;
				std::cin >> intBulbColor;
				if (intBulbColor >= 0 && intBulbColor < PSMTrackingColorType_MaxColorTypes)
				{
					bulbColor= static_cast<PSMTrackingColorType>(intBulbColor);
				}
			}
		}

		deviceIDs[i] = deviceID;
		bulbColors[i] = bulbColor;
	}

	if (deviceType == _deviceTypeController)
	{
        std::cout << "For virtual controllers, which axis corresponds to the trigger (-1 for default): ";
		std::cin >> triggerAxis;
    }
}

bool parse_arguments(
    int argc, 
    char** argv, 
    eDeviceType &deviceType, 
    int32_t &deviceCount, 
    PSMControllerID* deviceIDs, 
    PSMTrackingColorType* bulbColors,
    int32_t &triggerAxis,
	std::string &hostAddress,
    bool &bExitWithPSMoveService) 
{
	bool bSuccess = true;

	int index = 1;
	while (index < argc) {
		if ((strcmp(argv[index], "-controllers") == 0) && deviceCount < 1) {
			deviceType= _deviceTypeController;
		}
		else if ((strcmp(argv[index], "-hmd") == 0) && deviceCount < 1) {
			deviceType = _deviceTypeHMD;
			deviceCount = 1;

			// set the HMD id if specified
			index++;
			if ((index < argc) && isdigit(*argv[index]))
				deviceIDs[0] = atoi(argv[index]);

			index++;
		}
		else if ((strcmp(argv[index], "-t") == 0) && deviceCount < 1) {
			index++;

			//All numeric values after the -t flag are device IDs. Loop through and add them.
			while ((index < argc) && isdigit(*argv[index])) {
				//Only add up to four controllers
				if (deviceCount < 4) {
					deviceIDs[deviceCount] = static_cast<PSMControllerID>(atoi(argv[index]));
					deviceCount++;
				}
				else {
					std::cout << "More than four controllers have been specified on the command line!" << std::endl;
					bSuccess = false;
				}

				index++;
			}
		}
		else if (strcmp(argv[index], "-c") == 0) {
			index++;
			int32_t colorIndex = 0;
			//All numeric values after the -c flag are color indicies
			while ((index < argc) && (isdigit(*argv[index]) || (strcmp(argv[index], "-1") == 0))) {
				//Only add up to four controller indicies
				if (colorIndex < 4) {
					int32_t intBulbColor= atoi(argv[index]);
					if (intBulbColor >= 0 && intBulbColor < PSMTrackingColorType_MaxColorTypes)
					{
						bulbColors[colorIndex]= static_cast<PSMTrackingColorType>(intBulbColor);
					}
					else
					{
						bulbColors[colorIndex]= PSMTrackingColorType_MaxColorTypes;
					}
					colorIndex++;
				}
				else {
					std::cout << "More than four colors have been specified on the command line!" << std::endl;
					bSuccess = false;
				}

				index++;
			}
		}
		else if (strcmp(argv[index], "-triggerAxis") == 0) {
			index++;

			if ((index < argc) && isdigit(*argv[index])) {
				triggerAxis = atoi(argv[index]);
				index++;
			}
		}
		else if (strcmp(argv[index], "-x") == 0) {
			std::cout << "-x flag specified. Will not keep window open when finished" << std::endl;
			bExitWithPSMoveService = true;
			index++;
		}
		else if ((strcmp(argv[index], "-ip") == 0) && deviceCount < 1) {
			index++;

			if (index < argc) {
				hostAddress = argv[index];
				index++;
			}
		}
		else {
			std::cout << "Unrecognized command line argument " << argv[index] << std::endl;
			bSuccess = false;
			break;
		}
	}

    if (deviceType == _deviceTypeHMD)
    {
        if (deviceCount > 1)
        {
            std::cout << "Only one device supported when using HMD!" << std::endl;
            std::cout << "Setting device count to 1" << std::endl;
            deviceCount= 1;
        }

        if (bulbColors[0] != PSMTrackingColorType_MaxColorTypes)
        {
            std::cout << "Custom color not supported when using HMD!" << std::endl;
            std::cout << "Setting custom color to default." << std::endl;
            bulbColors[0]= PSMTrackingColorType_MaxColorTypes;
        }
    }

	return bSuccess;
}

int main(int argc, char** argv)
{
	eDeviceType deviceType= _deviceTypeController;
	int32_t deviceCount = 0;
	int deviceIDs[4];
	int32_t freepieIndicies[4] = { 0, 1, 2, 3 };
    int32_t triggerAxis= -1;
	std::string hostAddress= PSMOVESERVICE_DEFAULT_ADDRESS;
	PSMTrackingColorType bulbColors[4] = { PSMTrackingColorType_MaxColorTypes, PSMTrackingColorType_MaxColorTypes, PSMTrackingColorType_MaxColorTypes, PSMTrackingColorType_MaxColorTypes };
	bool bRun = true;
	bool bExitWithPSMoveService = false;

	if (argc == 1) {
		prompt_arguments(deviceType, deviceCount, deviceIDs, bulbColors, triggerAxis, hostAddress);
	}
	else {
		if (!parse_arguments(argc, argv, deviceType, deviceCount, deviceIDs, bulbColors, triggerAxis, hostAddress, bExitWithPSMoveService)) {
			std::cout << "Command line arguments are not valid." << std::endl;
			bRun = false;;
		}
	}

	if (bRun) {
		FreepieMoveClient* client = new FreepieMoveClient(hostAddress);
		client->run(deviceType, deviceCount, deviceIDs, bulbColors, freepieIndicies, deviceCount < 2, triggerAxis);
	}

	std::cout << "PSMoveFreepieBridge has ended" << std::endl;

	if (!bExitWithPSMoveService) {
		std::cin.ignore(INT_MAX);
	}

	return 0;
}