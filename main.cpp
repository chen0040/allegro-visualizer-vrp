#include "Application/Application.h"
#include "allegro_include/allegro.h"
#include "allegro_include/winalleg.h"

/// \file main.cpp
/// <summary>
/// contains the main() function which is the entry point of the application
/// </summary>

/*! \mainpage Visualizer of VRP
 *
 * \section intro_sec Introduction
 *
 * This documentation archive the source code comments and documentation of the visualizer of vehicle routing problem
 *
 * \section section1 Project Settings
 *
 *  The application is built using allegra library for the graphics rendering api
 *
 */


/// <summary>The main() function which is the entry point of the application</summary>
/// \param[in] argc the number of argument
/// \param[in] argv the argument array
int main(int argc, char* argv[])
{
	if(!SimulatorApp->Init(800, 600, true))
	{
		allegro_message("Failed to initialize");
		return 0;
	}

	SimulatorApp->Run();

	SimulatorApp->Cleanup();

	return 0;
}
END_OF_MAIN()