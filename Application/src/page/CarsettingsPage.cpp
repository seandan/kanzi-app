/*
 * CarsettingsPage.cpp
 *
 *  Created on: 2016-9-18
 *      Author: admin
 */

#include "CarsettingsPage.h"
#include "KanziDefine.h"
#include "log.h"
#include "car.h"
CarsettingsPage::CarsettingsPage(Application *pApp, int uid):PagePrefabs(pApp, uid),mDataPtr(NULL)
{
	// TODO Auto-generated constructor stub
}

CarsettingsPage::~CarsettingsPage()
{
	// TODO Auto-generated destructor stub
}

bool CarsettingsPage::Init()
{
	mDataPtr = mPage->lookupNode<Node2D>(CARSETTINGDATA);
	mPage->addMessageFilter(Slider2D::ValueChangedMessage,
			std::bind(&Car::OnValueChange, (Car*)theApp,
					mUID, std::placeholders::_1));
	//mPage->addMessageHandler(Button2D::ClickedMessage, std::bind(&Car::OnClick,(Car*)theApp,mUID,std::placeholders::_1));
	mPage->addMessageFilter(Button2D::ClickedMessage,
			std::bind(&Car::OnClick,(Car*)theApp,mUID,
					std::placeholders::_1));
	mPage->addMessageFilter(TrajectoryListBox3D::TargetChangedMessage,
			std::bind(&Car::OnTargetChange,(Car*)theApp,mUID,
					std::placeholders::_1));
	return true;
}

int CarsettingsPage::GetCWDelay()
{
	int nRet = -1;
	TrajectoryListBox3DSharedPtr popCW =
			mPage->lookupNode<TrajectoryListBox3D>("#tralist");
	if (popCW)
	{
		nRet = popCW->getSelectedItemIndex();
	}
	return nRet;
}

int CarsettingsPage::GetTipsVolume()
{
	int nRet = -1;
	TrajectoryListBox3DSharedPtr pop =
			mPage->lookupNode<TrajectoryListBox3D>("#tralist_tipsVolume");
	if (pop)
	{
		nRet = pop->getSelectedItemIndex();
	}
	return nRet;
}

int CarsettingsPage::GetAUTOLOCK()
{
	int nRet = -1;
	TrajectoryListBox3DSharedPtr popCW =
			mPage->lookupNode<TrajectoryListBox3D>("#tralist_autolock");
	if (popCW)
	{
		nRet = popCW->getSelectedItemIndex();
	}
	return nRet;
}

void CarsettingsPage::RenewUI(CarsettingsData UIData)
{
	if (mDataPtr == NULL)
	{
		//printf("CarsettingsPage::RenewUI pointer is NULL \n");
		return;
	}
	setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyCwDelay),
			UIData.nLightDelay);
	setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertySpeedLock),
			UIData.nSpeedLock);
	setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyTipsVolume),
			UIData.nTipsVolume);
	setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyRearviewMirrorFold),
			UIData.nRearMirrorFold);

	setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertyLightDelayInner),
				UIData.nLightDelayInner);
	setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertySwitchFZD),
				UIData.nFzdSwitch);
	setProperty(mDataPtr,DynamicPropertyType<int>(IntPropertySwitchZDJC),
				UIData.nZdjcSwitch);
}
