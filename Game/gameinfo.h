
#pragma once

#include <string>

class GameInfo
{

	public:

		int TeamSize;

		bool BlueA_Present;
		std::string BlueA_Name;
		bool BlueA_Local;
		bool BlueA_AI;

		bool BlueB_Present;
		std::string BlueB_Name;
		bool BlueB_Local;
		bool BlueB_AI;

		bool BlueC_Present;
		std::string BlueC_Name;
		bool BlueC_Local;
		bool BlueC_AI;

		bool RedA_Present;
		std::string RedA_Name;
		bool RedA_Local;
		bool RedA_AI;

		bool RedB_Present;
		std::string RedB_Name;
		bool RedB_Local;
		bool RedB_AI;

		bool RedC_Present;
		std::string RedC_Name;
		bool RedC_Local;
		bool RedC_AI;



		GameInfo()
		{
			TeamSize = 1;
			BlueA_Present = false;
			BlueB_Present = false;
			BlueC_Present = false;
			RedA_Present = false;
			RedB_Present = false;
			RedC_Present = false;

		};

};