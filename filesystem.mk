SOURCE_FILES := \
	resources/** 

NITROFS_FILES := \
	resources/act/ac_gmk_medal00.bac \
	resources/act/ac_gmk_medal01.bac \
	resources/act/ac_gmk_medal02.bac \
	resources/act/ac_gmk_medal03.bac \
	resources/act/ac_gmk_medal04.bac \
	resources/act/ac_gmk_medal05.bac \
	resources/act/ac_gmk_medal06.bac \
	resources/act/ac_gmk_medal07.bac \
	resources/act/ac_gmk_medal08.bac \
	resources/act/ac_gmk_medal09.bac \
	resources/act/ac_gmk_medal10.bac \
	resources/act/ac_gmk_medal11.bac \
	resources/act/ac_gmk_medal12.bac \
	resources/act/ac_gmk_medal13.bac \
	resources/act/dbg_rect.bac \
	resources/bg/dmcmn_dmta_base_p8.bbg \
	resources/bg/dmcmn_menu_base_p8.bbg \
	resources/bg/ft_coming_down.bbg \
	resources/bg/ft_coming_up.bbg \
	resources/bg/z11.bbg \
	resources/bg/z12.bbg \
	resources/bg/z1boss.bbg \
	resources/bg/z21.bbg \
	resources/bg/z2boss.bbg \
	resources/bg/z31.bbg \
	resources/bg/z3boss.bbg \
	resources/bg/z41.bbg \
	resources/bg/z4boss.bbg \
	resources/bg/z51.bbg \
	resources/bg/z5boss.bbg \
	resources/bg/z61.bbg \
	resources/bg/z6boss.bbg \
	resources/bg/z71.bbg \
	resources/bg/z7boss.bbg \
	resources/bg/z8boss.bbg \
	resources/bg/z91.bbg \
	resources/mod/boss1_body_lz7.nsbmd \
	resources/mod/boss1_stage_lz7.nsbmd \
	resources/mod/boss2_arm_lz7.nsbmd \
	resources/mod/boss2_ball_lz7.nsbmd \
	resources/mod/boss2_body_lz7.nsbmd \
	resources/mod/boss2_drop_lz7.nsbmd \
	resources/mod/boss2_spike_lz7.nsbmd \
	resources/mod/boss2_stage_00_lz7.nsbmd \
	resources/mod/boss2_stage_01_lz7.nsbmd \
	resources/mod/boss2_zako_lz7.nsbmd \
	resources/mod/boss3_body_lz7.nsbmd \
	resources/mod/boss3_stage_00_lz7.nsbmd \
	resources/mod/boss3_stage_01_lz7.nsbmd \
	resources/mod/boss3_stage_02_lz7.nsbmd \
	resources/mod/boss3_stage_03_lz7.nsbmd \
	resources/mod/boss4_body_lz7.nsbmd \
	resources/mod/boss4_core_lz7.nsbmd \
	resources/mod/boss4_stage_lz7.nsbmd \
	resources/mod/boss5_body_lz7.nsbmd \
	resources/mod/boss5_core_lz7.nsbmd \
	resources/mod/boss5_map_a_lz7.nsbmd \
	resources/mod/boss5_stage_lz7.nsbmd \
	resources/mod/boss6_body_lz7.nsbmd \
	resources/mod/boss6_sky_lz7.nsbmd \
	resources/mod/boss6_stage_lz7.nsbmd \
	resources/mod/boss6_zako_lz7.nsbmd \
	resources/mod/boss7_body_lz7.nsbmd \
	resources/mod/boss7_stage_lz7.nsbmd \
	resources/mod/bossF_arm_l_lz7.nsbmd \
	resources/mod/bossF_arm_r_lz7.nsbmd \
	resources/mod/bossF_body_lz7.nsbmd \
	resources/mod/bossF_etc.nsbmd \
	resources/mod/bossF_stage.nsbmd \
	resources/narc/act_com_b_lz7.narc \
	resources/narc/act_com_lz7.narc \
	resources/narc/cldm_ex_lz7.narc \
	resources/narc/cldm_mission_lz7.narc \
	resources/narc/cldm_mtral_lz7.narc \
	resources/narc/cldm_time_lz7.narc \
	resources/narc/cldm_vs.narc \
	resources/narc/dm_menu_sa_lz7.narc \
	resources/narc/dm_menu_ta_rank_lz7.narc \
	resources/narc/dm_save_error_lz7.narc \
	resources/narc/dm_sd_act_lz7.narc \
	resources/narc/dmas_vs.narc \
	resources/narc/dmbl_lz7.narc \
	resources/narc/dmcmn_antenna_lz7.narc \
	resources/narc/dmcs_vs.narc \
	resources/narc/dmlg_lz7.narc \
	resources/narc/dmni_lz7.narc \
	resources/narc/dmop_lz7.narc \
	resources/narc/dmop_pldm_lz7.narc \
	resources/narc/dmpz_lz7.narc \
	resources/narc/dmsou_lz7.narc \
	resources/narc/dmsr_lz7.narc \
	resources/narc/dmti_lz7.narc \
	resources/narc/dmvs_cmn.narc \
	resources/narc/dmvs_uinfo.narc \
	resources/narc/dmwf_error_lz7.narc \
	resources/narc/dmwf_fc_lz7.narc \
	resources/narc/dmwf_fl_lz7.narc \
	resources/narc/dmwf_vsrec_lz7.narc \
	resources/narc/emdm_lz7.narc \
	resources/narc/gm_mission.narc \
	resources/narc/mw_frame_lz7.narc \
	resources/narc/player_lz7.narc \
	resources/narc/pldm_01_01_lz7.narc \
	resources/narc/pldm_02_01_lz7.narc \
	resources/narc/pldm_11_1_01_lz7.narc \
	resources/narc/pldm_11_1_02_lz7.narc \
	resources/narc/pldm_13_00_lz7.narc \
	resources/narc/pldm_20_01_lz7.narc \
	resources/narc/pldm_20_02_lz7.narc \
	resources/narc/pldm_22_1_00_lz7.narc \
	resources/narc/pldm_24_00_lz7.narc \
	resources/narc/pldm_26_01_lz7.narc \
	resources/narc/pldm_35_01_lz7.narc \
	resources/narc/pldm_35_02_lz7.narc \
	resources/narc/pldm_46_01_lz7.narc \
	resources/narc/pldm_46_02_lz7.narc \
	resources/narc/pldm_47_1_1_2_00_lz7.narc \
	resources/narc/pldm_51_00_lz7.narc \
	resources/narc/pldm_55_00_lz7.narc \
	resources/narc/pldm_58_00_lz7.narc \
	resources/narc/pldm_63_01_lz7.narc \
	resources/narc/pldm_64_00_lz7.narc \
	resources/narc/pldm_66_00_lz7.narc \
	resources/narc/pldm_66_1_00_lz7.narc \
	resources/narc/pldm_67_00_lz7.narc \
	resources/narc/pldm_70_01_lz7.narc \
	resources/narc/pldm_72_00_lz7.narc \
	resources/narc/pldm_72_01_lz7.narc \
	resources/narc/pldm_73_01_lz7.narc \
	resources/narc/pldm_75_01_lz7.narc \
	resources/narc/pldm_depart_cmn_lz7.narc \
	resources/narc/sb_hover_lz7.narc \
	resources/narc/sb_jet_lz7.narc \
	resources/narc/sb_sailer_lz7.narc \
	resources/narc/sb_submarine_lz7.narc \
	resources/narc/tkdm_lz7.narc \
	resources/narc/vi_act_lz7.narc \
	resources/narc/vi_bg_lz7.narc \
	resources/narc/vi_msg_ctrl_lz7.narc \
	resources/narc/vi_pa_lz7.narc \
	resources/narc/vi_shadow_lz7.narc \
	resources/narc/win_simple_lz7.narc \
	resources/narc/z11_act_lz7.narc \
	resources/narc/z11_eve.narc \
	resources/narc/z11_map.narc \
	resources/narc/z11_raw.narc \
	resources/narc/z12_eve.narc \
	resources/narc/z12_map.narc \
	resources/narc/z12_raw.narc \
	resources/narc/z1boss_act_lz7.narc \
	resources/narc/z1boss_eve.narc \
	resources/narc/z1boss_map.narc \
	resources/narc/z1boss_raw.narc \
	resources/narc/z1t_act_lz7.narc \
	resources/narc/z1t_eve.narc \
	resources/narc/z1t_map.narc \
	resources/narc/z1t_raw.narc \
	resources/narc/z1t_tutorial.narc \
	resources/narc/z21_act_lz7.narc \
	resources/narc/z21_eve.narc \
	resources/narc/z21_map.narc \
	resources/narc/z21_raw.narc \
	resources/narc/z22_eve.narc \
	resources/narc/z22_map.narc \
	resources/narc/z22_raw.narc \
	resources/narc/z2boss_act_lz7.narc \
	resources/narc/z2boss_eve.narc \
	resources/narc/z2boss_map.narc \
	resources/narc/z2boss_raw.narc \
	resources/narc/z31_act_lz7.narc \
	resources/narc/z31_eve.narc \
	resources/narc/z31_map.narc \
	resources/narc/z31_raw.narc \
	resources/narc/z32_eve.narc \
	resources/narc/z32_map.narc \
	resources/narc/z32_raw.narc \
	resources/narc/z33_eve.narc \
	resources/narc/z33_map.narc \
	resources/narc/z3boss_act_lz7.narc \
	resources/narc/z3boss_eve.narc \
	resources/narc/z3boss_map.narc \
	resources/narc/z3boss_raw.narc \
	resources/narc/z41_act_lz7.narc \
	resources/narc/z41_eve.narc \
	resources/narc/z41_map.narc \
	resources/narc/z41_raw.narc \
	resources/narc/z42_eve.narc \
	resources/narc/z42_map.narc \
	resources/narc/z42_raw.narc \
	resources/narc/z4boss_act_lz7.narc \
	resources/narc/z4boss_eve.narc \
	resources/narc/z4boss_map.narc \
	resources/narc/z4boss_raw.narc \
	resources/narc/z51_act_lz7.narc \
	resources/narc/z51_eve.narc \
	resources/narc/z51_map.narc \
	resources/narc/z51_raw.narc \
	resources/narc/z52_act_lz7.narc \
	resources/narc/z52_eve.narc \
	resources/narc/z52_map.narc \
	resources/narc/z52_raw.narc \
	resources/narc/z5boss_act_lz7.narc \
	resources/narc/z5boss_eve.narc \
	resources/narc/z5boss_map.narc \
	resources/narc/z5boss_raw.narc \
	resources/narc/z61_act_lz7.narc \
	resources/narc/z61_eve.narc \
	resources/narc/z61_map.narc \
	resources/narc/z61_raw.narc \
	resources/narc/z62_eve.narc \
	resources/narc/z62_map.narc \
	resources/narc/z62_raw.narc \
	resources/narc/z6boss_act_lz7.narc \
	resources/narc/z6boss_eve.narc \
	resources/narc/z6boss_map.narc \
	resources/narc/z6boss_raw.narc \
	resources/narc/z71_act_lz7.narc \
	resources/narc/z71_eve.narc \
	resources/narc/z71_map.narc \
	resources/narc/z71_raw.narc \
	resources/narc/z72_eve.narc \
	resources/narc/z72_map.narc \
	resources/narc/z72_raw.narc \
	resources/narc/z7boss_act_lz7.narc \
	resources/narc/z7boss_eve.narc \
	resources/narc/z7boss_map.narc \
	resources/narc/z7boss_raw.narc \
	resources/narc/z8boss_act_lz7.narc \
	resources/narc/z8boss_eve.narc \
	resources/narc/z8boss_map.narc \
	resources/narc/z8boss_raw.narc \
	resources/narc/z91_act_lz7.narc \
	resources/narc/z91_eve.narc \
	resources/narc/z91_map.narc \
	resources/narc/z91_raw.narc \
	resources/narc/z92_eve.narc \
	resources/narc/z92_map.narc \
	resources/narc/z93_eve.narc \
	resources/narc/z93_map.narc \
	resources/narc/z94_eve.narc \
	resources/narc/z94_map.narc \
	resources/narc/zm10_eve.narc \
	resources/narc/zm10_map.narc \
	resources/narc/zm11_eve.narc \
	resources/narc/zm11_map.narc \
	resources/narc/zm1_eve.narc \
	resources/narc/zm1_map.narc \
	resources/narc/zm2_eve.narc \
	resources/narc/zm2_map.narc \
	resources/narc/zm3_eve.narc \
	resources/narc/zm3_map.narc \
	resources/narc/zm4_eve.narc \
	resources/narc/zm4_map.narc \
	resources/narc/zm5_eve.narc \
	resources/narc/zm5_map.narc \
	resources/narc/zm6_eve.narc \
	resources/narc/zm6_map.narc \
	resources/narc/zm7_eve.narc \
	resources/narc/zm7_map.narc \
	resources/narc/zm8_eve.narc \
	resources/narc/zm8_map.narc \
	resources/narc/zm9_eve.narc \
	resources/narc/zm9_map.narc \
	resources/narc/zr1_eve.narc \
	resources/narc/zr1_map.narc \
	resources/narc/zr2_eve.narc \
	resources/narc/zr2_map.narc \
	resources/narc/zr3_eve.narc \
	resources/narc/zr3_map.narc \
	resources/narc/zv1_eve.narc \
	resources/narc/zv1_map.narc \
	resources/narc/zv2_eve.narc \
	resources/narc/zv2_map.narc \
	resources/narc/zv3_eve.narc \
	resources/narc/zv3_map.narc \
	resources/narc/zv4_eve.narc \
	resources/narc/zv4_map.narc \
	resources/snd/z11/sound_data.sdat \
	resources/snd/z12/sound_data.sdat \
	resources/snd/z1t/sound_data.sdat \
	resources/snd/z1b/sound_data.sdat \
	resources/snd/z21/sound_data.sdat \
	resources/snd/z22/sound_data.sdat \
	resources/snd/z2b/sound_data.sdat \
	resources/snd/z31/sound_data.sdat \
	resources/snd/z32/sound_data.sdat \
	resources/snd/z3b/sound_data.sdat \
	resources/snd/z41/sound_data.sdat \
	resources/snd/z42/sound_data.sdat \
	resources/snd/z4b/sound_data.sdat \
	resources/snd/z51/sound_data.sdat \
	resources/snd/z52/sound_data.sdat \
	resources/snd/z5b/sound_data.sdat \
	resources/snd/z61/sound_data.sdat \
	resources/snd/z62/sound_data.sdat \
	resources/snd/z6b/sound_data.sdat \
	resources/snd/z71/sound_data.sdat \
	resources/snd/z72/sound_data.sdat \
	resources/snd/z7b/sound_data.sdat \
	resources/snd/z91/sound_data.sdat \
	resources/snd/zfb/sound_data.sdat \
	resources/snd/sb1/sound_data.sdat \
	resources/snd/sb2/sound_data.sdat \
	resources/snd/sb3/sound_data.sdat \
	resources/snd/sb4/sound_data.sdat \
	resources/snd/sb5/sound_data.sdat \
	resources/snd/sys/sound_data.sdat \
	resources/bb/ch.bb \
	resources/bb/cldm_lang.bb \
	resources/bb/dm_save_del.bb \
	resources/bb/dmas.bb \
	resources/bb/dmcs_lang.bb \
	resources/bb/dmta_menu.bb \
	resources/bb/dmwf_cmn.bb \
	resources/bb/dmwf_join.bb \
	resources/bb/dmwf_lang.bb \
	resources/bb/dmwf_rank_lang.bb \
	resources/bb/dmwf_yes.bb \
	resources/bb/gm_demoplay.bb \
	resources/bb/nl.bb \
	resources/bb/nv.bb \
	resources/bb/pldm_cmn.bb \
	resources/bb/pldm_msg_deu.bb \
	resources/bb/pldm_msg_eng.bb \
	resources/bb/pldm_msg_fra.bb \
	resources/bb/pldm_msg_ita.bb \
	resources/bb/pldm_msg_jpn.bb \
	resources/bb/pldm_msg_spa.bb \
	resources/bb/sb.bb \
	resources/bb/tkdm_bg.bb \
	resources/bb/tkdm_char.bb \
	resources/bb/tkdm_cutin.bb \
	resources/bb/tkdm_down.bb \
	resources/bb/tkdm_msg_deu.bb \
	resources/bb/tkdm_msg_eng.bb \
	resources/bb/tkdm_msg_fra.bb \
	resources/bb/tkdm_msg_ita.bb \
	resources/bb/tkdm_msg_jpn.bb \
	resources/bb/tkdm_msg_spa.bb \
	resources/bb/tkdm_name.bb \
	resources/bb/vi_act_loc.bb \
	resources/bb/vi_bg_up.bb \
	resources/bb/vi_dock.bb \
	resources/bb/vi_map_back.bb \
	resources/bb/vi_msg.bb \
	resources/bb/vi_npc.bb \
	resources/bb/vi_pa.bb \
	resources/bb/vi_son.bb \
	resources/bpa/gmk_medal00.bpa \
	resources/bpa/gmk_medal01.bpa \
	resources/bpa/gmk_medal02.bpa \
	resources/bpa/gmk_medal03.bpa \
	resources/bpa/gmk_medal04.bpa \
	resources/bpa/gmk_medal05.bpa \
	resources/bpa/gmk_medal06.bpa \
	resources/bpa/gmk_medal07.bpa \
	resources/bpa/gmk_medal08.bpa \
	resources/bpa/gmk_medal09.bpa \
	resources/bpa/gmk_medal10.bpa \
	resources/bpa/gmk_medal11.bpa \
	resources/bpa/gmk_medal12.bpa \
	resources/bpa/gmk_medal13.bpa \
	resources/bpa/vi_map.bpa \
	resources/ayk/pldm00_jpn_lz7.ayk \
	resources/ayk/pldm01_jpn_lz7.ayk \
	resources/ayk/ptdm00_jpn_lz7.ayk \
	resources/ayk/tkdm00_jpn_lz7.ayk \
	resources/ayk/tkdm01_jpn_lz7.ayk \
	resources/fnt/font_all.fnt \
	resources/fnt/font_ipl.fnt \
	resources/sbb/sb_joh00.sbb \
	resources/sbb/sb_joh00.sbj \
	resources/sbb/sb_joh01.sbb \
	resources/sbb/sb_joh01.sbj \
	resources/sbb/sb_joh02.sbb \
	resources/sbb/sb_joh02.sbj \
	resources/sbb/sb_joh03.sbb \
	resources/sbb/sb_joh03.sbj \
	resources/sbb/sb_joh04.sbb \
	resources/sbb/sb_joh04.sbj \
	resources/sbb/sb_joh05.sbb \
	resources/sbb/sb_joh05.sbj \
	resources/sbb/sb_joh06.sbb \
	resources/sbb/sb_joh06.sbj \
	resources/sbb/sb_ms001.sbb \
	resources/sbb/sb_ms002.sbb \
	resources/sbb/sb_ms003.sbb \
	resources/sbb/sb_ms004.sbb \
	resources/sbb/sb_ms051.sbb \
	resources/sbb/sb_ms052.sbb \
	resources/sbb/sb_ms061.sbb \
	resources/sbb/sb_ms062.sbb \
	resources/sbb/sb_ms071.sbb \
	resources/sbb/sb_ms072.sbb \
	resources/sbb/sb_ms081.sbb \
	resources/sbb/sb_ms082.sbb \
	resources/banner/banner.bnr \
	resources/banner/contest_race.nbfc \
	resources/banner/contest_race.nbfp \
	resources/banner/contest_ring.nbfc \
	resources/banner/contest_ring.nbfp \
	resources/mb/contest.srl \
	resources/keydat/pd_game00.dat \
	resources/keydat/pd_game01.dat \
	resources/keydat/pd_game02.dat \
	resources/keydat/pd_ship00.dat \
	resources/keydat/tp_ship00.dat \
	resources/extra/ex.bb \
	resources/extra/sound_data.sdat \
	resources/st/sound_test_lz7.st \
	resources/dwc/utility.bin \

# contest rom contains no files (they are read from the parent rom)
ifeq ($(GAME_VERSION),RUSH2_CONTEST)
SOURCE_FILES := 
NITROFS_FILES := 
endif

FILES_NEEDED_FOR_COMPILE = $(NITROFS_FILES)

$(DIFF_ARCS):
	cp $< $@

# ARCHIVES := $(filter %.narc,$(SOURCE_FILES) $(SRC_ARCS))
# BUNDLES := $(filter %.bb,$(SOURCE_FILES) $(SRC_ARCS))
# ARCHIVE_HEADERS := $(ARCHIVES:%.narc=%.h)
# BUNDLE_HEADERS := $(BUNDLES:%.bb=%.h)

$(filter-out $(DIFF_ARCS) $(FS_RULE_OVERRIDES),$(NITROFS_FILES)): ;

# This must come after the above includes
include graphics_files_rules.mk

NTR_FILE_EXT := bin NCGR NCLR NCER NSCR NSBMD NSBCA NSBTA

%.narc: NARC_DEPS = $(foreach ext,$(NTR_FILE_EXT),$(wildcard $*/*.$ext))
%.narc: $(NARC_DEPS)
	$(KNARC) -d $* -p $@ -i

%.naix: %.narc ;

.PHONY: filesystem clean-filesystem clean-fs
files_for_compile: $(FILES_NEEDED_FOR_COMPILE)
filesystem: $(NITROFS_FILES)
	$(ROMEXTRACT) $@ --rom baserom.nds
ifeq ($(COMPARE),1)
	$(SHA1SUM) --quiet -c $(WORK_DIR)/$(buildname)/filesystem.sha1
endif

clean-fs: clean-filesystem
clean-filesystem:
	$(RM) $(ARCHIVES) $(ARCHIVE_HEADERS) $(BUNDLES) $(BUNDLE_HEADERS)
	$(RM) -r $(FS_CLEAN_TARGETS)
