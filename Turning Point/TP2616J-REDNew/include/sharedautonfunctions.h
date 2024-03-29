#include "main.h"
#ifndef _TEAMFUNCTIONS
#define _TEAMFUNCTIONS

void sharedfunct_library_init(void);
void chassis_move(int velo);
void chassis_move_absolute(double posit, int velo);
void wait_move(int ticks, float p,float limitvalue);
extern int accelZ_init;
void wait_turn(int trn, int speed, int dir, int tout);
void setup_chassis(void);
void setup_ops(void);
void fire_ball(void);
void chassis_tare(void);
void stop_intake(void);
void matchmanager(void);
void index_until_shota(void);
void tune_turn(double);
void warning_screen(char *message);
bool motion_limited(float);
#define BALLFIRE 2000
#endif //_TEAMFUNCTIONS
