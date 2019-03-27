/*
 * CoagentApp.h
 *
 *  Created on: 2016-9-18
 *      Author: admin
 */

#ifndef COAGENTAPP_H_
#define COAGENTAPP_H_
#include <kanzi/kanzi.hpp>
#include "PPSDetect.h"
using namespace kanzi;
#define	 PPS_CANINFO "/pps/coagent/mcu/can?delta"
#define SYSTEM_STATUS_ATTR_TEMP "temperature"
#define SYSTEM_STATUS_ATTR_MUTE "mute"
#define SYSTEM_STATUS_ATTR_Lang "language"
#define SYSTEM_STATUS_ATTR_BT "bt"
#define SYSTEM_STATUS_ATTR_TIME "time"
#define SYSTEM_STATUS_TIME_DAT "dat"
#define SYSTEM_STATUS_TIME_MERIDIEM "meridiem"
#define SYSTEM_STATUS_ATTR_LANGUAGE "language"
#define SYSTEM_STATUS_ATTR_SPLIT "split"
#define SYSTEM_STATUS_ATTR_STATE "state"

struct TitleBarData{
	TitleBarData(){
		calling_status = false;
		missed_call_status = false;
		outter_temp = 27;
		mute_status = false;
		tbox_status = -1;
		wifi_status = -1;
		bt_status = 0;
		weather = "";
		time_mode = "am";
		time = "00:00";
	}
	bool calling_status;
	bool missed_call_status;
	bool mute_status;
	int outter_temp;
	int tbox_status;
	int wifi_status;
	int bt_status;
	string time;
	string time_mode;
	string weather;
};
class CoagentApp : public Application,public PPSDetect
{
	public:
		CoagentApp(const string& appName);
		virtual ~CoagentApp();
		virtual void onPostRender()final;
		virtual void onUpdate(kanzi::chrono::milliseconds deltaTime);
		virtual void OnSystemMessage(const char *attr_name, char *attr_val);
		virtual void OnTitleBarStatusChange(const char *attr_name, char *attr_val);
		virtual void OnAppCommandHandler(const char *attr_name, char *attr_val);
		//virtual void renderOverride();//渲染函数
		void updateTitleBarStatus();
		void registerMetadataOverride(ObjectFactory& ) KZ_OVERRIDE
		{
			getDomain()->registerModule<KanziComponentsModule>("kanzi_components");
		}
		void setTitleBarVisible(bool visible);
		bool isVisible()
		{
			return m_isVisible;
		}
		void setLanguage(int langId);
	private:
		void OnTimeChanged(char *strVal);
		Image2DSharedPtr 		Title;
		PageSharedPtr 			RootPage;

		string					strTime;
		int						nTimeMode;
		TitleBarData 			m_titleBarData;
		string					m_AppName;
		bool					m_isVisible;

		pthread_mutex_t 		m_mutex;
		pthread_cond_t 			m_cond;
};

#endif /* COAGENTAPP_H_ */
