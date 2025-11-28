/*
 * ades_odometria.h
 *
 *  Created on: Oct 27, 2025
 *      Author: jandr
 */

#ifndef INC_ADES_ODOMETRIA_H_
#define INC_ADES_ODOMETRIA_H_

#include "main.h"

#define PI 3.1416
#define RADIO 16.65
#define PULSOS 710
#define M_PI 1.5708
#define BASE_WHEEL_MM 85.0

typedef struct {
float x; // Posición en X (mm)
float y; // Posición en Y (mm)
float theta; // Orientación (rad)
float velMotorL; // Velocidad Motor Izquierdo (mm/s)
float velMotorR; // Velocidad Motor Derecho (mm/s)
float velLineal; // Velocidad lineal del robot (mm/s)
float velAngular; // Velocidad angular del robot (rad/s)
float avanceLineal; // Avance acumulado en línea recta
float left_distance_mm; // Distancia recorrida por la rueda izquierda
float right_distance_mm; // Distancia recorrida por la rueda derecha
float left_distance_mm_acum; // Acumulado de distancia izquierda
float right_distance_mm_acum; // Acumulado de distancia derecha
int16_t left_last_pulses;
int16_t right_last_pulses;
float d1;
float d4;
} Pose;


void updatePose (int16_t left_pulses, int16_t right_pulses, float delta_time_ms, Pose* pose);

void ades_odometria_reset (Pose* pose);


#endif /* INC_ADES_ODOMETRIA_H_ */
