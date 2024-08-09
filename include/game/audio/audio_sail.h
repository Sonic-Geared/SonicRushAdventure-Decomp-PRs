#ifndef RUSH2_SND_SAIL_H
#define RUSH2_SND_SAIL_H

// Sound Archive: Sequences
enum SND_SAIL_SEQ
{
	SND_SAIL_SEQ_SEQ_WET_BIKE,
	SND_SAIL_SEQ_SEQ_SAILING,
	SND_SAIL_SEQ_SEQ_HOVERCRAFT,
	SND_SAIL_SEQ_SEQ_SUBMARINE,
	SND_SAIL_SEQ_SEQ_RETIRE,
	SND_SAIL_SEQ_SEQ_DISCOVER,
	SND_SAIL_SEQ_SEQ_RESULT,
};

// Sound Archive: Sequence Archives
enum SND_SAIL_SEQ_ARCHIVES
{
	SND_SAIL_SEQARC_ARC_VOYAGE_SE,
};

// Sound Archive: Sequence Archive Entries
// Sound Archive: Sequence Archive => "ARC_Voyage_SE"
enum SND_SAIL_SEQARC_ARC_VOYAGE_SE
{
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_IDLING,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ACCEL,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_MAX_SPEED,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BREAK,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BOOST_ON,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BOOST,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BOOST_END,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_NO_ENERGY,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SKI_JUMP,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_LAND_WATER,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TRICK_SLIDE,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TRICK_SUC,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TRICK_FAIL,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SPLASH,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_DAMAGE,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_COLLISION,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RETIRE,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_LITTLE_SHARK,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_EXPLOSION,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ENEMY_DEAD,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RING,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ITEM,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_NAVIGATION,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_MACHINE_GUN,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BULLET_WATER,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BULLET_HIT,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RICOCHET,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_CANNON,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_CANNON_WATER,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_CANNON_BOMB,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BOMB,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_WEAPON,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RELOAD,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RELOADED,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BULLET_ERROR,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_DAMAGE_S,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_DAMAGE_L,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TORPEDO,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RETIRE2,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ENE_EXP_S,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ENE_EXP_M,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ENE_EXP_L,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ENE_CAN_S,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ENE_CAN_B,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BOMB_FALL,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_MISSILE,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SUBMARINE,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_IDLING_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ACCEL_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_MAX_SPEED_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BRAKE_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BOOST_ON_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BOOST_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BOOST_END_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_NO_ENERGY_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_HOVER_JUMP,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_LAND_WATER_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_LANDING,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_LAND_ON_ENE,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SPIN,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SPIN_OUT,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RETIRE_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_COLLISION_H,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ENEMY_BOAT,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ENEMY_HOVER,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SCREW,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SONAR,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ENEMY_FIND,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TOUCH,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ROCK_ON,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TOUCH_SLIDE,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ROCKON_MISS,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_AT_DECISION,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TORPEDO_S,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_DAMAGE_S_UW,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_DAMAGE_L_UW,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RETIRE_UW,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TORPEDO_UW,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ENE_SCREW,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_EXP_S,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_EXP_M,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_EXP_L,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_GOAL,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_GO,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_OWA,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_YAHOO,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_YEA,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_FOLLOW,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_KURAE,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_HORAYO,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_YOU,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_LEVEL,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_YARU,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_OUCH,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_T_WA,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_BL_UH,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ALL_UWA,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ALL_UWA2,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_T_DECIDE,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_CURSOL,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_COUNTDOWN,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_POPUP,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SCORE_INDICATION,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TRICK_SUC1,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TRICK_SUC2,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_GALLERY_MAX,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TRICK_MISS,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_DRIFT,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_DRIFT_SUB,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_PASSING,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_CHARGE_START,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_CHARGING,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_CHARGE_MAX,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SHOT_S,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SHOT_M,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_SHOT_B,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_GREAT,
	SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_DRIFT2,
};

// Sound Archive: Intrument Banks
enum SND_SAIL_INSTRUMENT_BANKS
{
	SND_SAIL_BANK_BANK_BGM,
	SND_SAIL_BANK_BANK_VOYAGE_SE,
	SND_SAIL_BANK_BANK_JINGLE,
};

// Sound Archive: Wave Archives
enum SND_SAIL_WAVE_ARCHIVES
{
	SND_SAIL_WAVEARC_WAVE_BGM,
	SND_SAIL_WAVEARC_WAVE_VOYAGE_SE,
	SND_SAIL_WAVEARC_WAVE_JINGLE,
};

// Sound Archive: Sequence Players
enum SND_SAIL_SEQ_PLAYER
{
	SND_SAIL_SEQPLAYER_PLAYER_BGM,
	SND_SAIL_SEQPLAYER_PLAYER_BGM2,
	SND_SAIL_SEQPLAYER_PLAYER_1,
	SND_SAIL_SEQPLAYER_PLAYER_2,
	SND_SAIL_SEQPLAYER_PLAYER_3,
	SND_SAIL_SEQPLAYER_PLAYER_4,
	SND_SAIL_SEQPLAYER_PLAYER_5,
};

#endif // !RUSH2_SND_SAIL_H
