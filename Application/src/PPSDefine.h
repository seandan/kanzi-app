/*
 * PPSDefine.h
 *
 *  Created on: 2016-9-18
 *      Author: admin
 */

#ifndef PPSDEFINE_H_
#define PPSDEFINE_H_

#define	 PPS_CANINFO "/pps/coagent/mcu/can?delta"
#define	 PPS_BCMSET "/pps/coagent/mcu/bcmset"
#define	 PPS_BCMRES "/pps/coagent/mcu/bcmres"

#define	 PPS_MCU "/pps/coagent/mcu/.all?delta"
#define	 PPS_MCU2 "/pps/coagent/mcu/tmps?delta"

#define	 PPS_AVM_SET "/pps/coagent/mcu/avmset"
#define	 PPS_AVM_RES "/pps/coagent/mcu/avmres"
//bcmset
#define		PPS_ATTR_LIGHTDELAY		"lightdelayout"
#define		PPS_ATTR_REARMIRRORFOLD	"rearmirrorfold"
#define		PPS_ATTR_SPEEDLOCK		"speedlock"
#define		PPS_ATTR_TIPSVOLUME		"hornalert"

#define 	PPS_ATTR_FZD			"assistillumina"
#define 	PPS_ATTR_ZDJC			"winremotautodown"
#define 	PPS_ATTR_TIPS_VAL		"hornalertvolume"
#define		PPS_ATTR_LIGHTDELAYINNER	"lightdelayin"

//bcmset write
#define		PPS_ATTR_LIGHTDELAY_INNER_CTL		"lightdelayinset"
#define		PPS_ATTR_LIGHTDELAY_CTL		"lightdelayoutset"
#define		PPS_ATTR_REARMIRRORFOLD_CTL	"rearmirautofoldset"
#define		PPS_ATTR_FZD_CTL			"assistilluminaset"
#define		PPS_ATTR_ZDJC_CTL			"winremotautodownset"
#define		PPS_ATTR_SPEEDLOCK_CTL		"speedlockset"
#define		PPS_ATTR_TIPSVOLUME_CTL		"hornalertstateset"
#define		PPS_ATTR_TIPSVOLUME_VAL_CTL		"hornalertvolumeset"

//tpms
#define		PPS_ATTR_KEY_STATE		"KeyState"
#define		PPS_ATTR_SELFCHECK		"selfchecking"//"SelfCheck"
#define		PPS_ATTR_TEMP			"temperature"
#define		PPS_ATTR_PRESSURE		"pressure"
#define		PPS_ATTR_TEMPWARM		"temperaturewarn"
#define		PPS_ATTR_PRESSUREWARM	"pressurewarn"

//高级辅助驾驶
#define		PPS_ADDR_BLINDDE_SET		"bsdsysswitch"//盲点检测
#define		PPS_ADDR_DORSYS_SET			"ldwswitch"//车道偏离系统
#define		PPS_LANEDEPARTURE_SET	    "modsysswitch"//行人识别

#define		PPS_ADDR_BLINDDE		"bsdopstatus"//盲点检测
#define		PPS_ADDR_DORSYS			"ldwopstatus"//车道偏离系统
#define		PPS_LANEDEPARTURE	    "modopstatus"//行人识别

#define		PPS_BSD_STATUS_ON		0x03
#define		PPS_LDW_STATUS_ON		0x03
#define		PPS_MOD_STATUS_ON		0x01

#endif /* PPSDEFINE_H_ */
