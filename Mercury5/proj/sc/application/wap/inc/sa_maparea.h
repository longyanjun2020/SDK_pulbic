
 /**
 * @file
 * Deal <map>,<Area> Tag
 */

#ifndef __ALYS_MAPAREA_H
#define __ALYS_MAPAREA_H

#define COORDS_MAX 20
#ifndef PI
#define PI 3.14159
#endif
/** map item struct*/
typedef struct _MapStruct
{
    int8_t * MapName;
    void * AreaList;
}MapStruct;

/** area item struct */
typedef struct _AreaStruct
{
    int32_t   Shape;
    int8_t * Href;
    int8_t * Coords;
}AreaStruct;

#ifdef __cplusplus
extern "C" {
#endif

/**add map item to the map list
*   \param mapname  name of the map
*/
void fnDBA_AddMapToList(int8_t * mapname);

/**Add Area item to Area List
*   \param  shape       shape of area
*   \param  href        href to link when clicked
*   \param  coords      group of positions
*/
void fnDBA_AddAreaToList(int8_t * shape,int8_t * href,int8_t * coords);

/**drop map-area data list
*   \param  ctxt        handle of page context
*/
void fnDBA_DropMapArea(T_DB_ParseCtxtPtr  ctxt);

#ifdef __cplusplus
}
#endif

#endif
