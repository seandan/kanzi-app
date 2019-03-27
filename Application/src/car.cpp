#include "Car.h"
#include "KanziDefine.h"
#include "PPSDefine.h"
#include <sys/pps.h>
#include<kzs_window_native.h>
#include "coagentbase.h"
#include "key.h"

#define DVR_CONTRL_PPS_PATH "/pps/coagent/capture/control"


void Car::mainOverride(const SystemProperties& systemProperties)
{
	LOGINFO("--\n");
	
	Application::mainOverride(systemProperties);
}

Car::Car() :
		CoagentApp("Car"),nKeyCusor(0),mMenuPage(this, PAGE_ID_MENU),mAdasPage(this,PAGE_ID_ADAS),
	mCarsettingsPage(this,PAGE_ID_CARSETTING),mTpmsPage(this, PAGE_ID_TPMS),
	bLoadFinish(false),nKeyMCU(-1)
{
	pthread_mutex_init(&key_mutex,NULL);


	mMenuPage.setPreFabsParam(Prefabs_MenuPage,
							 PageName_Menu,
							 KzkUrl_RootPage);

	mAdasPage.setPreFabsParam(Prefabs_Adas,
							 PageName_Adas,
							 KzkUrl_RootPage);

	mTpmsPage.setPreFabsParam(Prefabs_TpmsPage,
							 PageName_Tpms,
							 KzkUrl_RootPage);

	mCarsettingsPage.setPreFabsParam(Prefabs_Carsettings,
									PageName_Carsettings,
									KzkUrl_RootPage);

}

Car::~Car()
{
	LOG_IN_OUT
	pthread_mutex_destroy(&key_mutex);
}

void Car::OnHardKeyHandler(const char *attr_name, char *attr_val)
{
	LOG_IN_OUT
	char szTmp[128] = "";
	sprintf(szTmp, "%s:json:%s\n", attr_name, attr_val);
	//const char *pTmpParam = NULL;
	pps_decoder_t decoder;
	pps_decoder_initialize(&decoder, NULL);
	pps_decoder_parse_pps_str(&decoder, szTmp);
	pps_decoder_push_object(&decoder, NULL);

	int nKey = 0;
	const char* app;
	pps_decoder_get_string(&decoder, "app", &app);
	pps_decoder_get_int(&decoder, "key", &nKey);

	if (nKey == CK_BACK &&
		0 == strcmp(app, "Car"))//
	{
		//HideMyself();
		//OnClick();
		int pageuid = m_iCurPageID;
		const char* back = "back_button";
		if(pageuid == mMenuPage.Key())
		{
			OnClickMenuPage(back);
		}
		else if(pageuid == mTpmsPage.Key())
		{
			OnClickTpmsPage(back);
		}
		else if(pageuid == mCarsettingsPage.Key())
		{
			OnClickCarsettingsPage(back);
		}
		else if(pageuid == mAdasPage.Key())
		{
			OnClickAdasPage(back);
		}
	}
	pps_decoder_pop(&decoder);
	pps_decoder_cleanup(&decoder);
}



void Car::onMCUPPSChange(const char *attr_name,
						 const char *attr_val)
{
	if (attr_name == NULL || attr_val == NULL )
	{
		return;
	}
	//CARSETTINGS
	if(0 == strcmp(attr_name, PPS_ATTR_LIGHTDELAY))
	{
		//第一次，给MCU 发送保存的值
		int value = atoi(attr_val);
		if (mCarsettingsData.nLightDelay == -1)
		{
			SetLightDelay(POP_CWZM_TYPE, value);
			LOGINFO("Car::SetLightDelay:%d \n .",value);
		}
		mCarsettingsData.nLightDelay = value;
	}
	else if(0 == strcmp(attr_name, PPS_ATTR_REARMIRRORFOLD))
	{
		//第一次，给MCU 发送保存的值
		int value = atoi(attr_val);
		if (mCarsettingsData.nRearMirrorFold == -1)
		{
			SetRearMirrorFold(value);
			LOGINFO("Car::nRearMirrorFold:%d \n .",value);
		}
		mCarsettingsData.nRearMirrorFold = value;
	}
	else if(0 == strcmp(attr_name, PPS_ATTR_SPEEDLOCK))
	{
		//第一次，给MCU 发送保存的值
		int value = atoi(attr_val);
		if (mCarsettingsData.nSpeedLock == -1)
		{
			SetSpeedLock(value);
			LOGINFO("Car::SetSpeedLock:%d \n .",value);
		}
		mCarsettingsData.nSpeedLock = value;
	}
	else if(0 == strcmp(attr_name, PPS_ATTR_TIPSVOLUME))
	{
		//第一次，给MCU 发送保存的值
		int value = atoi(attr_val);
		if (mCarsettingsData.nTipsVolume == -1)
		{
			SetTipsVolume(value);
			LOGINFO("Car::SetTipsVolume:%d \n .",value);
		}
		mCarsettingsData.nTipsVolume = value;
	}
	else if(0 == strcmp(attr_name, PPS_ATTR_FZD))//辅助灯
	{
		int value = atoi(attr_val);
		if (mCarsettingsData.nFzdSwitch == -1)
		{
			SetFZDSwitch(value);
		}
		mCarsettingsData.nFzdSwitch = value;
	}
	else if(0 == strcmp(attr_name, PPS_ATTR_ZDJC))//自动降窗
	{
		int value = atoi(attr_val);
		if (-1 == mCarsettingsData.nZdjcSwitch)
		{
			SetZDJCSwitch(value);
		}
		mCarsettingsData.nZdjcSwitch = value;
	}
	else if(0 == strcmp(attr_name, PPS_ATTR_TIPS_VAL))//提示音量大小
	{
		int value = atoi(attr_val);
		if (-1 == mCarsettingsData.nTipsVolumeVal)
		{
			setTipsVolumeValue(value);
		}
		mCarsettingsData.nTipsVolumeVal = value;
	}
	else if(0 == strcmp(attr_name, PPS_ATTR_LIGHTDELAYINNER))//车内照明延迟
	{
		int value = atoi(attr_val);
		if (-1 == mCarsettingsData.nLightDelayInner)
		{
			SetLightDelay(POP_CNZM_TYPE, value);
			LOGINFO("Car::SetLightDelay:%d \n .",value);
		}
		mCarsettingsData.nLightDelayInner = value;
	}
	//TPMS
	//点火状态
	else if(0 == strcmp(attr_name, PPS_ATTR_KEY_STATE))
	{
		mTpmsData.nKeyState = atoi(attr_val);
	}
	//自检结果
	else if(0 == strcmp(attr_name, PPS_ATTR_SELFCHECK))
	{
		mTpmsData.nSelfCheck = atoi(attr_val);
	}
	//胎压
	else if(0 == strcmp(attr_name, PPS_ATTR_PRESSURE))
	{
		float p[4] = {0,0,0,0};
		sscanf(attr_val, "%f,%f,%f,%f", p,p+1,p+2,p+3);
		mTpmsData.SetPressure(p[0], p[1], p[2], p[3]);
		LOGINFO("%s:%f-%f-%f-%f\n", attr_name, p[0], p[1], p[2], p[3]);
	}
	//胎压警告
	else if(0 == strcmp(attr_name, PPS_ATTR_PRESSUREWARM))
	{
		int p[4] = {0,0,0,0};
		sscanf(attr_val, "%d,%d,%d,%d", p,p+1,p+2,p+3);
		mTpmsData.SetPressureWarming(p[0], p[1], p[2], p[3]);
		LOGINFO("%s:%d-%d-%d-%d\n", attr_name, p[0], p[1], p[2], p[3]);
	}
	//温度
	else if(0 == strcmp(attr_name, PPS_ATTR_TEMP))
	{
		float p[4] = {0,0,0,0};
		sscanf(attr_val, "%f,%f,%f,%f", p,p+1,p+2,p+3);
		mTpmsData.SetTemperature(p[0], p[1], p[2], p[3]);
		LOGINFO("%s:%f-%f-%f-%f\n", attr_name, p[0], p[1], p[2], p[3]);
	}
	//温度警告
	else if(0 == strcmp(attr_name, PPS_ATTR_TEMPWARM))
	{
		int p[4] = {0,0,0,0};
		sscanf(attr_val, "%d,%d,%d,%d", p,p+1,p+2,p+3);
		mTpmsData.SetTemperatureWarming(p[0], p[1], p[2], p[3]);
		LOGINFO("%s:%d-%d-%d-%d\n", attr_name, p[0], p[1], p[2], p[3]);
	}
	//盲点检测
	else if (0 == strcmp(attr_name, PPS_ADDR_BLINDDE))
	{
		int value = atoi(attr_val);
		if (PPS_BSD_STATUS_ON == value)
		{
			value = 1;
		}
		else
		{
			value = 0;
		}
		mAdasData.nbsms = value;
	}
	//车道偏离系统
	else if (0 == strcmp(attr_name, PPS_ADDR_DORSYS))
	{
		int value = atoi(attr_val);
		if (PPS_LDW_STATUS_ON == value)
		{
			value = 1;
		}
		else
		{
			value = 0;
		}
		mAdasData.nldws = value;
	}
	//行人识别
	else if (0 == strcmp(attr_name, PPS_LANEDEPARTURE))
	{
		int value = atoi(attr_val);
		if (PPS_MOD_STATUS_ON == value)
		{
			value = 1;
		}
		else
		{
			value = 0;
		}
		mAdasData.nprs = value;
	}
	//车速
	else if(0 == strcmp(attr_name, "carspeed"))
	{
		int value = atoi(attr_val);
		float f_speed = 0.0;
		if (value > 0 && value <= 0x14d5)
		{
			f_speed = value * 0.05625;
		}
		mTpmsData.fSpeed = f_speed;
		LOGINFO("mTpmsData.nSpeed d_speed:%f \n", f_speed);
	}
	else
	{}
}


void Car::onQuadviewPPSChange(const char *attr_name,
						      const char *attr_val)
{
	if (attr_name == NULL ||attr_val == NULL )
	{
		return;
	}

	//quad view state
	if(0 == strcmp(attr_name, "split"))
	{
		int state = atoi(attr_val);
		LOGINFO("quadview state:%d \n", state);
		if (state == SPLIT_ON)//分屏开关打开
		{
			//mMenuPage.onQuadView();
			//mAdasPage.onQuadView();
			//mCarsettingsPage.onQuadView();
			//mTpmsPage.onQuadView();
		}
		else if(state == SPLIT_OFF)//分屏开关关闭
		{
			mMenuPage.onFullView();
			mAdasPage.onFullView();
			mCarsettingsPage.onFullView();
			mTpmsPage.onFullView();
		}
		else if(state == SPLIT_TRIGGER)//分屏触发
		{
			mMenuPage.onQuadView();
			mAdasPage.onQuadView();
			mCarsettingsPage.onQuadView();
			mTpmsPage.onQuadView();
		}
		else if(state == SPLIT_HIDE)//分屏隐藏
		{
			mMenuPage.onFullView();
			mAdasPage.onFullView();
			mCarsettingsPage.onFullView();
			mTpmsPage.onFullView();
		}
		else if(state == SPLIT_SHOW)//分屏显示
		{
			mMenuPage.onQuadView();
			mAdasPage.onQuadView();
			mCarsettingsPage.onQuadView();
			mTpmsPage.onQuadView();
		}

	}
}

void Car::OnAttributeChange(int nKey,
							const char *attr_name,
							const char *attr_val)
{
	LOGINFO("nKey=%d,attrname=%s, val=%s\n", nKey, attr_name, attr_val);
	if(nKey ==nKeyMCU)
	{
		//CARSETTINGS
		LOGINFO("nKey=%d,attrname=%s, val=%s\n", nKey, attr_name, attr_val);
		onMCUPPSChange(attr_name, attr_val);

	}
	else if (nKey == mKeyQuad)
	{
		//quad view state
		onQuadviewPPSChange(attr_name, attr_val);
	}

	updateUi();
}

int Car::getKey()
{
	int nTmp = 0;
	pthread_mutex_lock(&key_mutex);
	nTmp = nKeyCusor;
	nKeyCusor++;
	pthread_mutex_unlock(&key_mutex);
	return nTmp;
}

void Car::onUpdate(chrono::milliseconds deltaTime)
{
	CoagentApp::onUpdate(deltaTime);
	if(!bLoadFinish)
	{
		return;
	}

#if 0
    static int i=0;
    //先出menu
    if(0==i)
    {
		mMenuPage.CreateInstance(Prefabs_MenuPage,
								 PageName_Menu,
								 KzkUrl_RootPage);
		mMenuPage.Show(true);
    }
    //再实例化别的

    else if(1==i)
    {
    	mAdasPage.CreateInstance(Prefabs_Adas,
    							 PageName_Adas,
    							 KzkUrl_RootPage);

    	mTpmsPage.CreateInstance(Prefabs_TpmsPage,
    							 PageName_Tpms,
    							 KzkUrl_RootPage);

    	mCarsettingsPage.CreateInstance(Prefabs_Carsettings,
    									PageName_Carsettings,
    									KzkUrl_RootPage);
    }

    else
    {
    	mCarsettingsPage.RenewUI(mCarsettingsData);
		mTpmsPage.RenewUI(mTpmsData);
		mAdasPage.RenewUI(mAdasData);

    }
    i++;

#else
    //mCarsettingsPage.RenewUI(mCarsettingsData);
	//mTpmsPage.RenewUI(mTpmsData);
	//mAdasPage.RenewUI(mAdasData);

#endif
}

void Car::updateUi()
{
	mCarsettingsPage.RenewUI(mCarsettingsData);
	mTpmsPage.RenewUI(mTpmsData);
	mAdasPage.RenewUI(mAdasData);
}

void Car::onProjectLoaded()
{
	getResourceManager()->setDefaultMemoryStrategy(kanzi::ResourceManager::MemoryStrategy::OptimizeMemory);
	//kanzi::ResourceManager::MemoryStrategy::OptimizeMemory
	//AddModule(PPS_CANINFO);
	nKeyMCU = AddModule(PPS_MCU, O_RDONLY);
	mKeyQuad = AddModule("/pps/coagent/system/status?delta", O_RDONLY);

	bLoadFinish=true;

	mMenuPage.CreateInstance(Prefabs_MenuPage,
									 PageName_Menu,
									 KzkUrl_RootPage);

	mAdasPage.CreateInstance(Prefabs_Adas,
	    							 PageName_Adas,
	    							 KzkUrl_RootPage);

	mTpmsPage.CreateInstance(Prefabs_TpmsPage,
							 PageName_Tpms,
							 KzkUrl_RootPage);

	mCarsettingsPage.CreateInstance(Prefabs_Carsettings,
									PageName_Carsettings,
									KzkUrl_RootPage);
	StartDetect();

	updateUi();

	mMenuPage.Show(true);
}

void Car::onConfigure(ApplicationProperties& configuration)
{
	LOGINFO("--\n");
	SetPresentWorkingDir();
	configuration.binaryName = "Car.kzb.cfg";
}

void Car::reqDVRApp(bool state)
{
	int nFD = open("/pps/coagent/services/event", O_WRONLY | O_CREAT);
	char *cmd = NULL;
	if (state)
	{
		cmd = "req:json:{\"event\":\"DVR\",\"state\":1,\"dat\":\"\"}";
	}
	else
	{
		cmd = "req:json:{\"event\":\"DVR\",\"state\":0,\"dat\":\"\"}";
	}
	if(nFD > 0)
	{
		write(nFD, cmd, strlen(cmd));
		close(nFD);
	}
}

//行车记录仪打开
void Car::reqDVROpen(bool state)
{
	int nFD = open(DVR_CONTRL_PPS_PATH, O_WRONLY | O_CREAT);
	char *cmd = NULL;
	if (state)
	{
		cmd = "[n]channel:n:0";
	}
	else
	{
		cmd = "[n]channel:n:3";
	}
	if(nFD > 0)
	{
		write(nFD, cmd, strlen(cmd));
		close(nFD);
	}
}

//行车记录仪不分屏
void Car::reqQuadViewVisible(bool state)
{
	int nFD = open(PPS_SERVICES_APP_CONTROL, O_WRONLY | O_CREAT);
	char *hideorshow;
	if (state)
	{
		hideorshow = "show";
	}
	else
	{
		hideorshow = "hide";
	}
	if(nFD > 0)
	{
		pps_encoder_t encoder;
		pps_encoder_initialize(&encoder, false);

		pps_encoder_start_object(&encoder, "req");

		pps_encoder_add_string(&encoder, "app", "QuadView");
		pps_encoder_add_string(&encoder, "action", hideorshow);
		pps_encoder_add_string(&encoder, "dat", "DVR");

		pps_encoder_end_object(&encoder);


		if (NULL != pps_encoder_buffer(&encoder))
		{
			int nLen = write(nFD, pps_encoder_buffer(&encoder), pps_encoder_length(&encoder));
			if(-1 == nLen)
			{
				printf("Car::reqQuadViewVisible write pps error!\n");
			}
		}

		pps_encoder_cleanup(&encoder);
		close(nFD);

		return;
	}
	return;
}

Application* createApplication()
{
	return new Car;
}
