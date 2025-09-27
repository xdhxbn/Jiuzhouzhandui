#ifndef PWM_h
#define PWM_h

void steering_engine_init(void);
void set_angle(uint16_t ccr);
void engine_init(void);
void engine_mode(int mode);
void engine_start(int start);
void engine_speed(int speed);
	
#endif
