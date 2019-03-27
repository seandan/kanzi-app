/********************************************************************

 @date:		2016/09/22

 @file:		TpmsPage.h

 @author:	Norby

 @brief:	car 胎压监测页面

 *********************************************************************/

#ifndef TPMSPAGE_H_
#define TPMSPAGE_H_
#include <kanzi/kanzi.hpp>
#include "PagePrefabs.h"
using namespace kanzi;

enum PressWarnType{
	PRESSWARN_NO_WARNNING = 0,
	PRESSWARN_NO_SENSOR=1,
	PRESSWARN_QUIKE_LEAKAGE=2,
	PRESSWARN_HIGH_PRESS=3,
	PRESSWARN_LOW_PRESS=4,
	PRESSWARN_SENSOR_BAT_LOW=5,
	PRESSWARN_SENSOR_ERROR=6,
	PRESSWARN_MICRO_WARNING=7

};

struct TyreData
{
		float 	fPressure;	//气压
		float 	fTemperature;	//温度
		int		nPressureWarming;//胎压告警
		int		nTemperatureWarming;//温度告警
		TyreData()
		{
			fPressure = 0.0;
			fTemperature = 0.0;
			nPressureWarming = 0;
			nTemperatureWarming = 0;
		}
};
struct TpmsData
{
		int nKeyState;///<点火状态，0x00:OFF档 0x01:ACC档 0x02:IGN档 0x03:CRANK+IG档 0x07:error
		int nSelfCheck;///<自检结果，0=false,1=true
		float fSpeed;
		TyreData LFTyre;
		TyreData RFTyre;
		TyreData LBTyre;
		TyreData RBTyre;
		TpmsData()
		{
			nKeyState = 0;
			nSelfCheck = 0;
			fSpeed = 0.0;
		}
		//设置胎压
		void SetPressure(float fLF, float fRF, float fLB, float fRB)
		{
			LFTyre.fPressure = fLF * 2.75;
			RFTyre.fPressure = fRF * 2.75;
			LBTyre.fPressure = fLB * 2.75;
			RBTyre.fPressure = fRB * 2.75;
		}
		//设置温度
		void SetTemperature(float fLF, float fRF, float fLB, float fRB)
		{
			LFTyre.fTemperature = fLF;
			RFTyre.fTemperature = fRF;
			LBTyre.fTemperature = fLB;
			RBTyre.fTemperature = fRB;
		}
		//设置温度报警类型
		void SetTemperatureWarming(int nLF, int nRF, int nLB, int nRB)
		{
			LFTyre.nTemperatureWarming = nLF;
			RFTyre.nTemperatureWarming = nRF;
			LBTyre.nTemperatureWarming = nLB;
			RBTyre.nTemperatureWarming = nRB;
		}
		//设置胎压报警类型
		void SetPressureWarming(int nLF, int nRF, int nLB, int nRB)
		{
			LFTyre.nPressureWarming = nLF;
			RFTyre.nPressureWarming = nRF;
			LBTyre.nPressureWarming = nLB;
			RBTyre.nPressureWarming = nRB;
		}
};

class TpmsPage:public PagePrefabs
{
	public:
		TpmsPage(Application *pApp, int uid);
		virtual ~TpmsPage();
		/*
		 * 初始化page指针和其他关键按键指针
		 * */
		virtual bool Init();
		void RenewUI(TpmsData UIData);
		void setPopTips();
	private:
		Node2DSharedPtr mDataPtr;
		TextBlock2DSharedPtr mAllTips;
		Button2DSharedPtr mPopTipsBtn;

};

#endif /* TPMSPAGE_H_ */
