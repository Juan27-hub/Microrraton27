/*
 * ades_odometria.c
 *
 *  Created on: Oct 27, 2025
 *      Author: jandr
 */

#include "ades_odometria.h"

void updatePose (int16_t left_pulses, int16_t right_pulses, float delta_time_ms, Pose* pose){
	float delta_time_s = delta_time_ms / 1000.0;
	//static const float stop_threshold = 5.0; ???

	float delta_left_pulses = (float)left_pulses - (float)pose->left_last_pulses;
	float delta_right_pulses = (float)right_pulses - (float)pose->right_last_pulses;

	pose->left_distance_mm = (2.0 * PI * RADIO * (float)delta_left_pulses) / PULSOS;
	pose->right_distance_mm = (2.0 * PI * RADIO * (float)delta_right_pulses) / PULSOS;
	pose->left_distance_mm_acum += pose->left_distance_mm;
	pose->right_distance_mm_acum += pose->right_distance_mm;
	pose->left_last_pulses = left_pulses;
	pose->right_last_pulses = right_pulses;

	float delta_lineal = (pose->left_distance_mm + pose->right_distance_mm) / 2.0;
	pose->avanceLineal += delta_lineal;
	pose->velLineal = delta_lineal/delta_time_s;
	pose->velMotorL = pose->left_distance_mm / delta_time_s;
	pose->velMotorR = pose->right_distance_mm / delta_time_s;

	float delta_angular = (pose->right_distance_mm - pose->left_distance_mm) / BASE_WHEEL_MM;
	pose->velAngular = delta_angular / delta_time_s;

	pose->theta += delta_angular;
	//if (pose->theta > PI) pose->theta -= 2.0 * M_PI;
	//else if (pose->theta < -M_PI) pose->theta += 2.0 * M_PI;

}

void ades_odometria_reset (Pose* pose){
	pose->x = 0.0;
	pose->y = 0.0;
	pose->theta = 0.0;
	pose->velMotorL = 0.0;
	pose->velMotorR = 0.0;
	pose->velLineal = 0.0;
	pose->velAngular = 0.0;
	pose->avanceLineal = 0.0;
	pose->left_distance_mm = 0.0;
	pose->right_distance_mm = 0.0;
	pose->left_distance_mm_acum = 0.0;
	pose->right_distance_mm_acum = 0.0;

}
