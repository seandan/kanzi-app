/********************************************************************

 @date:		2016/09/22

 @file:		CarsettingsPage.h

 @author:	Norby

 @brief:	car 汽车设定页面

 *********************************************************************/

#ifndef CARSETTINGSPAGE_H_
#define CARSETTINGSPAGE_H_
#include <kanzi/kanzi.hpp>
#include "PagePrefabs.h"
using namespace kanzi;
struct CarsettingsData
{
		int nLightDelay;//0=0s,1=15s,2=30s,3=45s,4=60s
		int nSpeedLock;//0=40km/h lock,1=15km/h lock,2=off
		int nTipsVolume;//提示音开关
		int nRearMirrorFold;
		int	nLightDelayInner;//车内灯延时关闭
		int nTipsVolumeVal;//提示音量大小
		int nZdjcSwitch;//自动降窗
		int nFzdSwitch;//辅助灯

		CarsettingsData()
		{
			nLightDelay = -1;
			nSpeedLock	= -1;
			nTipsVolume = -1;
			nRearMirrorFold = -1;
			nTipsVolumeVal = -1;
			nLightDelayInner = -1;
			nZdjcSwitch = -1;
			nFzdSwitch = -1;

		}
};
class CarsettingsPage:public PagePrefabs
{
	public:
		CarsettingsPage(Application *pApp, int uid);
		virtual ~CarsettingsPage();
		/*
		 * 初始化page指针和其他关键按键指针
		 * */
		virtual bool Init();
		int GetCWDelay();
		int GetAUTOLOCK();
		int GetTipsVolume();
		void RenewUI(CarsettingsData UIData);
	private:
		Node2DSharedPtr mDataPtr;
};

#endif /* MENUPAGE_H_ */
