#include "main.h"

#define KF 0
#define KP 1.0f
#define KI 0.001f
#define KD 0.1f

#define STOPTIP 100

  void set_motors(int speed) {
    motor_move(MOTOR_DRIVE_FRONT_LEFT,speed);
    motor_move(MOTOR_DRIVE_FRONT_RIGHT,speed);
    motor_move(MOTOR_DRIVE_BACK_RIGHT,speed);
    motor_move(MOTOR_DRIVE_BACK_LEFT,speed);
  }

  void turn_right(int ticks, int speed, int delay_option) {
    motor_move_relative(MOTOR_DRIVE_FRONT_LEFT,ticks,speed);
    motor_move_relative(MOTOR_DRIVE_FRONT_RIGHT,-ticks,-speed);
    motor_move_relative(MOTOR_DRIVE_BACK_RIGHT,-ticks,-speed);
    motor_move_relative(MOTOR_DRIVE_BACK_LEFT,ticks,speed);
    motor_tare_position(10);
    delay(delay_option);
  }

  void turn_left(int ticks, int speed, int delay_option) {
    motor_move_relative(MOTOR_DRIVE_FRONT_LEFT,-ticks,-speed);
    motor_move_relative(MOTOR_DRIVE_FRONT_RIGHT,ticks,speed);
    motor_move_relative(MOTOR_DRIVE_BACK_RIGHT,ticks,speed);
    motor_move_relative(MOTOR_DRIVE_BACK_LEFT,-ticks,-speed);
    motor_tare_position(10);
    delay(delay_option);
    }

  void shot() {
   delay(1000);
   motor_move_relative(MOTOR_INDEXER, 1000, 127);
   delay(1000);
   motor_tare_position(10);
}

  void bottomflag(int turn) {
   motor_move_relative(10, turn, 127);
   motor_move_relative(4, -turn, -127);
   motor_move_relative(8, turn, 127);
   motor_move_relative(2, -turn, -127);
   delay(100);
   while ((adi_digital_read('A')) == 0) {set_motors(90);}
   set_motors(0);
   delay(200);
   motor_set_brake_mode(10, MOTOR_BRAKE_BRAKE); motor_set_brake_mode(4, MOTOR_BRAKE_BRAKE); motor_set_brake_mode(8, MOTOR_BRAKE_BRAKE); motor_set_brake_mode(2, MOTOR_BRAKE_BRAKE);
   delay(500);
  }

  // Set motor to speed based on distance from `ticks`
  void motor_move_p(int motor, int ticks, float p) {
      set_motors(p);
  }

  void drive_straight(int motor, int ticks, float p, int actime) {
  int st = millis();
  int  ft = st + actime;
  int sp = (int)motor_get_position(motor);
      printf("ticks - %d pos - %d sp - %d\n\r",ticks,(int)motor_get_position(motor),sp);
  while ((abs(ticks)-abs(((int)motor_get_position(motor))-sp)) > 10) { // 10 = threshold, change to change where stop
    motor_move_p(motor, ticks, (millis() > ft )? p :  (p<0)?-50:50  );
      printf("ticks - %d pos - %d sp - %d\n\r",ticks,(int)motor_get_position(motor),sp);
    delay(20);
  }
}

  void autonomous() {
    double posit, dest;
    char rpm[20];

    motor_set_gearing(MOTOR_DRIVE_FRONT_LEFT, E_MOTOR_GEARSET_18);
  	motor_set_gearing(MOTOR_DRIVE_BACK_LEFT, E_MOTOR_GEARSET_18);
  	motor_set_gearing(MOTOR_DRIVE_FRONT_RIGHT, E_MOTOR_GEARSET_18);
  	motor_set_gearing(MOTOR_DRIVE_BACK_RIGHT, E_MOTOR_GEARSET_18);
  	motor_set_gearing(MOTOR_DESCORER, E_MOTOR_GEARSET_18);
  	motor_set_gearing(MOTOR_INTAKE, E_MOTOR_GEARSET_18);
    motor_set_gearing(MOTOR_INDEXER, E_MOTOR_GEARSET_18);
  	motor_set_gearing(MOTOR_FLYWHEEL, E_MOTOR_GEARSET_36);

    motor_set_reversed(10, 1);
    motor_set_reversed(8, 1);

    motor_move(MOTOR_FLYWHEEL, 105);
    motor_move(MOTOR_INTAKE, 127);

  posit = motor_get_position(10);
  dest = posit + 9000.0;
  printf("start motors\r\n");

  drive_straight(10, 1350, 127, 200);
set_motors(0);
delay(1000);

//Backward after Getting Ball, Does a Wall Reset
drive_straight(10, -150, -85, 200);
set_motors(0);
delay(500);

//Turn towards Left Flags
turn_left(600, 120, 1000);
printf("turn\r\n");
motor_tare_position(10);
  printf("shoot\r\n");
delay(1000);
 motor_move_relative(MOTOR_INDEXER, 1000, 127);//(MOTOR_INDEXER, 127);
 delay(1000);
 motor_tare_position(10);
delay(1000);
 motor_move(MOTOR_FLYWHEEL, 95);

 delay(1000);

 motor_move_relative(MOTOR_INDEXER, 1000, 120);//(MOTOR_INDEXER, 127);

 delay(1000);

 turn_right(1120, 115, 1000);
 drive_straight(10, -1750, -200, 200);
 delay(100);
 set_motors(-5);
 delay(1000);
}

// #include "main.h"
//
// /**
//  * Runs the user autonomous code. This function will be started in its own task
//  * with the default priority and stack size whenever the robot is enabled via
//  * the Field Management System or the VEX Competition Switch in the autonomous
//  * mode. Alternatively, this function may be called in initialize or opcontrol
//  * for non-competition testing purposes.
//  *
//  * If the robot is disabled or communications is lost, the autonomous task
//  * will be stopped. Re-enabling the robot will restart the task, not re-start it
//  * from where it left off.
//  */
//
// #define KF 0
// #define KP 1.0f
// #define KI 0.001f
// #define KD 0.1f
//
// #define turn 620
// #define forward1 2700
// #define backward1 2350
// #define cflagturn 600
// #define backwardcorner 780
// #define scndturn 530
// #define forwardback 2500
// #define snugcorner 100
// #define turntoplatform 550
// #define turnf 100
// #define backalign 300
// #define forward4 -1200
//
//
// void set_motors(int speed) {
//   motor_move(MOTOR_DRIVE_FRONT_LEFT,speed);
//   motor_move(MOTOR_DRIVE_FRONT_RIGHT,speed);
//   motor_move(MOTOR_DRIVE_BACK_RIGHT,speed);
//   motor_move(MOTOR_DRIVE_BACK_LEFT,speed);
// }
//
// // Set motor to speed based on distance from `ticks`
// void motor_move_p(int motor, int ticks, float p) {
//     set_motors(p);
// }
//
// // Move to position `ticks` using p for speed
// void wait_motor_move_p(int motor, int ticks, float p) {
//   while ((ticks-motor_get_position(motor)) > 10) { // 10 = threshold, change to change where stop
//     motor_move_p(motor, ticks, p);
//     delay(25);
//   }
// }
//
// void wait_motor_move_p_ac(int motor, int ticks, float p, int actime) {
//   int st = millis();
//   int  ft = st + actime;
//   while ((ticks-motor_get_position(motor)) > 10) { // 10 = threshold, change to change where stop
//     motor_move_p(motor, ticks, (millis() > ft )? p : (p<0)?-50:50 );
//
//     delay(20);
//   }
// }
//
// void wait_motor_move_ac(int motor, int ticks, float p, int actime) {
//   int st = millis();
//   int  ft = st + actime;
//   int sp = (int)motor_get_position(motor);
//       printf("ticks - %d pos - %d sp - %d\n\r",ticks,(int)motor_get_position(motor),sp);
//   while ((abs(ticks)-abs(((int)motor_get_position(motor))-sp)) > 10) { // 10 = threshold, change to change where stop
//     motor_move_p(motor, ticks, (millis() > ft )? p :  (p<0)?-50:50  );
//       printf("ticks - %d pos - %d sp - %d\n\r",ticks,(int)motor_get_position(motor),sp);
//     delay(20);
//   }
// }
// void wait_motor_move2(int motor, int ticks, float p, int actime){
//   int st = millis();
//   int  ft = st + actime;
//    motor_tare_position(motor);
//   int sp = (int)motor_get_position(motor);
//   while ((abs(ticks)-abs(((int)motor_get_position(motor)))) > 10) { // 10 = threshold, change to change where stop
//     motor_move_p(motor, ticks, p );
//     printf("ticks - %d pos - %d sp - %d\n\r",ticks,(int)motor_get_position(motor),sp);
//    // printf("looping\n\r");
//     delay(20);
//   }
//   set_motors(0);
// }
//
// // Move `ticks` forward from the current position using p for speed
// void wait_motor_move_p_rel(int motor, int ticks, float p) {
//
//   wait_motor_move_p(motor, motor_get_position(motor) + ticks, p);
// }
//
// void wait_motor_move_rel_ac(int motor, int ticks, float p, int actime) {
//
//   wait_motor_move_p_ac(motor, ticks, p, actime);
// }
//
// // Move `ticks` forward from the current position using p for speed
// void flywheel_go(float speed);
//
//
// void autonomous() {
//   double posit, dest;
//   motor_set_gearing(MOTOR_DRIVE_FRONT_LEFT, E_MOTOR_GEARSET_18);
// 	motor_set_gearing(MOTOR_DRIVE_BACK_LEFT, E_MOTOR_GEARSET_18);
// 	motor_set_gearing(MOTOR_DRIVE_FRONT_RIGHT, E_MOTOR_GEARSET_18);
// 	motor_set_gearing(MOTOR_DRIVE_BACK_RIGHT, E_MOTOR_GEARSET_18);
// 	motor_set_gearing(MOTOR_DESCORER, E_MOTOR_GEARSET_18);
// 	motor_set_gearing(MOTOR_INTAKE, E_MOTOR_GEARSET_18);
//   motor_set_gearing(MOTOR_INDEXER, E_MOTOR_GEARSET_18);
// 	motor_set_gearing(MOTOR_FLYWHEEL, E_MOTOR_GEARSET_36);
//   //motor_set_brake_mode(10, E_MOTOR_BRAKE_COAST);
//   //motor_set_brake_mode(4, E_MOTOR_BRAKE_COAST);
//   //motor_set_brake_mode(8, E_MOTOR_BRAKE_COAST);
//   //motor_set_brake_mode(2, E_MOTOR_BRAKE_COAST);
//   motor_set_reversed(10, 1);
//   motor_set_reversed(8, 1);
//
//    motor_move(MOTOR_FLYWHEEL, 127); // flywheel starts
//    motor_move(MOTOR_INTAKE, 127);//intake starts
//
//   posit = motor_get_position(10);
//   dest = posit + 9000.0;
//   printf("start motors\r\n");
//
//   wait_motor_move2(10, forward1, 90, 200);
//   delay(200);
//   wait_motor_move2(10, -backward1, -90, 200);
//
// motor_tare_position(10);
// motor_move_relative(10, cflagturn, 127);
// motor_move_relative(4, -cflagturn, -127);
// motor_move_relative(8, cflagturn, 127);
// motor_move_relative(2, -cflagturn, -127);
//   while(cflagturn>(abs(motor_get_position(10))+10))
//    {  printf("turnval = %d motorpos = %f \n\r",turnf,motor_get_position(10));
//   delay(10);
//   }
//   delay(250);
//   wait_motor_move2(10, backwardcorner, -90, 200);
//   delay(1000);
//   motor_move_relative(MOTOR_INDEXER, 1000, 127);
//   delay(750);
//
//
//     motor_move_relative(MOTOR_INDEXER, 2000, 127);
//
//     delay(2000);
//  //wait_motor_move2(10, -snugcorner, -127, 200);
//  //delay(250);
//     motor_tare_position(10);
// motor_move_relative(10, -scndturn, -127);
// motor_move_relative(4, scndturn, 127);
// motor_move_relative(8, -scndturn, -127);
// motor_move_relative(2, scndturn, 127);
//   while(scndturn>(abs(motor_get_position(10))+10))
//    {  printf("turnval = %d motorpos = %f \n\r",turnf,motor_get_position(10));
//   delay(10);
//   }
//    // wait_motor_move2(10, -backalign, -90, 200);
//     motor_move(MOTOR_INTAKE, -127);
//     delay(250);
//     wait_motor_move2(10, forwardback, 60, 200);
//         motor_tare_position(10);
//     delay(50);
// motor_move_relative(10, -turntoplatform, -127);
// motor_move_relative(4, turntoplatform, 127);
// motor_move_relative(8, -turntoplatform, -127);
// motor_move_relative(2, turntoplatform, 127);
//   //while(turntoplatform>(abs(motor_get_position(10))+10))
//   // {  printf("turnval = %d motorpos = %f \n\r",turnf,motor_get_position(10));
//   //delay(10);
//   //}
//  motor_move(MOTOR_INTAKE, 0);
//  set_motors(80);
//  delay(100);
//  set_motors(0);
//   //wait_motor_move2(10, 450, 60,200);
//   delay(1000);
//   wait_motor_move2(10, -3900, -127, 200);
//     //intake starts
// //   motor_tare_position(10);
// //   motor_move_relative(10,turn, 127);
// //   motor_move_relative(4, -turn, -127);
// //   motor_move_relative(8, turn, 127);
// //   motor_move_relative(2, -turn, -127);
// //   while(motor_get_target_position(10) > motor_get_position(10))
// // {
// //   printf("turn - %f - %f\r\n",motor_get_target_position(10),motor_get_position(10));
// //   delay(10);
// // }
// // delay(1000);
//
// // wait_motor_move_ac(10, 650, 127, 100);
// // motor_move_relative(10, 600, 127);
// // motor_move_relative(4, 600, 127);
// // motor_move_relative(8, 600, 127);
// // motor_move_relative(2, 600, 127);
// // while(motor_get_target_position(10) > motor_get_position(10))
// // {
// //   delay(3000);
// // }
// //
// // printf("turn\r\n");
// // motor_tare_position(10);
// // wait_motor_move_ac(10, forward2, 127, 200);
// //   set_motors(0);
// //   printf("shoot\r\n");
// // delay(1000);
// // ///  motor_tare_position(10);
// // motor_tare_position(10);
// //   motor_move_relative(10,turn, 127);
// //   motor_move_relative(4, -turn, -127);
// //   motor_move_relative(8, turn, 127);
// //   motor_move_relative(2, -turn, -127);
// // //   while(motor_get_target_position(10)-20 > motor_get_position(10))
// // // {
// // //   printf("turn - %f - %f\r\n",motor_get_target_position(10),motor_get_position(10));
// // //   delay(10);
// // // }
// //    motor_move(MOTOR_INTAKE, 0);
// // delay(1000);
//
// // motor_tare_position(10);
// // wait_motor_move_ac(10, forward3, 127, 200);
// // delay(1000);
// // motor_tare_position(10);
// // wait_motor_move_ac(10, forward4, -200, 200);
// // delay(1000);
// // set_motors(0);
//
// // motor_move_relative(MOTOR_INDEXER, 1000, 127);//(MOTOR_INDEXER, 127);
// //  delay(1000);
// //  motor_tare_position(10);
// //  wait_motor_move_ac(10, forward3, 127, 200);
// // set_motors(0);
// //
// //  delay(1000);
// //
// //  motor_move_relative(MOTOR_INDEXER, 1000, 127);//(MOTOR_INDEXER, 127);
// //
// //  delay(1000);
// //  motor_move_relative(10, turnf, 127);
// //  motor_move_relative(4, -turnf, -127);
// //  motor_move_relative(8, turnf, 127);
// //  motor_move_relative(2, -turnf, -127);
// //  delay(500);
// //   motor_tare_position(10);
// //   wait_motor_move_ac(10, forward4, 127, 200);
// // //while(motor_get_target_position(10) > motor_get_position(10))
// // {
// //  printf("turn - %f - %f\r\n",motor_get_target_position(10),motor_get_position(10));
// //  delay(2);
// // }
// //
//
//
// // wait_motor_move_ac(10, 100, 127, 100);
// // motor_move_relative(10, 600, 127);
// // motor_move_relative(4, 600, 127);
// // motor_move_relative(8, 600, 127);
// // motor_move_relative(2, 600, 127);
// // while(motor_get_target_position(10) > motor_get_position(10))
// // {
// //   delay(1000);
// // }
//
//
// //wait_motor_move_ac(10, forward4, 127, 200);
//
// //  set_motors(100);
// //
// // delay(800);
// //
// // set_motors(0);
// //
// // motor_move(MOTOR_FLYWHEEL,0);
// }
