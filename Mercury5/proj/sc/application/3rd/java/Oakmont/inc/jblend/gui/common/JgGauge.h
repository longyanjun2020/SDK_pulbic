/*
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Functions for modifying gauge component properties.
 */

#ifndef ___GUI_COMMON_GAUGE_H
#define ___GUI_COMMON_GAUGE_H

#include <JkTypes.h>

#include <gui/common/JgGUIEvent.h>
#include <gui/common/JgCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Gauge
 * @{
 */

/**
 *  The gauge value changed.
 *
 *  When the gauge value has changed, use #JginGUIEventPostEvent() to notify 
 *  this event to JBlend. 
 *  The values of the param members of the JGT_GUIEvent structure passed to 
 *  #JginGUIEventPostEvent() are indicated as follows.
 *
 *  @param param1 #JKSint32 Current value
 *  @param param2 #JKSint32 Previous value
 *  @param param3 -
 *  @param param4 -

 * @see JGT_GUIEvent::type
 */
#define JG_GUI_GAUGE_EVT_VALUE_CHANGED      (JG_GUI_EVT_END + 0x01)

/**
 * @internal
 * The maximum value of GUI gauge events
 */
#define JG_GUI_GAUGE_EVT_END              (JG_GUI_EVT_END + 0x01)

/**
 * The gauge component type
 * 
 * @see JgComGetComponentType
 */
#define JG_GAUGE   9

/**
 * The gauge handle
 * 
 * A gauge handle is data identifying the gauge. <br>
 * The gauge handle can be used as a component handle.
 * 
 * @see JGCom
 */
typedef JGCom       JGGauge;

/**
 *   The gauge mode: Normal (default)
 *
 *   In normal mode, the maximum gauge value and current value must be set
 *   accurately.
 * 
 * @see JgGaugeGetValue
 * @see JgGaugeGetMaxValue
 */
#define JG_GAUGE_MODE_NORMAL                0x00000000

/**
 *   The gauge mode: Indefinite
 * 
 *   Indefinite mode is chosen when a gauge is displayed with no maximum value
 *   determined in advance. In indefinite mode, the current gauge value must be
 *   set accurately, but the maximum can be any value that results in a suitable
 *   visual effect.
 *   The native system can change the maximum value as the current value changes,
 *   preserving the visual effect.
 * 
 * @see JgGaugeGetValue
 * @see JgGaugeGetMaxValue
 */
#define JG_GAUGE_MODE_INDEFINITE            0x00000001

/**
 *   The indefinite gauge type: Continuous
 * 
 *   A gauge whose displayed value is automatically increased by JBlend
 *   (the moment-by-moment changes cannot be indicated).
 *
 * 
 * @see JgGaugeGetIndefiniteType
 */
#define JG_GAUGE_INDEFINITE_TYPE_CONTINUOUS  0x00000000

/**
 *   The indefinite gauge type: Incremental
 * 
 *   A gauge whose displayed value is increased by the Java application.
 *
 * 
 * @see JgGaugeGetIndefiniteType
 */
#define JG_GAUGE_INDEFINITE_TYPE_INCREMENTAL 0x00000001

/**
 *   Gets the gauge mode.
 * 
 *   @param gauge The gauge handle
 *   @return The gauge mode is returned as one of the following values.
 * <br><br>
 * <ul>
 *  <li> #JG_GAUGE_MODE_NORMAL
 *  <li> #JG_GAUGE_MODE_INDEFINITE
 * </ul>
 * 
 * <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When gauge is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgGaugeGetMode(JGGauge gauge);

/**
 *   Gets the type of the indefinite gauge.
 *
 *   @param gauge The gauge handle
 *   @return      The gauge type is returned as one of the following values.
 *                <ul>
 *                 <li> #JG_GAUGE_INDEFINITE_TYPE_CONTINUOUS
 *                 <li> #JG_GAUGE_INDEFINITE_TYPE_INCREMENTAL
 *                </ul>
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When gauge is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgGaugeGetIndefiniteType(JGGauge gauge);

/**
 * Gets the gauge value.
 * 
 * @param gauge
 *        The gauge handle
 * @return
 *        The gauge value is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When gauge is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgGaugeGetValue(JGGauge gauge);

/**
 * Gets the gauge maximum value.
 * 
 * @param gauge
 *        The gauge handle
 * @return
 *        The gauge maximum value is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When gauge is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgGaugeGetMaxValue(JGGauge gauge);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_GAUGE_H */

