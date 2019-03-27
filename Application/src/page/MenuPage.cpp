/********************************************************************

 @date:		2016/09/22

 @file:		MenuPage.cpp

 @author:	Norby

 @brief:	car 菜单页面

 *********************************************************************/

#include "MenuPage.h"
#include "KanziDefine.h"
#include "log.h"
#include "car.h"
MenuPage::MenuPage(Application *pApp, int uid):PagePrefabs(pApp, uid)
{
	// TODO Auto-generated constructor stub

}

MenuPage::~MenuPage()
{
	// TODO Auto-generated destructor stub
}



bool MenuPage::Init()
{
	if(mPage)mPage->addMessageFilter(Slider2D::ValueChangedMessage,
			std::bind(&Car::OnValueChange, (Car*)theApp,
						mUID, std::placeholders::_1));
	//mPage->addMessageHandler(Button2D::ClickedMessage, std::bind(&Car::OnClick,(Car*)theApp,mUID,std::placeholders::_1));
	if(mPage)mPage->addMessageFilter(Button2D::ClickedMessage,
			std::bind(&Car::OnClick,(Car*)theApp,
						mUID,std::placeholders::_1));
	return true;
}
