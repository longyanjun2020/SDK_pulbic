/*
 * Copyright mstar. All Rights Reserved.
 * $Id: /include/uapps/wap/esmpclient/esmpclient_event.msg#2 $
 */

/*
 * This is the JavaScript event message file.
 *
 * The format for each JS event message is:
 *
 * MSG_DEF(<EVENT_INDEX_MACRO>, <EVENT_INDEX_NUMBER>, <EVENT_NAME>)
 *
 * where ;
 * <EVENT_INDEX_MACRO> is a legal C identifer that will be used in the
 * JS client source.
 *
 * <EVENT_INDEX_NUMBER> is an unique integral value identifying this event.
 *
 * <EVENT_NAME> is an event name index from the enum in jsexn.c;
 * JSEXN_NONE for none.  The given exception index will be raised by the
 * engine when the corresponding error occurs.
 *
 * e.g.
 *
 * EVENT_DEF(CJS_ONCLICK_INDEX,     0,      "onclick")
 *
 */

EVENT_DEF(CJS_ONCLICK_INDEX,     0,     "onclick")
EVENT_DEF(CJS_ONBLUR_INDEX,      1,     "onblur")
EVENT_DEF(CJS_ONFOCUS_INDEX,     2,     "onfocus")
EVENT_DEF(CJS_ONSUBMIT_INDEX,    3,     "onsubmit")
EVENT_DEF(CJS_ONRESET_INDEX,     4,     "onreset")
EVENT_DEF(CJS_ONLOAD_INDEX,      5,     "onload")
EVENT_DEF(CJS_ONUNLOAD_INDEX,    6,     "onunload")
EVENT_DEF(CJS_ONCHANGE_INDEX,    7,     "onchange")
EVENT_DEF(CJS_ONSELECT_INDEX,    8,     "onselect")
EVENT_DEF(CJS_ONDBLCLICK_INDEX,  9,     "ondblclick")

#ifdef SUPPORT_KEYBOARD_MOUSE
EVENT_DEF(CJS_ONKEYPRESS_INDEX,  10,    "onkeypress")
EVENT_DEF(CJS_ONKEYDOWN_INDEX,   11,    "onkeydown")
EVENT_DEF(CJS_ONKEYUP_INDEX,     12,    "onkeyup")
EVENT_DEF(CJS_ONABORT_INDEX,     13,    "onabort")
EVENT_DEF(CJS_ONERROR_INDEX,     14,    "onerror")

EVENT_DEF(CJS_ONMOUSEDOWN_INDEX, 15,    "onmousedown")
EVENT_DEF(CJS_ONMOUSEUP_INDEX,   16,    "onmouseup")
EVENT_DEF(CJS_ONMOUSEOVER_INDEX, 17,    "onmouseover")
EVENT_DEF(CJS_ONMOUSEMOVE_INDEX, 18,    "onmousemove")
EVENT_DEF(CJS_ONMOUSEOUT_INDEX,  19,    "onmouseout")
#endif /* SUPPORT_KEYBOARD_MOUSE */
