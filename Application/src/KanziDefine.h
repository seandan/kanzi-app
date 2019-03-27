/*
 * KanziDefine.h
 *
 *  Created on: 2016-9-12
 *      Author: admin
 */

#ifndef KANZIDEFINE_H_
#define KANZIDEFINE_H_

//UI刷新间隔
#define		UIRenewInterval		20
/*****************************************************Prefabs********************************************************/
//菜单页面模板
#define	Prefabs_MenuPage	"kzb://car/Prefabs/Menu"
//胎压页面模板
#define	Prefabs_TpmsPage	"kzb://car/Prefabs/TyrePressure"
//高级辅助驾驶页面模板
#define	Prefabs_Adas		"kzb://car/Prefabs/Adas"
//汽车设定页面模板
#define	Prefabs_Carsettings	"kzb://car/Prefabs/CarSettings"
//行车记录仪模板
#define Prefabs_CarDV		"kzb://car/Prefabs/pgCarDV"

//行车记录仪 setting
#define Prefabs_CarDVSeting		"kzb://car/Prefabs/pgCarDVSetting"

//行车记录仪 replay
#define Prefabs_CarDVReplay		"kzb://car/Prefabs/pgRePlay"

//行车记录仪 replay setting
#define Prefabs_CarDVReplaySetting		"kzb://car/Prefabs/pgReplaySetting"

//行车记录仪 photo mode
#define Prefabs_CarDVPhotoMode		"kzb://car/Prefabs/pgCarDVPhoto"


/*****************************************************Page********************************************************/
//菜单页面名字
#define	PageName_Menu			"MenuPage"
//胎压监测页面名字
#define	PageName_Tpms			"TpmsPage"
//高级辅助驾驶页面名字
#define	PageName_Adas			"AdasPage"
//汽车设定页面名字
#define	PageName_Carsettings	"CarsettingsPage"
//行车记录仪默认页面
#define PageNameCarDV			"CarDVDefault"
#define PageNameCarDVSeting		"CarDVSetting"
#define PageNameCarReplay		"CarDVReplay"
#define PageNameCarReplaySetting	"CarDVReplaySetting"
#define PageNameCarPhotoMode	"CarDVPhotoMode"

/*****************************************************kzb url********************************************************/
//root page
#define	KzkUrl_RootPage	"#RootPage"
#define	BUTTON_BACK		"#back_button"
#define	LIST_NORMAL		"#List"

#define	SLIDER			"#slider"
#define	CARSETTINGDATA	"#CarsettingsData"

#define	CarSetting_CW_POP_ACK	"Ack"

#define	MENU_PAGE_CARCODER		"CarCoder"
#define	MENU_PAGE_TPMS			"Tpms"
#define	MENU_PAGE_CARSETTINGS	"CarSettings"
#define	MENU_PAGE_ADAS			"Adas"
#define	MENU_PAGE_BACK			"back_button"

#define	TPMS_PAGE_BACK			"back_button"
#define	TPMS_PAGE_DATA			"#TpmsData"
#define TPMS_PAGE_POPTIPS_BTN	"#pop"
#define TPMS_PAGE_ALL_TIPS_TXTBLCOK	"#allTips"

#define CARSETTINGS_PAGE_CW			"CW"
#define CARSETTINGS_PAGE_CNZM			"CNZM"
#define	CARSETTINGS_PAGE_CW_ACK		"Ack"
#define	CARSETTINGS_PAGE_TIPS_VOLUME_ACK		"tipsVolume_Ack"
#define	CARSETTINGS_PAGE_LOCK_ACK	"auto_lock_ack"
#define	CARSETTINGS_PAGE_TIPS_VOLUME	"tips_volume"
#define	CARSETTINGS_PAGE_SWITCH_FZD		"switch_fzd"
#define	CARSETTINGS_PAGE_SWITCH_ZDJC	"switch_zdjc"
#define	CARSETTINGS_PAGE_REARVIEW_FOLD	"rearview_fold"
#define	CARSETTINGS_PAGE_BACK			"back_button"
#define	CARSETTINGS_PAGE_CW_POPLIST		"#tralist"
#define	CARSETTINGS_PAGE_LOCK_POPLIST	"#tralist_autolock"

#define CAR_DV_PAGE_BTN_BACK			"back_button"
#define CAR_DV_PAGE_BTN_PLAYBACKMODE			"btnPlayBackMode"
#define CAR_DV_PAGE_BTN_PHOTOMODE			"btnPhotoMode"
#define CAR_DV_PAGE_BTN_SETTING			"btnSetting"
#define CAR_DV_PAGE_DATA_NODE			"#dataNode"
#define CAR_DV_PAGE_SELECTMODE			"#lyModeSelect"
#define CAR_DV_PAGE_BTN_BACKACCEPT		"btnBackAccept"
#define CAR_DV_PAGE_BTN_IS_LOCK			"btnIsLock"
#define CAR_DV_PAGE_BTN_START			"btnStart"
#define CAR_DV_PAGE_BTN_MUTE			"btnMute"

#define CAR_DV_REPLAY_BTN_EDIT			"btnEdit"
#define CAR_DV_REPLAY_BTN_NEXT			"btnNext"
#define CAR_DV_REPLAY_BTN_PRE			"btnPre"
#define CAR_DV_REPLAY_BTN_LOCK			"btnLock"
#define CAR_DV_REPLAY_BTN_PLAYPAUSE		"btnPlayPause"

#define CAR_DV_REPLAY_SET_BTN_LOCKALL		"ListItemLockAll"
#define CAR_DV_REPLAY_SET_BTN_UNLOCKALL		"ListItemUnLockAll"
#define CAR_DV_REPLAY_SET_BTN_DELCUR		"ListItemDelCur"
#define CAR_DV_REPLAY_SET_BTN_DELALL		"ListItemDelAll"
#define CAR_DV_REPLAY_SET_POP_DEL			"#popDeleteFile"
#define CAR_DV_REPLAY_SET_POP_TOAST			"#popToastTips"

#define CAR_DV_PHOTO_BTN_SHOOT			"btnShoot"

#define	ADAS_PAGE_LDWS					"ldws"///<车道偏离系统
#define ADAS_PAGE_BSMS					"bsms"///<盲点监测系统
#define ADAS_PAGE_PRS					"prs"///<行人识别系统
#define	ADAS_PAGE_BACK					"back_button"
#define	ADAS_PAGE_DATA					"#AdasData"
#define ADAS_MAIN_LIST					"#Adas_MainList"
/*****************************************************property name***************************************************/
//list index
#define	PropertyName_ListIndex	"listindex"

#define		StrPropertyTime		"title_bar_time"
#define		StrPropertyTimeMode "title_bar_time_mode"

#define		MainMenuBackButton "#MenuBackButton"

#define		BoolPropertyIsQuadView	"isQuadView"
#define		IntPropertyHud	"hud"
#define		IntPropertyCwDelay	"delay_cw"
#define		IntPropertyCnDelay	"delay_cn"
#define		IntPropertySpeedLock	"lock_level"		//自动车速锁
#define		IntPropertyTipsVolume	"tip_volume"
#define		IntPropertyTipsVolumeValue	"tip_volume_level"
#define		IntPropertyLocateLight		"locate_lighting"
#define		IntPropertyAutoWindow		"auto_window"
#define		IntPropertyRearviewMirrorFold	"rearview_fold"

#define		IntPropertySwitchFZD	"switch_FZD"
#define		IntPropertySwitchZDJC	"switch_ZDJC"
#define		IntPropertyLightDelayInner	"delay_cw_inner"

#define		IntPropertyKeyState				"KeyState"
#define		IntPropertySelfCheck			"SelfCheck"
#define		IntPropertyBLPressure			"BLPressure"
#define		IntPropertyBLTemperature		"BLTemperature"
#define		IntPropertyBLTemperatureWarm	"TyreTempWarmLB"
#define		IntPropertyBLPressureWarm		"TyrePressureWarmLB"

#define		IntPropertyBRPressure			"BRPressure"
#define		IntPropertyBRTemperature		"BRTemperature"
#define		IntPropertyBRTemperatureWarm	"TyreTempWarmRB"
#define		IntPropertyBRPressureWarm		"TyrePressureWarmRB"

#define		IntPropertyFLPressure			"FLPressure"
#define		IntPropertyFLTemperature		"FLTemperature"
#define		IntPropertyFLTemperatureWarm	"TyreTempWarmLF"
#define		IntPropertyFLPressureWarm		"TyrePressureWarmLF"

#define		IntPropertyFRPressure			"FRPressure"
#define		IntPropertyFRTemperature		"FRTemperature"
#define		IntPropertyFRTemperatureWarm	"TyreTempWarmRF"
#define		IntPropertyFRPressureWarm		"TyrePressureWarmRF"
#define		FLOATPropertyCarSpeed			"CarSpeed"



/*****************************************************list index***************************************************/


/********************************************************alias*****************************************************/


#endif /* KANZIDEFINE_H_ */
