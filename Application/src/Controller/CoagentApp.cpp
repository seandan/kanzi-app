/*
 * CoagentApp.cpp
 *
 *  Created on: 2016-9-18
 *      Author: admin
 */

#include "CoagentApp.h"
#include "log.h"
#include <sys/pps.h>

constexpr const char * g_attr_name_title_bar_wifi = "wifi";
constexpr const char * g_attr_name_title_bar_tbox = "tbox";
constexpr const char * g_attr_name_title_bar_calling = "calling";
constexpr const char * g_attr_name_title_bar_missed_call = "missed_call";
constexpr const char * g_attr_name_title_bar_weather = "weather";

CoagentApp::CoagentApp(const string& appName):m_AppName(appName),m_isVisible(true),nTimeMode(-1),Title(NULL),RootPage(NULL)
{
	pthread_mutex_init(&m_mutex,NULL);
	pthread_cond_init(&m_cond,NULL);
}

CoagentApp::~CoagentApp()
{
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);
}


void CoagentApp::onUpdate(kanzi::chrono::milliseconds deltaTime)
{
	pthread_mutex_lock(&m_mutex);
	while (m_isVisible != true)
	{
		LOGINFO("wait for m_cond ===========before\n");
		pthread_cond_wait(&m_cond,&m_mutex);
		LOGINFO("wait for m_cond ===========after\n");
	}
	pthread_mutex_unlock(&m_mutex);

}

void CoagentApp::onPostRender()
{
	Application::onPostRender();
	if (Title == NULL)
	{
		Title = getScreen()->lookupNode<Image2D>("#TitleBar");
	}
	//updateTitleBarStatus();
}

//渲染函数
//void CoagentApp::renderOverride()
//{
//	pthread_mutex_lock(&m_mutex);
//	while (m_isVisible != true)
//	{
//		LOGINFO("wait for m_cond ===========before\n");
//		pthread_cond_wait(&m_cond,&m_mutex);
//		LOGINFO("wait for m_cond ===========after\n");
//	}
//	pthread_mutex_unlock(&m_mutex);
//}

void CoagentApp::setTitleBarVisible(bool visible)
{
	if (Title != NULL)
	{
		Title->setVisible(visible);
	}
}

void CoagentApp::setLanguage(int langId)
{
	if (RootPage == NULL)
	{
		LOGINFO("set language root page init! \n");
		RootPage = getScreen()->lookupNode<Page>("#RootPage");
	}
	RootPage->setProperty(DynamicPropertyType<int>("Lang"), langId);
	LOGINFO("set lang :%d \n", langId);
}

void CoagentApp::updateTitleBarStatus()
{
	if(!Title)
	{
		LOGINFO("can not file #TitleBar\n");
		return;
	}

	Title->setProperty(DynamicPropertyType<int>("title_bar_bt_status"),
												m_titleBarData.bt_status);
	Title->setProperty(DynamicPropertyType<bool>("title_bar_calling_status"),
												  m_titleBarData.calling_status);
	Title->setProperty(DynamicPropertyType<bool>("title_bar_missed_call_status"),
													m_titleBarData.missed_call_status);
	Title->setProperty(DynamicPropertyType<bool>("title_bar_mute_status"),
												m_titleBarData.mute_status);
	Title->setProperty(DynamicPropertyType<int>("title_bar_outter_temp"),
												 m_titleBarData.outter_temp);
	Title->setProperty(DynamicPropertyType<int>("title_bar_tbox_status"),
													m_titleBarData.tbox_status);
	Title->setProperty(DynamicPropertyType<string>("title_bar_time_mode"),
													m_titleBarData.time_mode);
	Title->setProperty(DynamicPropertyType<string>("title_bar_time"),
													m_titleBarData.time);
	Title->setProperty(DynamicPropertyType<string>("title_bar_weather"),
													m_titleBarData.weather);
	Title->setProperty(DynamicPropertyType<int>("title_bar_wifi_status"),
												m_titleBarData.wifi_status);
}

void CoagentApp::OnAppCommandHandler(const char *attr_name,
										char *attr_val)
{
	if((NULL == attr_name) || (NULL == attr_val))
	{
		return ;
	}

	if(0 != strcmp("req", attr_name))
	{
		return ;
	}

	char szTmp[128] = "\0";
	sprintf(szTmp, "%s:json:%s\n", attr_name, attr_val);

	pps_decoder_t decoder;
	pps_decoder_initialize(&decoder, NULL);

	pps_decoder_parse_pps_str(&decoder, szTmp);

	const char *strAPP = NULL;
	const char *strAction = NULL;
	const char *strMode = NULL;
	const char *strDat = NULL;

	pps_decoder_push(&decoder, "req");
	pps_decoder_get_string(&decoder, "app", &strAPP);
	pps_decoder_get_string(&decoder, "action", &strAction);
	pps_decoder_get_string(&decoder, "mode", &strMode);
	pps_decoder_get_string(&decoder, "dat", &strDat);



	 if((NULL != strAPP) &&
			 (0 == strcmp(m_AppName.c_str(), strAPP)))
	{
		if(0 == strcmp("show", strAction))
		{
			LOGINFO("show for m_cond ===========before\n");
			pthread_mutex_lock(&m_mutex);
			m_isVisible = true;
			pthread_cond_signal(&m_cond);
			pthread_mutex_unlock(&m_mutex);
			LOGINFO("show for m_cond ===========after\n");

		}
		else if(0 == strcmp("hide", strAction))
		{
			LOGINFO("hide for m_cond ===========before\n");
			m_isVisible = false;
			LOGINFO("hide for m_cond ===========after\n");
		}
		else
		{
			printf("[Coagentbase] The app show state %s is invalid .", strAction);
		}
	}
	pps_decoder_pop(&decoder);
	pps_decoder_cleanup(&decoder);
}

void CoagentApp::OnTimeChanged(char *strVal)
{
	if ( NULL == strVal )
		return;
	pps_decoder_t decoder;
	pps_decoder_initialize(&decoder, NULL);

	pps_decoder_parse_json_str(&decoder, strVal);

	const char *strDat = NULL;
	int nMeridiem = 0;

	pps_decoder_push(&decoder, NULL);
	pps_decoder_get_string(&decoder, SYSTEM_STATUS_TIME_DAT, &strDat);
	pps_decoder_get_int(&decoder, SYSTEM_STATUS_TIME_MERIDIEM, &nMeridiem);
	pps_decoder_pop(&decoder);
	pps_decoder_cleanup(&decoder);

	m_titleBarData.time = strDat;
	if (nMeridiem == 0)
	{
		m_titleBarData.time_mode = "am";
	}
	else if (nMeridiem == 1)
	{
		m_titleBarData.time_mode = "pm";
	}
	else
	{
		m_titleBarData.time_mode = "";
	}
}

void CoagentApp::OnTitleBarStatusChange(const char *attr_name, char *attr_val)
{
	LOGINFO("name=%s,value=%s\n", attr_name, attr_val);
	if(0 == strcmp(SYSTEM_STATUS_ATTR_TIME, attr_name))
	{
		OnTimeChanged(attr_val);
	}
	else if(0 == strcmp(attr_name, SYSTEM_STATUS_ATTR_TEMP))
	{
		m_titleBarData.outter_temp = atoi(attr_val)*10;
	}

	else if(0 == strcmp(attr_name, SYSTEM_STATUS_ATTR_MUTE))
	{
		int mute = atoi(attr_val);
		if (mute == 0)
		{
			m_titleBarData.mute_status = false;
		}
		else
		{
			m_titleBarData.mute_status = true;
		}
	}

	else if(0 == strcmp(attr_name, SYSTEM_STATUS_ATTR_BT))
	{
		m_titleBarData.bt_status = atoi(attr_val);
	}
	else if (0==strcmp(attr_name, g_attr_name_title_bar_wifi))
	{
		m_titleBarData.wifi_status = atoi(attr_val);
	}
	else if (0 == strcmp(attr_name, g_attr_name_title_bar_weather))
	{
		m_titleBarData.weather = attr_val;
	}
	else if (0 == strcmp(attr_name, g_attr_name_title_bar_calling))
	{
		int value = atoi(attr_val);
		if (value == 0)
		{
			m_titleBarData.calling_status = false;
		}
		else
		{
			m_titleBarData.calling_status = true;
		}

	}
	else if (0 == strcmp(attr_name, g_attr_name_title_bar_missed_call))
	{
		int value = atoi(attr_val);
		if (value == 0)
		{
			m_titleBarData.missed_call_status = false;
		}
		else
		{
			m_titleBarData.missed_call_status = true;
		}
	}
	else if (0 == strcmp(attr_name, g_attr_name_title_bar_tbox))
	{
		m_titleBarData.tbox_status = atoi(attr_val);
	}

	updateTitleBarStatus();
}

void CoagentApp::OnSystemMessage(const char *attr_name, char *attr_val)
{
	LOGINFO("name=%s,value=%s\n", attr_name, attr_val);
	if (0 == strcmp(attr_name, SYSTEM_STATUS_ATTR_TIME))
	{
		pps_decoder_t decoder;
		pps_decoder_initialize(&decoder, NULL);
		pps_decoder_parse_json_str(&decoder, attr_val);

		const char *strDat = NULL;
		int nMeridiem = 0;

		pps_decoder_push(&decoder, NULL);
		pps_decoder_get_string(&decoder, SYSTEM_STATUS_TIME_DAT, &strDat);
		pps_decoder_get_int(&decoder, SYSTEM_STATUS_TIME_MERIDIEM, &nMeridiem);
		pps_decoder_pop(&decoder);
		if (PPS_DECODER_OK == pps_decoder_status(&decoder, true))
		{
			strTime = strDat;
			nTimeMode = nMeridiem;
			LOGINFO("time=%s,mode=%d\n", strDat, nTimeMode);
		}
		pps_decoder_cleanup(&decoder);
	}
	else if (0 == strcmp(attr_name, SYSTEM_STATUS_ATTR_MUTE))
	{
		int mute = atoi(attr_val);
		if (mute == 0)
		{
			m_titleBarData.mute_status = false;
		}
		else
		{
			m_titleBarData.mute_status = true;
		}
		updateTitleBarStatus();
	}
	else if (0 == strcmp(attr_name, SYSTEM_STATUS_ATTR_Lang))
	{
		int lang = atoi(attr_val);
		setLanguage(lang);
	}
	else
	{

	}


}
