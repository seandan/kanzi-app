/*
 * PPSDetect.h
 *
 *  Created on: 2016-9-18
 *      Author: admin
 */

#ifndef PPSDETECT_H_
#define PPSDETECT_H_
#include <vector>
#include <pthread.h>
#include <fcntl.h>
#include <sys/select.h>
#include <stdio.h>
typedef std::vector<int> vecPPS;
#define PPS_SYSTEM_STATUS "/pps/coagent/system/status?delta"
#define PPS_TITLE_BAR_STATUS "/pps/coagent/titlebar/status?delta"
#define PPS_HARDER_KEY	"/pps/coagent/system/key?wait,delta"
#define PPS_APP_COMD_STATE	"/pps/coagent/services/app/command?delta"
class PPSDetect
{
	public:
		PPSDetect();
		virtual ~PPSDetect();
		int AddModule(const char *strPPSFile, int mode=O_RDWR|O_CREAT, int flag=0x777);
		void StartDetect();
		virtual void OnAttributeChange(int nKey, const char *attr_name, const char *attr_val){}
		virtual void OnSystemMessage(const char *attr_name, char *attr_val){}
		virtual void OnTitleBarStatusChange(const char *attr_name, char *attr_val){}
		virtual void OnHardKeyHandler(const char *attr_name, char *attr_val){}
		virtual void OnAppCommandHandler(const char *attr_name, char *attr_val){}
	private:
		void Parse(int nKey, char *szBuf);
		static void *pthread_detect(void *arg);
		void detect();
	private:
		pthread_mutex_t fd_mutex;
		pthread_mutex_t cond_mutex;
		pthread_cond_t mycond;
		vecPPS 			mPPSVec;
		fd_set 			mDetectSet;
		int 			nMaxFd;
	private:
		int				nSystemStatusKey;	///<系统信息pps，时间温度等
		int				nTitleBarStatusKey; //title bar 状态显示
		int				nHardKeyKey;//hardkey
		int 			nAppCommand;
};

#endif /* PPSDETECT_H_ */
