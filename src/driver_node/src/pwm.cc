#include <iostream>
#include <string>
#include <sys/stat.h>
#include "pwm.h"
#define BASE_PATH "sys/class/PWM/"

namespace pwm{
	std::ofstream sysfs;

	static bool fileExists(const std::string& filename)
	{
		struct stat buf;
		if (stat(filename.c_str(), &buf) != -1)
		{
			return true;
		}
		return false;
	}

	SYSFS_RES pwm_set_duty(std::String reg, int dutycycle){
	  std::string path = BASE_PATH + reg + "DUTY";
	  if (fileExists(path)){
		  sysfs.open(path);
		  sysfs << dutycycle;
		  sysfs.close();
		  return SUCCESS;
	  }else
		  return FAIL;
	}
	SYSFS_RES pwm_set_period(std::String reg, int period){
		std::string path = BASE_PATH + reg + "PERIOD";
		if (fileExists(path)){
			sysfs.open(path);
			sysfs << period;
			sysfs.close();
			return SUCCESS;
		}else
			return FAIL;
	}

	SYSFS_RES pwm_set_enable(std::String reg){
		std::string path = BASE_PATH + reg + "ENABLE";
		if (fileExists(path)){
			sysfs.open(path);
			sysfs << 3;
			sysfs.close();
			return SUCCESS;
		}else
			return FAIL;
	}
}
