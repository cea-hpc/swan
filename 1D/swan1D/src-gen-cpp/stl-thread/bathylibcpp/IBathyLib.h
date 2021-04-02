/*** GENERATED FILE - DO NOT OVERWRITE ***/

#ifndef __IBATHYLIB_H_
#define __IBATHYLIB_H_

#include <fstream>
#include <iomanip>
#include <type_traits>
#include <limits>
#include <utility>
#include <cmath>
#include "nablalib/mesh/CartesianMesh2DFactory.h"
#include "nablalib/mesh/CartesianMesh2D.h"
#include "nablalib/utils/Utils.h"
#include "nablalib/utils/Timer.h"
#include "nablalib/types/Types.h"

using namespace nablalib::mesh;
using namespace nablalib::utils;
using namespace nablalib::types;

class IBathyLib
{
public:
	virtual void jsonInit(const char* jsonContent) = 0;

	/* 
	 * Here are the other methods to implement in Sequential class.
	 * Some of them can be templates. Therefore they can not be virtual.
	 *

	double nextWaveHeight();

	double nextDepth();

	double nextLat();

	double nextLon();
	*/
};

#endif
