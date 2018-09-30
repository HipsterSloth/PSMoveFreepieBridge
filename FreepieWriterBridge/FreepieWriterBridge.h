#pragma once
#include "../thirdparty/headers/FreePIE/freepie_io.h"
using namespace System;

namespace FreepieWriterBridge {

	public ref class FreepieWriterBridge
	{
		public:static void WriteToFreepie(freepie_io_6dof_data data, int32_t freepieIndex)
		{
			//Can't send freepie_io_6dof_data directly, need to copy into CS compatible struct
			FreepieWriter::FreepieWriter::FreepieData csData;
			csData.x = data.x;
			csData.y = data.y;
			csData.z = data.z;
			csData.pitch = data.pitch;
			csData.yaw = data.yaw;
			csData.roll = data.roll;
			FreepieWriter::FreepieWriter::WriteData(csData, freepieIndex);
		}
	};
}

__declspec(dllexport) void WriteToFreepie(freepie_io_6dof_data data, int32_t freepieIndex = 0)
{
	FreepieWriterBridge::FreepieWriterBridge bridge;
	bridge.WriteToFreepie(data, freepieIndex);
}