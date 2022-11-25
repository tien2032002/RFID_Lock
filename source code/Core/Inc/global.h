/*
 * global.h
 *
 *  Created on: Oct 29, 2022
 *      Author: Administrator
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

//trang thai
#define INIT		0 //khoi tao
#define LOCK		1 //cua dong
#define UNLOCK		2 //cua mo
#define WRONG1		3 //sai lan 1
#define WRONG2		4 //sai lan 2
#define ALARM		5 //hu coi
#define REG_PROCESS	6 //xu li the gan nhat
#define MEM_DELETE	7 //xoa bo nho

//
#define BUZZER_TIME 500

extern uint8_t CARD_BUF[5];


#endif /* INC_GLOBAL_H_ */
