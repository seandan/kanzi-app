/********************************************************************

 @date:		2016/10/27

 @file:		car_click.cpp

 @author:	Norby

 @brief:	点击、滚动等界面操作的响应处理

 *********************************************************************/
#include "Car.h"
#include "KanziDefine.h"
#include <sys/pps.h>
#include "PPSDefine.h"

//滚动
void Car::OnValueChange(int pageuid,
		Slider2D::ValueChangedMessageArguments &arg)
{
	float value = arg.getValue();
	string name = arg.getSource()->getName();
	monolog("value change to page=%d:value=%f,name=%s\n",
			pageuid, value,name.c_str());
}

//列表焦点变化
void Car::OnTargetChange(int pageuid,
		TrajectoryListBox3D::TargetChangedMessageArguments &arg)
{
	string name = arg.getSource()->getName();
	int index = arg.getItem()->getProperty(
			DynamicPropertyType<kzInt>(PropertyName_ListIndex));

	optional<size_t>  a = arg.getItemIndex();

	monolog("target change to: %d:%d,=%s, its index=%d\n",
			pageuid, index,name.c_str(), *a);
}

//总处理
void Car::OnClick(int pageuid, Button2D::ClickedMessageArguments &arg)
{
	string name = arg.getSource()->getName();
	LOGINFO("click on %d:%s\n", pageuid,name.c_str());
	if(pageuid == mMenuPage.Key())
	{
		OnClickMenuPage(name);
	}
	else if(pageuid == mTpmsPage.Key())
	{
		OnClickTpmsPage(name);
	}
	else if(pageuid == mCarsettingsPage.Key())
	{
		OnClickCarsettingsPage(name);
	}
	else if(pageuid == mAdasPage.Key())
	{
		OnClickAdasPage(name);
	}

}



//点击了菜单界面(即car的主界面)
void Car::OnClickMenuPage(string strName)
{
	//点击了行车记录仪
	if(MENU_PAGE_CARCODER == strName)
	{
		//reqDVRApp(true);
		//发送行车记录仪打开
		reqDVROpen(true);

	}
	//胎压
	else if(MENU_PAGE_TPMS == strName)
	{
		mTpmsPage.Show(true);
	}
	//汽车设定
	else if(MENU_PAGE_CARSETTINGS == strName)
	{
		mCarsettingsPage.Show(true);
	}
	//高级辅助驾驶
	else if(MENU_PAGE_ADAS == strName)
	{
		mAdasPage.Show(true);
	}
	else if(MENU_PAGE_BACK == strName)
	{
		HideMyself();
	}

}

//点击了汽车设定界面
void Car::OnClickCarsettingsPage(string strName)
{

	if(CARSETTINGS_PAGE_CW_ACK == strName)
	{
		int nCWDelay = mCarsettingsPage.GetCWDelay();
		SetLightDelay(m_iTypePop, nCWDelay);
	}
	else if (CARSETTINGS_PAGE_CW == strName)//车外照明延迟关闭
	{
		m_iTypePop = POP_CWZM_TYPE;
	}
	else if (CARSETTINGS_PAGE_CNZM == strName)//车内照明延迟关闭
	{
		m_iTypePop = POP_CNZM_TYPE;
	}
	else if(CARSETTINGS_PAGE_TIPS_VOLUME_ACK == strName)
	{
		//提示音大小
		int value = mCarsettingsPage.GetTipsVolume();
		setTipsVolumeValue(value);

	}
	else if(CARSETTINGS_PAGE_LOCK_ACK== strName)
	{
		int nAutoLock = mCarsettingsPage.GetAUTOLOCK();
		SetSpeedLock(nAutoLock);
	}
	else if(CARSETTINGS_PAGE_TIPS_VOLUME== strName)
	{
		SetTipsVolume();//设置提示音开关
	}
	else if(CARSETTINGS_PAGE_REARVIEW_FOLD== strName)
	{
		SetRearMirrorFold();
	}
	else if (CARSETTINGS_PAGE_SWITCH_FZD== strName)//辅助灯
	{
		SetFZDSwitch(mCarsettingsData.nFzdSwitch==0?1:0);
	}
	else if (CARSETTINGS_PAGE_SWITCH_ZDJC== strName)//自动降窗
	{
		SetZDJCSwitch(mCarsettingsData.nZdjcSwitch==0?1:0);
	}
	else if(CARSETTINGS_PAGE_BACK== strName)
	{
		mMenuPage.Show(true);
	}
}

//点击了胎压监控界面
void Car::OnClickTpmsPage(string strName)
{
	if(TPMS_PAGE_BACK == strName)
	{
		mMenuPage.Show(true);
	}
}

//PPS_LANEDEPARTURE_SET"modsysswitch"//行人识别
void Car::onModSwitch()
{
	int mod = 0;
	if (mAdasData.nprs)//已经是on的状态
	{
		mod = 0x01;
	}
	else
	{
		mod = 0x02;
	}
	avmsetWrite(PPS_LANEDEPARTURE_SET, mod);
}

void Car::avmsetWrite(const char *attr, int value)
{
	if (attr == NULL)
	{
		return;
	}
	int nFD = open(PPS_AVM_SET, O_WRONLY);
	if(nFD > 0)
	{
		char tmp[64] = "";
		sprintf(tmp, "%s:n:%d", attr, value);
		write(nFD, tmp, strlen(tmp));
		close(nFD);
	}
}

//"ldwswitch"PPS_ADDR_DORSYS_SET//车道偏离系统
void Car::onLdWSwitch()
{
	int value = 0;
	if (mAdasData.nldws)
	{
		value = 0x03;
	}
	else
	{
		value = 0x02;
	}
	avmsetWrite(PPS_ADDR_DORSYS_SET, value);
}

//PPS_ADDR_BLINDDE_SET//盲点检测
void Car::onBsdSwitch()
{
	int value = 0;
	if (mAdasData.nbsms)
	{
		value = 0x02;
	}
	else
	{
		value = 0x01;
	}
	avmsetWrite(PPS_ADDR_BLINDDE_SET, value);
}
//点击了高级辅助驾驶界面
void Car::OnClickAdasPage(string strName)
{
	if(ADAS_PAGE_LDWS == strName)
	{
		onLdWSwitch();
		LOGINFO("LDW Switch Press !\n");
	}
	else if(ADAS_PAGE_BSMS== strName)
	{
		onBsdSwitch();
		LOGINFO("BSD Switch Press !\n");
	}
	else if(ADAS_PAGE_PRS== strName)
	{
		onModSwitch();
		LOGINFO("MOD Switch Press !\n");
	}
	else if(ADAS_PAGE_BACK== strName)
	{
		mMenuPage.Show(true);
	}
}

//设置车外照明延迟
void Car::SetLightDelay(int type, int value)
{
	char * set = NULL;
	if (type == POP_CNZM_TYPE)
	{
		set = PPS_ATTR_LIGHTDELAY_INNER_CTL;
	}
	else
	{
		set = PPS_ATTR_LIGHTDELAY_CTL;
	}
	int nFD = open(PPS_BCMSET, O_WRONLY);
	if(nFD > 0)
	{
		char tmp[64] = "";
		sprintf(tmp, "%s:n:%d", set, value);
		LOGINFO("Car::SetLightDelay[%s]:%d \n .",set,value);
		write(nFD, tmp, strlen(tmp));
		close(nFD);
	}
}

void Car::setTipsVolumeValue(int value)
{
	int nFD = open(PPS_BCMSET, O_WRONLY);
	if(nFD > 0)
	{
		char tmp[64] = "";
		sprintf(tmp, "%s:n:%d", PPS_ATTR_TIPSVOLUME_VAL_CTL, value);
		write(nFD, tmp, strlen(tmp));
		close(nFD);
	}
}

//设置设防提示音开关
void Car::SetTipsVolume()
{
	int nFD = open(PPS_BCMSET, O_WRONLY);
	if(nFD > 0)
	{
		char tmp[64] = "";
		sprintf(tmp, "%s:n:%d", PPS_ATTR_TIPSVOLUME_CTL, mCarsettingsData.nTipsVolume==0?1:0);
		write(nFD, tmp, strlen(tmp));
		close(nFD);
	}
}

//设置遥控倒车后视折叠
void Car::SetRearMirrorFold()
{
	int nFD = open(PPS_BCMSET, O_WRONLY);
	if(nFD > 0)
	{
		char tmp[64] = "";
		sprintf(tmp, "%s:n:%d",
				PPS_ATTR_REARMIRRORFOLD_CTL,
				mCarsettingsData.nRearMirrorFold==0?1:0);
		write(nFD, tmp, strlen(tmp));
		close(nFD);
	}
}

//设置辅助灯开关
void Car::SetFZDSwitch(int state)
{
	int nFD = open(PPS_BCMSET, O_WRONLY);
	if(nFD > 0)
	{
		char tmp[64] = "";
		sprintf(tmp, "%s:n:%d",
				PPS_ATTR_FZD_CTL,
				state);
		write(nFD, tmp, strlen(tmp));
		close(nFD);
	}
}

//设置自动降窗开关
void Car::SetZDJCSwitch(int state)
{
	int nFD = open(PPS_BCMSET, O_WRONLY);
	if(nFD > 0)
	{
		char tmp[64] = "";
		sprintf(tmp, "%s:n:%d",
				PPS_ATTR_ZDJC_CTL,
				state);
		write(nFD, tmp, strlen(tmp));
		close(nFD);
	}
}

//设置设防提示音开关
void Car::SetTipsVolume(int value)
{
	int nFD = open(PPS_BCMSET, O_WRONLY);
	if(nFD > 0)
	{
		char tmp[64] = "";
		sprintf(tmp, "%s:n:%d", PPS_ATTR_TIPSVOLUME_CTL, value);
		write(nFD, tmp, strlen(tmp));
		close(nFD);
	}
}

//设置遥控倒车后视折叠
void Car::SetRearMirrorFold(int value)
{
	int nFD = open(PPS_BCMSET, O_WRONLY);
	if(nFD > 0)
	{
		char tmp[64] = "";
		sprintf(tmp, "%s:n:%d", PPS_ATTR_REARMIRRORFOLD_CTL, value);
		write(nFD, tmp, strlen(tmp));
		close(nFD);
	}
}



//设置自动车速锁
void Car::SetSpeedLock(int value)
{
	int nFD = open(PPS_BCMSET, O_WRONLY);
	if(nFD > 0)
	{
		char tmp[64] = "";
		sprintf(tmp, "%s:n:%d", PPS_ATTR_SPEEDLOCK_CTL, value);
		write(nFD, tmp, strlen(tmp));
		close(nFD);
	}
}

//发送命令请求隐藏car
void Car::HideMyself()
{
	int nFD = open("/pps/coagent/services/app/control", O_WRONLY | O_CREAT);

	if(nFD > 0)
	{
		pps_encoder_t encoder;
		pps_encoder_initialize(&encoder, false);

		pps_encoder_start_object(&encoder, "req");

		pps_encoder_add_string(&encoder, "app", "Car");
		pps_encoder_add_string(&encoder, "action", "hide");
		pps_encoder_add_string(&encoder, "dat", "null");

		pps_encoder_end_object(&encoder);


		if (NULL != pps_encoder_buffer(&encoder))
		{
			int nLen = write(nFD, pps_encoder_buffer(&encoder), pps_encoder_length(&encoder));
			if(-1 == nLen)
			{
				LOGINFO("Write pps %s failed .", "control");
			}
		}

		pps_encoder_cleanup(&encoder);
		close(nFD);
	}

	LOGINFO("Car hide \n");
}
