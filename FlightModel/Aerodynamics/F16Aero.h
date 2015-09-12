#ifndef _F16AERO_H_
#define _F16AERO_H_

#include "../stdafx.h"
#include "F16AeroData.h"
#include "../UtilityFunctions.h"

namespace F16
{
	class AERO_Function
	{
	public:
		ND_INFO ndinfo; // dimensions descriptor

		double **X; // pointers to static arrays of data (X matrix)

		double *data; // pointer to static array of related data (Y)

		UtilBuffer buf; // reusable buffer to reduce malloc()/free()

		AERO_Function()
			: ndinfo()
			, X(NULL)
			, data(NULL)
			, buf()
		{
			ndinfo.nDimension = 0;
		}

		~AERO_Function()
		{
			if (ndinfo.nPoints != NULL)
			{
				free(ndinfo.nPoints);
				ndinfo.nPoints = NULL;
			}
			if (X != NULL)
			{
				free(X);
				X = NULL;
			}
		}

		void init(const int nDimension)
		{
			ndinfo.nDimension = nDimension;
			ndinfo.nPoints = (int*)malloc(ndinfo.nDimension*sizeof(int));
			X = (double **) malloc(ndinfo.nDimension*sizeof(double*));

			int nVertices = (1<<nDimension);
			buf.getVec(nVertices); // preallocate
		}

		double interpnf(const double *xPar)
		{
			return interpn(X, data, xPar, ndinfo, buf);
		}
	};


	// this is temporary while sorting out the stuff in namespace..
	class F16Aero
	{
	protected:
		double		Cx_total;
		double		Cx;
		double		Cx_delta_lef;
		double		Cxq;
		double		Cxq_delta_lef;
		double		Cz_total;
		double		Cz;
		double		Cz_delta_lef;
		double		Czq;
		double		Czq_delta_lef;
		double		Cm_total;
		double		Cm;
		double		eta_el;
		double		Cm_delta_lef;
		double		Cmq;
		double		Cmq_delta_lef;
		double		Cm_delta;
		double		Cm_delta_ds;
		double		Cy_total;
		double		Cy;
		double		Cy_delta_lef;
		double		Cy_delta_r30;
		double		Cy_delta_a20;
		double		Cy_delta_a20_lef;
		double		Cyr;
		double		Cyr_delta_lef;
		double		Cyp;
		double		Cyp_delta_lef;
		double		Cn_total;
		double		Cn;
		double		Cn_delta_lef;
		double		Cn_delta_r30;
		double		Cn_delta_beta;
		double		Cn_delta_a20;
		double		Cn_delta_a20_lef;
		double		Cnr;
		double		Cnr_delta_lef;
		double		Cnp;
		double		Cnp_delta_lef;
		double		Cl_total;
		double		Cl;
		double		Cl_delta_lef;
		double		Cl_delta_r30;
		double		Cl_delta_beta;
		double		Cl_delta_a20;
		double		Cl_delta_a20_lef;
		double		Clr;
		double		Clr_delta_lef;
		double		Clp;
		double		Clp_delta_lef;

		AERO_Function fn_Cx;
		AERO_Function fn_Cz;
		AERO_Function fn_Cm;
		AERO_Function fn_Cy;
		AERO_Function fn_Cn;
		AERO_Function fn_Cl;
		AERO_Function fn_Cx_lef;
		AERO_Function fn_Cz_lef;
		AERO_Function fn_Cm_lef;
		AERO_Function fn_Cy_lef;
		AERO_Function fn_Cn_lef;
		AERO_Function fn_Cl_lef;
		AERO_Function fn_CXq;
		AERO_Function fn_CZq;
		AERO_Function fn_CMq;
		AERO_Function fn_CYp;
		AERO_Function fn_CYr;
		AERO_Function fn_CNr;
		AERO_Function fn_CNp;
		AERO_Function fn_CLp;
		AERO_Function fn_CLr;
		AERO_Function fn_delta_CXq_lef;
		AERO_Function fn_delta_CYr_lef;
		AERO_Function fn_delta_CYp_lef;
		AERO_Function fn_delta_CZq_lef;
		AERO_Function fn_delta_CLr_lef;
		AERO_Function fn_delta_CLp_lef;
		AERO_Function fn_delta_CMq_lef;
		AERO_Function fn_delta_CNr_lef;
		AERO_Function fn_delta_CNp_lef;
		AERO_Function fn_Cy_r30;
		AERO_Function fn_Cn_r30;
		AERO_Function fn_Cl_r30;
		AERO_Function fn_Cy_a20;
		AERO_Function fn_Cy_a20_lef;
		AERO_Function fn_Cn_a20;
		AERO_Function fn_Cn_a20_lef;
		AERO_Function fn_Cl_a20;
		AERO_Function fn_Cl_a20_lef;
		AERO_Function fn_delta_CNbeta;
		AERO_Function fn_delta_CLbeta;
		AERO_Function fn_delta_Cm;
		AERO_Function fn_eta_el;

		double _Cx(double alpha,double beta,double dele)
		{
			//CX0120_ALPHA1_BETA1_DH1_201.dat
			double x[3];	
			x[0] = alpha;
			x[1] = beta;
			x[2] = dele;
			return fn_Cx.interpnf(x);
		}

		double _Cz(double alpha,double beta, double dele)
		{
			//CZ0120_ALPHA1_BETA1_DH1_301.dat
			double x[3];	/* Number of dimension */
			x[0] = alpha;
			x[1] = beta;
			x[2] = dele;
			return fn_Cz.interpnf(x);
		}

		double _Cm(double alpha,double beta,double dele)
		{
			//CM0120_ALPHA1_BETA1_DH1_101.dat
		
			double x[3];	
			x[0] = alpha;
			x[1] = beta;
			x[2] = dele;
			return fn_Cm.interpnf(x);
		}

		double _Cy(double alpha,double beta)
		{
			// CY0320_ALPHA1_BETA1_401.dat

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cy.interpnf(x);
		}

		double _Cn(double alpha, double beta, double dele)
		{
			//CN0120_ALPHA1_BETA1_DH2_501.dat

			double x[3];	
			x[0] = alpha;
			x[1] = beta;
			x[2] = dele;
			return fn_Cn.interpnf(x);
		}

		double _Cl(double alpha, double beta,double dele)
		{
			double x[3];
			x[0] = alpha;
			x[1] = beta;
			x[2] = dele;
			return fn_Cl.interpnf(x);
		}

		double _Cx_lef(double alpha,double beta)
		{
			//CX0820_ALPHA2_BETA1_202.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cx_lef.interpnf(x);
		}

		double _Cz_lef(double alpha,double beta)
		{
			//CZ0820_ALPHA2_BETA1_302.dat
		
			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cz_lef.interpnf(x);
		}

		double _Cm_lef(double alpha,double beta)
		{
			//CM0820_ALPHA2_BETA1_102.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cm_lef.interpnf(x);
		}

		double _Cy_lef(double alpha,double beta)
		{
			//CY0820_ALPHA2_BETA1_402.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cy_lef.interpnf(x);
		}

		double _Cn_lef(double alpha,double beta)
		{
			//CN0820_ALPHA2_BETA1_502.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cn_lef.interpnf(x);
		}

		double _Cl_lef(double alpha,double beta)
		{
			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[2];
			x[0] = alpha;
			x[1] = beta;
			return fn_Cl_lef.interpnf(x);
		}

		double _CXq(double alpha)
		{
			//CX1120_ALPHA1_204.dat

			double x[1];	
			x[0] = alpha;
			return fn_CXq.interpnf(x);
		}

		double _CZq(double alpha)
		{
			//CZ1120_ALPHA1_304.dat

			double x[1];	
			x[0] = alpha;
			return fn_CZq.interpnf(x);
		}

		double _CMq(double alpha)
		{
			//CM1120_ALPHA1_104.dat

			double x[1];	
			x[0] = alpha;
			return fn_CMq.interpnf(x);
		}

		double _CYp(double alpha)
		{
			//CY1220_ALPHA1_408.dat

			double x[1];	
			x[0] = alpha;
			return fn_CYp.interpnf(x);
		}

		double _CYr(double alpha)
		{
			//CY1320_ALPHA1_406.dat

			double x[1];	
			x[0] = alpha;
			return fn_CYr.interpnf(x);
		}

		double _CNr(double alpha)
		{
			//CN1320_ALPHA1_506.dat

			double x[1];	
			x[0] = alpha;
			return fn_CNr.interpnf(x);
		}

		double _CNp(double alpha)
		{
			//CN1220_ALPHA1_508.dat

			double x[1];	
			x[0] = alpha;
			return fn_CNp.interpnf(x);
		}

		double _CLp(double alpha)
		{
			//CL1220_ALPHA1_608.dat

			double x[1];	
			x[0] = alpha;
			return fn_CLp.interpnf(x);
		}

		double _CLr(double alpha)
		{
			//CL1320_ALPHA1_606.dat

			double x[1];	
			x[0] = alpha;
			return fn_CLr.interpnf(x);
		}

		double _delta_CXq_lef(double alpha)
		{
			//CX1420_ALPHA2_205.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[1];	
			x[0] = alpha;
			return fn_delta_CXq_lef.interpnf(x);
		}

		double _delta_CYr_lef(double alpha)
		{
			//CY1620_ALPHA2_407.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[1];	
			x[0] = alpha;
			return fn_delta_CYr_lef.interpnf(x);
		}

		double _delta_CYp_lef(double alpha)
		{
			//CY1520_ALPHA2_409.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[1];	
			x[0] = alpha;
			return fn_delta_CYp_lef.interpnf(x);
		}

		double _delta_CZq_lef(double alpha)
		{
			//CZ1420_ALPHA2_305.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[1];	
			x[0] = alpha;
			return fn_delta_CZq_lef.interpnf(x);
		}

		double _delta_CLr_lef(double alpha)
		{
			//CL1620_ALPHA2_607.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[1];	
			x[0] = alpha;
			return fn_delta_CLr_lef.interpnf(x);
		}

		double _delta_CLp_lef(double alpha)
		{
			//CL1520_ALPHA2_609.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[1];	
			x[0] = alpha;
			return fn_delta_CLp_lef.interpnf(x);
		}

		double _delta_CMq_lef(double alpha)
		{
			//CM1420_ALPHA2_105.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[1];	
			x[0] = alpha;
			return fn_delta_CMq_lef.interpnf(x);
		}

		double _delta_CNr_lef(double alpha)
		{
			//CN1620_ALPHA2_507.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[1];	
			x[0] = alpha;
			return fn_delta_CNr_lef.interpnf(x);
		}

		double _delta_CNp_lef(double alpha)
		{
			//CN1520_ALPHA2_509.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[1];	
			x[0] = alpha;
			return fn_delta_CNp_lef.interpnf(x);
		}

		double _Cy_r30(double alpha, double beta)
		{
			//CY0720_ALPHA1_BETA1_405.dat

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cy_r30.interpnf(x);
		}

		double _Cn_r30(double alpha, double beta)
		{
			//CN0720_ALPHA1_BETA1_503.dat

			double x[2];
			x[0] = alpha;
			x[1] = beta;
			return fn_Cn_r30.interpnf(x);
		}

		double _Cl_r30(double alpha, double beta)
		{
			//CL0720_ALPHA1_BETA1_603.dat

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cl_r30.interpnf(x);
		}

		double _Cy_a20(double alpha, double beta)
		{
			//CY0620_ALPHA1_BETA1_403.dat

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cy_a20.interpnf(x);
		}

		double _Cy_a20_lef(double alpha, double beta)
		{
			//CY0920_ALPHA2_BETA1_404.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cy_a20_lef.interpnf(x);
		}

		double _Cn_a20(double alpha, double beta)
		{
			//CN0620_ALPHA1_BETA1_504.dat

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cn_a20.interpnf(x);
		}

		double _Cn_a20_lef(double alpha, double beta)
		{
			//CN0920_ALPHA2_BETA1_505.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cn_a20_lef.interpnf(x);
		}

		double _Cl_a20(double alpha, double beta)
		{
			//CL0620_ALPHA1_BETA1_604.dat

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cl_a20.interpnf(x);
		}

		double _Cl_a20_lef(double alpha, double beta)
		{
			//CL0920_ALPHA2_BETA1_605.dat

			if(alpha > 45.0)
			{
				alpha = 45.0;
			}

			double x[2];	
			x[0] = alpha;
			x[1] = beta;
			return fn_Cl_a20_lef.interpnf(x);
		}

		double _delta_CNbeta(double alpha)
		{
			//CN9999_ALPHA1_brett.dat

			double x[1];	
			x[0] = alpha;
			return fn_delta_CNbeta.interpnf(x);
		}

		double _delta_CLbeta(double alpha)
		{
			//CL9999_ALPHA1_brett.dat

			double x[1];	
			x[0] = alpha;
			return fn_delta_CLbeta.interpnf(x);
		}

		double _delta_Cm(double alpha)
		{
			//CM9999_ALPHA1_brett.dat

			double x[1];	
			x[0] = alpha;
			return fn_delta_Cm.interpnf(x);
		}

		double _eta_el(double el)
		{
			//ETA_DH1_brett.dat
			double x[1];	
			x[0] = el;
			return fn_eta_el.interpnf(x);
		}


		/*
		double _delta_Cm_ds(double alpha, double el){
		...............
		...............
		} End of function(...) */

		void hifi_C(double alpha,double beta,double el)
		{
			Cx = _Cx(alpha,beta,el);
			Cz = _Cz(alpha,beta,el);
			Cm = _Cm(alpha,beta,el);
			Cy = _Cy(alpha,beta);
			Cn = _Cn(alpha,beta,el);
			Cl = _Cl(alpha,beta,el);
		}

		void hifi_damping(double alpha)
		{
			Cxq = _CXq(alpha);
			Cyr = _CYr(alpha);
			Cyp = _CYp(alpha);
			Czq = _CZq(alpha);
			Clr = _CLr(alpha);
			Clp = _CLp(alpha);
			Cmq = _CMq(alpha);
			Cnr = _CNr(alpha);
			Cnp = _CNp(alpha);
		}

		void hifi_C_lef(double alpha, double beta)
		{
			Cx_delta_lef = _Cx_lef(alpha,beta) - _Cx(alpha,beta,0);
			Cz_delta_lef = _Cz_lef(alpha,beta) - _Cz(alpha,beta,0);
			Cm_delta_lef = _Cm_lef(alpha,beta) - _Cm(alpha,beta,0);
			Cy_delta_lef = _Cy_lef(alpha,beta) - _Cy(alpha,beta);
			Cn_delta_lef = _Cn_lef(alpha,beta) - _Cn(alpha,beta,0);
			Cl_delta_lef = _Cl_lef(alpha,beta) - _Cl(alpha,beta,0);
		}

		void hifi_damping_lef(double alpha)
		{
			Cxq_delta_lef = _delta_CXq_lef(alpha);
			Cyr_delta_lef = _delta_CYr_lef(alpha);
			Cyp_delta_lef = _delta_CYp_lef(alpha);
			Czq_delta_lef = _delta_CZq_lef(alpha);
			Clr_delta_lef = _delta_CLr_lef(alpha);
			Clp_delta_lef = _delta_CLp_lef(alpha);
			Cmq_delta_lef = _delta_CMq_lef(alpha);
			Cnr_delta_lef = _delta_CNr_lef(alpha);
			Cnp_delta_lef = _delta_CNp_lef(alpha);
		}

		void hifi_rudder(double alpha, double beta)
		{
			Cy_delta_r30 = _Cy_r30(alpha,beta) - _Cy(alpha,beta);
			Cn_delta_r30 = _Cn_r30(alpha,beta) - _Cn(alpha,beta,0);
			Cl_delta_r30 = _Cl_r30(alpha,beta) - _Cl(alpha,beta,0);
		}

		void hifi_ailerons(double alpha, double beta)
		{
			Cy_delta_a20     = _Cy_a20(alpha,beta) - _Cy(alpha,beta);
			Cy_delta_a20_lef = _Cy_a20_lef(alpha,beta) - _Cy_lef(alpha,beta) - Cy_delta_a20;
			Cn_delta_a20     = _Cn_a20(alpha,beta) - _Cn(alpha,beta,0);
			Cn_delta_a20_lef = _Cn_a20_lef(alpha,beta) - _Cn_lef(alpha,beta) - Cn_delta_a20;
			Cl_delta_a20     = _Cl_a20(alpha,beta) - _Cl(alpha,beta,0);
			Cl_delta_a20_lef = _Cl_a20_lef(alpha,beta) - _Cl_lef(alpha,beta) - Cl_delta_a20;
		}

		void hifi_other_coeffs(double alpha, double el)
		{
			Cn_delta_beta = _delta_CNbeta(alpha);
			Cl_delta_beta = _delta_CLbeta(alpha);
			Cm_delta      = _delta_Cm(alpha);
			eta_el        = _eta_el(el);
			Cm_delta_ds   = 0;       /* ignore deep-stall regime, delta_Cm_ds = 0 */
		}

	public:
		F16Aero();
		~F16Aero() {};

		void updateFrame(const double alpha_DEG, const double beta_DEG, const double elevator_DEG, const double frameTime)
		{
			const double alpha1_DEG_Limited	= limit(alpha_DEG,-20.0,90.0);
			const double beta1_DEG_Limited	= limit(beta_DEG,-30.0,30.0);

			// TODO: speed brake handling..
			// TODO Speedbrakes aero (from JBSim F16.xml config)

			hifi_C(alpha1_DEG_Limited, beta1_DEG_Limited, elevator_DEG);
			hifi_damping(alpha1_DEG_Limited);
			hifi_C_lef(alpha1_DEG_Limited, beta1_DEG_Limited);
			hifi_damping_lef(alpha1_DEG_Limited);
			hifi_rudder(alpha1_DEG_Limited, beta1_DEG_Limited);
			hifi_ailerons(alpha1_DEG_Limited, beta1_DEG_Limited);
			hifi_other_coeffs(alpha1_DEG_Limited, elevator_DEG);
		}

		/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		compute Cx_tot, Cz_tot, Cm_tot, Cy_tot, Cn_tot, and Cl_total
		(as on NASA report p37-40)
		%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
		void computeTotals(const double AtmosTotalVelocity_FPS, 
						const double flap_PCT, const double leadingEdgeFlap_PCT, const double aileron_PCT, const double rudder_PCT,
						const double pitchRate_RPS, const double rollRate_RPS, const double yawRate_RPS, 
						const double alpha_DEG, const double beta_DEG, const double LgCxGearAero, const double LgCzGearAero)
		{
			// precalculate some terms to simplify statements
			const double totalVelocity_FPS = 2*AtmosTotalVelocity_FPS;
			const double meanChordFPS = (F16::meanChord_FT / totalVelocity_FPS);
			const double wingSpanFPS = (F16::wingSpan_FT / totalVelocity_FPS);

			const double diffCgPCT = (F16::referenceCG_PCT - F16::actualCG_PCT);
			const double meanChordPerWingSpan = (F16::meanChord_FT / F16::wingSpan_FT);

			// FLAPS (From JBSim F16.xml config)
			double CLFlaps = 0.35 * flap_PCT;
			double CDFlaps = 0.08 * flap_PCT;
			double CzFlaps = - (CLFlaps * cos(alpha_DEG * F16::degtorad) + CDFlaps * sin(F16::degtorad));
			double CxFlaps = - (-CLFlaps * sin(alpha_DEG * F16::degtorad) + CDFlaps * cos(F16::degtorad));

			/* XXXXXXXX Cx_tot XXXXXXXX */
			double dXdQ = meanChordFPS * (Cxq + Cxq_delta_lef*leadingEdgeFlap_PCT);
			Cx_total = Cx + Cx_delta_lef*leadingEdgeFlap_PCT + dXdQ*pitchRate_RPS;
			Cx_total += CxFlaps + LgCxGearAero;

			/* ZZZZZZZZ Cz_tot ZZZZZZZZ */ 
			double dZdQ = meanChordFPS * (Czq + Cz_delta_lef*leadingEdgeFlap_PCT);
			Cz_total = Cz + Cz_delta_lef*leadingEdgeFlap_PCT + dZdQ*pitchRate_RPS;
			Cz_total += CzFlaps + LgCzGearAero;

			/* MMMMMMMM Cm_tot MMMMMMMM */ 
			double dMdQ = meanChordFPS * (Cmq + Cmq_delta_lef*leadingEdgeFlap_PCT);
			Cm_total = Cm*eta_el + Cz_total*diffCgPCT + Cm_delta_lef*leadingEdgeFlap_PCT + dMdQ*pitchRate_RPS + Cm_delta + Cm_delta_ds;

			/* YYYYYYYY Cy_tot YYYYYYYY */
			double dYdail = Cy_delta_a20 + Cy_delta_a20_lef*leadingEdgeFlap_PCT;
			double dYdR = wingSpanFPS * (Cyr + Cyr_delta_lef*leadingEdgeFlap_PCT);
			double dYdP = wingSpanFPS * (Cyp + Cyp_delta_lef*leadingEdgeFlap_PCT);
			Cy_total = Cy + Cy_delta_lef*leadingEdgeFlap_PCT + dYdail*aileron_PCT + Cy_delta_r30*rudder_PCT + dYdR*yawRate_RPS + dYdP*rollRate_RPS;
	
			/* NNNNNNNN Cn_tot NNNNNNNN */ 
			double dNdail = Cn_delta_a20 + Cn_delta_a20_lef*leadingEdgeFlap_PCT;
			double dNdR = wingSpanFPS * (Cnr + Cnr_delta_lef*leadingEdgeFlap_PCT);
			double dNdP = wingSpanFPS * (Cnp + Cnp_delta_lef*leadingEdgeFlap_PCT);
			Cn_total = Cn + Cn_delta_lef*leadingEdgeFlap_PCT - Cy_total*diffCgPCT*meanChordPerWingSpan + dNdail*aileron_PCT + Cn_delta_r30*rudder_PCT + dNdR*yawRate_RPS + dNdP*rollRate_RPS + Cn_delta_beta*beta_DEG;

			/* LLLLLLLL Cl_total LLLLLLLL */
			double dLdail = Cl_delta_a20 + Cl_delta_a20_lef*leadingEdgeFlap_PCT;
			double dLdR = wingSpanFPS * (Clr + Clr_delta_lef*leadingEdgeFlap_PCT);
			double dLdP = wingSpanFPS * (Clp + Clp_delta_lef*leadingEdgeFlap_PCT);
			Cl_total = Cl + Cl_delta_lef*leadingEdgeFlap_PCT + dLdail*aileron_PCT + Cl_delta_r30*rudder_PCT + dLdR*yawRate_RPS + dLdP*rollRate_RPS + Cl_delta_beta*beta_DEG;
		}

		double getCxTotal() const { return Cx_total; }
		double getCzTotal() const { return Cz_total; }
		double getCmTotal() const { return Cm_total; }
		double getCyTotal() const { return Cy_total; }
		double getCnTotal() const { return Cn_total; }
		double getClTotal() const { return Cl_total; }

	}; // class F16Aero

	// constructor
	F16Aero::F16Aero() :
		Cx_total(0),
		Cx(0),				
		Cx_delta_lef(0),	
		Cxq(0),				
		Cxq_delta_lef(0),	
		Cz_total(0),		
		Cz(0),				
		Cz_delta_lef(0),	
		Czq(0),				
		Czq_delta_lef(0),	
		Cm_total(0),		
		Cm(0),				
		eta_el(0),			
		Cm_delta_lef(0),	
		Cmq(0),				
		Cmq_delta_lef(0),	
		Cm_delta(0),		
		Cm_delta_ds(0),		
		Cy_total(0),		
		Cy(0),				
		Cy_delta_lef(0),	
		Cy_delta_r30(0),	
		Cy_delta_a20(0),	
		Cy_delta_a20_lef(0),
		Cyr(0),				
		Cyr_delta_lef(0),	
		Cyp(0),				
		Cyp_delta_lef(0),	
		Cn_total(0),		
		Cn(0),				
		Cn_delta_lef(0),	
		Cn_delta_r30(0),	
		Cn_delta_beta(0),	
		Cn_delta_a20(0),	
		Cn_delta_a20_lef(0),
		Cnr(0),				
		Cnr_delta_lef(0),	
		Cnp(0),				
		Cnp_delta_lef(0),	
		Cl_total(0),		
		Cl(0),				
		Cl_delta_lef(0),	
		Cl_delta_r30(0),	
		Cl_delta_beta(0),	
		Cl_delta_a20(0),	
		Cl_delta_a20_lef(0),
		Clr(0),				
		Clr_delta_lef(0),	
		Clp(0),				
		Clp_delta_lef(0),
		fn_Cx(),
		fn_Cz(),
		fn_Cm(),
		fn_Cy(),
		fn_Cn(),
		fn_Cl(),
		fn_Cx_lef(),
		fn_Cz_lef(),
		fn_Cm_lef(),
		fn_Cy_lef(),
		fn_Cn_lef(),
		fn_Cl_lef(),
		fn_CXq(),
		fn_CZq(),
		fn_CMq(),
		fn_CYp(),
		fn_CYr(),
		fn_CNr(),
		fn_CNp(),
		fn_CLp(),
		fn_CLr(),
		fn_delta_CXq_lef(),
		fn_delta_CYr_lef(),
		fn_delta_CYp_lef(),
		fn_delta_CZq_lef(),
		fn_delta_CLr_lef(),
		fn_delta_CLp_lef(),
		fn_delta_CMq_lef(),
		fn_delta_CNr_lef(),
		fn_delta_CNp_lef(),
		fn_Cy_r30(),
		fn_Cn_r30(),
		fn_Cl_r30(),
		fn_Cy_a20(),
		fn_Cy_a20_lef(),
		fn_Cn_a20(),
		fn_Cn_a20_lef(),
		fn_Cl_a20(),
		fn_Cl_a20_lef(),
		fn_delta_CNbeta(),
		fn_delta_CLbeta(),
		fn_delta_Cm(),
		fn_eta_el()
	{
		fn_Cx.init(3);
		fn_Cx.data = _CxData;
		fn_Cx.ndinfo.nPoints[0] = alpha1_size;	
		fn_Cx.ndinfo.nPoints[1] = beta1_size; 
		fn_Cx.ndinfo.nPoints[2] = dh1_size; 
		fn_Cx.X[0] = alpha1;
		fn_Cx.X[1] = beta1;
		fn_Cx.X[2] = dh1;

		fn_Cz.init(3); /* alpha,beta,dele */
		fn_Cz.data = _CzData;
		fn_Cz.ndinfo.nPoints[0] = alpha1_size;	/* Alpha npoints */
		fn_Cz.ndinfo.nPoints[1] = beta1_size; /* Beta npoints  */
		fn_Cz.ndinfo.nPoints[2] = dh1_size;  /* dele npoints  */
		fn_Cz.X[0] = alpha1;
		fn_Cz.X[1] = beta1;
		fn_Cz.X[2] = dh1;

		fn_Cm.init(3);
		fn_Cm.data = _CmData;
		fn_Cm.ndinfo.nPoints[0] = alpha1_size;	
		fn_Cm.ndinfo.nPoints[1] = beta1_size; 
		fn_Cm.ndinfo.nPoints[2] = dh1_size; 
		fn_Cm.X[0] = alpha1;
		fn_Cm.X[1] = beta1;
		fn_Cm.X[2] = dh1;

		fn_Cy.init(2);
		fn_Cy.data = _CyData;
		fn_Cy.ndinfo.nPoints[0] = alpha1_size;	
		fn_Cy.ndinfo.nPoints[1] = beta1_size; 
		fn_Cy.X[0] = alpha1;
		fn_Cy.X[1] = beta1;

		fn_Cn.init(3);
		fn_Cn.data = _CnData;
		fn_Cn.ndinfo.nPoints[0] = alpha1_size;	
		fn_Cn.ndinfo.nPoints[1] = beta1_size;	
		fn_Cn.ndinfo.nPoints[2] = dh2_size;
		fn_Cn.X[0] = alpha1;
		fn_Cn.X[1] = beta1;
		fn_Cn.X[2] = dh2;

		fn_Cl.init(3);
		fn_Cl.data = _ClData;
		fn_Cl.ndinfo.nPoints[0] = alpha1_size;	
		fn_Cl.ndinfo.nPoints[1] = beta1_size;
		fn_Cl.ndinfo.nPoints[2] = dh2_size;
		fn_Cl.X[0] = alpha1;
		fn_Cl.X[1] = beta1;
		fn_Cl.X[2] = dh2;

		fn_Cx_lef.init(2);
		fn_Cx_lef.data = _Cx_lefData;
		fn_Cx_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_Cx_lef.ndinfo.nPoints[1] = beta1_size;
		fn_Cx_lef.X[0] = alpha2;
		fn_Cx_lef.X[1] = beta1;

		fn_Cz_lef.init(2);
		fn_Cz_lef.data = _Cz_lefData;
		fn_Cz_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_Cz_lef.ndinfo.nPoints[1] = beta1_size; 
		fn_Cz_lef.X[0] = alpha2;
		fn_Cz_lef.X[1] = beta1;

		fn_Cm_lef.init(2);
		fn_Cm_lef.data = _Cm_lefData;
		fn_Cm_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_Cm_lef.ndinfo.nPoints[1] = beta1_size; 
		fn_Cm_lef.X[0] = alpha2;
		fn_Cm_lef.X[1] = beta1;

		fn_Cy_lef.init(2);
		fn_Cy_lef.data = _Cy_lefData;
		fn_Cy_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_Cy_lef.ndinfo.nPoints[1] = beta1_size; 
		fn_Cy_lef.X[0] = alpha2;
		fn_Cy_lef.X[1] = beta1;

		fn_Cn_lef.init(2);
		fn_Cn_lef.data = _Cn_lefData;
		fn_Cn_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_Cn_lef.ndinfo.nPoints[1] = beta1_size; 
		fn_Cn_lef.X[0] = alpha2;
		fn_Cn_lef.X[1] = beta1;

		fn_Cl_lef.init(2); /* alpha,beta*/
		fn_Cl_lef.data = _Cl_lefData;
		fn_Cl_lef.ndinfo.nPoints[0] = alpha2_size;	/* Alpha npoints */
		fn_Cl_lef.ndinfo.nPoints[1] = beta1_size; /* Beta npoints  */
		fn_Cl_lef.X[0] = alpha2;
		fn_Cl_lef.X[1] = beta1;

		fn_CXq.init(1);
		fn_CXq.data = _CxqData;
		fn_CXq.ndinfo.nPoints[0] = alpha1_size;	
		fn_CXq.X[0] = alpha1;

		fn_CZq.init(1);
		fn_CZq.data = _CzqData;
		fn_CZq.ndinfo.nPoints[0] = alpha1_size;	
		fn_CZq.X[0] = alpha1;

		fn_CMq.init(1);
		fn_CMq.data = _CmqData;
		fn_CMq.ndinfo.nPoints[0] = alpha1_size;	
		fn_CMq.X[0] = alpha1;

		fn_CYp.init(1);
		fn_CYp.data = _CypData;
		fn_CYp.ndinfo.nPoints[0] = alpha1_size;	
		fn_CYp.X[0] = alpha1;

		fn_CYr.init(1);
		fn_CYr.data = _CyrData;
		fn_CYr.ndinfo.nPoints[0] = alpha1_size;	
		fn_CYr.X[0] = alpha1;

		fn_CNr.init(1);
		fn_CNr.data = _CnrData;
		fn_CNr.ndinfo.nPoints[0] = alpha1_size;	
		fn_CNr.X[0] = alpha1;

		fn_CNp.init(1);
		fn_CNp.data = _CnpData;
		fn_CNp.ndinfo.nPoints[0] = alpha1_size;	
		fn_CNp.X[0] = alpha1;

		fn_CLp.init(1);
		fn_CLp.data = _ClpData;
		fn_CLp.ndinfo.nPoints[0] = alpha1_size;	
		fn_CLp.X[0] = alpha1;

		fn_CLr.init(1);
		fn_CLr.data = _ClrData;
		fn_CLr.ndinfo.nPoints[0] = alpha1_size;	
		fn_CLr.X[0] = alpha1;

		fn_delta_CXq_lef.init(1);
		fn_delta_CXq_lef.data = _delta_CXq_lefData;
		fn_delta_CXq_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_delta_CXq_lef.X[0] = alpha2;

		fn_delta_CYr_lef.init(1);
		fn_delta_CYr_lef.data = _delta_CYr_lefData;
		fn_delta_CYr_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_delta_CYr_lef.X[0] = alpha2;

		fn_delta_CYp_lef.init(1);
		fn_delta_CYp_lef.data = _delta_CYp_lefData;
		fn_delta_CYp_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_delta_CYp_lef.X[0] = alpha2;

		fn_delta_CZq_lef.init(1);
		fn_delta_CZq_lef.data = _delta_CZq_lefData;
		fn_delta_CZq_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_delta_CZq_lef.X[0] = alpha2;

		fn_delta_CLr_lef.init(1);
		fn_delta_CLr_lef.data = _delta_CLr_lefData;
		fn_delta_CLr_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_delta_CLr_lef.X[0] = alpha2;

		fn_delta_CLp_lef.init(1);
		fn_delta_CLp_lef.data = _delta_CLp_lefData;
		fn_delta_CLp_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_delta_CLp_lef.X[0] = alpha2;

		fn_delta_CMq_lef.init(1);
		fn_delta_CMq_lef.data = _delta_CMq_lefData;
		fn_delta_CMq_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_delta_CMq_lef.X[0] = alpha2;

		fn_delta_CNr_lef.init(1);
		fn_delta_CNr_lef.data = _delta_CNr_lefData;
		fn_delta_CNr_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_delta_CNr_lef.X[0] = alpha2;

		fn_delta_CNp_lef.init(1);
		fn_delta_CNp_lef.data = _delta_CNp_lefData;
		fn_delta_CNp_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_delta_CNp_lef.X[0] = alpha2;

		fn_Cy_r30.init(2);
		fn_Cy_r30.data = _Cy_r30Data;
		fn_Cy_r30.ndinfo.nPoints[0] = alpha1_size;	
		fn_Cy_r30.ndinfo.nPoints[1] = beta1_size;	
		fn_Cy_r30.X[0] = alpha1;
		fn_Cy_r30.X[1] = beta1;

		fn_Cn_r30.init(2);
		fn_Cn_r30.data = _Cn_r30Data;
		fn_Cn_r30.ndinfo.nPoints[0] = alpha1_size;	
		fn_Cn_r30.ndinfo.nPoints[1] = beta1_size;	
		fn_Cn_r30.X[0] = alpha1;
		fn_Cn_r30.X[1] = beta1;

		fn_Cl_r30.init(2);
		fn_Cl_r30.data = _Cl_r30Data;
		fn_Cl_r30.ndinfo.nPoints[0] = alpha1_size;
		fn_Cl_r30.ndinfo.nPoints[1] = beta1_size;	
		fn_Cl_r30.X[0] = alpha1;
		fn_Cl_r30.X[1] = beta1;

		fn_Cy_a20.init(2);
		fn_Cy_a20.data = _Cy_a20Data;
		fn_Cy_a20.ndinfo.nPoints[0] = alpha1_size;	
		fn_Cy_a20.ndinfo.nPoints[1] = beta1_size;	
		fn_Cy_a20.X[0] = alpha1;
		fn_Cy_a20.X[1] = beta1;

		fn_Cy_a20_lef.init(2);
		fn_Cy_a20_lef.data = _Cy_a20_lefData;
		fn_Cy_a20_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_Cy_a20_lef.ndinfo.nPoints[1] = beta1_size;	
		fn_Cy_a20_lef.X[0] = alpha2;
		fn_Cy_a20_lef.X[1] = beta1;

		fn_Cn_a20.init(2);
		fn_Cn_a20.data = _Cn_a20Data;
		fn_Cn_a20.ndinfo.nPoints[0] = alpha1_size;	
		fn_Cn_a20.ndinfo.nPoints[1] = beta1_size;	
		fn_Cn_a20.X[0] = alpha1;
		fn_Cn_a20.X[1] = beta1;

		fn_Cn_a20_lef.init(2);
		fn_Cn_a20_lef.data = _Cn_a20_lefData;
		fn_Cn_a20_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_Cn_a20_lef.ndinfo.nPoints[1] = beta1_size;	
		fn_Cn_a20_lef.X[0] = alpha2;
		fn_Cn_a20_lef.X[1] = beta1;

		fn_Cl_a20.init(2);
		fn_Cl_a20.data = _Cl_a20Data;
		fn_Cl_a20.ndinfo.nPoints[0] = alpha1_size;	
		fn_Cl_a20.ndinfo.nPoints[1] = beta1_size;	
		fn_Cl_a20.X[0] = alpha1;
		fn_Cl_a20.X[1] = beta1;

		fn_Cl_a20_lef.init(2);
		fn_Cl_a20_lef.data = _Cl_a20_lefData;
		fn_Cl_a20_lef.ndinfo.nPoints[0] = alpha2_size;	
		fn_Cl_a20_lef.ndinfo.nPoints[1] = beta1_size;	
		fn_Cl_a20_lef.X[0] = alpha2;
		fn_Cl_a20_lef.X[1] = beta1;

		fn_delta_CNbeta.init(1);
		fn_delta_CNbeta.data = _delta_CNbetaData;
		fn_delta_CNbeta.ndinfo.nPoints[0] = alpha1_size;	
		fn_delta_CNbeta.X[0] = alpha1;

		fn_delta_CLbeta.init(1);
		fn_delta_CLbeta.data = _delta_CLbetaData;
		fn_delta_CLbeta.ndinfo.nPoints[0] = alpha1_size;	
		fn_delta_CLbeta.X[0] = alpha1;

		fn_delta_Cm.init(1);
		fn_delta_Cm.data = _delta_CmData;
		fn_delta_Cm.ndinfo.nPoints[0] = alpha1_size;	
		fn_delta_Cm.X[0] = alpha1;

		fn_eta_el.init(1);
		fn_eta_el.data = _eta_elData;
		fn_eta_el.ndinfo.nPoints[0] = dh1_size;	
		fn_eta_el.X[0] = dh1;
	} // F16Aero::F16Aero()
}

#endif // ifndef _F16AERO_H_
