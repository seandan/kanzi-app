/*
 * PPSDetect.cpp
 *
 *  Created on: 2016-9-18
 *      Author: admin
 */

#include "PPSDetect.h"
#define max(a,b) (a)>(b)?(a):(b)
#include <sys/pps.h>

PPSDetect::PPSDetect() :
		nMaxFd(-1),nSystemStatusKey(-1),nTitleBarStatusKey(-1),nAppCommand(-1)
{
	// TODO Auto-generated constructor stub
	pthread_mutex_init(&fd_mutex, NULL);
	pthread_mutex_init(&cond_mutex, NULL);
	pthread_cond_init(&mycond,NULL);
	mPPSVec.clear();
	FD_ZERO(&mDetectSet);
	nSystemStatusKey = AddModule(PPS_SYSTEM_STATUS);
	nTitleBarStatusKey = AddModule(PPS_TITLE_BAR_STATUS);
	nHardKeyKey = AddModule(PPS_HARDER_KEY);
	nAppCommand = AddModule(PPS_APP_COMD_STATE);
	pthread_create(NULL, NULL, pthread_detect, this);
}

PPSDetect::~PPSDetect()
{
	pthread_mutex_lock(&fd_mutex);
	vecPPS::iterator it = mPPSVec.begin();
	for (; it != mPPSVec.end(); it++)
	{
		if ((*it)>0)
		{
			close((*it));
		}
	}
	pthread_mutex_unlock(&fd_mutex);
	pthread_mutex_destroy(&fd_mutex);
	pthread_mutex_destroy(&cond_mutex);
	pthread_cond_destroy(&mycond);
	mPPSVec.clear();
}

void PPSDetect::StartDetect()
{
	 pthread_cond_signal(&mycond);
}

int PPSDetect::AddModule(const char *strPPSFile, int mode, int flag)
{
	int nFD = open(strPPSFile, mode, flag);
	if (nFD > 1)
	{
		pthread_mutex_lock(&fd_mutex);
		mPPSVec.push_back(nFD);
		FD_SET(nFD, &mDetectSet);
		nMaxFd = max(nFD, nMaxFd);
		pthread_mutex_unlock(&fd_mutex);
	}
	else
	{
		printf("open %s, false\n", strPPSFile);
	}
	return nFD;
}

void* PPSDetect::pthread_detect(void *arg)
{
	PPSDetect *pD = (PPSDetect*) arg;
	pD->detect();
	return 0;
}

void PPSDetect::Parse(int nKey, char *szBuf)
{
	pps_attrib_t info;
	pps_status_t status;
	char *buff = szBuf;
	while (PPS_END != (status = ppsparse(&buff, NULL, NULL, &info, 0)))
	{
		switch (status)
		{
			case PPS_OBJECT_CREATED:
				//printf("PPS_OBJECT_CREATED :%s\n", info.obj_name);
				break;
			case PPS_OBJECT_DELETED:
				//printf("PPS_OBJECT_DELETED :%s\n", info.obj_name);
				break;
			case PPS_OBJECT_TRUNCATED:
				//printf("PPS_OBJECT_TRUNCATED :%s\n", info.obj_name);
				break;
			case PPS_OBJECT:
				//printf("PPS_OBJECT :%s\n", buff);
				break;
			case PPS_ATTRIBUTE:
				if ((NULL != info.attr_name) && (NULL != info.value))
				{
					//printf("PPS_ATTRIBUTE :%s=%s\n", info.attr_name, info.value);
					if(nSystemStatusKey == nKey)
					{
						OnSystemMessage(info.attr_name, info.value);
					}
					else if (nTitleBarStatusKey == nKey)
					{
						OnTitleBarStatusChange(info.attr_name, info.value);
					}
					else if (nHardKeyKey == nKey)
					{
						OnHardKeyHandler(info.attr_name, info.value);
					}
					else if (nAppCommand == nKey)
					{
						OnAppCommandHandler(info.attr_name, info.value);
					}
					else
					{
						OnAttributeChange(nKey, info.attr_name, info.value);
					}
				}
				break;
			case PPS_ATTRIBUTE_DELETED:
				//printf("PPS_ATTRIBUTE_DELETED :%s\n", info.attr_name);
				break;
			default:
				break;
		}
	}
}
void PPSDetect::detect()
{
	pthread_mutex_lock(&cond_mutex);
	pthread_cond_wait(&mycond, &cond_mutex);
	pthread_mutex_unlock(&cond_mutex);
	while (1)
	{
		fd_set tmpfd = mDetectSet;
		int rc = 0;
		switch (rc = select(1 + nMaxFd, &tmpfd, 0, 0, NULL))
		{
			case -1:
				//Error
				break;
			case 0:
				//Timeout
				break;
			default:
			{
				pthread_mutex_lock(&fd_mutex);
				vecPPS::iterator it = mPPSVec.begin();
				for (; it != mPPSVec.end(); it++)
				{
					if (FD_ISSET((*it), &tmpfd))
					{
						char szBuf[1024 * 5] = "";
						int nLen = read((*it), szBuf, sizeof(szBuf) - 1);
						if (nLen > 1)
						{
							szBuf[nLen] = '\0';
							Parse( (*it), szBuf);
						}
					}
				}
				pthread_mutex_unlock(&fd_mutex);
				break;
			}
		}
	}
}
