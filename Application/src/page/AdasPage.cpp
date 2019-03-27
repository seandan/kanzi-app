/*
 * AdasPage.cpp
 *
 *  Created on: 2016-9-18
 *      Author: admin
 */

#include "AdasPage.h"
#include "KanziDefine.h"
#include "log.h"
#include "car.h"
AdasPage::AdasPage(Application *pApp, int uid):PagePrefabs(pApp, uid)
{
}

AdasPage::~AdasPage()
{
}

bool AdasPage::Init()
{
	m_adasMainList = mPage->lookupNode<GridListBox2D>(ADAS_MAIN_LIST);

	mDataPtr = mPage->lookupNode<Node2D>(ADAS_PAGE_DATA);
	mPage->addMessageFilter(Slider2D::ValueChangedMessage,
			std::bind(&Car::OnValueChange, (Car*)theApp,
					mUID, std::placeholders::_1));
	//mPage->addMessageHandler(Button2D::ClickedMessage, std::bind(&Car::OnClick,(Car*)theApp,mUID,std::placeholders::_1));
	mPage->addMessageFilter(Button2D::ClickedMessage,
			std::bind(&Car::OnClick,(Car*)theApp,
					mUID,std::placeholders::_1));
	return true;
}
void AdasPage::RenewUI(AdasData UIData)
{
	if (mDataPtr == NULL)
	{
		//printf("AdasPage::RenewUI pointer is NULL \n");
		return;
	}
	setProperty(mDataPtr,DynamicPropertyType<int>(ADAS_PAGE_LDWS),
			UIData.nldws);
	setProperty(mDataPtr,DynamicPropertyType<int>(ADAS_PAGE_PRS),
			UIData.nprs);
	setProperty(mDataPtr,DynamicPropertyType<int>(ADAS_PAGE_BSMS),
			UIData.nbsms);
}
