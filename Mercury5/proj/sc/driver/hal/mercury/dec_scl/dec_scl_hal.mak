#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_dec_scl_hal)/src 
#  $(PATH_scl_hal)/src/pq

PATH_H +=\
  $(PATH_dec_scl_hal)/inc \
  $(PATH_dec_scl)/inc \
  $(PATH_scl_hal)/inc/pq \
  $(PATH_scl)/inc/pq\
  $(PATH_project_Dvr_CarDV_SDK_cfg_pq)/inc\
 # $(PATH_dec_scl)/inc/pq



#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  hal_dec_scl.c\
  hal_dec_scl_hvsp.c\
#  hal_scl_pq_qualitymap_main.c \
 # hal_scl_pq.c



