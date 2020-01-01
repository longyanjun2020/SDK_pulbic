#ifndef __MMI_CLSRV_CLMSG_H__
#define __MMI_CLSRV_CLMSG_H__


//---------------------------------------------------------------------------
#ifndef CL_ZONEID_UNKNOW
#define CL_ZONEID_UNKNOW 	0
#endif

#define CL_ZONEID_INC 	    1
#define CL_ZONEID_HOME 	    2

#define CL_ZONEID_HK 	    3
#define CL_ZONEID_MC        4   //Macau
#define CL_ZONEID_TW        5

#define CL_ZONEID_Yidong    6
#define CL_ZONEID_Liantong  7   //
#define CL_ZONEID_Dianxin   8   //
#define CL_ZONEID_Wangtong  9   //

#define CL_ZONEID_Beijing   10

#define CL_ZONEID_SJZ       11  //石家庄
#define CL_ZONEID_Taiyuan   12  //
#define CL_ZONEID_Jinan     13  //
#define CL_ZONEID_Zhengzhou 14  //
#define CL_ZONEID_Harbin    15  //
#define CL_ZONEID_Hangzhou  16  //
#define CL_ZONEID_Hefei     17  //
#define CL_ZONEID_Fuzhou    18  //
#define CL_ZONEID_Nanchang  19  //

#define CL_ZONEID_Guangzhou 20
#define CL_ZONEID_Shanghai 	21
#define CL_ZONEID_Tianjin 	22
#define CL_ZONEID_Chongqing	23
#define CL_ZONEID_Shenyang	24
#define CL_ZONEID_Nanjing	25
//#define CL_ZONEID_XXXX    26
#define CL_ZONEID_Wuhan	    27
#define CL_ZONEID_Chengdu	28
#define CL_ZONEID_Xian	    29

#define CL_ZONEID_Hainan    30  //海南
#define CL_ZONEID_HLJ       31  //黑龙江
#define CL_ZONEID_Jilin     32  //吉林
#define CL_ZONEID_Liaoning  33  //辽宁
#define CL_ZONEID_NMG       34  //内蒙古
#define CL_ZONEID_Xinjiang  35  //新疆
#define CL_ZONEID_Ningxia   36  //宁夏
#define CL_ZONEID_Gansu     37  //甘肃
#define CL_ZONEID_SHX       38  //陕西
#define CL_ZONEID_Shanxi    39  //山西
#define CL_ZONEID_Hebei     40  //河北
#define CL_ZONEID_Henan     41  //河南
#define CL_ZONEID_Shandong  42  //山东
#define CL_ZONEID_Xizang    43  //西藏
#define CL_ZONEID_Qinghai   44  //青海
#define CL_ZONEID_Yunnan    45  //云南
#define CL_ZONEID_Sichuan   46  //四川
#define CL_ZONEID_Hubei     47  //湖北
#define CL_ZONEID_Anhui     48  //安徽
#define CL_ZONEID_Guangxi   49  //广西
#define CL_ZONEID_Guangdong 50  //广东
#define CL_ZONEID_Guizhou   51  //贵州
#define CL_ZONEID_Hunan     52  //湖南
#define CL_ZONEID_Jiangxi   53  //江西
#define CL_ZONEID_Jiangsu   54  //江苏
#define CL_ZONEID_Zhejiang  55  //浙江
#define CL_ZONEID_Fujian    56  //福建

#define CL_ZONEID_Shenzhen  57  //
#define CL_ZONEID_Wenzhou   58  //
#define CL_ZONEID_Xiamen    59  //
#define CL_ZONEID_Changsha  60  //
#define CL_ZONEID_Qingdao   61  //
#define CL_ZONEID_Dongguan  62  //

#define CL_ZONEID_LEAFMARK  63  //
//---------------------------------------------------------------------------
#define CL_ZONEID_USA_Canada	101    //USA&Canada
#define CL_ZONEID_Russia		107    //
#define CL_ZONEID_Egypt			120    //
#define CL_ZONEID_Greece		130    //
#define CL_ZONEID_Netherlands	131    //
#define CL_ZONEID_Belgium		132    //比利时
#define CL_ZONEID_France		133    //
#define CL_ZONEID_Spain			134    //
#define CL_ZONEID_Hungary		136    //
#define CL_ZONEID_Italy			139    //

#define CL_ZONEID_Romania		140    //
#define CL_ZONEID_Switzerland	141    //
#define CL_ZONEID_Austria		143    //奥地利
#define CL_ZONEID_UK			144    //
#define CL_ZONEID_Denmark		145    //
#define CL_ZONEID_Sweden		146    //
#define CL_ZONEID_Norway		147    //
#define CL_ZONEID_Poland		148    //
#define CL_ZONEID_Germany		149    //
#define CL_ZONEID_Peru			151    //秘鲁

#define CL_ZONEID_Mexico		152    //
#define CL_ZONEID_Cuba			153    //
#define CL_ZONEID_Argentina		154    //
#define CL_ZONEID_Brazil		155    //
#define CL_ZONEID_Chile		    156    //
#define CL_ZONEID_Colombia		157    //
#define CL_ZONEID_Venezuela		158    //委内瑞拉
#define CL_ZONEID_Malaysia		160    //
#define CL_ZONEID_Australia		161    //
#define CL_ZONEID_Indonesia		162    //

#define CL_ZONEID_Philippines	163    //
#define CL_ZONEID_NewZealand	164    //
#define CL_ZONEID_Singapore		165    //
#define CL_ZONEID_Thailand		166    //
#define CL_ZONEID_Japan			181    //
#define CL_ZONEID_SouthKorea	182    //
#define CL_ZONEID_China			186    //
#define CL_ZONEID_Turkey		190    //
#define CL_ZONEID_India			191    //
#define CL_ZONEID_Pakistan		192    //

#define CL_ZONEID_SriLanka		194    //
#define CL_ZONEID_Myanmar		195    //缅甸
#define CL_ZONEID_Iran			198    //

//---------------------------------------------------------------------------
#define CL_ZONEID_0310	310//河北	邯郸市					4
#define CL_ZONEID_0311	311//河北	石家庄市				4
#define CL_ZONEID_0312	312//河北	保定市					4
#define CL_ZONEID_0313	313//河北	张家口市				4
#define CL_ZONEID_0314	314//河北	承德市					4
#define CL_ZONEID_0315	315//河北	唐山市					4
#define CL_ZONEID_0316	316//河北	廊坊市					4
#define CL_ZONEID_0317	317//河北	沧州市					4
#define CL_ZONEID_0318	318//河北	衡水市					4
#define CL_ZONEID_0319	319//河北	邢台市					4

#define CL_ZONEID_0335	335//河北	秦皇岛市				4

#define CL_ZONEID_0349	349//山西	朔州					4

#define CL_ZONEID_0350	350//山西	忻州市					4
#define CL_ZONEID_0351	351//山西	太原市					4
#define CL_ZONEID_0352	352//山西	大同市					4
#define CL_ZONEID_0353	353//山西	阳泉市					4
#define CL_ZONEID_0354	354//山西	榆次市					4
#define CL_ZONEID_0355	355//山西	长治县					4
#define CL_ZONEID_0356	356//山西	晋城市					4
#define CL_ZONEID_0357	357//山西	临汾市					4
#define CL_ZONEID_0358	358//山西	离石					4
#define CL_ZONEID_0359	359//山西	运城市					4

#define CL_ZONEID_0370	370//山西	商丘市					4

#define CL_ZONEID_0371	371//河南	郑州市					4
#define CL_ZONEID_0372	372//河南	安阳市					4
#define CL_ZONEID_0373	373//河南	新乡市					4
#define CL_ZONEID_0374	374//河南	许昌市					4
#define CL_ZONEID_0375	375//河南	平顶山市				4
#define CL_ZONEID_0376	376//河南	信阳市					4
#define CL_ZONEID_0377	377//河南	南阳市					4
#define CL_ZONEID_0378	378//河南	开封市					4
#define CL_ZONEID_0379	379//河南	洛阳市					4

#define CL_ZONEID_0391	391//河南	焦作市					4
#define CL_ZONEID_0392	392//河南	鹤壁市					4
#define CL_ZONEID_0393	393//河南	濮阳市					4
#define CL_ZONEID_0394	394//河南	周口市					4
#define CL_ZONEID_0395	395//河南	漯河市					4
#define CL_ZONEID_0396	396//河南	驻马店市				4
#define CL_ZONEID_0398	398//河南	三门峡市				4

#define CL_ZONEID_0410	410//辽宁	铁岭市					4
#define CL_ZONEID_0411	411//辽宁	大连市					4
#define CL_ZONEID_0412	412//辽宁	鞍山市					4
#define CL_ZONEID_0413	413//辽宁	抚顺市					4
#define CL_ZONEID_0414	414//辽宁	本溪市					4
#define CL_ZONEID_0415	415//辽宁	丹东市					4
#define CL_ZONEID_0416	416//辽宁	锦州市					4
#define CL_ZONEID_0417	417//辽宁	营口市					4
#define CL_ZONEID_0418	418//辽宁	阜新市					4
#define CL_ZONEID_0419	419//辽宁	辽阳市					4

#define CL_ZONEID_0421	421//辽宁	朝阳市					4
#define CL_ZONEID_0427	427//辽宁	盘锦市					4
#define CL_ZONEID_0429	429//辽宁	葫芦岛市				4

#define CL_ZONEID_0431	431//吉林	长春市					4
#define CL_ZONEID_0432	432//吉林	吉林市					4
#define CL_ZONEID_0433	433//吉林	延吉市					4
#define CL_ZONEID_0434	434//吉林	四平市					4
#define CL_ZONEID_0435	435//吉林	通化市					4
#define CL_ZONEID_0436	436//吉林	白城市					4
#define CL_ZONEID_0437	437//吉林	辽源市					4
#define CL_ZONEID_0438	438//吉林	扶余市					4
#define CL_ZONEID_0439	439//吉林	白山市					4

#define CL_ZONEID_0440	440//吉林	珲春					4
#define CL_ZONEID_0448	448//吉林	梅河口市				4

#define CL_ZONEID_0451	451//黑龙江	哈尔滨市				4
#define CL_ZONEID_0452	452//黑龙江	齐齐哈尔市				4
#define CL_ZONEID_0453	453//黑龙江	牡丹江市				4
#define CL_ZONEID_0454	454//黑龙江	佳木斯市				4
#define CL_ZONEID_0455	455//黑龙江	绥化市					4
#define CL_ZONEID_0456	456//黑龙江	黑河市					4
#define CL_ZONEID_0457	457//黑龙江	加格达奇				4
#define CL_ZONEID_0458	458//黑龙江	伊春市					4
#define CL_ZONEID_0459	459//黑龙江	大庆市					4

#define CL_ZONEID_0464	464//黑龙江	七台河					4
#define CL_ZONEID_0467	467//黑龙江	鸡西					4
#define CL_ZONEID_0468	468//黑龙江	鹤岗					4
#define CL_ZONEID_0469	469//黑龙江	双鸭山					4

#define CL_ZONEID_0470	470//内蒙古	海拉尔市				4
#define CL_ZONEID_0471	471//内蒙古	呼和浩特市				4
#define CL_ZONEID_0472	472//内蒙古	包头市					4
#define CL_ZONEID_0473	473//内蒙古	乌海市					4
#define CL_ZONEID_0474	474//内蒙古	集宁市					4
#define CL_ZONEID_0475	475//内蒙古	通辽市					4
#define CL_ZONEID_0476	476//内蒙古	赤峰市					4
#define CL_ZONEID_0477	477//内蒙古	东胜市					4
#define CL_ZONEID_0478	478//内蒙古	临河市					4
#define CL_ZONEID_0479	479//内蒙古	锡林浩特市				4

#define CL_ZONEID_0482	482//内蒙古	乌兰浩特市				4
#define CL_ZONEID_0483	483//内蒙古	阿拉善盟				4

#define CL_ZONEID_0510	510//江苏	无锡市					3
#define CL_ZONEID_0511	511//江苏	镇江市					3
#define CL_ZONEID_0512	512//江苏	苏州市					3
#define CL_ZONEID_0513	513//江苏	南通市					3
#define CL_ZONEID_0514	514//江苏	扬州市					3
#define CL_ZONEID_0515	515//江苏	盐城市					3
#define CL_ZONEID_0516	516//江苏	徐州市					3
#define CL_ZONEID_0517	517//江苏	淮安市					3
#define CL_ZONEID_0518	518//江苏	连云港市				3
#define CL_ZONEID_0519	519//江苏	常州市					3

#define CL_ZONEID_0520	520//江苏	常熟市					3
#define CL_ZONEID_0523	523//江苏	泰州市					3
#define CL_ZONEID_0527	527//江苏	宿迁市					3

#define CL_ZONEID_0530	530//山东	荷泽市					4
#define CL_ZONEID_0531	531//山东	济南市					4
#define CL_ZONEID_0532	532//山东	青岛市					4
#define CL_ZONEID_0533	533//山东	淄博市					4
#define CL_ZONEID_0534	534//山东	德州市					4
#define CL_ZONEID_0535	535//山东	烟台市					4
#define CL_ZONEID_0536	536//山东	潍坊市					4
#define CL_ZONEID_0537	537//山东	济宁市					4
#define CL_ZONEID_0538	538//山东	泰安市					4
#define CL_ZONEID_0539	539//山东	临沂市					4

#define CL_ZONEID_0543	543//山东	滨州市					4
#define CL_ZONEID_0546	546//山东	东营市					4

#define CL_ZONEID_0631	631//山东	威海市					4
#define CL_ZONEID_0632	632//山东	枣庄市					4
#define CL_ZONEID_0633	633//山东	日照市					4
#define CL_ZONEID_0634	634//山东	莱芜市					4
#define CL_ZONEID_0635	635//山东	聊城市					4

#define CL_ZONEID_0550	550//安徽	滁州市					3
#define CL_ZONEID_0551	551//安徽	合肥市					3
#define CL_ZONEID_0552	552//安徽	蚌埠市					3
#define CL_ZONEID_0553	553//安徽	芜湖市					3
#define CL_ZONEID_0554	554//安徽	淮南市					3
#define CL_ZONEID_0555	555//安徽	马鞍山市				3
#define CL_ZONEID_0556	556//安徽	安庆市					3
#define CL_ZONEID_0557	557//安徽	宿州市					3
#define CL_ZONEID_0558	558//安徽	阜阳/亳州市				3
#define CL_ZONEID_0559	559//安徽	黄山市					3

#define CL_ZONEID_0561	561//安徽	淮北市					3
#define CL_ZONEID_0562	562//安徽	铜陵市					3
#define CL_ZONEID_0563	563//安徽	宣城市					3
#define CL_ZONEID_0564	564//安徽	六安市					3
#define CL_ZONEID_0565	565//安徽	巢湖市					3
#define CL_ZONEID_0566	566//安徽	池州市					3

#define CL_ZONEID_0570	570//浙江	衢州市					3
#define CL_ZONEID_0571	571//浙江	杭州市					3
#define CL_ZONEID_0572	572//浙江	湖州市					3
#define CL_ZONEID_0573	573//浙江	嘉兴市					3
#define CL_ZONEID_0574	574//浙江	宁波市					3
#define CL_ZONEID_0575	575//浙江	绍兴市					3
#define CL_ZONEID_0576	576//浙江	台州市					3
#define CL_ZONEID_0577	577//浙江	温州市					3
#define CL_ZONEID_0578	578//浙江	丽水市					3
#define CL_ZONEID_0579	579//浙江	金华市					3

#define CL_ZONEID_0580	580//浙江	舟山市					3

#define CL_ZONEID_0591	591//福建	福州市					3
#define CL_ZONEID_0592	592//福建	厦门市					3
#define CL_ZONEID_0593	593//福建	宁德市					3
#define CL_ZONEID_0594	594//福建	莆田市					3
#define CL_ZONEID_0595	595//福建	泉州市					3
#define CL_ZONEID_0596	596//福建	漳州市					3
#define CL_ZONEID_0597	597//福建	龙岩市					3
#define CL_ZONEID_0598	598//福建	三明市					3
#define CL_ZONEID_0599	599//福建	南平市					3

#define CL_ZONEID_0710	710    //湖北	襄樊市					3
#define CL_ZONEID_0711	711    //湖北	鄂州市					3
#define CL_ZONEID_0712	712    //湖北	孝感市					3
#define CL_ZONEID_0713	713    //湖北	黄冈市					3
#define CL_ZONEID_0714	714    //湖北	黄石市					3
#define CL_ZONEID_0715	715    //湖北	咸宁市					3
#define CL_ZONEID_0716	716    //湖北	荆州市					3
#define CL_ZONEID_0717	717    //湖北	宜昌市					3
#define CL_ZONEID_0718	718    //湖北	恩施州					3
#define CL_ZONEID_0719	719    //湖北	十堰市					3

#define CL_ZONEID_0722	722    //湖北	随州市					3
#define CL_ZONEID_0724	724    //湖北	荆门市					3
#define CL_ZONEID_0728	728    //湖北	潜江市					3

#define CL_ZONEID_0730	730	//湖南	岳阳市					3
#define CL_ZONEID_0731	731	//湖南	长沙市					3
#define CL_ZONEID_0732	732	//湖南	湘潭市					3
#define CL_ZONEID_0733	733	//湖南	株州市					3
#define CL_ZONEID_0734	734	//湖南	衡阳市					3
#define CL_ZONEID_0735	735	//湖南	郴州市					3
#define CL_ZONEID_0736	736	//湖南	常德市					3
#define CL_ZONEID_0737	737	//湖南	益阳市					3
#define CL_ZONEID_0738	738	//湖南	娄底市					3
#define CL_ZONEID_0739	739	//湖南	邵阳市					3

#define CL_ZONEID_0743	743	//湖南	湘西州					3
#define CL_ZONEID_0744	744	//湖南	张家界市				3
#define CL_ZONEID_0745	745	//湖南	怀化市					3
#define CL_ZONEID_0746	746	//湖南	永州市					3

#define CL_ZONEID_0660	660	//广东	汕尾市					3
#define CL_ZONEID_0661	661	//广东	潮阳市					3
#define CL_ZONEID_0662	662	//广东	阳江市					3
#define CL_ZONEID_0663	663	//广东	揭阳市					3
#define CL_ZONEID_0668	668	//广东	茂名市					3

#define CL_ZONEID_0750	750	//广东	江门市					3
#define CL_ZONEID_0751	751	//广东	韶关市					3
#define CL_ZONEID_0752	752	//广东	惠州市					3
#define CL_ZONEID_0753	753	//广东	梅州市					3
#define CL_ZONEID_0754	754	//广东	汕头市					3
#define CL_ZONEID_0755	755	//广东	深圳市					3
#define CL_ZONEID_0756	756	//广东	珠海市					3
#define CL_ZONEID_0757	757	//广东	佛山市					3
#define CL_ZONEID_0758	758	//广东	肇庆市					3
#define CL_ZONEID_0759	759	//广东	湛江市					3

#define CL_ZONEID_0760	760	//广东	中山市					3
#define CL_ZONEID_0762	762	//广东	河源市					3
#define CL_ZONEID_0763	763	//广东	清远市					3
#define CL_ZONEID_0765	765	//广东	顺德市					3
#define CL_ZONEID_0766	766	//广东	云浮市					3
#define CL_ZONEID_0768	768	//广东	潮州市					3
#define CL_ZONEID_0769	769	//广东	东莞市					3

#define CL_ZONEID_0770	770	//广西	防城港市				3
#define CL_ZONEID_0771	771	//广西	南宁市					3
#define CL_ZONEID_0772	772	//广西	柳州市					3
#define CL_ZONEID_0773	773	//广西	桂林市					3
#define CL_ZONEID_0774	774	//广西	梧州市					3
#define CL_ZONEID_0775	775	//广西	玉林市					3
#define CL_ZONEID_0776	776	//广西	百色市					3
#define CL_ZONEID_0777	777	//广西	钦州市					3
#define CL_ZONEID_0778	778	//广西	河池市					3
#define CL_ZONEID_0779	779	//广西	北海市					3

#define CL_ZONEID_0701	701//江西	鹰潭市					3

#define CL_ZONEID_0790	790//江西	新余市					3
#define CL_ZONEID_0791	791//江西	南昌市					3
#define CL_ZONEID_0792	792//江西	九江市					3
#define CL_ZONEID_0793	793//江西	上饶市					3
#define CL_ZONEID_0794	794//江西	抚州市					3
#define CL_ZONEID_0795	795//江西	宜春市					3
#define CL_ZONEID_0796	796//江西	吉安市					3
#define CL_ZONEID_0797	797//江西	赣州市					3
#define CL_ZONEID_0798	798//江西	景德镇市				3
#define CL_ZONEID_0799	799//江西	萍乡市					3

#define CL_ZONEID_0812  812//四川	攀枝花市				3
#define CL_ZONEID_0813	813//四川	自贡市					3
#define CL_ZONEID_0816	816//四川	绵阳市					3
#define CL_ZONEID_0817	817//四川	南充市					3
#define CL_ZONEID_0818	818//四川	达州市					3
#define CL_ZONEID_0825	825//四川	遂宁市					3
#define CL_ZONEID_0826	826//四川	广安市					3
#define CL_ZONEID_0827	827//四川	巴中市					3
#define CL_ZONEID_0830	830//四川	泸州市					3
#define CL_ZONEID_0831	831//四川	宜宾市					3
#define CL_ZONEID_0832	832//四川	内江市					3
#define CL_ZONEID_0833	833//四川	乐山市					3
#define CL_ZONEID_0834	834//四川	凉山州					3
#define CL_ZONEID_0835	835//四川	雅安市					3
#define CL_ZONEID_0836	836//四川	甘孜州					3
#define CL_ZONEID_0837	837//四川	阿坝州					3
#define CL_ZONEID_0838	838//四川	德阳市					3
#define CL_ZONEID_0839	839//四川	广元市					3

#define CL_ZONEID_0851	851//贵州	贵阳市					3
#define CL_ZONEID_0852	852//贵州	遵义市					3
#define CL_ZONEID_0853	853//贵州	安顺市					3
#define CL_ZONEID_0854	854//贵州	黔南州					3
#define CL_ZONEID_0855	855//贵州	黔东南州				3
#define CL_ZONEID_0856	856//贵州	铜仁地区				3
#define CL_ZONEID_0857	857//贵州	毕节地区				3
#define CL_ZONEID_0858	858//贵州	六盘水市				3
#define CL_ZONEID_0859	859//贵州	黔西南州				3

#define CL_ZONEID_0691	691//云南	西双版纳州				3
#define CL_ZONEID_0692	692//云南	德宏州					3

#define CL_ZONEID_0870	870//云南	昭通市					3
#define CL_ZONEID_0871	871//云南	昆明市					3
#define CL_ZONEID_0872	872//云南	大理州					3
#define CL_ZONEID_0873	873//云南	红河州					3
#define CL_ZONEID_0874	874//云南	曲靖市					3
#define CL_ZONEID_0875	875//云南	保山市					3
#define CL_ZONEID_0876	876//云南	文山州					3
#define CL_ZONEID_0877	877//云南	玉溪市					3
#define CL_ZONEID_0878	878//云南	楚雄州					3
#define CL_ZONEID_0879	879//云南	思茅地区				3

#define CL_ZONEID_0883	883//云南	临沧地区				3
#define CL_ZONEID_0886	886//云南	怒江州					3
#define CL_ZONEID_0887	887//云南	迪庆州					3
#define CL_ZONEID_0888	888//云南	丽江地区				3

#define CL_ZONEID_0807	807//西藏	双湖					3

#define CL_ZONEID_0891	891//西藏	拉萨市					3
#define CL_ZONEID_0892	892//西藏	日喀则地区				3
#define CL_ZONEID_0893	893//西藏	山南地区				3
#define CL_ZONEID_0894	894//西藏	林芝地区				3
#define CL_ZONEID_0895	895//西藏	昌都地区				3
#define CL_ZONEID_0896	896//西藏	那曲地区				3
#define CL_ZONEID_0897	897//西藏	阿里地区				3

#define CL_ZONEID_0890	890//海南   儋州
#define CL_ZONEID_0898	898//海南	海口
#define CL_ZONEID_0899	899//海南	三亚

#define CL_ZONEID_0293	293//陕西	咸阳市					3
#define CL_ZONEID_0910	910//陕西	咸阳市(原)				3
#define CL_ZONEID_0911	911//陕西	延安市					3
#define CL_ZONEID_0912	912//陕西	榆林市					3
#define CL_ZONEID_0913	913//陕西	渭南市					3
#define CL_ZONEID_0914	914//陕西	商洛市					3
#define CL_ZONEID_0915	915//陕西	安康市					3
#define CL_ZONEID_0916	916//陕西	汉中市					3
#define CL_ZONEID_0917	917//陕西	宝鸡市					3
#define CL_ZONEID_0919	919//陕西	铜川市					3

#define CL_ZONEID_0930	930//甘肃	临夏州					3
#define CL_ZONEID_0931	931//甘肃	兰州市					3
#define CL_ZONEID_0932	932//甘肃	定西地区				3
#define CL_ZONEID_0933	933//甘肃	平凉市					3
#define CL_ZONEID_0934	934//甘肃	西峰市					3
#define CL_ZONEID_0935	935//甘肃	武威/金昌市				3
#define CL_ZONEID_0936	936//甘肃	张掖市					3
#define CL_ZONEID_0937	937//甘肃	嘉峪关/酒泉市			3
#define CL_ZONEID_0938	938//甘肃	天水市					3
#define CL_ZONEID_0939	939//甘肃	陇南地区				3

#define CL_ZONEID_0941	941//甘肃	甘南州					3
#define CL_ZONEID_0943	943//甘肃	白银市					3

#define CL_ZONEID_0951	951//宁夏	银川市					3
#define CL_ZONEID_0952	952//宁夏	石嘴山市				3
#define CL_ZONEID_0953	953//宁夏	吴忠市					3
#define CL_ZONEID_0954	954//宁夏	固原市					3
#define CL_ZONEID_0955	955//宁夏	中卫市					3

#define CL_ZONEID_0970	970//青海	海北州					3
#define CL_ZONEID_0971	971//青海	西宁市					3
#define CL_ZONEID_0972	972//青海	海东地区				3
#define CL_ZONEID_0973	973//青海	黄南州					3
#define CL_ZONEID_0974	974//青海	海南州					3
#define CL_ZONEID_0975	975//青海	果洛州					3
#define CL_ZONEID_0976	976//青海	玉树州					3
#define CL_ZONEID_0977	977//青海	海西州					3
#define CL_ZONEID_0979	979//青海	格尔木					3

#define CL_ZONEID_0901	901//新疆	塔城地区				3
#define CL_ZONEID_0902	902//新疆	哈密地区				3
#define CL_ZONEID_0903	903//新疆	和田地区				3
#define CL_ZONEID_0906	906//新疆	阿勒泰地区				3
#define CL_ZONEID_0908	908//新疆	克孜州		3
#define CL_ZONEID_0909	909//新疆	博尔塔拉州				3

#define CL_ZONEID_0990	990//新疆	克拉玛依市				3
#define CL_ZONEID_0991	991//新疆	乌鲁木齐市				3
#define CL_ZONEID_0992	992//新疆	伊犁州					3
#define CL_ZONEID_0993	993//新疆	石河子市				3
#define CL_ZONEID_0994	994//新疆	昌吉州					3
#define CL_ZONEID_0995	995//新疆	吐鲁番地区				3
#define CL_ZONEID_0996	996//新疆	巴音郭楞州				3
#define CL_ZONEID_0997	997//新疆	阿克苏地区				3
#define CL_ZONEID_0998	998//新疆	喀什地区				3
#define CL_ZONEID_0999	999//新疆	伊犁地区				3


#define CL_ZONEID_MAX   1023

//---------------------------------------------------------------------------


#endif
