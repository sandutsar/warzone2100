/*
 * Text.c (was Strings.c)
 *
 * String management functions
 */

#include "lib/framework/frame.h"
#include "lib/framework/strres.h"
#include "text.h"

/* The numbers of strings that will be loaded */
#define STRING_INIT		20
#define STRING_EXT		5

/* The fixed id buffer for the string resource system
 * This just tells it what the keywords are for the fixed strings
 */
STR_ID asFixedID[STR_MAX_ID] =
{
	// Default string
	{STR_DEFAULT,				"DEFAULT"},

	// Reticule strings
	{STR_RET_OPTIONS,			"RET_OPTIONS"},
	{STR_RET_INTELLIGENCE,		"RET_INTELLIGENCE"},
	{STR_RET_MANUFACTURE,		"RET_MANUFACTURE"},
	{STR_RET_DESIGN,				"RET_DESIGN"},
	{STR_RET_RESEARCH,			"RET_RESEARCH"},
	{STR_RET_BUILD,				"RET_BUILD"},
	{STR_RET_CLOSE,				"RET_CLOSE"},
	{STR_RET_COMMAND,			"RET_COMMAND"},

	// Miscellaneous strings
	{STR_MISC_CLOSE,				"MISC_CLOSE"},
	{STR_MISC_LOADGAME,			"MISC_LOADGAME"},
	{STR_MISC_SAVEGAME,			"MISC_SAVEGAME"},
	{STR_MISC_QUIT,				"MISC_QUIT"},
	{STR_MISC_PAUSED,			"MISC_PAUSED"},

	// Design screen strings
	{STR_DES_NEWVEH,					"DES_NEWVEH"},
	{STR_DES_STORE,					"DES_STORE"},
	{STR_DES_CANCEL,					"DES_CANCEL"},
	{STR_DES_DEL,					"DES_DEL"},
	{STR_DES_NEW,					"DES_NEW"},
	{STR_DES_ARMOUR_KIN,				"DES_ARMOUR_KIN"},
	{STR_DES_ARMOUR_HEAT,			"DES_ARMOUR_HEAT"},
	{STR_DES_POWER,					"DES_POWER"},
	{STR_DES_WEIGHT,					"DES_WEIGHT"},
	{STR_DES_POWERUSE,				"DES_POWERUSE"},
	{STR_DES_SENSOR_RANGE,			"DES_SENSOR_RANGE"},
	{STR_DES_SENSOR_POWER,			"DES_SENSOR_POWER"},
	{STR_DES_ECM_POWER,				"DES_ECM_POWER"},
	{STR_DES_BUILD_POINTS,			"DES_BUILD_POINTS"},
	{STR_DES_RANGE,					"DES_RANGE"},
	{STR_DES_DAMAGE,					"DES_DAMAGE"},
	{STR_DES_ROF,					"DES_ROF"},
	{STR_DES_AIR,					"DES_AIR"},
	{STR_DES_ROAD,					"DES_ROAD"},
	{STR_DES_OFFROAD,				"DES_OFFROAD"},
	{STR_DES_WATER,					"DES_WATER"},
	{STR_DES_WEAPONS,				"DES_WEAPONS"},
	{STR_DES_OTHER,					"DES_OTHER"},
	{STR_DES_COMMAND,				"DES_COMMAND"},
	{STR_DES_BODY,					"DES_BODY"},
	{STR_DES_PROPULSION,				"DES_PROPULSION"},
	{STR_DES_TURRET,					"DES_TURRET"},
	{STR_DES_TEMPPOWER,				"DES_TEMPPOWER"},
	{STR_DES_TEMPBODY,				"DES_TEMPBODY"},

	// Other interface strings
	{STR_INT_BLDPROGRESS,			"INT_BLDPROGRESS"},
	{STR_INT_BLDSPEED,				"INT_BLDSPEED"},
	{STR_INT_PWRUSAGE,				"INT_PWRUSAGE"},
	{STR_INT_RESMESSAGE,				"INT_RESMESSAGE"},
	{STR_INT_GENMESSAGE,				"INT_GENMESSAGE"},
	{STR_INT_MISMESSAGE,				"INT_MISMESSAGE"},
        {STR_INT_RESCOMPLETED,                            "INT_RESCOMPLETED"},
	{STR_INT_TRANSPORTER,			"INT_TRANSPORTER"},
	{STR_INT_TRANSLAUNCH,			"INT_TRANSLAUNCH"},
	{STR_INT_DPOINT,					"INT_DPOINT"},
	{STR_INT_LOOP,					"INT_LOOP"},
	{STR_INT_POWERACCRUED,			"INT_POWERACCRUED"},
	{STR_INT_POWER,		            "INT_POWER"},


	// multiplayer strings
	{STR_MUL_PHONENO,				"MUL_PHONENO"},
	{STR_MUL_IPADDR,					"MUL_IPADDR"},
	{STR_MUL_COM1,					"MUL_COM1"},
	{STR_MUL_COM2,					"MUL_COM2"},
	{STR_MUL_COM3,					"MUL_COM3"},
	{STR_MUL_COM4,					"MUL_COM4"},
	{STR_MUL_CANCEL,					"MUL_CANCEL"},
	{STR_MUL_OK,						"MUL_OK"},
	{STR_MUL_PLAYER,					"MUL_PLAYER"},
	{STR_MUL_GAME,					"MUL_GAME"},
	{STR_MUL_MAXPLAY,				"MUL_MAXPLAY"},
	{STR_MUL_ARENA,					"MUL_ARENA"},
	{STR_MUL_CAMPAIGN,				"MUL_CAMPAIGN"},
	{STR_MUL_REFRESH,				"MUL_REFRESH"},
	{STR_MUL_HOST,					"MUL_HOST"},
	{STR_MUL_CLEAR,					"MUL_CLEAR"},
	{STR_MUL_DEFAULT,				"MUL_DEFAULT"},
	{STR_MUL_LOAD,					"MUL_LOAD"},
	{STR_MUL_SAVE,					"MUL_SAVE"},
	{STR_MUL_DESIGN,					"MUL_DESIGN"},
	{STR_MUL_SEARCHING,				"MUL_SEARCHING"},
	{STR_MUL_14400,						"MUL_14400"},
	{STR_MUL_19200,						"MUL_19200"},
	{STR_MUL_56000,						"MUL_56000"},
	{STR_MUL_115200,						"MUL_115200"},
	{STR_MUL_SIDECONNECTION,				"MUL_SIDECONNECTION"},
	{STR_MUL_SIDEOPTIONS	,				"MUL_SIDEOPTIONS"},
	{STR_MUL_SIDEGAMES	,				"MUL_SIDEGAMES"},
	{STR_MUL_SIDEPLAYERS	,				"MUL_SIDEPLAYERS"},
	{STR_MUL_SIDEFORCE,					"MUL_SIDEFORCE"},
	{STR_MUL_SIDETEMPLATES,				"MUL_SIDETEMPLATES"},
	{STR_MUL_SIDEINFO,					"MUL_SIDEINFO"},

	{STR_MUL_CHAT,			"MUL_CHAT"},
	{STR_MUL_STARTING,		"MUL_STARTING"},
	{STR_MUL_ALLIANCES,		"MUL_ALLIANCES"},
	{STR_MUL_SCORE,			"MUL_SCORE"},
	{STR_MUL_KILLS,			"MUL_KILLS"},
	{STR_MUL_PING,			"MUL_PING"},
	{STR_MUL_POWLO,			"MUL_POWLO"},
	{STR_MUL_POWMED,			"MUL_POWMED"},
	{STR_MUL_POWHI,			"MUL_POWHI"},
	{STR_MUL_TECH1,			"MUL_TECH1"},
	{STR_MUL_TECH2,			"MUL_TECH2"},
	{STR_MUL_TECH3,			"MUL_TECH3"},
	{STR_MUL_CAMPCLEAN,		"MUL_CAMPCLEAN"},
	{STR_MUL_CAMPDEFENCE,		"MUL_CAMPDEFENCE"},
	{STR_MUL_CAMPBASE,		"MUL_CAMPBASE"},
	{STR_MUL_PLAYERIC,		"MUL_PLAYERIC"},
	{STR_MUL_FORCEIC,		"MUL_FORCEIC"},
	{STR_MUL_MAPIC,			"MUL_MAPIC"},
	{STR_MUL_GAMEIC,			"MUL_GAMEIC"},
	{STR_MUL_ALLIANCEN,		"MUL_ALLIANCEN"},
	{STR_MUL_ALLIANCEY,		"MUL_ALLIANCEY"},
	{STR_MUL_ALLIANCEAI,	"MUL_ALLIANCEAI"},
	{STR_MUL_NOLIM,			"MUL_NOLIM"},
	{STR_MUL_TIMELIM,		"MUL_TIMELIM"},
	{STR_MUL_FRAGLIM,		"MUL_FRAGLIM"},
	{STR_CON_MODEM,			"CON_MODEM"},
	{STR_CON_INTERNET,		"CON_INTERNET"},
	{STR_CON_LAN	,			"CON_LAN"},
	{STR_CON_CABLE,			"CON_CABLE"},
	{STR_CON_MORE,			"CON_MORE"},
	{STR_GAMES_GAMES,		"GAMES_GAMES"},
	{STR_LABEL_TYPE	,		"LABEL_TYPE"},
	{STR_LABEL_ALLI,			"LABEL_ALLI"},
	{STR_LABEL_TEC,			"LABEL_TEC"},
	{STR_LABEL_BASE,			"LABEL_BASE"},
	{STR_LABEL_LIMIT,		"LABEL_LIMIT"},
	{STR_LABEL_FOG,			"LABEL_FOG"},
	{STR_MUL_PLAYERS,		"MUL_PLAYERS"},
	{STR_MUL_PLAY,			"MUL_PLAY"},

	{STR_MUL_COMP,			"MUL_COMP"},
	{STR_MUL_COMP_Y,			"MUL_COMP_Y"},
	{STR_MUL_COMP_N,			"MUL_COMP_N"},
	{STR_MUL_STRLIM,			"MUL_STRLIM"},
	{STR_MUL_SKIRMISH,		"MUL_SKIRMISH"},
	{STR_MUL_TEAMPLAY,		"MUL_TEAMPLAY"},
	{STR_MUL_FOG_ON,			"MUL_FOG_ON"},
	{STR_MUL_FOG_OFF,		"MUL_FOG_OFF"},

	{STR_ALLI_STATE,			"ALLI_STATE"},
	{STR_ALLI_VIS,			"ALLI_VIS"},
	{STR_ALLI_TEC,			"ALLI_TEC"},
	{STR_ALLI_DRO,			"ALLI_DRO"},
	{STR_ALLI_POW,			"ALLI_POW"},
	{STR_ALLI_REQ,			"ALLI_REQ"},
	{STR_ALLI_OFF,			"ALLI_OFF"},
	{STR_ALLI_BRK,			"ALLI_BRK"},
	{STR_ALLI_FRM,			"ALLI_FRM"},

	{STR_GIFT_VIS,			"GIFT_VIS"},
	{STR_GIFT_DRO,			"GIFT_DRO"},
	{STR_GIFT_TEC,			"GIFT_TEC"},
	{STR_GIFT_POW,			"GIFT_POW"},

	{STR_MUL_ARTIF,			"MUL_ARTIF"},

	{STR_COMPATIBLE,			"COMPATIBLE"},
	{STR_PLAYER_NAME,		"PLAYER_NAME"},
	{STR_GAME_NAME,			"GAME_NAME"},

	//In Game Options
	{STR_GAME_QUIT,			"GAME_QUIT"},
	{STR_GAME_RESUME,		"GAME_RESUME"},

	// FrontEnd STrings
	{STR_FE_SIDEMAIN ,					"FE_SIDEMAIN"},
	{STR_FE_SINGLE ,						"FE_SINGLE"},
	{STR_FE_MULTI ,						"FE_MULTI"},
	{STR_FE_OPTIONS,						"FE_OPTIONS"},
	{STR_FE_INTRO,						"FE_INTRO"},
	{STR_FE_QUIT	,						"FE_QUIT"},
	{STR_FE_SIDESINGLE1,					"FE_SIDESINGLE1"},
	{STR_FE_SIDESINGLE2,					"FE_SIDESINGLE2"},
	{STR_FE_SIDETUT,						"FE_SIDETUT"},
	{STR_FE_NEW ,						"FE_NEW"},
	{STR_FE_LOAD,						"FE_LOAD"},
	{STR_FE_TUT,							"FE_TUT"},
	{STR_FE_FASTPLAY,					"FE_FASTPLAY"},
	{STR_FE_RETURN ,						"FE_RETURN"},
	{STR_FE_SIDEMULTI,					"FE_SIDEMULTI"},
	{STR_FE_HOST	,						"FE_HOST"},
	{STR_FE_JOIN ,						"FE_JOIN"},
	{STR_FE_FORCEEDIT,					"FE_FORCEEDIT"},
	{STR_FE_SKIRMISH,					"FE_SKIRMISH"},
	{STR_FE_SIDEOPTIONS,					"FE_SIDEOPTIONS"},
	{STR_FE_MOUSE,						"FE_MOUSE"},
	{STR_FE_SCROLL,						"FE_SCROLL"},
	{STR_FE_GAMMA,						"FE_GAMMA"},
	{STR_FE_FX,						"FE_FX"},
	{STR_FE_3D_FX,						"FE_3D_FX"},
	{STR_FE_MUSIC,						"FE_MUSIC"},
	{STR_FE_CLAN,						"FE_CLAN"},
	{STR_FE_CRAPFOG,					"FE_CRAPFOG"},
	{STR_FE_GOODFOG,					"FE_GOODFOG"},

	{STR_FE_VIDEO,						"FE_VIDEO"},
	{STR_FE_SOFTWARE,					"FE_SOFTWARE"},
	{STR_FE_DIRECTX,						"FE_DIRECTX"},
	{STR_FE_OPENGL,						"FE_OPENGL"},
	{STR_FE_GLIDE,						"FE_GLIDE"},
	{STR_FE_GAME,						"FE_GAME"},
	{STR_FE_GRAPHICS,					"FE_GRAPHICS"},
	{STR_FE_AUDIO,						"FE_AUDIO"},
	{STR_FE_TEXTURE,						"FE_TEXTURE"},
	{STR_FE_EFFECTS,						"FE_EFFECTS"},
	{STR_FE_FOG,							"FE_FOG"},
	{STR_FE_TRANSPARENCY,				"FE_TRANSPARENCY"},

	{STR_FE_DIFFICULTY,					"FE_DIFFICULTY"},
	{STR_EASY,							"EASY"},
	{STR_NORMAL,							"NORMAL"},
	{STR_HARD,							"HARD"},



	// Ingame MultiPlayer Announcements.
	{STR_MUL_LEAVE,						"MUL_LEAVE"},
	{STR_MUL_JOINING,					"MUL_JOINING"},
	{STR_MUL_RESPOND,					"MUL_RESPOND"},


	// Droid order screen.
	{STR_DORD_RANGE1,					"DORD_RANGE1"},
	{STR_DORD_RANGE2,					"DORD_RANGE2"},
	{STR_DORD_RANGE3,					"DORD_RANGE3"},
	{STR_DORD_REPAIR1,					"DORD_REPAIR1"},
	{STR_DORD_REPAIR2,					"DORD_REPAIR2"},
	{STR_DORD_REPAIR3,					"DORD_REPAIR3"},
	{STR_DORD_FIRE1,						"DORD_FIRE1"},
	{STR_DORD_FIRE2,						"DORD_FIRE2"},
	{STR_DORD_FIRE3,						"DORD_FIRE3"},
	{STR_DORD_PATROL,					"DORD_PATROL"},
	{STR_DORD_PERSUE,					"DORD_PERSUE"},
	{STR_DORD_GUARD,						"DORD_GUARD"},
	{STR_DORD_HOLDPOS,					"DORD_HOLDPOS"},
	{STR_DORD_RETREPAIR,					"DORD_RETREPAIR"},
	{STR_DORD_RETBASE,					"DORD_RETBASE"},
	{STR_DORD_EMBARK,					"DORD_EMBARK"},
	{STR_DORD_ARMRECYCLE,				"DORD_ARMRECYCLE"},
	{STR_DORD_RECYCLE,					"DORD_RECYCLE"},
	{STR_DORD_FACTORY,					"DORD_FACTORY"},

	{STR_GAM_DERRICK,					"GAM_DERRICK"},
	{STR_GAM_DROIDSTATE,					"GAM_DROIDSTATE"},
	{STR_GAM_UNITLOST,					"GAM_UNITLOST"},
	{STR_GAM_NORTH,						"GAM_NORTH"},
	{STR_GAM_ENERGY,						"GAM_ENERGY"},
	{STR_GAM_RESREM,						"GAM_RESREM"},
	{STR_GAM_POWCON,						"GAM_POWCON"},
	{STR_GAM_STRDAM,						"GAM_STRDAM"},
	{STR_GAM_ELECDAM,					"GAM_ELECDAM"},
	{STR_GAM_STRREST,					"GAM_STRREST"},
	{STR_GAM_GOHQ,						"GAM_GOHQ"},
	{STR_GAM_NOHQ,						"GAM_NOHQ"},
	{STR_GAM_RESREWARD,					"GAM_RESREWARD"},
	{STR_GAM_UNITSEL,					"GAM_UNITSEL"},
	{STR_GAM_REINF,						"GAM_REINF"},
	{STR_GAM_GAMEOVER,					"GAM_GAMEOVER"},
	{STR_GAM_JOINING,					"GAM_JOINING"},
	{STR_GAM_REWELEC,					"GAM_REWELEC"},
	{STR_GAM_REWPROP,					"GAM_REWPROP"},
	{STR_GAM_REWBODY,					"GAM_REWBODY"},
	{STR_GAM_REWWEAP,					"GAM_REWWEAP"},
	{STR_GAM_REWNOWT,					"GAM_REWNOWT"},
	{STR_GAM_REWREPA,					"GAM_REWREPA"},
	{STR_GAM_REWREPN,					"GAM_REWREPN"},
	{STR_GAM_RESNOTFOUND,				"GAM_RESNOTFOUND"},
	{STR_GAM_REPNOTFOUND,				"GAM_REPNOTFOUND"},
	{STR_GP_SELECTED,					"GP_SELECTED"},
	{STR_GP_ASSIGNED,					"GP_ASSIGNED"},
	{STR_GP_CENTERED,					"GP_CENTERED"},
	{STR_GP_ALLIGN, 						"GP_ALLIGN"},
	{STR_MR_OBJECTIVE_ACHIEVED,			"MR_OBJECTIVE_ACHIEVED"},
	{STR_MR_OBJECTIVE_FAILED,		 	"MR_OBJECTIVE_FAILED"},
	{STR_MR_SAVE_GAME,			 		"MR_SAVE_GAME"},
	{STR_MR_LOAD_GAME,			 		"MR_LOAD_GAME"},
	{STR_MR_QUIT_TO_MAIN,			 	"MR_QUIT_TO_MAIN"},
	{STR_MR_CONTINUE,				 	"MR_CONTINUE"},
	{STR_MR_UNIT_LOSSES,					"MR_UNIT_LOSSES"},
	{STR_MR_STRUCTURE_LOSSES,			"MR_STRUCTURE_LOSSES"},
	{STR_MR_FORCE_INFO,					"MR_FORCE_INFO"},
	{STR_MR_RANKINGS,					"MR_RANKINGS"},


	{STR_MR_UNITS_BUILT,		 			"MR_UNITS_BUILT"},
	{STR_MR_UNITS_KILLED,	   			"MR_UNITS_KILLED"},
	{STR_MR_UNITS_LOST,		 			"MR_UNITS_LOST"},
	{STR_MR_UNITS_NOW,		 			"MR_UNITS_NOW"},
	{STR_MR_AV_UNIT_EL,		 			"MR_AV_UNIT_EL"},
	{STR_MR_STR_BUILT,		 			"MR_STR_BUILT"},
	{STR_MR_STR_BLOWN_UP,	   			"MR_STR_BLOWN_UP"},
	{STR_MR_STR_LOST,		 			"MR_STR_LOST"},
	{STR_MR_STR_NOW,						"MR_STR_NOW"},
	{STR_MR_ARTEFACTS_FOUND,	 			"MR_ARTEFACTS_FOUND"},
	{STR_MR_MISSION_TIME,	   			"MR_MISSION_TIME"},
	{STR_MR_GAME_TIME,					"MR_GAME_TIME"},
	{STR_MR_SHOTS_ON_TARGET,	 			"MR_SHOTS_ON_TARGET"},
	{STR_MR_SHOTS_OFF_TARGET,   			"MR_SHOTS_OFF_TARGET"},
	{STR_MR_BABAS_RUN_OVER,	 			"MR_BABAS_RUN_OVER"},

	{STR_MR_LEVEL_ROOKIE, 			"MR_LEVEL_ROOKIE"},
	{STR_MR_LEVEL_GREEN,	 			"MR_LEVEL_GREEN"},
	{STR_MR_LEVEL_TRAINED, 			"MR_LEVEL_TRAINED"},
	{STR_MR_LEVEL_REGULAR, 			"MR_LEVEL_REGULAR"},
	{STR_MR_LEVEL_PROF,	 			"MR_LEVEL_PROF"},
	{STR_MR_LEVEL_VETERAN, 			"MR_LEVEL_VETERAN"},
	{STR_MR_LEVEL_CRACK,	 			"MR_LEVEL_CRACK"},
	{STR_MR_LEVEL_ELITE,	 			"MR_LEVEL_ELITE"},
	{STR_MR_LEVEL_SPECIAL,	 		"MR_LEVEL_SPECIAL"},
	{STR_MR_LEVEL_ACE,	 			"MR_LEVEL_ACE"},

	{STR_DL_LEVEL_ROOKIE, 			"DL_LEVEL_ROOKIE"},
	{STR_DL_LEVEL_GREEN,	 			"DL_LEVEL_GREEN"},
	{STR_DL_LEVEL_TRAINED,	 		"DL_LEVEL_TRAINED"},
	{STR_DL_LEVEL_REGULAR, 			"DL_LEVEL_REGULAR"},
	{STR_DL_LEVEL_PROF,	 			"DL_LEVEL_PROF"},
	{STR_DL_LEVEL_VETERAN, 			"DL_LEVEL_VETERAN"},
	{STR_DL_LEVEL_CRACK,	 			"DL_LEVEL_CRACK"},
	{STR_DL_LEVEL_ELITE,	 			"DL_LEVEL_ELITE"},
	{STR_DL_LEVEL_SPECIAL, 			"DL_LEVEL_SPECIAL"},
	{STR_DL_LEVEL_ACE,	 			"DL_LEVEL_ACE"},

	{STR_CD_CHANGE,					"CD_CHANGE"},
	{STR_CD_CHANGE_1OR2,				"CD_CHANGE_1OR2"},

	{STR_GAME_REPLAY,				"GAME_REPLAY"},
	{STR_GAME_SAVED,					"GAME_SAVED"},
	{STR_GAME_LOADED,				"GAME_LOADED"},
	{STR_DORD_CYBORG_FACTORY,		"DORD_CYBORG_FACTORY"},
	{STR_GAME_RESTART,				"GAME_RESTART"},


	{STR_GAM_MAXUNITSREACHED,		"GAM_MAXUNITSREACHED"},

	{STR_KM_KEYMAP,					"KM_KEYMAP"},
	{STR_KM_KEYMAP_SIDE,				"KM_KEYMAP_SIDE"},
	{STR_BIND_CHOMAN,				"BIND_CHOMAN"},
	{STR_BIND_CHORES,				"BIND_CHORES"},
	{STR_BIND_CHOBUI,				"BIND_CHOBUI"},
	{STR_BIND_CHODES	,				"BIND_CHODES"},
	{STR_BIND_CHOINT	,				"BIND_CHOINT"},
	{STR_BIND_CHOCOM	,				"BIND_CHOCOM"},
	{STR_BIND_TOGRAD	,				"BIND_TOGRAD"},
	{STR_BIND_TOGCON	,				"BIND_TOGCON"},
	{STR_BIND_BARS	,				"BIND_BARS"},
	{STR_BIND_SHOT,					"BIND_SHOT"},
	{STR_BIND_PAUSE,					"BIND_PAUSE"},
	{STR_BIND_PREV,					"BIND_PREV"},
	{STR_BIND_AS1,					"BIND_AS1"},
	{STR_BIND_AS2,					"BIND_AS2"},
	{STR_BIND_AS3,					"BIND_AS3"},
	{STR_BIND_AS4,					"BIND_AS4"},
	{STR_BIND_AS5,					"BIND_AS5"},
	{STR_BIND_AS6,					"BIND_AS6"},
	{STR_BIND_AS7,					"BIND_AS7"},
	{STR_BIND_AS8,					"BIND_AS8"},
	{STR_BIND_AS9,					"BIND_AS9"},
	{STR_BIND_GR1,					"BIND_GR1"},
	{STR_BIND_GR2,					"BIND_GR2"},
	{STR_BIND_GR3,					"BIND_GR3"},
	{STR_BIND_GR4,					"BIND_GR4"},
	{STR_BIND_GR5,					"BIND_GR5"},
	{STR_BIND_GR6,					"BIND_GR6"},
	{STR_BIND_GR7,					"BIND_GR7"},
	{STR_BIND_GR8,					"BIND_GR8"},
	{STR_BIND_GR9,					"BIND_GR9"},

	{STR_BIND_MULOP,					"BIND_MULOP"},
	{STR_BIND_AUDON,					"BIND_AUDON"},
	{STR_BIND_AUDOFF,				"BIND_AUDOFF"},
	{STR_BIND_NORTH	,				"BIND_NORTH"},
	{STR_BIND_TRACK	,				"BIND_TRACK"},
	{STR_BIND_OPT	,				"BIND_OPT"},
	{STR_BIND_RIN	,				"BIND_RIN"},
	{STR_BIND_ROUT	,				"BIND_ROUT"},
	{STR_BIND_ZIN	,				"BIND_ZIN"},
	{STR_BIND_ZOUT	,				"BIND_ZOUT"},
	{STR_BIND_PF		,				"BIND_PF"},
	{STR_BIND_RL		,				"BIND_RL"},
	{STR_BIND_RP		,				"BIND_RP"},
	{STR_BIND_RR		,				"BIND_RR"},
	{STR_BIND_PB		,				"BIND_PB"},
	{STR_BIND_ORD	,				"BIND_ORD"},
	{STR_BIND_RESJ	,				"BIND_RESJ"},
	{STR_BIND_REPJ	,				"BIND_REPJ"},
	{STR_BIND_OVERL	,				"BIND_OVERL"},
	{STR_BIND_CENTV	,				"BIND_CENTV"},
	{STR_BIND_CEASE	,				"BIND_CEASE"},
	{STR_BIND_UNITJ	,				"BIND_UNITJ"},
	{STR_BIND_ENGAG	,				"BIND_ENGAG"},
	{STR_BIND_FAW	,				"BIND_FAW"},
	{STR_BIND_RTB	,				"BIND_RTB"},
	{STR_BIND_DEFR	 ,				"BIND_DEFR"},
	{STR_BIND_SPLIM	,				"BIND_SPLIM"},
	{STR_BIND_SHOR	,				"BIND_SHOR"},
	{STR_BIND_PURS	,				"BIND_PURS"},
	{STR_BIND_PATR	,				"BIND_PATR"},
	{STR_BIND_REPA	,				"BIND_REPA"},
	{STR_BIND_DSTOP	,				"BIND_DSTOP"},
	{STR_BIND_SENDT	,				"BIND_SENDT"},
	{STR_BIND_LONGR	,				"BIND_LONGR"},
	{STR_BIND_SCAT	,				"BIND_SCAT"},
	{STR_BIND_LDAM	,				"BIND_LDAM"},
	{STR_BIND_HDAM	,				"BIND_HDAM"},
	{STR_BIND_NDAM	,				"BIND_NDAM"},
	{STR_BIND_ACU	,				"BIND_ACU"},
	{STR_BIND_ABDU	,				"BIND_ABDU"},
	{STR_BIND_AHTR	,				"BIND_AHTR"},
	{STR_BIND_AHOV	,				"BIND_AHOV"},
	{STR_BIND_RECY	,				"BIND_RECY"},
	{STR_BIND_ASCR	,				"BIND_ASCR"},
	{STR_BIND_ATR	,				"BIND_ATR"},
	{STR_BIND_ALL	,				"BIND_ALL"},
	{STR_BIND_AVTOL	,				"BIND_AVTOL"},
	{STR_BIND_AWHE	,				"BIND_AWHE"},
	{STR_BIND_ASIMIL	,				"BIND_ASIMIL"},

// something else.
{STR_GAM_DERRICK_BURNING,			"GAM_DERRICK_BURNING"},
{STR_SEL_NO_STRUCTURE,				"SEL_NO_STRUCTURE"},

{STR_FE_SSHAKE,							"FE_SSHAKE"},
{STR_FE_MFLIP,							"FE_MFLIP"},
{STR_FE_ON,								"FE_ON"},
{STR_FE_OFF,								"FE_OFF"},

{STR_FE_GREEN,					"FE_GREEN"},
{STR_FE_ORANGE,					"FE_ORANGE"},
{STR_FE_GREY	,					"FE_GREY"},
{STR_FE_BLACK,					"FE_BLACK"},
{STR_FE_RED	,					"FE_RED"},
{STR_FE_BLUE	,					"FE_BLUE"},
{STR_FE_PINK	,					"FE_PINK"},
{STR_FE_CYAN	,					"FE_CYAN"},
{STR_BIND_CONJ,					"BIND_CONJ"},
{STR_BIND_SENJ,					"BIND_SENJ"},
{STR_BIND_COMJ,					"BIND_COMJ"},

{STR_GAM_CONNOTFOUND,			"GAM_CONNOTFOUND"},
{STR_GAM_SENNOTFOUND,			"GAM_SENNOTFOUND"},
{STR_GAM_COMNOTFOUND,			"GAM_COMNOTFOUND"},

	// commander keys
	{STR_BIND_CMD1,					"BIND_CMD1"},
	{STR_BIND_CMD2,					"BIND_CMD2"},
	{STR_BIND_CMD3,					"BIND_CMD3"},
	{STR_BIND_CMD4,					"BIND_CMD4"},
	{STR_BIND_CMD5,					"BIND_CMD5"},
	{STR_BIND_CMD6,					"BIND_CMD6"},
	{STR_BIND_CMD7,					"BIND_CMD7"},
	{STR_BIND_CMD8,					"BIND_CMD8"},
	{STR_BIND_CMD9,					"BIND_CMD9"},

	{STR_BIND_SELFACTORY,	   			"BIND_SELFACTORY"},
	{STR_BIND_SELRESEARCH,   			"BIND_SELRESEARCH"},
	{STR_BIND_SELPOWER,	   			"BIND_SELPOWER"},
	{STR_BIND_SELCYBORG,	   			"BIND_SELCYBORG"},
	{STR_BIND_CONSOLE,	   			"BIND_CONSOLE"},
	{STR_BIND_UP,					"BIND_UP"},
	{STR_BIND_DOWN,			 		"BIND_DOWN"},
	{STR_BIND_RIGHT,			 		"BIND_RIGHT"},
	{STR_BIND_LEFT,			 		"BIND_LEFT"},

	// game speed keys and messages
	{STR_BIND_SPEED_UP,					"BIND_SPEED_UP"},
	{STR_BIND_SLOW_DOWN,					"BIND_SLOW_DOWN"},
	{STR_BIND_NORMAL_SPEED,				"BIND_NORMAL_SPEED"},
	{STR_GAM_SPEED_UP,					"GAM_SPEED_UP"},
	{STR_GAM_SLOW_DOWN,					"GAM_SLOW_DOWN"},
	{STR_GAM_NORMAL_SPEED,				"GAM_NORMAL_SPEED"},

	{STR_BIND_RELOAD,					"BIND_RELOAD"},
	{STR_BIND_RADJUMP,					"BIND_RADJUMP"},

	{STR_DORD_FIREDES,					"DORD_FIREDES"},
	{STR_DORD_VTOL_FACTORY,				"DORD_VTOL_FACTORY"},

	{STR_FE_SUBTITLES,					"FE_SUBTITLES"},
	{STR_BIND_REOPEN_BUILD,				"BIND_REOPEN_BUILD"},
	{STR_GAM_BUILD_REOPEN,				"GAM_BUILD_REOPEN"},
	{STR_GAM_BUILD_NO_REOPEN,			"GAM_BUILD_NO_REOPEN"},
	{STR_GAM_FORMATION_ON,				"GAM_FORMATION_ON"},
	{STR_GAM_FORMATION_OFF,				"GAM_FORMATION_OFF"},

	{STR_SEQ_PLAYBACK,					"SEQ_PLAYBACK"},
	{STR_SEQ_FULL,						"SEQ_FULL"},
	{STR_SEQ_WINDOW,						"SEQ_WINDOW"},
	{STR_SEQ_MINIMAL,					"SEQ_MINIMAL"}

};

/* The string resource object */
STR_RES *psStringRes;

/* Initialise the string system */
BOOL stringsInitialise(void)
{
	if (!strresCreate(&psStringRes, STRING_INIT, STRING_EXT))
	{
		return FALSE;
	}

	if (!strresLoadFixedID(psStringRes, asFixedID, STR_MAX_ID))
	{
		return FALSE;
	}

	return TRUE;
}


/* Shut down the string system */
void stringsShutDown(void)
{
	strresDestroy(psStringRes);
}

