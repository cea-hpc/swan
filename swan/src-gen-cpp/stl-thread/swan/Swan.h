/* DO NOT EDIT THIS FILE - it is machine generated */

#ifndef __SWAN_H_
#define __SWAN_H_

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
#include "BathyLib.h"

using namespace nablalib::mesh;
using namespace nablalib::utils;
using namespace nablalib::types;
using namespace nablalib::utils::stl;

/******************** Free functions declarations ********************/

namespace swanfreefuncs
{
template<size_t x>
RealArray1D<x> sumR1(RealArray1D<x> a, RealArray1D<x> b);
}

/******************** Module declaration ********************/

class Swan
{
public:
	struct Options
	{
		std::string outputPath;
		int outputPeriod;
		double X_EDGE_LENGTH;
		double Y_EDGE_LENGTH;
		bool Dload;
		double Dini;
		double Dup;
		double deltat;
		int maxIter;
		double stopTime;
		bool Loadwave;
		int Wavemode;
		double LX;
		double X0;
		double Y0;
		double Amp;
		double Sigma;
		BathyLib bathyLib;

		void jsonInit(const char* jsonContent);
	};

	Swan(CartesianMesh2D* aMesh, Options& aOptions);
	~Swan();

	void simulate();
	void computeTn() noexcept;
	void iniCenter() noexcept;
	void initTime() noexcept;
	void initUini() noexcept;
	void updateDij() noexcept;
	void updateHcalc() noexcept;
	void initDijini() noexcept;
	void initHini() noexcept;
	void initU() noexcept;
	void updateDtot() noexcept;
	void updateHinner() noexcept;
	void updateHouter() noexcept;
	void initDij() noexcept;
	void initH() noexcept;
	void initUcalc() noexcept;
	void updateUcalc() noexcept;
	void iniDt() noexcept;
	void initHcalc() noexcept;
	void updateUinner() noexcept;
	void updateUouter() noexcept;
	void setUpTimeLoopN() noexcept;
	void executeTimeLoopN() noexcept;

private:
	void dumpVariables(int iteration, bool useTimer=true);

	// Mesh and mesh variables
	CartesianMesh2D* mesh;
	size_t nbNodes, nbNodesOfCell, nbFaces, nbInnerFaces, nbCells, nbInnerCells, nbTopCells, nbBottomCells, nbLeftCells, nbRightCells;

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
	const double deltax;
	const double deltay;
	static constexpr double g = -9.8;
	std::vector<RealArray1D<2>> center;
	double t_n;
	double t_nplus1;
	double t_n0;
	std::vector<RealArray1D<2>> X;
	std::vector<double> U_n;
	std::vector<double> U_nplus1;
	std::vector<double> U_n0;
	std::vector<double> Uini;
	std::vector<double> Ucalc_n;
	std::vector<double> Ucalc_nplus1;
	std::vector<double> Ucalc_n0;
	std::vector<double> H_n;
	std::vector<double> H_nplus1;
	std::vector<double> H_n0;
	std::vector<double> Hini;
	std::vector<double> Hcalc_n;
	std::vector<double> Hcalc_nplus1;
	std::vector<double> Hcalc_n0;
	std::vector<double> Dijini;
	std::vector<double> Dij_n;
	std::vector<double> Dij_nplus1;
	std::vector<double> Dij_n0;
	std::vector<double> Dt_n;
	std::vector<double> Dt_nplus1;
	std::vector<double> Dt_n0;
};

#endif
