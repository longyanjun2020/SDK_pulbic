
CSN_DEFINES = __R_99__ __E_GPRS__

CSN_SRCS = \
		smg.csn\
		ss.csn\
		ss0408.csn\
		crss.csn\
		cc.csn\
		sms.csn\
		sim.csn\
		mmc.csn\
		mmp.csn\
		rrc.csn\
		rrcp.csn\
		rrd.csn\
		rrt.csn\
		mmt.csn

CSN_DEPS = standard.csn\
		ss_asn1.csn\
		cc_asn1.csn\
		rra_defs.csn\
		rrccomie.csn\
		rrtcomie.csn\
		mmt_sms.csn\
		mmt_ciss.csn\
		mmt_stlk.csn\
		mmt_cc.csn\
		mmt_bear.csn\
		mmt_LLC.csn

CSN_R1 = mmt.c
CSN_R2 = cc.c rrc.c rrd.c smg.c ss.c ss0408.c
CSN_R5 = crss.c mmc.c mmp.c rrcp.c rrt.c sim.c sms.c
CSN_M  = rrcp.c rrt.c
