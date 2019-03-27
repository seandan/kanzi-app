/********************************************************************

 @date:		2016/09/22

 @file:		MenuPage.h

 @author:	Norby

 @brief:	car 菜单页面

 *********************************************************************/

#ifndef MENUPAGE_H_
#define MENUPAGE_H_
#include <kanzi/kanzi.hpp>
#include "PagePrefabs.h"
using namespace kanzi;

class MenuPage:public PagePrefabs
{
	public:
		MenuPage(Application *pApp, int uid);
		virtual ~MenuPage();
		/*
		 * 初始化page指针和其他关键按键指针
		 * */
		virtual bool Init();
	private:
};

#endif /* MENUPAGE_H_ */
