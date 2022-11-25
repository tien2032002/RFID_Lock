/*
 * fsm.c
 *
 *  Created on: Nov 11, 2022
 *      Author: Acer
 */

#include "global.h"
#include "fsm.h"
#include "button.h"
#include "software_timer.h"
#include "main.h"
#include "memory_struct.h"



int state=INIT;
int admin_id;

void fsm_run() {
	switch (state) {
	case INIT:
		//quet the admin va luu vao bo nho
		//sau khi co the duoc quet , thay doi state
		//admin_id=reader();
		if (flagForButtonPress[REG_IDX]==1) {
			flagForButtonPress[REG_IDX]=0;
			if (equalZero(CARD_BUF)==0) {
				set_admin(CARD_BUF);
				state=UNLOCK;
			}

		}
		break;
	case UNLOCK:
		//dua ra tin hieu mo cua
		HAL_GPIO_WritePin(LOCK_SIGNAL_GPIO_Port, LOCK_SIGNAL_Pin, GPIO_PIN_SET);

		//neu bam nut dong cua, qua trang thai dong cua
		if (flagForButtonPress[LOCK_IDX]==1) {
			flagForButtonPress[LOCK_IDX]=0;
			state=LOCK;
		}
		//bam nut dang ki the de qua trang thai dang ki the
		if (flagForButtonPress[REG_IDX]==1)  {
			flagForButtonPress[REG_IDX]=0;
			state=REG_PROCESS;
		}
		//bam nut reset de qua trang thai xoa bo nho
		if (flagForButtonPress[RESET_IDX]==1) {
			flagForButtonPress[RESET_IDX]=0;
			state=MEM_DELETE;
		}

		//quet the
		if (search(CARD_BUF)==1) {
			state=LOCK;
		}
		/*if (the duoc quet da duoc dang ki) {
			state=LOCK;
		}*/
		break;
	case LOCK:
		//dua ra tin hieu dong cua
		HAL_GPIO_WritePin(LOCK_SIGNAL_GPIO_Port, LOCK_SIGNAL_Pin, GPIO_PIN_SET);

		//neu bam nut mo cua, qua trang thai mo cua
		if (flagForButtonPress[UNLOCK_IDX]==1) {
			flagForButtonPress[UNLOCK_IDX]=0;
			state=UNLOCK;
		}
		//quet the
		if (search(CARD_BUF)==1) {
			state=UNLOCK;
		}
		else state=WRONG1;
		/*if (the duoc quet da duoc dang ki) {
			state=UNLOCK;
		}

		else {
			state=WRONG1;
		}*/
		break;
	case WRONG1:
		//quet the
		/*if (the duoc quet da duoc dang ki) {
			state=UNLOCK;
		}
		else {
			state=WRONG2;
		}*/
		break;
	case WRONG2:
		//quet the
		/*if (the duoc quet da duoc dang ki) {
			state=UNLOCK;
		}
		else {
			state=ALARM;
			setTimer1(500);
		}*/
		break;
	case ALARM:
		HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, GPIO_PIN_SET);
		//quet the
		/*if (the duoc quet da duoc dang ki) {
			state=UNLOCK;
		}
		else {
			state=ALARM;
		}*/
		if (timer1_flag==1) {
			timer1_flag=0;
			state=WRONG2;
		}
		break;
	case MEM_DELETE:
		//Trong 5s k lam gi se tro ve trang thai UNLOCK
		//Neu the duoc quet vao la the admin, sau do an nut RESET se xoa bo nho
		//Neu the duoc quet khong phai the admin, tro ve trang thai UNLOCK
		break;
	case REG_PROCESS:
		//Trong 5s k lam gi se tro ve trang thai UNLOCK
		//Neu the duoc quet khong phai the admin, tro ve trang thai UNLOCK
		//Neu the duoc quet vao la the admin, sau do quet the can dang ki vao, an nut REGISTER se luu the vua quet vao bo nho
		break;
	default:
		break;
	}
}
