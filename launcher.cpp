/***********************************************************************
CONFIGURATIONS

Every new project needs to be configured, goto:
Project Properties (alt + F7) -> Configuration Properties -> General
Now select appropriate platform and select Configuration: All Configurations

Edit Output Directory field accordingly to the project:

For 32 bit builds
$(SolutionDir)..\..\Bin\Windows\32Bit\$(Configuration)\

For 64 bit builds
$(SolutionDir)..\..\Bin\Windows\64Bit\$(Configuration)\

Build order and to set what project depends on which project.
Select Solution right click on:
Project Build Order ... for setting project build order
Project Dependencies ... for setting project dependencies
***********************************************************************/

#include "Source/Core/Core.hpp"
#include "Source/Core/Math/Math.hpp"
#include "Source/Core/Math/GlobalPosition.hpp"

#include <iostream>

// CFlightController
// 1. Read sensor inputs/measurements (CIOController)
// 2. Process commands from radio receiver (CRadioComms) or from flight route (CFlightRoute)
// 3. Execute flight control law algorithms (CFlightLaws)
// 4. Apply new control inputs (CIOController)

using namespace atl;

int main()
{
    std::cout << "Welcome!\n";

	GlobalPosition lPeterborough(52.573921, -0.250830);
	GlobalPosition lNottingham(52.950001, -1.150000);

	printf("dist: %lfkm\n", CMath::calcDistHarversineM(52.573921, -0.250830, 52.95, -1.15) / 1000.0);
	printf("dist: %lfkm\n", CMath::calcDistHarversineM(lPeterborough, lNottingham) / 1000.0);

	printf("initial bearing: %.2lf deg\n", CMath::calcInitialBearingDeg(lPeterborough, lNottingham));

	std::cin.get();
}
