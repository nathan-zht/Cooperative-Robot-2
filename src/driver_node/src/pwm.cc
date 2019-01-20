#include <fstream>
#include <string>
#include <sys/stat.h>
#include "pwm.hh"
#define BASE_PATH "/sys/class/PWM/"
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

SYSFS_RES pwm_set_duty(std::string reg, int dutycycle){
  std::string path = BASE_PATH + reg + "/DUTY";
  if (fileExists(path)){
	  sysfs.open(path.c_str());
	  sysfs << dutycycle;
	  sysfs.close();
	  return SUCCESS;
  }else
	  return FAILED;
}
SYSFS_RES pwm_set_period(std::string reg, int period){
	std::string path = BASE_PATH + reg + "/PERIOD";
	if (fileExists(path)){
		sysfs.open(path.c_str());
		sysfs << period;
		sysfs.close();
		return SUCCESS;
	}else
		return FAILED;
}

SYSFS_RES pwm_set_enable(std::string reg){
	std::string path = BASE_PATH + reg + "/ENABLE";
	if (fileExists(path)){
		sysfs.open(path.c_str());
		sysfs << 3;
		sysfs.close();
		return SUCCESS;
	}else
		return FAILED;
}
