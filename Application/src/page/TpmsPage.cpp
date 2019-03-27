/********************************************************************

 @date:		2016/09/22

 @file:		TpmsPage.cpp

 @author:	Norby

 @brief:	car 胎压监测页面

 *********************************************************************/

#include "TpmsPage.h"
#include "KanziDefine.h"
#include "log.h"
#include "car.h"
TpmsPage::TpmsPage(Application *pApp, int uid):
					PagePrefabs(pApp, uid),mDataPtr(NULL)
{
	// TODO Auto-generated constructor stub
}

TpmsPage::~TpmsPage()
{
	// TODO Auto-generated destructor stub
}

bool TpmsPage::Init()
{
	mDataPtr = mPage->lookupNode<Node2D>(TPMS_PAGE_DATA);
	mAllTips = mPage->lookupNode<TextBlock2D>(TPMS_PAGE_ALL_TIPS_TXTBLCOK);
	mPopTipsBtn = mPage->lookupNode<Button2D>(TPMS_PAGE_POPTIPS_BTN);
	mPage->addMessageFilter(Slider2D::ValueChangedMessage,
			std::bind(&Car::OnValueChange,
						(Car*)theApp, mUID, std::placeholders::_1));
	//mPage->addMessageHandler(Button2D::ClickedMessage, std::bind(&Car::OnClick,(Car*)theApp,mUID,std::placeholders::_1));
	mPage->addMessageFilter(Button2D::ClickedMessage,
			std::bind(&Car::OnClick,
						(Car*)theApp,mUID,std::placeholders::_1));
	return true;
}

void TpmsPage::RenewUI(TpmsData UIData)
{
	if(mDataPtr)
	{
		//点火状态
		setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyKeyState),
				UIData.nKeyState);
				//3);
		//自检状态
		setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertySelfCheck),
				UIData.nSelfCheck);
				//1);
		setProperty(mDataPtr,DynamicPropertyType<float>(FLOATPropertyCarSpeed),
						UIData.fSpeed);
		//左后
		setProperty(mDataPtr,DynamicPropertyType<float>(IntPropertyBLPressure),
				UIData.LBTyre.fPressure);
		setProperty(mDataPtr,DynamicPropertyType<float>(IntPropertyBLTemperature),
				UIData.LBTyre.fTemperature);
		setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyBLTemperatureWarm),
				UIData.LBTyre.nTemperatureWarming);
		setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyBLPressureWarm),
				UIData.LBTyre.nPressureWarming);
		//右后
		setProperty(mDataPtr,DynamicPropertyType<float>(IntPropertyBRPressure),
				UIData.RBTyre.fPressure);
		setProperty(mDataPtr,DynamicPropertyType<float>(IntPropertyBRTemperature),
				UIData.RBTyre.fTemperature);
		setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyBRTemperatureWarm),
				UIData.RBTyre.nTemperatureWarming);
		setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyBRPressureWarm),
				UIData.RBTyre.nPressureWarming);
		//左前
		setProperty(mDataPtr,DynamicPropertyType<float>(IntPropertyFLPressure),
				UIData.LFTyre.fPressure);
		setProperty(mDataPtr,DynamicPropertyType<float>(IntPropertyFLTemperature),
				UIData.LFTyre.fTemperature);
		setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyFLTemperatureWarm),
				UIData.LFTyre.nTemperatureWarming);
		setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyFLPressureWarm),
				UIData.LFTyre.nPressureWarming);
		//右前
		setProperty(mDataPtr,DynamicPropertyType<float>(IntPropertyFRPressure),
				UIData.RFTyre.fPressure);
		setProperty(mDataPtr,DynamicPropertyType<float>(IntPropertyFRTemperature),
				UIData.RFTyre.fTemperature);
		setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyFRTemperatureWarm),
				UIData.RFTyre.nTemperatureWarming);
		setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyFRPressureWarm),
				UIData.RFTyre.nPressureWarming);

	}
	else
	{
		LOGINFO("Data ptr is null\n");
	}


	setPopTips();

}

void TpmsPage::setPopTips()
{
	if (mPopTipsBtn == NULL || mAllTips == NULL)
	{
		LOGINFO("mPopTipsBtn == NULL\n");
		return;
	}
	int pressWarn = 0;
	int tempWarn = 0;
	//LOGINFO("pressWarn:%d, tempWarn:%d \n", pressWarn, tempWarn);
	std::vector<std::string> strVect;
	mPopTipsBtn->getProperty(
			DynamicPropertyType<int>("TyrePressureWarm"), pressWarn);
	mPopTipsBtn->getProperty(
				DynamicPropertyType<int>("TyreTempWarm"), tempWarn);
	if (pressWarn == PRESSWARN_QUIKE_LEAKAGE)
	{
		strVect.push_back("轮胎快速漏气，请检查车辆轮胎并及时补救!");
	}
	if (tempWarn)
	{
		strVect.push_back("轮温过高，请停车待温度正常后再行驶车辆!");
	}
	if (pressWarn == PRESSWARN_HIGH_PRESS)
	{
		strVect.push_back("轮胎气压过高，请将对应的轮胎放气至标准气压值!");
	}
	if (pressWarn == PRESSWARN_LOW_PRESS)
	{
		strVect.push_back("轮胎气压过低，请将对应的轮胎充气至标准气压值!");
	}
	if (pressWarn == PRESSWARN_MICRO_WARNING)
	{
		strVect.push_back("轮胎气压偏高或微低，请将对应轮胎调整至标准气压值!");
	}
	if (pressWarn == PRESSWARN_NO_SENSOR)
	{
		strVect.push_back("轮胎传感器丢失，请注意检查维修!");
	}
	if (pressWarn == PRESSWARN_SENSOR_BAT_LOW)
	{
		strVect.push_back("传感器电池量过低，请到维修店更换新的电池!");
	}
	if (pressWarn == PRESSWARN_SENSOR_ERROR)
	{
		strVect.push_back("轮胎内传感器损坏，请到维修店更换新的传感器!!");
	}
	std::string tips;
	std::vector<std::string>::iterator it = strVect.begin();
	std::vector<std::string>::iterator itEnd = strVect.end();
	int index = 1;
	for (; it !=itEnd; ++it)
	{
		char chr[4];
		memset(chr, 0, sizeof(chr));
		sprintf(chr, "%d, ", index);
		string trIndex(chr);
		tips.append(trIndex + *it);
		tips.append("\n");
		++index;
	}
	//LOGINFO("all tips:%s \n", tips.c_str());

	mAllTips->setProperty(TextBlock2D::TextProperty, tips);
}
