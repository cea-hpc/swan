/* DO NOT EDIT THIS FILE - it is machine generated */

#include "SwanModule.h"
#include <arcane/Concurrency.h>
#include <arcane/ITimeLoopMng.h>

using namespace Arcane;

/*** Free functions **********************************************************/

namespace swanfreefuncs
{
	RealArrayVariant sumR1(RealArrayVariant a, RealArrayVariant b)
	{
		return swanfreefuncs::operatorAdd(a, b);
	}
	
	RealArrayVariant operatorAdd(RealArrayVariant a, RealArrayVariant b)
	{
		UniqueArray<Real> result(a.size());
		for (Int32 ix0=0; ix0<a.size(); ix0++)
		{
			result[ix0] = a[ix0] + b[ix0];
		}
		return result;
	}
	
	RealArrayVariant operatorMult(const Real a, RealArrayVariant b)
	{
		UniqueArray<Real> result(b.size());
		for (Int32 ix0=0; ix0<b.size(); ix0++)
		{
			result[ix0] = a * b[ix0];
		}
		return result;
	}
}

/*** Module/Service **********************************************************/

SwanModule::SwanModule(const ModuleBuildInfo& bi)
: ArcaneSwanObject(bi)
{}

void SwanModule::init()
{
	// initialization of mesh attributes
	m_mesh = CartesianMesh2D::createInstance(mesh());

	// initialization of other attributes
	m_lastDump = numeric_limits<int>::min();
	m_n = 0;
	m_deltax = options()->xEdgeLength();
	m_deltay = options()->yEdgeLength();

	// constant time step
	m_global_deltat = options()->deltat();
	if (options()->bathyLib.isPresent())
		m_bathy_lib.jsonInit(options()->bathyLib.value().localstr());

	// calling jobs
	iniCenter(); // @1.0
	initTime(); // @1.0
	initUini(); // @1.0
	initDijini(); // @2.0
	initHini(); // @2.0
	initU(); // @2.0
	initDij(); // @3.0
	initH(); // @3.0
	initUcalc(); // @3.0
	initHcalc(); // @4.0
	iniDt(); // @5.0
	iniHru(); // @5.0
	setUpTimeLoopN(); // @6.0
}

/**
 * Job computeTn called @1.0 in executeTimeLoopN method.
 * In variables: deltat, t_n
 * Out variables: t_nplus1
 */
void SwanModule::computeTn()
{
	m_t_nplus1 = m_t_n + options()->deltat();
}

/**
 * Job iniCenter called @1.0 in simulate method.
 * In variables: X
 * Out variables: center
 */
void SwanModule::iniCenter()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			const auto jId(jCells.asItemLocalId());
			Real2 reduction0{0.0, 0.0};
			{
				const auto nodesOfCellJ(m_mesh->getNodesOfCell(jId));
				const Int32 nbNodesOfCellJ(nodesOfCellJ.size());
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					const auto rId(nodesOfCellJ[rNodesOfCellJ]);
					const auto rNodes(rId);
					reduction0 = Real2(swanfreefuncs::sumR1(reduction0, m_X[rNodes]));
				}
			}
			m_center[jCells] = (Real2(swanfreefuncs::operatorMult(0.25, reduction0)));
		}
	});
}

/**
 * Job initTime called @1.0 in simulate method.
 * In variables: 
 * Out variables: t_n0
 */
void SwanModule::initTime()
{
	m_t_n0 = 0.0;
}

/**
 * Job initUini called @1.0 in simulate method.
 * In variables: 
 * Out variables: Uini
 */
void SwanModule::initUini()
{
	arcaneParallelForeach(m_mesh->getGroup("InnerFaces"), [&](FaceVectorView view)
	{
		ENUMERATE_FACE(fInnerFaces, view)
		{
			const auto fId(fInnerFaces.asItemLocalId());
			const auto fFaces(fId);
			m_Uini[fFaces] = 0.0;
		}
	});
}

/**
 * Job updateDij called @1.0 in executeTimeLoopN method.
 * In variables: Dij_n
 * Out variables: Dij_nplus1
 */
void SwanModule::updateDij()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			m_Dij_nplus1[jCells] = m_Dij_n[jCells];
		}
	});
}

/**
 * Job updateHcalc called @1.0 in executeTimeLoopN method.
 * In variables: Dt_n, H_n, U_n, deltat, deltax, deltay
 * Out variables: Hcalc_nplus1
 */
void SwanModule::updateHcalc()
{
	const Real tmp_deltat(options()->deltat());
	arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(icInnerCells, view)
		{
			const auto icId(icInnerCells.asItemLocalId());
			const auto icCells(icId);
			Real TD1(0.0);
			Real TD2(0.0);
			{
				const auto rfId(m_mesh->getRightFaceOfCell(icId));
				const auto rfFaces(rfId);
				const auto rcId(m_mesh->getRightCell(icId));
				const auto rcCells(rcId);
				if (m_U_n[rfFaces] <= 0) 
					TD1 = m_Dt_n[rcCells];
				else
					TD1 = m_Dt_n[icCells];
			}
			{
				const auto lfId(m_mesh->getLeftFaceOfCell(icId));
				const auto lfFaces(lfId);
				const auto lcId(m_mesh->getLeftCell(icId));
				const auto lcCells(lcId);
				if (m_U_n[lfFaces] <= 0) 
					TD2 = m_Dt_n[icCells];
				else
					TD2 = m_Dt_n[lcCells];
			}
			Real TV1(0.0);
			Real TV2(0.0);
			{
				const auto tfId(m_mesh->getTopFaceOfCell(icId));
				const auto tfFaces(tfId);
				const auto tcId(m_mesh->getTopCell(icId));
				const auto tcCells(tcId);
				if (m_U_n[tfFaces] <= 0) 
					TV1 = m_Dt_n[tcCells];
				else
					TV1 = m_Dt_n[icCells];
			}
			{
				const auto bfId(m_mesh->getBottomFaceOfCell(icId));
				const auto bfFaces(bfId);
				const auto bcId(m_mesh->getBottomCell(icId));
				const auto bcCells(bcId);
				if (m_U_n[bfFaces] <= 0) 
					TV2 = m_Dt_n[icCells];
				else
					TV2 = m_Dt_n[bcCells];
			}
			{
				const auto rfId(m_mesh->getRightFaceOfCell(icId));
				const auto rfFaces(rfId);
				const auto lfId(m_mesh->getLeftFaceOfCell(icId));
				const auto lfFaces(lfId);
				const auto tfId(m_mesh->getTopFaceOfCell(icId));
				const auto tfFaces(tfId);
				const auto bfId(m_mesh->getBottomFaceOfCell(icId));
				const auto bfFaces(bfId);
				m_Hcalc_nplus1[icCells] = m_H_n[icCells] - tmp_deltat / (m_deltax) * (m_U_n[rfFaces] * TD1 - m_U_n[lfFaces] * TD2) - tmp_deltat / m_deltay * (m_U_n[tfFaces] * TV1 - m_U_n[bfFaces] * TV2);
			}
		}
	});
}

/**
 * Job initDijini called @2.0 in simulate method.
 * In variables: Dini, Dup, LX, center, loadBathy
 * Out variables: Dijini
 */
void SwanModule::initDijini()
{
	const bool tmp_loadBathy(options()->loadBathy());
	const Real tmp_Dini(options()->dini());
	const Real tmp_Dup(options()->dup());
	const Real tmp_LX(options()->lX());
	ENUMERATE_CELL(icInnerCells, m_mesh->getGroup("InnerCells"))
	{
		const auto icId(icInnerCells.asItemLocalId());
		const auto icCells(icId);
		if (tmp_loadBathy) 
			m_Dijini[icCells] = m_bathy_lib.nextDepth();
		else
			m_Dijini[icCells] = tmp_Dini + m_center[icCells][0] * (tmp_Dup - tmp_Dini) / (tmp_LX);
	}
}

/**
 * Job initHini called @2.0 in simulate method.
 * In variables: Amp, Sigma, X0, Y0, center, loadWave, waveMode
 * Out variables: Hini
 */
void SwanModule::initHini()
{
	const bool tmp_loadWave(options()->loadWave());
	const Int32 tmp_waveMode(options()->waveMode());
	const Real tmp_X0(options()->x0());
	const Real tmp_Amp(options()->amp());
	const Real tmp_Sigma(options()->sigma());
	const Real tmp_Y0(options()->y0());
	ENUMERATE_CELL(icInnerCells, m_mesh->getGroup("InnerCells"))
	{
		const auto icId(icInnerCells.asItemLocalId());
		const auto icCells(icId);
		if (tmp_loadWave) 
			m_Hini[icCells] = m_bathy_lib.nextWaveHeight();
		else
			if (tmp_waveMode == 1) 
		{
			if (m_center[icCells][0] < tmp_X0) 
				m_Hini[icCells] = tmp_Amp;
			else
				m_Hini[icCells] = 2.0;
		}
		else
			if (tmp_waveMode == 2) 
			m_Hini[icCells] = tmp_Amp * std::exp(-0.5 * (m_center[icCells][0] - tmp_X0) * (m_center[icCells][0] - tmp_X0) / (tmp_Sigma * tmp_Sigma)) * std::exp(-0.5 * (m_center[icCells][1] - tmp_Y0) * (m_center[icCells][1] - tmp_Y0) / (tmp_Sigma * tmp_Sigma));
		else
			if (tmp_waveMode == 3) 
			m_Hini[icCells] = tmp_Amp * std::exp(-0.5 * (m_center[icCells][0] - tmp_X0) * (m_center[icCells][0] - tmp_X0) / (tmp_Sigma * tmp_Sigma));
		else
			if (tmp_waveMode == 4) 
		{
			if (m_center[icCells][0] < (tmp_X0 / 2.0)) 
				m_Hini[icCells] = tmp_Amp * std::sin(m_center[icCells][0] * (2 * 3.1415 / tmp_X0));
			else
				m_Hini[icCells] = 0.0;
		}
	}
}

/**
 * Job initU called @2.0 in simulate method.
 * In variables: Uini
 * Out variables: U_n0
 */
void SwanModule::initU()
{
	arcaneParallelForeach(m_mesh->getGroup("TopCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(tcTopCells, view)
		{
			const auto tcId(tcTopCells.asItemLocalId());
			const auto rfId(m_mesh->getRightFaceOfCell(tcId));
			const auto rfFaces(rfId);
			const auto bcId(m_mesh->getBottomCell(tcId));
			const auto brfId(m_mesh->getRightFaceOfCell(bcId));
			const auto brfFaces(brfId);
			m_U_n0[rfFaces] = m_Uini[brfFaces];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("BottomCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(bcBottomCells, view)
		{
			const auto bcId(bcBottomCells.asItemLocalId());
			const auto rfId(m_mesh->getRightFaceOfCell(bcId));
			const auto rfFaces(rfId);
			const auto tcId(m_mesh->getTopCell(bcId));
			const auto trfId(m_mesh->getRightFaceOfCell(tcId));
			const auto trfFaces(trfId);
			m_U_n0[rfFaces] = m_Uini[trfFaces];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("LeftCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(lcLeftCells, view)
		{
			const auto lcId(lcLeftCells.asItemLocalId());
			const auto lfId(m_mesh->getLeftFaceOfCell(lcId));
			const auto lfFaces(lfId);
			const auto rfId(m_mesh->getRightFaceOfCell(lcId));
			const auto rfFaces(rfId);
			m_U_n0[lfFaces] = m_Uini[rfFaces];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("RightCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(rcRightCells, view)
		{
			const auto rcId(rcRightCells.asItemLocalId());
			const auto rfId(m_mesh->getRightFaceOfCell(rcId));
			const auto rfFaces(rfId);
			const auto lfId(m_mesh->getLeftFaceOfCell(rcId));
			const auto lfFaces(lfId);
			m_U_n0[rfFaces] = m_Uini[lfFaces];
		}
	});
}

/**
 * Job updateHru called @2.0 in executeTimeLoopN method.
 * In variables: Dij_nplus1, Hcalc_nplus1
 * Out variables: Hru_nplus1
 */
void SwanModule::updateHru()
{
	arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(icInnerCells, view)
		{
			const auto icId(icInnerCells.asItemLocalId());
			const auto icCells(icId);
			m_Hru_nplus1[icCells] = std::max(m_Hcalc_nplus1[icCells], m_Dij_nplus1[icCells]);
		}
	});
}

/**
 * Job initDij called @3.0 in simulate method.
 * In variables: Dijini
 * Out variables: Dij_n0
 */
void SwanModule::initDij()
{
	arcaneParallelForeach(m_mesh->getGroup("TopCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(tcTopCells, view)
		{
			const auto tcId(tcTopCells.asItemLocalId());
			const auto tcCells(tcId);
			const auto bcId(m_mesh->getBottomCell(tcId));
			const auto bcCells(bcId);
			m_Dij_n0[tcCells] = m_Dijini[bcCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("BottomCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(bcBottomCells, view)
		{
			const auto bcId(bcBottomCells.asItemLocalId());
			const auto bcCells(bcId);
			const auto tcId(m_mesh->getTopCell(bcId));
			const auto tcCells(tcId);
			m_Dij_n0[bcCells] = m_Dijini[tcCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("LeftCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(lcLeftCells, view)
		{
			const auto lcId(lcLeftCells.asItemLocalId());
			const auto lcCells(lcId);
			const auto rcId(m_mesh->getRightCell(lcId));
			const auto rcCells(rcId);
			m_Dij_n0[lcCells] = m_Dijini[rcCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("RightCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(rcRightCells, view)
		{
			const auto rcId(rcRightCells.asItemLocalId());
			const auto rcCells(rcId);
			const auto lcId(m_mesh->getLeftCell(rcId));
			const auto lcCells(lcId);
			m_Dij_n0[rcCells] = m_Dijini[lcCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(icInnerCells, view)
		{
			const auto icId(icInnerCells.asItemLocalId());
			const auto icCells(icId);
			m_Dij_n0[icCells] = m_Dijini[icCells];
		}
	});
}

/**
 * Job initH called @3.0 in simulate method.
 * In variables: Hini
 * Out variables: H_n0
 */
void SwanModule::initH()
{
	arcaneParallelForeach(m_mesh->getGroup("TopCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(tTopCells, view)
		{
			const auto tId(tTopCells.asItemLocalId());
			const auto tCells(tId);
			const auto btId(m_mesh->getBottomCell(tId));
			const auto btCells(btId);
			m_H_n0[tCells] = m_Hini[btCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("BottomCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(bBottomCells, view)
		{
			const auto bId(bBottomCells.asItemLocalId());
			const auto bCells(bId);
			const auto tbId(m_mesh->getTopCell(bId));
			const auto tbCells(tbId);
			m_H_n0[bCells] = m_Hini[tbCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("LeftCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(lLeftCells, view)
		{
			const auto lId(lLeftCells.asItemLocalId());
			const auto lCells(lId);
			const auto rlId(m_mesh->getRightCell(lId));
			const auto rlCells(rlId);
			m_H_n0[lCells] = m_Hini[rlCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("RightCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(rRightCells, view)
		{
			const auto rId(rRightCells.asItemLocalId());
			const auto rCells(rId);
			const auto lrId(m_mesh->getLeftCell(rId));
			const auto lrCells(lrId);
			m_H_n0[rCells] = m_Hini[lrCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(icInnerCells, view)
		{
			const auto icId(icInnerCells.asItemLocalId());
			const auto icCells(icId);
			m_H_n0[icCells] = m_Hini[icCells];
		}
	});
}

/**
 * Job initUcalc called @3.0 in simulate method.
 * In variables: U_n0
 * Out variables: Ucalc_n0
 */
void SwanModule::initUcalc()
{
	arcaneParallelForeach(allFaces(), [&](FaceVectorView view)
	{
		ENUMERATE_FACE(jFaces, view)
		{
			m_Ucalc_n0[jFaces] = m_U_n0[jFaces];
		}
	});
}

/**
 * Job updateDtot called @3.0 in executeTimeLoopN method.
 * In variables: Dij_nplus1, Hru_nplus1
 * Out variables: Dt_nplus1
 */
void SwanModule::updateDtot()
{
	arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jInnerCells, view)
		{
			const auto jId(jInnerCells.asItemLocalId());
			const auto jCells(jId);
			m_Dt_nplus1[jCells] = std::max(-m_Dij_nplus1[jCells] + m_Hru_nplus1[jCells], 0.0);
		}
	});
}

/**
 * Job updateHinner called @3.0 in executeTimeLoopN method.
 * In variables: Hru_nplus1
 * Out variables: H_nplus1
 */
void SwanModule::updateHinner()
{
	arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(icInnerCells, view)
		{
			const auto icId(icInnerCells.asItemLocalId());
			const auto icCells(icId);
			m_H_nplus1[icCells] = m_Hru_nplus1[icCells];
		}
	});
}

/**
 * Job updateHouter called @3.0 in executeTimeLoopN method.
 * In variables: Hru_nplus1
 * Out variables: H_nplus1
 */
void SwanModule::updateHouter()
{
	arcaneParallelForeach(m_mesh->getGroup("TopCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(tcTopCells, view)
		{
			const auto tcId(tcTopCells.asItemLocalId());
			const auto tcCells(tcId);
			const auto bcId(m_mesh->getBottomCell(tcId));
			const auto bcCells(bcId);
			m_H_nplus1[tcCells] = m_Hru_nplus1[bcCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("BottomCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(bcBottomCells, view)
		{
			const auto bcId(bcBottomCells.asItemLocalId());
			const auto bcCells(bcId);
			const auto tcId(m_mesh->getTopCell(bcId));
			const auto tcCells(tcId);
			m_H_nplus1[bcCells] = m_Hru_nplus1[tcCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("LeftCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(lcLeftCells, view)
		{
			const auto lcId(lcLeftCells.asItemLocalId());
			const auto lcCells(lcId);
			const auto rcId(m_mesh->getRightCell(lcId));
			const auto rcCells(rcId);
			m_H_nplus1[lcCells] = m_Hru_nplus1[rcCells];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("RightCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(rcRightCells, view)
		{
			const auto rcId(rcRightCells.asItemLocalId());
			const auto rcCells(rcId);
			const auto lcId(m_mesh->getLeftCell(rcId));
			const auto lcCells(lcId);
			m_H_nplus1[rcCells] = m_Hru_nplus1[lcCells];
		}
	});
}

/**
 * Job initHcalc called @4.0 in simulate method.
 * In variables: H_n0
 * Out variables: Hcalc_n0
 */
void SwanModule::initHcalc()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			m_Hcalc_n0[jCells] = m_H_n0[jCells];
		}
	});
}

/**
 * Job updateUcalc called @4.0 in executeTimeLoopN method.
 * In variables: H_nplus1, U_n, deltat, deltax, deltay, g
 * Out variables: Ucalc_nplus1
 */
void SwanModule::updateUcalc()
{
	const Real tmp_deltat(options()->deltat());
	arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(icInnerCells, view)
		{
			const auto icId(icInnerCells.asItemLocalId());
			const auto icCells(icId);
			const auto rfcId(m_mesh->getRightFaceOfCell(icId));
			const auto rfcFaces(rfcId);
			const auto tfcId(m_mesh->getTopFaceOfCell(icId));
			const auto tfcFaces(tfcId);
			Real TU1(0.0);
			Real TV1(0.0);
			Real V1(0.0);
			{
				const auto bfcId(m_mesh->getBottomFaceOfCell(icId));
				const auto bfcFaces(bfcId);
				const auto icpId(m_mesh->getRightCell(icId));
				const auto tfcpId(m_mesh->getTopFaceOfCell(icpId));
				const auto tfcpFaces(tfcpId);
				const auto bfcpId(m_mesh->getBottomFaceOfCell(icpId));
				const auto bfcpFaces(bfcpId);
				V1 = (m_U_n[tfcFaces] + m_U_n[bfcFaces] + m_U_n[tfcpFaces] + m_U_n[bfcpFaces]) / 4;
			}
			if (V1 <= 0) 
			{
				const auto ictId(m_mesh->getTopCell(icId));
				const auto rfctId(m_mesh->getRightFaceOfCell(ictId));
				const auto rfctFaces(rfctId);
				TV1 = m_U_n[rfctFaces] - m_U_n[rfcFaces];
			}
			else
			{
				const auto icbId(m_mesh->getBottomCell(icId));
				const auto rfcbId(m_mesh->getRightFaceOfCell(icbId));
				const auto rfcbFaces(rfcbId);
				TV1 = m_U_n[rfcFaces] - m_U_n[rfcbFaces];
			}
			if (m_U_n[rfcFaces] <= 0) 
			{
				const auto icpId(m_mesh->getRightCell(icId));
				const auto rfcpId(m_mesh->getRightFaceOfCell(icpId));
				const auto rfcpFaces(rfcpId);
				const auto lfcpId(m_mesh->getLeftFaceOfCell(icpId));
				const auto lfcpFaces(lfcpId);
				TU1 = m_U_n[rfcpFaces] - m_U_n[lfcpFaces];
			}
			else
			{
				const auto lfcId(m_mesh->getLeftFaceOfCell(icId));
				const auto lfcFaces(lfcId);
				TU1 = m_U_n[rfcFaces] - m_U_n[lfcFaces];
			}
			{
				const auto icpId(m_mesh->getRightCell(icId));
				const auto icpCells(icpId);
				m_Ucalc_nplus1[rfcFaces] = m_U_n[rfcFaces] - (tmp_deltat / m_deltax) * (m_U_n[rfcFaces] * TU1 - m_g * (m_H_nplus1[icpCells] - m_H_nplus1[icCells])) - (tmp_deltat / m_deltay) * (V1 * TV1);
			}
			Real TV2(0.0);
			Real TU2(0.0);
			Real U1(0.0);
			{
				const auto lfcId(m_mesh->getLeftFaceOfCell(icId));
				const auto lfcFaces(lfcId);
				const auto ictId(m_mesh->getTopCell(icId));
				const auto rfctId(m_mesh->getRightFaceOfCell(ictId));
				const auto rfctFaces(rfctId);
				const auto lfctId(m_mesh->getLeftFaceOfCell(ictId));
				const auto lfctFaces(lfctId);
				U1 = (m_U_n[rfcFaces] + m_U_n[lfcFaces] + m_U_n[rfctFaces] + m_U_n[lfctFaces]) / 4;
			}
			if (U1 <= 0) 
			{
				const auto icpId(m_mesh->getRightCell(icId));
				const auto tfcpId(m_mesh->getTopFaceOfCell(icpId));
				const auto tfcpFaces(tfcpId);
				TU2 = m_U_n[tfcpFaces] - m_U_n[tfcFaces];
			}
			else
			{
				const auto icmId(m_mesh->getLeftCell(icId));
				const auto tfcmId(m_mesh->getTopFaceOfCell(icmId));
				const auto tfcmFaces(tfcmId);
				TU2 = m_U_n[tfcFaces] - m_U_n[tfcmFaces];
			}
			if (m_U_n[tfcFaces] <= 0) 
			{
				const auto icpId(m_mesh->getTopCell(icId));
				const auto tfcpId(m_mesh->getTopFaceOfCell(icpId));
				const auto tfcpFaces(tfcpId);
				const auto bfcpId(m_mesh->getBottomFaceOfCell(icpId));
				const auto bfcpFaces(bfcpId);
				TV2 = m_U_n[tfcpFaces] - m_U_n[bfcpFaces];
			}
			else
			{
				const auto bfcId(m_mesh->getBottomFaceOfCell(icId));
				const auto bfcFaces(bfcId);
				TV2 = m_U_n[tfcFaces] - m_U_n[bfcFaces];
			}
			{
				const auto icpId(m_mesh->getTopCell(icId));
				const auto icpCells(icpId);
				m_Ucalc_nplus1[tfcFaces] = m_U_n[tfcFaces] - (tmp_deltat / m_deltay) * (m_U_n[tfcFaces] * TV2 - m_g * (m_H_nplus1[icpCells] - m_H_nplus1[icCells])) - (tmp_deltat / m_deltax) * (U1 * TU2);
			}
		}
	});
}

/**
 * Job iniDt called @5.0 in simulate method.
 * In variables: Dij_n0, Hcalc_n0
 * Out variables: Dt_n0
 */
void SwanModule::iniDt()
{
	arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jInnerCells, view)
		{
			const auto jId(jInnerCells.asItemLocalId());
			const auto jCells(jId);
			m_Dt_n0[jCells] = std::max(-m_Dij_n0[jCells] + m_Hcalc_n0[jCells], 0.0);
		}
	});
}

/**
 * Job iniHru called @5.0 in simulate method.
 * In variables: Dij_n0, Hcalc_n0
 * Out variables: Hru_n0
 */
void SwanModule::iniHru()
{
	arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(icInnerCells, view)
		{
			const auto icId(icInnerCells.asItemLocalId());
			const auto icCells(icId);
			m_Hru_n0[icCells] = std::max(m_Hcalc_n0[icCells], m_Dij_n0[icCells]);
		}
	});
}

/**
 * Job updateUrunup called @5.0 in executeTimeLoopN method.
 * In variables: Dt_nplus1, H_n, H_nplus1, Ucalc_nplus1, epsh, epsu
 * Out variables: Urn_nplus1
 */
void SwanModule::updateUrunup()
{
	const Real tmp_epsh(options()->epsh());
	const Real tmp_epsu(options()->epsu());
	{
		arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
		{
			ENUMERATE_CELL(icInnerCells, view)
			{
				const auto icId(icInnerCells.asItemLocalId());
				const auto icCells(icId);
				const auto rfcId(m_mesh->getRightFaceOfCell(icId));
				const auto rfcFaces(rfcId);
				if ((m_Dt_nplus1[icCells] < tmp_epsh)) 
					m_Urn_nplus1[rfcFaces] = 0.0;
				else
					m_Urn_nplus1[rfcFaces] = m_Ucalc_nplus1[rfcFaces];
			}
		});
		arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
		{
			ENUMERATE_CELL(icInnerCells, view)
			{
				const auto icId(icInnerCells.asItemLocalId());
				const auto icCells(icId);
				const auto lfcId(m_mesh->getRightFaceOfCell(icId));
				const auto lfcFaces(lfcId);
				if ((m_Dt_nplus1[icCells] < tmp_epsh)) 
					m_Urn_nplus1[lfcFaces] = 0.0;
				else
					m_Urn_nplus1[lfcFaces] = m_Ucalc_nplus1[lfcFaces];
			}
		});
		arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
		{
			ENUMERATE_CELL(icInnerCells, view)
			{
				const auto icId(icInnerCells.asItemLocalId());
				const auto icCells(icId);
				const auto tfcId(m_mesh->getTopFaceOfCell(icId));
				const auto tfcFaces(tfcId);
				if ((m_Dt_nplus1[icCells] < tmp_epsh)) 
					m_Urn_nplus1[tfcFaces] = 0.0;
				else
					m_Urn_nplus1[tfcFaces] = m_Ucalc_nplus1[tfcFaces];
			}
		});
		arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
		{
			ENUMERATE_CELL(icInnerCells, view)
			{
				const auto icId(icInnerCells.asItemLocalId());
				const auto icCells(icId);
				const auto bfcId(m_mesh->getBottomFaceOfCell(icId));
				const auto bfcFaces(bfcId);
				if ((m_Dt_nplus1[icCells] < tmp_epsh)) 
					m_Urn_nplus1[bfcFaces] = 0.0;
				else
					m_Urn_nplus1[bfcFaces] = m_Ucalc_nplus1[bfcFaces];
			}
		});
		arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
		{
			ENUMERATE_CELL(icInnerCells, view)
			{
				const auto icId(icInnerCells.asItemLocalId());
				const auto icCells(icId);
				const auto icpId(m_mesh->getRightCell(icId));
				const auto icpCells(icpId);
				const auto icmId(m_mesh->getLeftCell(icId));
				const auto lfcId(m_mesh->getLeftFaceOfCell(icId));
				const auto lfcFaces(lfcId);
				const auto rfcId(m_mesh->getRightFaceOfCell(icId));
				const auto rfcFaces(rfcId);
				const auto rfcmId(m_mesh->getRightFaceOfCell(icmId));
				const auto rfcmFaces(rfcmId);
				if ((m_Dt_nplus1[icCells] > tmp_epsh) && (m_Dt_nplus1[icpCells] < tmp_epsh) && (m_Ucalc_nplus1[lfcFaces] > tmp_epsu) && (m_H_nplus1[icCells] > m_H_n[icpCells] + tmp_epsh)) 
					m_Urn_nplus1[rfcFaces] = m_Ucalc_nplus1[rfcmFaces];
			}
		});
		arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
		{
			ENUMERATE_CELL(icInnerCells, view)
			{
				const auto icId(icInnerCells.asItemLocalId());
				const auto icCells(icId);
				const auto icmId(m_mesh->getLeftCell(icId));
				const auto icmCells(icmId);
				const auto lfcId(m_mesh->getLeftFaceOfCell(icId));
				const auto lfcFaces(lfcId);
				const auto rfcId(m_mesh->getRightFaceOfCell(icId));
				const auto rfcFaces(rfcId);
				if ((m_Dt_nplus1[icCells] > tmp_epsh) && (m_Dt_nplus1[icmCells] < tmp_epsh) && (m_Ucalc_nplus1[rfcFaces] < -1 * tmp_epsu) && (m_H_nplus1[icCells] > m_H_n[icmCells] + tmp_epsh)) 
					m_Urn_nplus1[lfcFaces] = m_Ucalc_nplus1[rfcFaces];
			}
		});
		arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
		{
			ENUMERATE_CELL(icInnerCells, view)
			{
				const auto icId(icInnerCells.asItemLocalId());
				const auto icCells(icId);
				const auto ictId(m_mesh->getTopCell(icId));
				const auto ictCells(ictId);
				const auto tfcId(m_mesh->getTopFaceOfCell(icId));
				const auto tfcFaces(tfcId);
				const auto bfcId(m_mesh->getBottomFaceOfCell(icId));
				const auto bfcFaces(bfcId);
				if ((m_Dt_nplus1[icCells] > tmp_epsh) && (m_Dt_nplus1[ictCells] < tmp_epsh) && (m_Ucalc_nplus1[bfcFaces] > tmp_epsu) && (m_H_nplus1[icCells] > m_H_n[ictCells] + tmp_epsh)) 
					m_Urn_nplus1[tfcFaces] = m_Ucalc_nplus1[bfcFaces];
			}
		});
		arcaneParallelForeach(m_mesh->getGroup("InnerCells"), [&](CellVectorView view)
		{
			ENUMERATE_CELL(icInnerCells, view)
			{
				const auto icId(icInnerCells.asItemLocalId());
				const auto icCells(icId);
				const auto icbId(m_mesh->getBottomCell(icId));
				const auto icbCells(icbId);
				const auto tfcId(m_mesh->getTopFaceOfCell(icId));
				const auto tfcFaces(tfcId);
				const auto bfcId(m_mesh->getBottomFaceOfCell(icId));
				const auto bfcFaces(bfcId);
				if ((m_Dt_nplus1[icCells] > tmp_epsh) && (m_Dt_nplus1[icbCells] < tmp_epsh) && (m_Ucalc_nplus1[tfcFaces] < -1 * tmp_epsu) && (m_H_nplus1[icCells] > m_H_n[icbCells] + tmp_epsh)) 
					m_Urn_nplus1[bfcFaces] = m_Ucalc_nplus1[tfcFaces];
			}
		});
	}
}

/**
 * Job setUpTimeLoopN called @6.0 in simulate method.
 * In variables: Dij_n0, Dt_n0, H_n0, Hcalc_n0, Hru_n0, U_n0, Ucalc_n0, t_n0
 * Out variables: Dij_n, Dt_n, H_n, Hcalc_n, Hru_n, U_n, Ucalc_n, t_n
 */
void SwanModule::setUpTimeLoopN()
{
	m_t_n = m_t_n0;
	arcaneParallelForeach(allFaces(), [&](FaceVectorView view)
	{
		ENUMERATE_FACE(i1Faces, view)
		{
			m_U_n[i1Faces] = m_U_n0[i1Faces];
		}
	});
	arcaneParallelForeach(allFaces(), [&](FaceVectorView view)
	{
		ENUMERATE_FACE(i1Faces, view)
		{
			m_Ucalc_n[i1Faces] = m_Ucalc_n0[i1Faces];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_H_n[i1Cells] = m_H_n0[i1Cells];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_Hcalc_n[i1Cells] = m_Hcalc_n0[i1Cells];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_Hru_n[i1Cells] = m_Hru_n0[i1Cells];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_Dij_n[i1Cells] = m_Dij_n0[i1Cells];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_Dt_n[i1Cells] = m_Dt_n0[i1Cells];
		}
	});
}

/**
 * Job updateUinner called @6.0 in executeTimeLoopN method.
 * In variables: Urn_nplus1
 * Out variables: U_nplus1
 */
void SwanModule::updateUinner()
{
	arcaneParallelForeach(m_mesh->getGroup("InnerFaces"), [&](FaceVectorView view)
	{
		ENUMERATE_FACE(icInnerFaces, view)
		{
			const auto icId(icInnerFaces.asItemLocalId());
			const auto icFaces(icId);
			m_U_nplus1[icFaces] = m_Urn_nplus1[icFaces];
		}
	});
}

/**
 * Job updateUouter called @6.0 in executeTimeLoopN method.
 * In variables: Urn_nplus1
 * Out variables: U_nplus1
 */
void SwanModule::updateUouter()
{
	arcaneParallelForeach(m_mesh->getGroup("TopCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(tcTopCells, view)
		{
			const auto tcId(tcTopCells.asItemLocalId());
			const auto rfId(m_mesh->getRightFaceOfCell(tcId));
			const auto rfFaces(rfId);
			const auto bcId(m_mesh->getBottomCell(tcId));
			const auto brfId(m_mesh->getRightFaceOfCell(bcId));
			const auto brfFaces(brfId);
			m_U_nplus1[rfFaces] = m_Urn_nplus1[brfFaces];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("BottomCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(bcBottomCells, view)
		{
			const auto bcId(bcBottomCells.asItemLocalId());
			const auto rfId(m_mesh->getRightFaceOfCell(bcId));
			const auto rfFaces(rfId);
			const auto bcfId(m_mesh->getTopCell(bcId));
			const auto trfId(m_mesh->getRightFaceOfCell(bcfId));
			const auto trfFaces(trfId);
			m_U_nplus1[rfFaces] = m_Urn_nplus1[trfFaces];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("LeftCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(lcLeftCells, view)
		{
			const auto lcId(lcLeftCells.asItemLocalId());
			const auto lfId(m_mesh->getLeftFaceOfCell(lcId));
			const auto lfFaces(lfId);
			const auto rfId(m_mesh->getRightFaceOfCell(lcId));
			const auto rfFaces(rfId);
			m_U_nplus1[lfFaces] = m_Urn_nplus1[rfFaces];
		}
	});
	arcaneParallelForeach(m_mesh->getGroup("RightCells"), [&](CellVectorView view)
	{
		ENUMERATE_CELL(rcRightCells, view)
		{
			const auto rcId(rcRightCells.asItemLocalId());
			const auto rfId(m_mesh->getRightFaceOfCell(rcId));
			const auto rfFaces(rfId);
			const auto lfId(m_mesh->getLeftFaceOfCell(rcId));
			const auto lfFaces(lfId);
			m_U_nplus1[rfFaces] = m_Urn_nplus1[lfFaces];
		}
	});
}

/**
 * Job executeTimeLoopN called @7.0 in simulate method.
 * In variables: Dij_n, Dt_n, H_n, Hcalc_n, Hru_n, U_n, Ucalc_n, Urn_n, lastDump, maxIter, n, outputPeriod, stopTime, t_n, t_nplus1
 * Out variables: Dij_nplus1, Dt_nplus1, H_nplus1, Hcalc_nplus1, Hru_nplus1, U_nplus1, Ucalc_nplus1, Urn_nplus1, t_nplus1
 */
void SwanModule::executeTimeLoopN()
{
	m_n++;
	computeTn(); // @1.0
	updateDij(); // @1.0
	updateHcalc(); // @1.0
	updateHru(); // @2.0
	updateDtot(); // @3.0
	updateHinner(); // @3.0
	updateHouter(); // @3.0
	updateUcalc(); // @4.0
	updateUrunup(); // @5.0
	updateUinner(); // @6.0
	updateUouter(); // @6.0
	
	// Evaluate loop condition with variables at time n
	bool continueLoop = (m_t_nplus1 < options()->stopTime() && m_n < options()->maxIter());
	
	m_t_n = m_t_nplus1;
	arcaneParallelForeach(allFaces(), [&](FaceVectorView view)
	{
		ENUMERATE_FACE(i1Faces, view)
		{
			m_U_n[i1Faces] = m_U_nplus1[i1Faces];
		}
	});
	arcaneParallelForeach(allFaces(), [&](FaceVectorView view)
	{
		ENUMERATE_FACE(i1Faces, view)
		{
			m_Ucalc_n[i1Faces] = m_Ucalc_nplus1[i1Faces];
		}
	});
	arcaneParallelForeach(allFaces(), [&](FaceVectorView view)
	{
		ENUMERATE_FACE(i1Faces, view)
		{
			m_Urn_n[i1Faces] = m_Urn_nplus1[i1Faces];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_H_n[i1Cells] = m_H_nplus1[i1Cells];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_Hcalc_n[i1Cells] = m_Hcalc_nplus1[i1Cells];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_Hru_n[i1Cells] = m_Hru_nplus1[i1Cells];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_Dij_n[i1Cells] = m_Dij_nplus1[i1Cells];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_Dt_n[i1Cells] = m_Dt_nplus1[i1Cells];
		}
	});
	
	if (!continueLoop)
		subDomain()->timeLoopMng()->stopComputeLoop(true);
}

ARCANE_REGISTER_MODULE_SWAN(SwanModule);
