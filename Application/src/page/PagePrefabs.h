/********************************************************************

 @date:		2016/09/22

 @file:		PagePrefabs.h

 @author:	Norby

 @brief:	页面实例化基类

 *********************************************************************/

#ifndef PagePrefabs_H_
#define PagePrefabs_H_

#include <kanzi/kanzi.hpp>
using namespace kanzi;
class PagePrefabs
{
	public:
		PagePrefabs(Application *pApp, int uid);
		virtual ~PagePrefabs();
		int Key(){return mUID;}
		bool CreateInstance(const char *prefabs_path,
							const char *instance_name,
							const char *parent_path);
		bool CreateInstance();
		void setPreFabsParam(const char *prefabs_path,
				const char *instance_name,
				const char *parent_path);
		virtual void Show(bool bShow);
		/*
		 * 初始化page指针和其他关键按键指针
		 * */
		virtual void onQuadView();
		virtual void onFullView();
		virtual bool Init(){return true;}
	    template <typename DataType>
	    void setProperty(ObjectSharedPtr dstPtr,const PropertyType<DataType>& propertyType, typename PropertyType<DataType>::DataType value)
	    {
	    	DataType curValue = dstPtr->getProperty(propertyType);
	    	if(curValue != value)
	    	{
	    		dstPtr->setProperty(propertyType, value);
	    	}
	    }
	protected:
		Application *theApp;		///<app类指针
		PageSharedPtr mPage;		///<页面指针
		int				mUID;
		std::string m_prefabs_path;
		std::string m_instance_name;
		std::string m_parent_path;
};

#endif /* PagePrefabs_H_ */
