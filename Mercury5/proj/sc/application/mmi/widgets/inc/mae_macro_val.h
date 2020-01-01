#define ApBegin(thmId, apid )

#define WndBegin(wid) static const wid##_t t##wid ={

#define WdgBegin(wdgClsid, wdgName) { //0x55AA55AA, sizeof(struct wdgName##_t_), 123,

#define ChildBegin(wdgClsid, order, childName) {


#define ChildEnd(wdgClsid, order, childName) },


#define VTMWdgBegin(wdgClsid, WdgId, wdgName) {


#define VTMWdgEnd(wdgClsid, WdgId, wdgName) },


#define WdgEnd(wdgClsid, wdgName) },

#define WndEnd(wid)  };

#define ApEnd(thmId, apid )

#define DynamicStructBegin(name) {
#define DynamicStructEnd(name) },

