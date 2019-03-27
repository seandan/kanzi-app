/********************************************************************

 @date:		2016/09/22

 @file:		PagePrefabs.cpp

 @author:	Norby

 @brief:	页面实例化基类

 *********************************************************************/

#include "PagePrefabs.h"
#include "log.h"
#include "KanziDefine.h"
#include "car.h"

PagePrefabs::PagePrefabs(Application *pApp, int uid):
				theApp(pApp),mPage(NULL),mUID(uid)
{
	// TODO Auto-generated constructor stub
}

PagePrefabs::~PagePrefabs()
{
	// TODO Auto-generated destructor stub
}


void PagePrefabs::Show(bool bShow)
{
	if(mPage)
	{
		mPage->navigate(bShow);
	}
	else
	{
		CreateInstance();
		mPage->navigate(bShow);
	}
	if (bShow)
	{
		((Car*)theApp)->setCurPage(Key());
	}
}

void PagePrefabs::onQuadView()
{
	if (mPage)
	setProperty(mPage, DynamicPropertyType<bool>(BoolPropertyIsQuadView), true);
}
void PagePrefabs::onFullView()
{
	if (mPage)
	setProperty(mPage, DynamicPropertyType<bool>(BoolPropertyIsQuadView), false);
}

bool PagePrefabs::CreateInstance()
{
	printf("create page %s \n", m_prefabs_path.c_str());
	CreateInstance(m_prefabs_path.c_str(),
					m_instance_name.c_str(),
					m_parent_path.c_str());
}

void PagePrefabs::setPreFabsParam(const char *prefabs_path,
									const char *instance_name,
									const char *parent_path)
{
	if (prefabs_path == NULL ||
		instance_name == NULL ||
		parent_path == NULL)
	{
		printf("PagePrefabs::setPreFabsParam pointer null \n");
	}

	m_prefabs_path = prefabs_path;
	m_instance_name = instance_name;
	m_parent_path = parent_path;

}
bool PagePrefabs::CreateInstance(const char *prefabs_path,
								 const char *instance_name,
								 const char *parent_path)
{
	if(NULL != mPage)
	{
		return true;
	}
	if (NULL == theApp)
	{
		LOGINFO("Application is NULL, Init Create Instance false\n");
		return false;
	}

	ResourceManager * resManager = theApp->getResourceManager();
	//setDefaultMemoryStrategy
	if(NULL == resManager)
	{
		LOGINFO("Get resourceManager false\n");
		return false;
	}

	PrefabTemplateSharedPtr prefabs = resManager->acquireResource<PrefabTemplate>(prefabs_path);
	if(NULL == prefabs)
	{
		LOGINFO("Get prefabs %s false\n", prefabs_path);
		return false;
	}

	mPage =  prefabs->instantiate<Page>(instance_name);
	if(NULL == mPage)
	{
		LOGINFO("Instantiate  page %s false\n", instance_name);
		return false;
	}

	PageSharedPtr RootPage = theApp->getScreen()->lookupNode<Page>(parent_path);
	if (NULL != RootPage)
	{
		RootPage->addChild(mPage);
		Init();
		LOGINFO("create instance %s:%s\n",prefabs_path,instance_name);
	}
	else
	{
		LOGINFO("Get %s false\n", parent_path);
		return false;
	}
	return true;
}
