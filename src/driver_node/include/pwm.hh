#ifndef PWM_HH
#define PWM_HH

typedef enum{
	SUCCESS = 0,
	FAILED = -1
}SYSFS_RES;

SYSFS_RES pwm_set_duty(std::string reg, int dutycycle);
SYSFS_RES pwm_set_period(std::string reg, int period);
SYSFS_RES pwm_set_enable(std::string reg);
#endif
