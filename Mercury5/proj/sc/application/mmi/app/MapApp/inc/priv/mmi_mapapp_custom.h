/**
* @file mmi_mapapp_custom.h
*
* @version $Id: mmi_mapapp_custom.h 2009-02-05 Golden Chen $
*/
#ifndef __MMI_MAPAPP_CUSTOM_H__
#define __MMI_MAPAPP_CUSTOM_H__

#ifndef         SUPPORT_TWICE_RD_DRAWING
#define         SUPPORT_TWICE_RD_DRAWING
#endif

#define         USE_POI
#define         DRAWLINE_TURBO
#define         NAME_COLLISION_DETECT
//#define         USE_STATIC_MEMORY
//#define         SOFTWARE_REDRAW_PANMAP_COPYSCRN
//#define         CHECK_MAPAPP_VERSION

/* Define constant config and attribute settings */

#define                 MapView_TitleBar_Height              MAIN_TITLE_HEIGHT
#define         		MapView_Width						MAIN_LCD_WIDTH
#define                 MapView_Height					    (MAIN_LCD_HEIGHT-MapView_TitleBar_Height*2)
#define                 MapView_Half_Width                  (MapView_Width/2)
#define                 MapView_Half_Height                 (MapView_Height/2)
#define                 MapView_HardwareShortCutBound       MAIN_LCD_HEIGHT


/* Road Color - Light */
#define					MAPVIEW_HIGHWAY_COLOR_R			    248        /* 一級 */
#define         		MAPVIEW_HIGHWAY_COLOR_G				128
#define         		MAPVIEW_HIGHWAY_COLOR_B				  8

#define					MAPVIEW_NHIGHWAY_COLOR_R			248        /* 二級 */
#define         		MAPVIEW_NHIGHWAY_COLOR_G			128
#define         		MAPVIEW_NHIGHWAY_COLOR_B			  8

#define					MAPVIEW_EXPRESSWAY_COLOR_R			255       /* 三級 */
#define					MAPVIEW_EXPRESSWAY_COLOR_G			255
#define					MAPVIEW_EXPRESSWAY_COLOR_B		 	  0

#define					MAPVIEW_PHIGHWAY_COLOR_R            255       /* 四級 */
#define					MAPVIEW_PHIGHWAY_COLOR_G        	255
#define					MAPVIEW_PHIGHWAY_COLOR_B              0

#define					MAPVIEW_MAINROAD_COLOR_R    		255       /* 五級 */
#define					MAPVIEW_MAINROAD_COLOR_G    		255
#define					MAPVIEW_MAINROAD_COLOR_B     		  0

#define			MAPVIEW_SECONDARYROAD_COLOR_R            255   /* 六級 */
#define			MAPVIEW_SECONDARYROAD_COLOR_G            255
#define			MAPVIEW_SECONDARYROAD_COLOR_B            255

#define			MAPVIEW_ORDINARYROAD_COLOR_R            255    /* 七級 */
#define			MAPVIEW_ORDINARYROAD_COLOR_G            255
#define			MAPVIEW_ORDINARYROAD_COLOR_B            255

#define			MAPVIEW_ENTRANCEEXIT_COLOR_R            255     /* 八級 */
#define			MAPVIEW_ENTRANCEEXIT_COLOR_G            255
#define			MAPVIEW_ENTRANCEEXIT_COLOR_B            255

#define			MAPVIEW_PATH_COLOR_R            255                   /* 九級 */
#define			MAPVIEW_PATH_COLOR_G            255
#define			MAPVIEW_PATH_COLOR_B            255

#define			MAPVIEW_WALK_COLOR_R            255                /* 步行道路 */
#define			MAPVIEW_WALK_COLOR_G            255
#define			MAPVIEW_WALK_COLOR_B            255

#define         MAPVIEW_CROSS_COLOR_R           255           /* 人行橫道 */
#define         MAPVIEW_CROSS_COLOR_G           255
#define         MAPVIEW_CROSS_COLOR_B           255

#define         MAPVIEW_FLYOVER_COLOR_R           255          /* 天橋 */
#define         MAPVIEW_FLYOVER_COLOR_G           255
#define         MAPVIEW_FLYOVER_COLOR_B           255

#define         MAPVIEW_UNDERPASS_COLOR_R         255          /* 地下通道 */
#define         MAPVIEW_UNDERPASS_COLOR_G         255
#define         MAPVIEW_UNDERPASS_COLOR_B         255

#define         MAPVIEW_RAILWAYPASS_COLOR_R         255        /* 地鐵通道 */
#define         MAPVIEW_RAILWAYPASS_COLOR_G         255
#define         MAPVIEW_RAILWAYPASS_COLOR_B         255

/* Road Outline Color - Light */
#define			MAPVIEW_HIGHWAY_TWCOLOR_R			    184        /* 一級 */
#define         MAPVIEW_HIGHWAY_TWCOLOR_G				 96
#define         MAPVIEW_HIGHWAY_TWCOLOR_B				  0

#define			MAPVIEW_NHIGHWAY_TWCOLOR_R			184        /* 二級 */
#define         MAPVIEW_NHIGHWAY_TWCOLOR_G			 96
#define         MAPVIEW_NHIGHWAY_TWCOLOR_B			  0

#define			MAPVIEW_EXPRESSWAY_TWCOLOR_R			184       /* 三級 */
#define			MAPVIEW_EXPRESSWAY_TWCOLOR_G			184
#define			MAPVIEW_EXPRESSWAY_TWCOLOR_B		 	  0

#define			MAPVIEW_PHIGHWAY_TWCOLOR_R            184       /* 四級 */
#define			MAPVIEW_PHIGHWAY_TWCOLOR_G        	  184
#define			MAPVIEW_PHIGHWAY_TWCOLOR_B              0

#define			MAPVIEW_MAINROAD_TWCOLOR_R    		184       /* 五級 */
#define			MAPVIEW_MAINROAD_TWCOLOR_G    		184
#define			MAPVIEW_MAINROAD_TWCOLOR_B     		  0

#define			MAPVIEW_SECONDARYROAD_TWCOLOR_R            176   /* 六級 */
#define			MAPVIEW_SECONDARYROAD_TWCOLOR_G            176
#define			MAPVIEW_SECONDARYROAD_TWCOLOR_B            176

#define			MAPVIEW_ORDINARYROAD_TWCOLOR_R            176    /* 七級 */
#define			MAPVIEW_ORDINARYROAD_TWCOLOR_G            176
#define			MAPVIEW_ORDINARYROAD_TWCOLOR_B            176

#define			MAPVIEW_ENTRANCEEXIT_TWCOLOR_R            176     /* 八級 */
#define			MAPVIEW_ENTRANCEEXIT_TWCOLOR_G            176
#define			MAPVIEW_ENTRANCEEXIT_TWCOLOR_B            176

#define			MAPVIEW_PATH_TWCOLOR_R            176                   /* 九級 */
#define			MAPVIEW_PATH_TWCOLOR_G            176
#define			MAPVIEW_PATH_TWCOLOR_B            176

#define			MAPVIEW_WALK_TWCOLOR_R            208                /* 步行道路 */
#define			MAPVIEW_WALK_TWCOLOR_G            208
#define			MAPVIEW_WALK_TWCOLOR_B            208

#define         MAPVIEW_CROSS_TWCOLOR_R           208           /* 人行橫道 */
#define         MAPVIEW_CROSS_TWCOLOR_G           208
#define         MAPVIEW_CROSS_TWCOLOR_B           208

#define         MAPVIEW_FLYOVER_TWCOLOR_R           255          /* 天橋 */
#define         MAPVIEW_FLYOVER_TWCOLOR_G           255
#define         MAPVIEW_FLYOVER_TWCOLOR_B           255

#define         MAPVIEW_UNDERPASS_TWCOLOR_R         255          /* 地下通道 */
#define         MAPVIEW_UNDERPASS_TWCOLOR_G         255
#define         MAPVIEW_UNDERPASS_TWCOLOR_B         255

#define         MAPVIEW_RAILWAYPASS_TWCOLOR_R         255        /* 地鐵通道 */
#define         MAPVIEW_RAILWAYPASS_TWCOLOR_G         255
#define         MAPVIEW_RAILWAYPASS_TWCOLOR_B         255

/* Road Color - Dark */
#define					MAPVIEW_HIGHWAY_DARK_COLOR_R			    248        /* 一級 */
#define         		MAPVIEW_HIGHWAY_DARK_COLOR_G				104
#define         		MAPVIEW_HIGHWAY_DARK_COLOR_B				  0

#define					MAPVIEW_NHIGHWAY_DARK_COLOR_R			248        /* 二級 */
#define         		MAPVIEW_NHIGHWAY_DARK_COLOR_G			104
#define         		MAPVIEW_NHIGHWAY_DARK_COLOR_B			  0

#define					MAPVIEW_EXPRESSWAY_DARK_COLOR_R			248       /* 三級 */
#define					MAPVIEW_EXPRESSWAY_DARK_COLOR_G			216
#define					MAPVIEW_EXPRESSWAY_DARK_COLOR_B		 	  0

#define					MAPVIEW_PHIGHWAY_DARK_COLOR_R            248       /* 四級 */
#define					MAPVIEW_PHIGHWAY_DARK_COLOR_G        	 216
#define					MAPVIEW_PHIGHWAY_DARK_COLOR_B              0

#define					MAPVIEW_MAINROAD_DARK_COLOR_R    		248       /* 五級 */
#define					MAPVIEW_MAINROAD_DARK_COLOR_G    		216
#define					MAPVIEW_MAINROAD_DARK_COLOR_B     		  0

#define			MAPVIEW_SECONDARYROAD_DARK_COLOR_R            255   /* 六級 */
#define			MAPVIEW_SECONDARYROAD_DARK_COLOR_G            255
#define			MAPVIEW_SECONDARYROAD_DARK_COLOR_B            255

#define			MAPVIEW_ORDINARYROAD_DARK_COLOR_R            255    /* 七級 */
#define			MAPVIEW_ORDINARYROAD_DARK_COLOR_G            255
#define			MAPVIEW_ORDINARYROAD_DARK_COLOR_B            255

#define			MAPVIEW_ENTRANCEEXIT_DARK_COLOR_R            255     /* 八級 */
#define			MAPVIEW_ENTRANCEEXIT_DARK_COLOR_G            255
#define			MAPVIEW_ENTRANCEEXIT_DARK_COLOR_B            255

#define			MAPVIEW_PATH_DARK_COLOR_R            255                   /* 九級 */
#define			MAPVIEW_PATH_DARK_COLOR_G            255
#define			MAPVIEW_PATH_DARK_COLOR_B            255

#define			MAPVIEW_WALK_DARK_COLOR_R            255                /* 步行道路 */
#define			MAPVIEW_WALK_DARK_COLOR_G            255
#define			MAPVIEW_WALK_DARK_COLOR_B            255

#define         MAPVIEW_CROSS_DARK_COLOR_R           255           /* 人行橫道 */
#define         MAPVIEW_CROSS_DARK_COLOR_G           255
#define         MAPVIEW_CROSS_DARK_COLOR_B           255

#define         MAPVIEW_FLYOVER_DARK_COLOR_R            255          /* 天橋 */
#define         MAPVIEW_FLYOVER_DARK_COLOR_G            255
#define         MAPVIEW_FLYOVER_DARK_COLOR_B            255

#define         MAPVIEW_UNDERPASS_DARK_COLOR_R          255          /* 地下通道 */
#define         MAPVIEW_UNDERPASS_DARK_COLOR_G          255
#define         MAPVIEW_UNDERPASS_DARK_COLOR_B          255

#define         MAPVIEW_RAILWAYPASS_DARK_COLOR_R          255        /* 地鐵通道 */
#define         MAPVIEW_RAILWAYPASS_DARK_COLOR_G          255
#define         MAPVIEW_RAILWAYPASS_DARK_COLOR_B          255

/* Road Outline DARK_COLOR - Dark */
#define			MAPVIEW_HIGHWAY_DARK_TWCOLOR_R			    160        /* 一級 */
#define         MAPVIEW_HIGHWAY_DARK_TWCOLOR_G				 88
#define         MAPVIEW_HIGHWAY_DARK_TWCOLOR_B				  0

#define			MAPVIEW_NHIGHWAY_DARK_TWCOLOR_R			    160        /* 二級 */
#define         MAPVIEW_NHIGHWAY_DARK_TWCOLOR_G			     88
#define         MAPVIEW_NHIGHWAY_DARK_TWCOLOR_B			      0

#define			MAPVIEW_EXPRESSWAY_DARK_TWCOLOR_R			168       /* 三級 */
#define			MAPVIEW_EXPRESSWAY_DARK_TWCOLOR_G			160
#define			MAPVIEW_EXPRESSWAY_DARK_TWCOLOR_B		 	  0

#define			MAPVIEW_PHIGHWAY_DARK_TWCOLOR_R            168       /* 四級 */
#define			MAPVIEW_PHIGHWAY_DARK_TWCOLOR_G        	   160
#define			MAPVIEW_PHIGHWAY_DARK_TWCOLOR_B              0

#define			MAPVIEW_MAINROAD_DARK_TWCOLOR_R    		   168       /* 五級 */
#define			MAPVIEW_MAINROAD_DARK_TWCOLOR_G    		   160
#define			MAPVIEW_MAINROAD_DARK_TWCOLOR_B     		 0

#define			MAPVIEW_SECONDARYROAD_DARK_TWCOLOR_R            176   /* 六級 */
#define			MAPVIEW_SECONDARYROAD_DARK_TWCOLOR_G            176
#define			MAPVIEW_SECONDARYROAD_DARK_TWCOLOR_B            176

#define			MAPVIEW_ORDINARYROAD_DARK_TWCOLOR_R            176    /* 七級 */
#define			MAPVIEW_ORDINARYROAD_DARK_TWCOLOR_G            176
#define			MAPVIEW_ORDINARYROAD_DARK_TWCOLOR_B            176

#define			MAPVIEW_ENTRANCEEXIT_DARK_TWCOLOR_R            176     /* 八級 */
#define			MAPVIEW_ENTRANCEEXIT_DARK_TWCOLOR_G            176
#define			MAPVIEW_ENTRANCEEXIT_DARK_TWCOLOR_B            176

#define			MAPVIEW_PATH_DARK_TWCOLOR_R            176                   /* 九級 */
#define			MAPVIEW_PATH_DARK_TWCOLOR_G            176
#define			MAPVIEW_PATH_DARK_TWCOLOR_B            176

#define			MAPVIEW_WALK_DARK_TWCOLOR_R            208                /* 步行道路 */
#define			MAPVIEW_WALK_DARK_TWCOLOR_G            208
#define			MAPVIEW_WALK_DARK_TWCOLOR_B            208

#define         MAPVIEW_CROSS_DARK_TWCOLOR_R           208           /* 人行橫道 */
#define         MAPVIEW_CROSS_DARK_TWCOLOR_G           208
#define         MAPVIEW_CROSS_DARK_TWCOLOR_B           208

#define         MAPVIEW_FLYOVER_DARK_TWCOLOR_R           255          /* 天橋 */
#define         MAPVIEW_FLYOVER_DARK_TWCOLOR_G           255
#define         MAPVIEW_FLYOVER_DARK_TWCOLOR_B           255

#define         MAPVIEW_UNDERPASS_DARK_TWCOLOR_R         255          /* 地下通道 */
#define         MAPVIEW_UNDERPASS_DARK_TWCOLOR_G         255
#define         MAPVIEW_UNDERPASS_DARK_TWCOLOR_B         255

#define         MAPVIEW_RAILWAYPASS_DARK_TWCOLOR_R         255        /* 地鐵通道 */
#define         MAPVIEW_RAILWAYPASS_DARK_TWCOLOR_G         255
#define         MAPVIEW_RAILWAYPASS_DARK_TWCOLOR_B         255

/* Geometry Color - Light */
#define			MAPVIEW_AD_FACE_COLOR_R             216       /* 行政區-面 */
#define			MAPVIEW_AD_FACE_COLOR_G             216
#define			MAPVIEW_AD_FACE_COLOR_B             200

#define			MAPVIEW_AD2_BORDER_COLOR_R           112     /* 國界(線) */
#define			MAPVIEW_AD2_BORDER_COLOR_G           112
#define			MAPVIEW_AD2_BORDER_COLOR_B           112

#define			MAPVIEW_AD3_BORDER_COLOR_R           248     /* 未定國界(線) */
#define			MAPVIEW_AD3_BORDER_COLOR_G           128
#define			MAPVIEW_AD3_BORDER_COLOR_B            64

#define			MAPVIEW_AD4_BORDER_COLOR_R           144     /* 省級區界, 未定省界 */
#define			MAPVIEW_AD4_BORDER_COLOR_G           144
#define			MAPVIEW_AD4_BORDER_COLOR_B           144

#define                 MAPVIEW_AD8_BORDER_COLOR_R           184      /* 地市級區界 */
#define                 MAPVIEW_AD8_BORDER_COLOR_G           196
#define                 MAPVIEW_AD8_BORDER_COLOR_B           200

#define                 MAPVIEW_AD9_BORDER_COLOR_R           200     /* 區縣級區界 */
#define                 MAPVIEW_AD9_BORDER_COLOR_G           212
#define                 MAPVIEW_AD9_BORDER_COLOR_B           216

#define			MAPVIEW_AD5_BORDER_COLOR_R               0      /* 珊瑚礁 */
#define			MAPVIEW_AD5_BORDER_COLOR_G           140
#define			MAPVIEW_AD5_BORDER_COLOR_B               8

#define			MAPVIEW_AD6_BORDER_COLOR_R           232     /* 特別行政區 */
#define			MAPVIEW_AD6_BORDER_COLOR_G              0
#define			MAPVIEW_AD6_BORDER_COLOR_B           248

#define                 MAPVIEW_AD7_COAST_COLOR_R              16    /* 海岸線 */
#define                 MAPVIEW_AD7_COAST_COLOR_G              72
#define                 MAPVIEW_AD7_COAST_COLOR_B             128

#define			MAPVIEW_RL_RAILWAY_COLOR_R          136         /* 鐵路 */
#define			MAPVIEW_RL_RAILWAY_COLOR_G          140
#define			MAPVIEW_RL_RAILWAY_COLOR_B          152

#define			MAPVIEW_WA_WATER_COLOR_R           160         /* 水系(面, 線) */
#define			MAPVIEW_WA_WATER_COLOR_G           180
#define			MAPVIEW_WA_WATER_COLOR_B           200

#define			MAPVIEW_VE_GREEN_COLOR_R	       176         /* 植披 */
#define			MAPVIEW_VE_GREEN_COLOR_G           220
#define			MAPVIEW_VE_GREEN_COLOR_B           120

#define			MAPVIEW_ISLAND_COLOR_R             216       /* 島嶼 */
#define			MAPVIEW_ISLAND_COLOR_G             216
#define			MAPVIEW_ISLAND_COLOR_B             200

#define			MAPVIEW_TF_TRANSPORT_COLOR_R           200        /* 交通設施 */  /* 機場 */
#define			MAPVIEW_TF_TRANSPORT_COLOR_G           200
#define			MAPVIEW_TF_TRANSPORT_COLOR_B           168


#define			MAPVIEW_CF_CULTU_COLOR_R           200        /* 文化設施 */
#define			MAPVIEW_CF_CULTU_COLOR_G           192
#define			MAPVIEW_CF_CULTU_COLOR_B           216

#define         MAPVIEW_CF_SCHOOL_COLOR_R          192        /* 學校, 教育設施 */
#define         MAPVIEW_CF_SCHOOL_COLOR_G          192
#define         MAPVIEW_CF_SCHOOL_COLOR_B          192


#define			MAPVIEW_LF_AMUSE_COLOR_R           216        /* 休閒設施 */
#define			MAPVIEW_LF_AMUSE_COLOR_G           232
#define			MAPVIEW_LF_AMUSE_COLOR_B           176

#define         MAPVIEW_MF_GOVERN_COLOR_R          176        /* 政府機關 */
#define         MAPVIEW_MF_GOVERN_COLOR_G          176
#define         MAPVIEW_MF_GOVERN_COLOR_B          176

#define         MAPVIEW_MF_HOSPITAL_COLOR_R         232       /* 醫院 */
#define         MAPVIEW_MF_HOSPITAL_COLOR_G         204
#define         MAPVIEW_MF_HOSPITAL_COLOR_B         200

#define			MAPVIEW_BACKGROUND_COLOR_R          160        /* 海洋背景色 */
#define			MAPVIEW_BACKGROUND_COLOR_G          180
#define			MAPVIEW_BACKGROUND_COLOR_B          200

/* Geometry Color - Dark */
#define			MAPVIEW_AD_FACE_DARK_COLOR_R           168       /* 行政區-面 */
#define			MAPVIEW_AD_FACE_DARK_COLOR_G           180
#define			MAPVIEW_AD_FACE_DARK_COLOR_B           184

#define			MAPVIEW_AD2_BORDER_DARK_COLOR_R           80     /* 國界(線) */
#define			MAPVIEW_AD2_BORDER_DARK_COLOR_G           80
#define			MAPVIEW_AD2_BORDER_DARK_COLOR_B           80

#define			MAPVIEW_AD3_BORDER_DARK_COLOR_R           248      /* 未定國界(線) */
#define			MAPVIEW_AD3_BORDER_DARK_COLOR_G           128
#define			MAPVIEW_AD3_BORDER_DARK_COLOR_B             64

#define			MAPVIEW_AD4_BORDER_DARK_COLOR_R           128      /* 省級區界, 未定省界 */
#define			MAPVIEW_AD4_BORDER_DARK_COLOR_G           128
#define			MAPVIEW_AD4_BORDER_DARK_COLOR_B           128

#define                 MAPVIEW_AD8_BORDER_DARK_COLOR_R           152      /* 地市級區界 */
#define                 MAPVIEW_AD8_BORDER_DARK_COLOR_G           164
#define                 MAPVIEW_AD8_BORDER_DARK_COLOR_B           168

#define                 MAPVIEW_AD9_BORDER_DARK_COLOR_R           168     /* 區縣級區界 */
#define                 MAPVIEW_AD9_BORDER_DARK_COLOR_G           184
#define                 MAPVIEW_AD9_BORDER_DARK_COLOR_B           184

#define			MAPVIEW_AD5_BORDER_DARK_COLOR_R               0      /* 珊瑚礁 */
#define			MAPVIEW_AD5_BORDER_DARK_COLOR_G           140
#define			MAPVIEW_AD5_BORDER_DARK_COLOR_B               8

#define			MAPVIEW_AD6_BORDER_DARK_COLOR_R           232     /* 特別行政區 */
#define			MAPVIEW_AD6_BORDER_DARK_COLOR_G              0
#define			MAPVIEW_AD6_BORDER_DARK_COLOR_B           248

#define                 MAPVIEW_AD7_COAST_DARK_COLOR_R                24    /* 海岸線 */
#define                 MAPVIEW_AD7_COAST_DARK_COLOR_G              188
#define                 MAPVIEW_AD7_COAST_DARK_COLOR_B              216

#define			MAPVIEW_RL_RAILWAY_DARK_COLOR_R           96         /* 鐵路 */
#define			MAPVIEW_RL_RAILWAY_DARK_COLOR_G          120
#define			MAPVIEW_RL_RAILWAY_DARK_COLOR_B          120

#define			MAPVIEW_WA_WATER_DARK_COLOR_R            72         /* 水系(面, 線) */
#define			MAPVIEW_WA_WATER_DARK_COLOR_G            96
#define			MAPVIEW_WA_WATER_DARK_COLOR_B            96

#define			MAPVIEW_VE_GREEN_DARK_COLOR_R	        144         /* 植披 */
#define			MAPVIEW_VE_GREEN_DARK_COLOR_G           180
#define			MAPVIEW_VE_GREEN_DARK_COLOR_B            88

#define			MAPVIEW_ISLAND_DARK_COLOR_R             168       /* 島嶼 */
#define			MAPVIEW_ISLAND_DARK_COLOR_G             180
#define			MAPVIEW_ISLAND_DARK_COLOR_B             184

#define			MAPVIEW_TF_TRANSPORT_DARK_COLOR_R           200        /* 交通設施 */  /* 機場 */
#define			MAPVIEW_TF_TRANSPORT_DARK_COLOR_G           192
#define			MAPVIEW_TF_TRANSPORT_DARK_COLOR_B           216

#define			MAPVIEW_CF_CULTU_DARK_COLOR_R           168        /* 文化設施 */
#define			MAPVIEW_CF_CULTU_DARK_COLOR_G           164
#define			MAPVIEW_CF_CULTU_DARK_COLOR_B           248

#define         MAPVIEW_CF_SCHOOL_DARK_COLOR_R          136        /* 學校, 教育設施 */
#define         MAPVIEW_CF_SCHOOL_DARK_COLOR_G          144
#define         MAPVIEW_CF_SCHOOL_DARK_COLOR_B          152

#define			MAPVIEW_LF_AMUSE_DARK_COLOR_R           152        /* 休閒設施 */
#define			MAPVIEW_LF_AMUSE_DARK_COLOR_G           196
#define			MAPVIEW_LF_AMUSE_DARK_COLOR_B           152

#define         MAPVIEW_MF_GOVERN_DARK_COLOR_R          136        /* 政府機關 */
#define         MAPVIEW_MF_GOVERN_DARK_COLOR_G          136
#define         MAPVIEW_MF_GOVERN_DARK_COLOR_B          136

#define         MAPVIEW_MF_HOSPITAL_DARK_COLOR_R         208       /* 醫院 */
#define         MAPVIEW_MF_HOSPITAL_DARK_COLOR_G         140
#define         MAPVIEW_MF_HOSPITAL_DARK_COLOR_B         136

#define			MAPVIEW_BACKGROUND_DARK_COLOR_R         124        /* 海洋背景色 */
#define			MAPVIEW_BACKGROUND_DARK_COLOR_G         142
#define			MAPVIEW_BACKGROUND_DARK_COLOR_B         146

#endif
