#include <kanzi/kanzi.hpp>
#include <unistd.h>
#include <pthread.h>
#include "CoagentApp.h"
#include "log.h"
#include "pwd.h"
#include "MenuPage.h"
#include "TpmsPage.h"
#include "AdasPage.h"
#include "CarsettingsPage.h"
#include "PPSDetect.h"

using namespace kanzi;
#define POP_CNZM_TYPE		0
#define POP_CWZM_TYPE		1

enum PageID{
	PAGE_ID_MENU = 0,
	PAGE_ID_ADAS,
	PAGE_ID_CARSETTING,
	PAGE_ID_TPMS
};


class Car: public CoagentApp
{
	typedef void (Car::*pClickFunc)(Button2D::ClickedMessageArguments&);
public:
	Car();
	~Car();
	virtual void onConfigure(ApplicationProperties& configuration) KZ_OVERRIDE;
	virtual void onProjectLoaded() KZ_OVERRIDE;
	virtual void OnAttributeChange(int nKey, const char *attr_name, const char *attr_val);
	//MCU PPS变化
	void onMCUPPSChange(const char *attr_name, const char *attr_val);
	//分屏PPS变化
	void onQuadviewPPSChange(const char *attr_name, const char *attr_val);
	void OnValueChange(int pageuid, Slider2D::ValueChangedMessageArguments &arg);
	void OnTargetChange(int pageuid, TrajectoryListBox3D::TargetChangedMessageArguments &arg);
	virtual void OnHardKeyHandler(const char *attr_name, char *attr_val);
	//画面更新
	virtual void onUpdate(chrono::milliseconds deltaTime);
	virtual void mainOverride(const SystemProperties& systemProperties);
	//每个页面分配一个页面ID
	int getKey();
	//所有页面点击事件
	void OnClick(int pageuid, Button2D::ClickedMessageArguments &arg);
	//主菜单页面点击事件
	void OnClickMenuPage(string strName);
	//汽车设定页面点击事件
	void OnClickCarsettingsPage(string strName);
	//胎压监测页面点击事件
	void OnClickTpmsPage(string strName);
	//高级辅助驾驶页面点击事件
	void OnClickAdasPage(string strName);

	//行车记录仪不分屏
	void reqQuadViewVisible(bool state);
	//行车记录仪打开 视频
	void reqDVROpen(bool state);
	void reqDVRApp(bool state);
	void setCurPage(int pageid)
	{
		m_iCurPageID = pageid;
	}
	void updateUi();
private:
	//发送命令要求隐藏自己
	void HideMyself();
	//设置车外照明延迟
	void SetLightDelay(int type, int value);
	//设置设防提示音
	void SetTipsVolume();
	//设置遥控后视镜折叠
	void SetRearMirrorFold();
	//设置设防提示音
	void SetTipsVolume(int value);
	void setTipsVolumeValue(int value);
	//设置遥控后视镜折叠
	void SetRearMirrorFold(int value);
	//设置自动车速锁
	void SetSpeedLock(int value);
	void avmsetWrite(const char *attr, int value);
	//行人识别
	void onModSwitch();
	//车道偏离系统
	void onLdWSwitch();
	//盲点检测
	void onBsdSwitch();

	//设置辅助灯开关
	void SetFZDSwitch(int state);
	//设置自动降窗开关
	void SetZDJCSwitch(int state);
private:
	int						nKeyCusor;
	MenuPage 				mMenuPage;
	AdasPage				mAdasPage;
	CarsettingsPage			mCarsettingsPage;
	TpmsPage				mTpmsPage;

	Button2DSharedPtr 		MainMenuBackButtonPtr;
	pthread_mutex_t			key_mutex;
	bool					bLoadFinish;
private:
	//mcu pps fd
	int		nKeyMCU;
	//quadview fd
	int		mKeyQuad;
private:
	CarsettingsData 		mCarsettingsData;
	TpmsData				mTpmsData;
	AdasData				mAdasData;

	int m_iTypePop;
	int m_iCurPageID;

};


