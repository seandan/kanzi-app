#ifndef PWD_H
#define PWD_H
#include "log.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
static const int MAX_FILE_PATH = 256;

static void SetPresentWorkingDir()
{

	/*
	 * @brief /proc/self/exefile文件中存有当前可执行文件的全路径
	 * 
	 **/
	char dir[MAX_FILE_PATH] = { 0 };
	std::string  temp, file_path;

	int fd = open("/proc/self/exefile", O_RDONLY);
	if (fd < 0)
	{
		LOGINFO("open file failed");
		return;
	}
	int nCount = read(fd, dir, MAX_FILE_PATH - 1);
	if (nCount > 0)
	{
		temp = dir;
	}
	close(fd);

	/*
	 * @note 找到最后一个'/'，确定可执行文件目录
	 **/
	int nPos = temp.find_last_of('/');  /*查找'/'字符*/
	if (nPos != -1)
	{
		file_path = temp.substr(0, nPos + 1);
	}

	/*
	 * @note 修改当前可执行程序的工作目录
	 **/
	if (chdir(file_path.c_str()) < 0)
	{
		LOGINFO("change current work path failed");
	}
}
#endif
