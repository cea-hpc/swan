/* DO NOT EDIT THIS FILE - it is machine generated */

#ifndef __BOUSSINESQ_H_
#define __BOUSSINESQ_H_

#include <fstream>
#include <iomanip>
#include <type_traits>
#include <limits>
#include <utility>
#include <cmath>
#include <rapidjson/document.h>
#include "nablalib/utils/Utils.h"
#include "nablalib/utils/Timer.h"
#include "nablalib/types/Types.h"
#include "nablalib/utils/stl/Parallel.h"
#include "CartesianMesh2D.h"
#include "PvdFileWriter2D.h"
#include "BathyLib.h"
#include "LinearAlgebra.h"

using namespace nablalib::utils;
using namespace nablalib::types;
using namespace nablalib::utils::stl;

/******************** Free functions declarations ********************/

namespace boussinesqfreefuncs
{
template<size_t x>
RealArray1D<x> sumR1(RealArray1D<x> a, RealArray1D<x> b);
double maxR0(double a, double b);
template<size_t x0>
RealArray1D<x0> operatorAdd(RealArray1D<x0> a, RealArray1D<x0> b);
template<size_t x0>
RealArray1D<x0> operatorMult(double a, RealArray1D<x0> b);
}

/******************** Module declaration ********************/

class Boussinesq
{
public:
	Boussinesq(CartesianMesh2D& aMesh);
	~Boussinesq();

	void jsonInit(const char* jsonContent);

	void simulate();
	void computeTn() noexcept;
	void iniB() noexcept;
	void iniCenter() noexcept;
	void iniMcurr() noexcept;
	void iniNcurr() noexcept;
	void initM() noexcept;
	void initMm() noexcept;
	void initN() noexcept;
	void initNm() noexcept;
	void initTime() noexcept;
	void setUpTimeLoopK() noexcept;
	void updateA() noexcept;
	void updateC() noexcept;
	void updateMm() noexcept;
	void updateMouter() noexcept;
	void updateNm() noexcept;
	void updateNouter() noexcept;
	void executeTimeLoopK() noexcept;
	void initDijini() noexcept;
	void initHini() noexcept;
	void updateB() noexcept;
	void initDij() noexcept;
	void initH() noexcept;
	void tearDownTimeLoopK() noexcept;
	void updateMcurr() noexcept;
	void initDt() noexcept;
	void updateD() noexcept;
	void updateM() noexcept;
	void updateN() noexcept;
	void iniD() noexcept;
	void updateMinner() noexcept;
	void updateNcurr() noexcept;
	void updateNinner() noexcept;
	void computeResidual() noexcept;
	void setUpTimeLoopN() noexcept;
	void updateH() noexcept;
	void executeTimeLoopN() noexcept;
	void updateHinner() noexcept;
	void updateHouter() noexcept;
	void updateDt() noexcept;

private:
	void dumpVariables(int iteration, bool useTimer=true);

	// Mesh and mesh variables
	CartesianMesh2D& mesh;
	size_t nbNodes;
	size_t nbCells;
	size_t nbInnerCells;
	size_t nbTopCells;
	size_t nbBottomCells;
	size_t nbLeftCells;
	size_t nbRightCells;

	// Options and global variables
	PvdFileWriter2D* writer;
	std::string outputPath;
	BathyLib bathyLib;
	LinearAlgebra linearAlgebra;
	int outputPeriod;
	int lastDump;
	int n;
	int k;
	double X_EDGE_LENGTH;
	double Y_EDGE_LENGTH;
	double deltat;
	int maxIter;
	int maxIterationsK;
	double stopTime;
	bool loadWave;
	int waveMode;
	double X0;
	double Y0;
	double Amp;
	double Sigma;
	bool loadBathy;
	double LX;
	double Dini;
	double Dup;
	double epsilon;
	double residual;
	double deltax;
	double deltay;
	static constexpr double g = -9.8;
	std::vector<RealArray1D<2>> X;
	std::vector<RealArray1D<2>> center;
	double t_n;
	double t_nplus1;
	double t_n0;
	std::vector<double> H_n;
	std::vector<double> H_nplus1;
	std::vector<double> H_n0;
	std::vector<double> Hcalc_n;
	std::vector<double> Hcalc_nplus1;
	std::vector<double> Hini;
	Matrix A;
	Vector B_n;
	Vector B_nplus1;
	Vector B_n0;
	Vector B_nplus1_k;
	Vector B_nplus1_kplus1;
	Matrix C;
	Vector D_n;
	Vector D_nplus1;
	Vector D_n0;
	Vector D_nplus1_k;
	Vector D_nplus1_kplus1;
	std::vector<double> Mcalc_n;
	std::vector<double> Mcalc_nplus1;
	std::vector<double> M_n;
	std::vector<double> M_nplus1;
	std::vector<double> M_n0;
	std::vector<double> Mm_n;
	std::vector<double> Mm_nplus1;
	std::vector<double> Mm_n0;
	Vector Mcurr_n;
	Vector Mcurr_nplus1;
	Vector Mcurr_nplus1_k;
	Vector Mcurr_nplus1_kplus1;
	std::vector<double> Ncalc_n;
	std::vector<double> Ncalc_nplus1;
	std::vector<double> N_n;
	std::vector<double> N_nplus1;
	std::vector<double> N_n0;
	std::vector<double> Nm_n;
	std::vector<double> Nm_nplus1;
	std::vector<double> Nm_n0;
	Vector Ncurr_n;
	Vector Ncurr_nplus1;
	Vector Ncurr_nplus1_k;
	Vector Ncurr_nplus1_kplus1;
	std::vector<double> Dijini;
	std::vector<double> Dij;
	std::vector<double> Dt_n;
	std::vector<double> Dt_nplus1;
	std::vector<double> Dt_n0;

	// Timers
	Timer globalTimer;
	Timer cpuTimer;
	Timer ioTimer;
};

#endif
