/*** GENERATED FILE - DO NOT OVERWRITE ***/

#ifndef SWANGEO_H_
#define SWANGEO_H_

#include <fstream>
#include <iomanip>
#include <type_traits>
#include <limits>
#include <utility>
#include <cmath>
#include "nablalib/mesh/CartesianMesh2DFactory.h"
#include "nablalib/mesh/CartesianMesh2D.h"
#include "nablalib/mesh/PvdFileWriter2D.h"
#include "nablalib/utils/Utils.h"
#include "nablalib/utils/Timer.h"
#include "nablalib/types/Types.h"
#include "nablalib/utils/stl/Parallel.h"
#include "bathylib/BathyLib.h"

using namespace nablalib::mesh;
using namespace nablalib::utils;
using namespace nablalib::types;
using namespace nablalib::utils::stl;

/******************** Module declaration ********************/

class Swangeo
{
public:
	struct Options
	{
		std::string outputPath;
		int outputPeriod;
		bool DConst;
		double Dini;
		double deltat;
		int maxIter;
		double stopTime;
		bathylib::BathyLib bathyLib;

		void jsonInit(const char* jsonContent);
	};

	Swangeo(CartesianMesh2D* aMesh, Options& aOptions);
	~Swangeo();

	void simulate();
	void computeTn() noexcept;
	void initDijini() noexcept;
	void initFxy() noexcept;
	void initHini() noexcept;
	void initRijini() noexcept;
	void initTime() noexcept;
	void initUini() noexcept;
	void initVini() noexcept;
	void initXc() noexcept;
	void updateHinner() noexcept;
	void updateHouter() noexcept;
	void updateRij() noexcept;
	void updateUinner() noexcept;
	void updateUouter() noexcept;
	void updateVinner() noexcept;
	void updateVouter() noexcept;
	void initDij() noexcept;
	void initH() noexcept;
	void initRij() noexcept;
	void initU() noexcept;
	void initV() noexcept;
	void initXcAndYc() noexcept;
	void initBool() noexcept;
	void initdeltaxdeltay() noexcept;
	void setUpTimeLoopN() noexcept;
	void executeTimeLoopN() noexcept;

private:
	void dumpVariables(int iteration, bool useTimer=true);

	// Mesh and mesh variables
	CartesianMesh2D* mesh;
	size_t nbNodes, nbFaces, nbInnerFaces, nbInnerVerticalFaces, nbInnerHorizontalFaces, nbCells, nbInnerCells, nbOuterCells, nbTopCells, nbBottomCells, nbLeftCells, nbRightCells;

	// User options
	Options& options;
	PvdFileWriter2D writer;

	// Timers
	Timer globalTimer;
	Timer cpuTimer;
	Timer ioTimer;

public:
	// Global variables
	int lastDump;
	int n;
	static constexpr double deltax_lon = 0.033;
	static constexpr double deltay_lat = 0.033;
	static constexpr double g = -9.8;
	static constexpr double C = 40.0;
	static constexpr double F = 0.0;
	static constexpr double DEG2RAD_DP = 0.01745;
	static constexpr double DEG2RAD = DEG2RAD_DP;
	static constexpr double DEG2M_DP = 111194.9266;
	static constexpr double DEG2M = DEG2M_DP;
	double t_n;
	double t_nplus1;
	double t_n0;
	std::vector<RealArray1D<2>> X;
	std::vector<RealArray1D<2>> Xc;
	std::vector<double> xc;
	std::vector<double> yc;
	std::vector<double> deltax;
	std::vector<double> deltay;
	std::vector<double> U_n;
	std::vector<double> U_nplus1;
	std::vector<double> U_n0;
	std::vector<double> Uini;
	std::vector<double> V_n;
	std::vector<double> V_nplus1;
	std::vector<double> V_n0;
	std::vector<double> Vini;
	std::vector<double> H_n;
	std::vector<double> H_nplus1;
	std::vector<double> H_n0;
	std::vector<double> Hini;
	std::vector<double> Rijini;
	std::vector<double> Rij_n;
	std::vector<double> Rij_nplus1;
	std::vector<double> Rij_n0;
	std::vector<double> Fx;
	std::vector<double> Fy;
	std::vector<double> Dijini;
	std::vector<double> Dij;
	std::vector<double> Bool;
};

#endif