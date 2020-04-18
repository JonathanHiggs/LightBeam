#pragma once

#include <chrono>
#include <iostream>


namespace LightBeam
{
	namespace Util
	{

		class Timer
		{
		private:
			std::ostream* os;
			std::string identifier;
			std::chrono::time_point<std::chrono::steady_clock> start; // , end;
			//std::chrono::duration<float> duration;

		public:
			Timer(std::ostream* os, const std::string & identifier)
				: os{ os }
				, identifier{ identifier }
				, start{ std::chrono::high_resolution_clock::now() }
			{ }

			~Timer()
			{
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = end - start;
				auto ms = duration.count() * 1e-6;

				(*os) << identifier << " took ";

				if (ms < 1100)
					(*os) << ms << " ms";
				else if (ms < 61000)
					(*os) << ms / 1000 << " s";
				else if (ms < 3660000)
					(*os) << ms / 60000 << " m";
				else
					(*os) << ms / 3600000 << " h";

				(*os) << std::endl;
			}
		};

	}
}
