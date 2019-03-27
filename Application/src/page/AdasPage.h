/*
 * AdasPage.h
 *
 *  Created on: 2016-9-18
 *      Author: admin
 */

#ifndef ADASPAGE_H_
#define ADASPAGE_H_
#include <kanzi/kanzi.hpp>
#include "PagePrefabs.h"
using namespace kanzi;

struct AdasData
{
		int nldws;///<车道偏离轨迹
		int nbsms;///<盲点检测系统
		int nprs; ///<行人识别系统
};
class AdasPage:public PagePrefabs
{
	public:
		AdasPage(Application *pApp, int uid);
		virtual ~AdasPage();
		/*
		 * 初始化page指针和其他关键按键指针
		 * */
		virtual bool Init();
	void RenewUI(AdasData UIData);
	private:
		Node2DSharedPtr mDataPtr;

		GridListBox2DSharedPtr m_adasMainList;
};

#endif /* ADASPAGE_H_ */
