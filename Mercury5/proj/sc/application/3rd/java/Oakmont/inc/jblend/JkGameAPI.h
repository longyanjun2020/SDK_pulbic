/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkGameAPI.h
 *  Game JSI
 */

/**
 * @addtogroup Game_JSI
 * @anchor     __ameAPIRef
 * @{
 */

#ifndef ___MIDPSYS_JK_GAMEAPI_H
#define ___MIDPSYS_JK_GAMEAPI_H

#include "JkTypes.h"
#include "JkGraphics.h"
#include "JkVideo.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 *  The Up key. This is the Up key bit in the value returned by #JkGameGetKeyState().
 */
#define JKGAME_KEY_UP           0x00000002
/**
 *  The Down key. This is the Down key bit in the value returned by #JkGameGetKeyState().
 */
#define JKGAME_KEY_DOWN         0x00000040
/**
 *  The Left key. This is the Left key bit in the value returned by #JkGameGetKeyState().
 */
#define JKGAME_KEY_LEFT         0x00000004
/**
 *  The Right key. This is the Right key bit in the value returned by #JkGameGetKeyState().
 */
#define JKGAME_KEY_RIGHT        0x00000020
/**
 *  The Select key. This is the Select key bit in the value returned by #JkGameGetKeyState().
 */
#define JKGAME_KEY_FIRE         0x00000100
/**
 *  The A key. This is the A key bit in the value returned by #JkGameGetKeyState().
 */
#define JKGAME_KEY_A            0x00000200
/**
 *  The B key. This is the B key bit in the value returned by #JkGameGetKeyState().
 */
#define JKGAME_KEY_B            0x00000400
/**
 *  The C key. This is the C key bit in the value returned by #JkGameGetKeyState().
 */
#define JKGAME_KEY_C            0x00000800
/**
 *  The D key. This is the D key bit in the value returned by #JkGameGetKeyState().
 */
#define JKGAME_KEY_D            0x00001000


/**
 *  Get the game key states from the game input device.
 *
 * @return
 *  Return game key states as per the bit assignments below.<br>
 *   #JKGAME_KEY_UP<br>
 *   #JKGAME_KEY_DOWN<br>
 *   #JKGAME_KEY_LEFT<br>
 *   #JKGAME_KEY_RIGHT<br>
 *   #JKGAME_KEY_FIRE<br>
 *   #JKGAME_KEY_A<br>
 *   #JKGAME_KEY_B<br>
 *   #JKGAME_KEY_C<br>
 *   #JKGAME_KEY_D
 *
 *  <p>
 *  Return the game key states. The purpose of this function is to prevent the key information
 *  used by Java applications from lagging behind the actual hardware states.<br>
 *  </p><p>
 *  Set bits in the return value as in the table below.
 *  </p>
 *  <table>
 *   <tr>
 *    <td><b>Key state</b></td>
 *    <td><b>Return value bits</b></td>
 *   </tr>
 *   <tr>
 *    <td> Currently pressed, or pressed at least once since the previous time #JkGameGetKeyState() was called </td>
 *    <td> 1 </td>
 *   </tr>
 *   <tr>
 *    <td> Currently released, and not pressed since the previous time #JkGameGetKeyState() was called. </td>
 *    <td> 0 </td>
 *   </tr>
 *  </table>
 *
 *  <p>The first time #JkGameGetKeyState() is called, set this information based only on the state at that point in time.</p>
 *
 *  The mapping of game key bits to actual keys is dependent on the native system specifications.<br>
 *
 *  This function corresponds to the javax.microedition.lcdui.game.GameCanvas class getKeyStates() method.
 *
 */
JKUint32    JkGameGetKeyState (void);



/**
 * Draw, rotating 90 degrees clockwise.
 *
 * This constant is designated as a parameter when #JKGAME_SET_TRANSFORM is
 * designated as one of the #JkGameSetAttribute() categories.
 */
#define JKGAME_DRAW_ROTATE90    0x0001
/**
 * Draw, rotating 180 degrees clockwise.
 *
 * This constant is designated as a parameter when #JKGAME_SET_TRANSFORM is
 * designated as one of the #JkGameSetAttribute() categories.
 */
#define JKGAME_DRAW_ROTATE180   0x0002
/**
 * Draw, rotating 270 degrees clockwise.
 *
 * This constant is designated as a parameter when #JKGAME_SET_TRANSFORM is
 * designated as one of the #JkGameSetAttribute() categories.
 */
#define JKGAME_DRAW_ROTATE270   0x0003
/**
 * Draw, flipping horizontally.
 *
 * This constant is designated as a parameter when #JKGAME_SET_TRANSFORM is
 * designated as one of the #JkGameSetAttribute() categories.
 */
#define JKGAME_DRAW_FLIP_H      0x0004



/**
 *      A graphics primitive type describing a sprite.
 */
#define JKGAME_PRIMTYPE_2DSPRITE        1
/**
 *      A graphics primitive type describing a tiled layer.
 */
#define JKGAME_PRIMTYPE_TILEDLAYER      2


/**
 * Create a graphics primitive.
 *
 * @param nPrimitiveType Identifier of the type of graphics primitive to be created.
 *                       Either of the following types is designated.
 *                       <ul>
 *                        <li>#JKGAME_PRIMTYPE_2DSPRITE
 *                        <li>#JKGAME_PRIMTYPE_TILEDLAYER
 *                       </ul>
 * @param pArg           A pointer to the initialization parameters array.
 *                       This pointer remains in effect until return from this function.
 *
 * @return  If the graphics primitive was successfully created, return a graphics primitive handle.
 *          JBlend uses this handle as a parameter when calling other JSIs. <br>
 *          If graphics primitive creation failed, return #JK_INVALID_HANDLE.
 *
 *  Create a new graphics primitive based on the graphics primitive type designated in the
 *  nPrimitiveType parameter.
 *  The initialization parameters are stored in the memory area indicated by the pArg parameter.
 *  The contents of the initialization parameters differ depending on the graphic primitive type.
 *
 * <dl>
 *  <dt><b>Sprite</b></dt>
 *   <dd>When nPrimitiveType is #JKGAME_PRIMTYPE_2DSPRITE, the initialization
 *       parameters designated by pArg have the format below.
 * <pre>
 *     +-------------+
 * + 0 | hImage      | Handle of the image type used as texture, either
 *     |             | JKOffScreenHandle or JKImageHandle.
 *     +-------------+
 * + 4 | bOffScreen  | hImage type (JK_TRUE: JKOffScreenHandle type/
 *     |             |              JK_FALSE: JKImageHandle type)
 *     +-------------+
 * + 8 | frameWidth  | Width (in pixels) of the area used as
 *     |             | the sprite frame in the texture.
 *     +-------------+
 * +12 | frameHeight | Height (in pixels) of the area used as
 *     |             | the sprite frame in the texture.
 *     +-------------+
 * </pre>
 *        bOffScreen stores a value indicating the type of image used as a texture, namely,
 *        JK_TRUE if hImage is JKOffScreenHandle, and JK_FALSE if hImage is JKImageHandle.
 *        <br><br>
 *        Indicated below are the necessary attribute values for sprite primitives,
 *        and the constant values designated in #JkGameSetAttribute() for setting these attributes.
 *        See the explanations of each constant for the initial attribute values.
 *  <table>
 *   <tr>
 *    <td><b>Attribute value<b></td>    <td><b>Constant value designated in #JkGameSetAttribute()<b></td>
 *   </tr><tr>
 *    <td>Sprite collision rectangle</td>       <td>#JKGAME_SET_COLLISIONRECT</td>
 *   </tr><tr>
 *    <td>Current sprite frame</td>       <td>#JKGAME_SET_TEXTUREUV </td>
 *   </tr><tr>
 *    <td>Sprite center</td>             <td>#JKGAME_SET_CENTER</td>
 *   </tr><tr>
 *    <td>Sprite image transform option</td> <td>#JKGAME_SET_TRANSFORM</td>
 *   </tr>
 *  </table>
 * </dd>
 *
 *  <dt><b>Tiled layer</b></dt>
 *   <dd>When nPrimitiveType is #JKGAME_PRIMTYPE_TILEDLAYER, the initialization
 *       parameters designated by pArg have the format below.
 * <pre>
 *       +---------------+
 *   + 0 |  hImage       | Handle of image used as texture
 *       |               |
 *       +---------------+
 *   + 4 |  bOffScreen   | JK_TRUE: hImage is JKOffScreenHandle;
 *       |               | JK_FALSE: hImage is JKImageHandle
 *       +---------------+
 *   + 8 |  tileWidth    | Width of area used as tile in the texture
 *       |               |
 *       +---------------+
 *   +12 |  tileHeight   | Height of area used as tile in the texture
 *       |               |
 *       +---------------+
 *   +16 |  gridColumns  | Grid columns of tiled layer
 *       |               |
 *       +---------------+
 *   +20 |  gridRows     | Grid rows of tiled layer
 *       |               |
 *       +---------------+
 * </pre>
 *        bOffScreen stores a value indicating the type of image used as a texture, namely,
 *        JK_TRUE if hImage is JKOffScreenHandle, and JK_FALSE if hImage is JKImageHandle.
 *        <br>
 *        As the initial state when a tiled layer is created, set the tile index of each cell
 *        to 0 (empty cell).
 *   </dd>
 * </dl>
 *
 *  Initialization parameters contain the minimum information needed for graphics primitive creation.
 *  Information not included in these parameters is not stipulated for this function interface.
 *  If values specified in MIDP are to be designated, set these values internally.
 *
 */
JKHandle    JkGameCreatePrimitive (JKSint32 nPrimitiveType, const JKUint32 *pArg);



/**
 *  Discard a graphics primitive.
 *
 * @param nPrimitiveType Identifier of the graphics primitive type.
 *                       Either of the following types is designated.
 *                       <ul>
 *                        <li>#JKGAME_PRIMTYPE_2DSPRITE
 *                        <li>#JKGAME_PRIMTYPE_TILEDLAYER
 *                       </ul>
 * @param hPrimitive     Graphics primitive handle.
 *                       The value returned by #JkGameCreatePrimitive() is designated.
 *
 * JBlend calls this function when a graphics primitive created by #JkGameCreatePrimitive()
 * is no longer needed.
 *
 * Discarding of the texture (offscreen or immutable image) set for the graphics primitive is
 * handled by Low-level Graphics Component. Make sure this is not done by the Game Function.
 *
 */
void        JkGameDeletePrimitive (JKSint32 nPrimitiveType, JKHandle hPrimitive);



/**
 *  Draw a graphics primitive.
 *
 * @param g              Handle of the graphics context where the primitive is to be drawn.
 * @param nPrimitiveType Identifier indicating the type of graphics primitive to be drawn.
 *                       Either of the following is designated.
 *                       <ul>
 *                        <li>#JKGAME_PRIMTYPE_2DSPRITE
 *                        <li>#JKGAME_PRIMTYPE_TILEDLAYER
 *                       </ul>
 * @param hPrimitive     Handle of the graphics primitive.
 *                       The value returned by #JkGameCreatePrimitive() is designated.
 * @param x              The x parameter indicating the drawing position in the graphics context.
 * @param y              The y parameter indicating the drawing position in the graphics context.
 *
 * Draw the graphics primitive in the designated graphics context.<br>
 *
 * If the graphics primitive is a sprite, transform the current sprite frame contents based on the
 * sprite transform option and center settings, then draw the result in the destination graphics context.
 * Drawing position (x y) are the screen coordinates of the result which applied the transformation of a sprite.
 * For example, When #JKGAME_DRAW_ROTATE90 was applied to the sprite,
 * (x,y) points is the coordinates of the upper left corner of the sprite which rotated 90 degrees.
 *
 * If the graphics primitive is a tiled layer, draw the entire grid in the destination graphics context
 * in accord with the tile index settings for each grid cell.
 *
 */
void        JkGameDrawPrimitive (JKGraphicsContext g, JKSint32 nPrimitiveType, JKHandle hPrimitive, JKSint32 x, JKSint32 y);



/**
 *  Set a tile index in a tiled layer cell.
 *
 *  This value is designated in the nAttrType parameter of #JkGameSetAttribute().
 *  When this value is designated, the parameters indicated by the pArg parameter of
 *  #JkGameSetAttribute() have the format below.
 *
 * <pre>
 *      +---------------+
 *  + 0 | col           | Horizontal position of cell
 *      +---------------+
 *  + 4 | row           | Vertical position of cell
 *      +---------------+
 *  + 8 | numCols       | Number of cells in horizontal direction
 *      +---------------+
 *  +12 | numRows       | Number of cells in vertical direction
 *      +---------------+
 *  +16 | tileIndex     | Tile index
 *      +---------------+
 * </pre>
 *
 *  With (col, row) as the upper left cell, set the value of tileIndex as the tile index to be set for
 *  multiple cells in an area made up of numCols cells in the horizontal direction and numRows cells
 *  in the vertical direction.
 *
 *  Make it possible to set the tile index of cells as static tile, animated tile, or empty cell
 *  (index=0).
 *
 *  The functioning when this value is designated in #JkGameSetAttribute() corresponds to that of
 *  the javax.microedition.lcdui.game.TiledLayer class fillCells() method and setCell() method.
 *
 * @see JkGameSetAttribute()
 * @see JKGAME_SET_ANIMTILE
 */
#define JKGAME_SET_CELL             0

/**
 *  Set the texture to be used for a graphics primitive.
 *
 *  This value is designated in the nAttrType parameter of #JkGameSetAttribute().
 *  When this value is designated, the parameters indicated by the pArg parameter of
 *  #JkGameSetAttribute() have the format below.
 *
 * <pre>
 *     +-------------+
 * + 0 | hImage      | Handle of the image type, either JKOffScreenHandle
 *     |             | or JKImageHandle.
 *     +-------------+
 * + 4 | bOffScreen  | hImage type  (JK_TRUE: JKOffScreenHandle type/
 *     |             |               JK_FALSE: JKImageHandle type)
 *     +-------------+
 * + 8 | frameWidth  | Width (in pixels) of the texture area used by the
 *     |             | sprite frame or by one tile of the tiled layer.
 *     +-------------+
 * +12 | frameHeight | Height (in pixels) of the texture area used by the
 *     |             | sprite frame or by one tile of the tiled layer.
 *     +-------------+
 * </pre>
 *
 *  Update the parameters set by #JkGameCreatePrimitive() for sprite primitives.
 *  If the native system stores internal information relating to these parameters, that
 *  information must also be updated.
 *
 *  Of the parameters set by #JkGameCreatePrimitive() for tiled layer primitives,
 *  update those other than gridColumns and gridRows with the above parameter values.
 *  If the native system stores internal information relating to these parameters, that
 *  information must also be updated.
 *
 *  Processing such as the deletion of the previously set JKOffScreenHandle or JKImageHandle
 *  type handle for sprites and tiled layers is handled by Low-level Graphics Component.
 *  Make sure this processing is not done by the Game Function.
 *
 *  The functioning when JKGAME_SET_TEXTURE is set in #JkGameSetAttribute() corresponds to that
 *  of the javax.microedition.lcdui.game.Sprite class setImage() method for sprites, or of the
 *  javax.microedition.lcdui.game.TiledLayer class setStaticTileSet() method for tiled layers.
 *
 * @see JkGameSetAttribute()
 */
#define JKGAME_SET_TEXTURE          1

/**
 *  Set the coordinate position of the current sprite frame in texture.
 *
 *  This value is designated in the nAttrType parameter of #JkGameSetAttribute().
 *  When this value is designated, the parameters indicated by the pArg parameter of
 *  #JkGameSetAttribute() have the format below.
 *
 * <pre>
 *      +---------------+
 *  + 0 | u             | Horizontal position of sprite frame in texture
 *      +---------------+
 *  + 4 | v             | Vertical position of sprite frame in texture
 *      +---------------+
 * </pre>
 * Parameters u and v are designated as integer multiples of the sprite frame width and height,
 * respectively.<br>
 *
 *  In the initial state after a sprite primitive is created, set the upper left
 *  corner frame as the current sprite frame. That is, set both u and v parameters to 0.
 *
 * @see JkGameSetAttribute()
 */
#define JKGAME_SET_TEXTUREUV        2

/**
 *  Set a sprite collision rectangle.
 *
 *  This value is designated in the nAttrType parameter of #JkGameSetAttribute().
 *  It is designated only for a sprite.
 *  When this value is designated, the parameters indicated by the pArg parameter of
 *  #JkGameSetAttribute() have the format below.
 *
 * <pre>
 *      +---------------+
 *  + 0 | x             | Horizontal position of the collision rectangle
 *      +---------------+
 *  + 4 | y             | Vertical position of the collision rectangle
 *      +---------------+
 *  + 8 | width         | Width (in pixels) of the collision rectangle
 *      +---------------+
 *  +12 | height        | Height (in pixels) of the collision rectangle
 *      +---------------+
 * </pre>
 *
 *  The x,y coordinates indicate the position relative to the upper left corner of the sprite,
 *  before transformation processing. <br>
 *
 *  In the initial state after a sprite primitive is created, set the x and y coordinates
 *  of the collision rectangle to 0 and match its width and height to the sprite frame width and height.
 *
 *  The functioning when this value is designated in #JkGameSetAttribute() corresponds to that of
 *  the javax.microedition.lcdui.game.Sprite class defineCollisionRectangle() method.
 *
 * @see JkGameSetAttribute()
 */
#define JKGAME_SET_COLLISIONRECT    3

/**
 *  Set the sprite center.
 *
 *  This value is designated in the nAttrType parameter of #JkGameSetAttribute().
 *  It is designated only for a sprite.
 *  When this value is designated, the parameters indicated by the pArg parameter of
 *  #JkGameSetAttribute() have the format below.
 *
 * <pre>
 *      +---------------+
 *  + 0 | x             | Horizontal position of center
 *      |               |  (relative x coordinate in the sprite)
 *      +---------------+
 *  + 4 | y             | Vertical position of center
 *      |               |  (relative y coordinate in the sprite)
 *      +---------------+
 * </pre>
 *
 *  The x,y coordinates indicate the position relative to the upper left corner of the sprite,
 *  before transformation processing. <br>
 *
 *  In the initial state after a sprite primitive is created, the center coordinates
 *  should be (0,0). In other words, set the above parameters x and y to 0.
 *
 *  The functioning when this value is designated in #JkGameSetAttribute() corresponds to that of
 *  the javax.microedition.lcdui.game.Sprite class defineReferencePixel() method.
 *
 * @see JkGameSetAttribute()
 */
#define JKGAME_SET_CENTER           4

/**
 *  Set the sprite image transform option.
 *
 *  This value is designated in the nAttrType parameter of #JkGameSetAttribute().
 *  It is designated only for a sprite.
 *  When this value is designated, the parameter indicated by the pArg parameter of
 *  #JkGameSetAttribute() has the format below.
 *
 * <pre>
 *      +---------------+
 *  + 0 | transform     | Sprite image transform option
 *      +---------------+
 * </pre>
 *
 *  The functioning when this value is designated in #JkGameSetAttribute() corresponds to that of
 *  the javax.microedition.lcdui.game.Sprite class setTransform() method.
 *  Adhere to the constant definitions below when interpreting the value of the transform parameter
 *  indicated by the pArg parameter.
 *  <ul>
 *   <li>#JKGAME_DRAW_ROTATE90
 *   <li>#JKGAME_DRAW_ROTATE180
 *   <li>#JKGAME_DRAW_ROTATE270
 *   <li>#JKGAME_DRAW_FLIP_H
 *  </ul>
 *  Bit 2 is for designating horizontal flipping (#JKGAME_DRAW_FLIP_H), and bits 1-0 for rotation
 *  (#JKGAME_DRAW_ROTATE90/ #JKGAME_DRAW_ROTATE180/ #JKGAME_DRAW_ROTATE270). A value of 0 means no
 *  flipping or rotation is designated.
 *  Apply image transformation in the order of <_em>horizontal flipping, then rotation</_em>.
 *
 *  In the initial state after a sprite primitive is created, no image transform option
 *  should be set. That is, start with the transform parameter set to 0.
 *
 * @see JkGameSetAttribute()
 * @image html sprite_transforms.gif    "Figure 1. Sprite Transforms"
 */
#define JKGAME_SET_TRANSFORM        5

/**
 *  Set animated tile information for a tiled layer.
 *
 *  This value is designated in the nAttrType parameter of #JkGameSetAttribute().
 *  It is designated only for a tiled layer.
 *  When this value is designated, the parameters indicated by the pArg parameter of
 *  #JkGameSetAttribute() have the format below.
 *
 * <pre>
 *      +-----------------------+
 *  + 0 | animatedTileIndex     | Animated tile index
 *      +-----------------------+
 *  + 4 | staticTileIndex       | Related tile index
 *      +-----------------------+
 * </pre>
 *
 *  The value of animatedTileIndex is <_em>always negative</_em>. The first animated tile is -1, the second is -2.
 *  The animated tile index may be designated as a tile index of a tiled layer cell using #JKGAME_SET_CELL.
 *
 *  The functioning when this value is designated in #JkGameSetAttribute() corresponds to that of
 *  the javax.microedition.lcdui.game.TiledLayer class setAnimatedTile() method.
 *
 * @see JkGameSetAttribute()
 * @see JKGAME_SET_CELL
 */
#define JKGAME_SET_ANIMTILE         6


/**
 *  Get the contents of the designated tiled layer cell.
 *
 *  This value is designated in the nAttrType parameter of #JkGameGetAttribute().
 *  It is designated only for a tiled layer.
 *  When this value is designated, the parameters indicated by the pArg parameter of
 *  #JkGameGetAttribute() have the format below.
 *
 * <pre>
 *      +---------------+
 *  + 0 | x             | Horizontal position of the cell
 *      +---------------+
 *  + 4 | y             | Vertical position of the cell
 *      +---------------+
 * </pre>
 *
 *  Put the tile index of the cell at position x, y in the memory area indicated by the pResult
 *  parameter of #JkGameGetAttribute(), as illustrated below.
 *
 * <pre>
 *      +---------------+
 *  + 0 | tileIndex     | Tile index set in the cell
 *      +---------------+
 * </pre>
 *
 *  The functioning when this value is designated in #JkGameGetAttribute() corresponds to that of
 *  the javax.microedition.lcdui.game.TiledLayer class getCell() method.
 * @see JkGameGetAttribute()
 */
#define JKGAME_GET_CELL             0

/**
 *  Get the static tile index corresponding to an animated tile index of a tiled layer.
 *
 *  This value is designated in the nAttrType parameter of #JkGameGetAttribute().
 *  It is designated only for a tiled layer.
 *  The value of animatedTileIndex is <_em>always negative</_em>. The first animated tile is -1, the second is -2.
 *  When this value is designated, the parameters indicated by the pArg parameter of
 *  #JkGameGetAttribute() have the format below.
 *
 * <pre>
 *      +-----------------------+
 *  + 0 | animatedTileIndex     | Animated tile index
 *      +-----------------------+
 * </pre>
 *
 *  Put the staticTileIndex related with animatedTileIndex in the memory area indicated by the pResult
 *  parameter of #JkGameGetAttribute(), as illustrated below.
 *
 * <pre>
 *      +-----------------------+
 *  + 0 | staticTileIndex       | Related tile index
 *      +-----------------------+
 * </pre>
 *
 *  The functioning when this value is designated in #JkGameGetAttribute() corresponds to that of
 *  the javax.microedition.lcdui.game.TiledLayer class getAnimatedTile() method.
 * @see JkGameGetAttribute()
 */
#define JKGAME_GET_ANIMTILE         1

/**
 *                       Set graphics primitive attributes.
 * @param nPrimitiveType Identifier indicating the graphics primitive type.
 *                       Either of the following values is designated.
 *                       <ul>
 *                        <li>#JKGAME_PRIMTYPE_2DSPRITE
 *                        <li>#JKGAME_PRIMTYPE_TILEDLAYER
 *                       </ul>
 * @param hPrimitive     Handle of the graphics primitive.
 *                       The value returned by #JkGameCreatePrimitive() is designated.
 * @param nAttrType      The type of attribute to be set.<br>
 *                       When #JKGAME_PRIMTYPE_2DSPRITE is designated as nPrimitiveType,
 *                       one of the following is designated.
 *                       <ul>
 *                        <li>#JKGAME_SET_TEXTURE
 *                        <li>#JKGAME_SET_TEXTUREUV
 *                        <li>#JKGAME_SET_COLLISIONRECT
 *                        <li>#JKGAME_SET_CENTER
 *                        <li>#JKGAME_SET_TRANSFORM
 *                       </ul>
 *                       When #JKGAME_PRIMTYPE_TILEDLAYER  is designated as nPrimitiveType,
 *                       one of the following is designated.
 *                       <ul>
 *                        <li>#JKGAME_SET_TEXTURE
 *                        <li>#JKGAME_SET_ANIMTILE
 *                        <li>#JKGAME_SET_CELL
 *                       </ul>
 * @param pArg           An array of the attribute data settings. The contents differ depending
 *                       on the attribute type.
 *
 * Set the graphics primitive attributes designated in the nAttrType parameter.
 * Attribute values are designated in the memory area indicated by the pArg parameter.
 * For details see the explanations of the constants designated in nAttrType.
 *
 *
 * @see JKGAME_SET_TEXTURE
 * @see JKGAME_SET_TEXTUREUV
 * @see JKGAME_SET_COLLISIONRECT
 * @see JKGAME_SET_CENTER
 * @see JKGAME_SET_TRANSFORM
 * @see JKGAME_SET_CELL
 * @see JKGAME_SET_ANIMTILE
 */
void    JkGameSetAttribute (JKSint32 nPrimitiveType, JKHandle hPrimitive, JKSint32 nAttrType, const JKUint32 *pArg);


/**
 *          Get the attribute settings of a graphics primitive.
 *
 * @param nPrimitiveType Identifier indicating the graphics primitive type.
 *                       #JKGAME_PRIMTYPE_TILEDLAYER is designated.
 * @param hPrimitive     Handle of the graphics primitive.
 *                       The value returned by #JkGameCreatePrimitive() is designated.
 * @param nAttrType      The type of attribute.
 *                       Either of the following values is designated.
 *                       <ul>
 *                        <li>#JKGAME_GET_CELL
 *                        <li>#JKGAME_GET_ANIMTILE
 *                       </ul>
 * @param pArg           Pointer to an array of parameters designated for acquisition.
 *                       The contents differ with the attribute type.
 *                       If the parameter is not required, #JK_NULL is set.
 * @param pResult        Pointer to an array for storing the attribute data.
 *
 * Get the graphics primitive attributes designated in nAttrType and put the results in the memory area
 * designated in the pResult parameter.
 * For details of the attributes to be acquired, see the explanations of the constants designated in nAttrType.
 *
 * @see JKGAME_GET_CELL
 * @see JKGAME_GET_ANIMTILE
 */
JKBool  JkGameGetAttribute (JKSint32 nPrimitiveType, JKHandle hPrimitive, JKSint32 nAttrType, const JKUint32 *pArg, JKUint32 *pResult);

/**
 *  Check for collision between sprites.
 *
 *  This constant is designated in the nTargetType parameter of #JkGameCollisionDetect2D().
 */
#define JKGAME_COLLIDE_WITH_SPRITE          0
/**
 *  Check for collision between a sprite and a tiled layer.
 *
 *  This constant is designated in the nTargetType parameter of #JkGameCollisionDetect2D().
 */
#define JKGAME_COLLIDE_WITH_TILEDLAYER      1
/**
 *  Check for collision between a sprite and offscreen image.
 *
 *  This constant is designated in the nTargetType parameter of #JkGameCollisionDetect2D().
 */
#define JKGAME_COLLIDE_WITH_OFFSCREEN       2
/**
 *  Check for collision between a sprite and immutable image.
 *
 *  This constant is designated in the nTargetType parameter of #JkGameCollisionDetect2D().
 */
#define JKGAME_COLLIDE_WITH_IMMUTABLE       3

/**
 *  Check for collision on the screen between a sprite and another graphics primitive or image.
 *
 * @param   pArg Pointer to an array containing the parameters for collision detection use.
 * @return       Return the collision detection result.<br>
 *               Collision: #JK_TRUE <br>
 *               No collision: #JK_FALSE
 *
 * The parameters indicated by pArg have the format below.
 * <pre>
 *      +---------------+
 *  + 0 | bPixelLevel   |   Whether pixel-level detection is used
 *      |               |
 *      +---------------+
 *  + 4 | hSprite       |   Handle of sprite to be checked for collision
 *      |               |
 *      +---------------+
 *  + 8 | spritePosX    |   Horizontal position of sprite to be checked
 *      |               |   for collision
 *      +---------------+
 *  +12 | spritePosY    |   Vertical position of sprite to be checked
 *      |               |    for collision
 *      +---------------+
 *  +16 | nTargetType   |   Type of target object with which sprite
 *      |               |    collision is to be checked
 *      +---------------+
 *  +20 | nTargetHandle |   Handle of target object
 *      |               |
 *      +---------------+
 *  +24 | targetPosX    |   Horizontal position of target object
 *      |               |
 *      +---------------+
 *  +28 | targetPosY    |   Vertical position of target object
 *      |               |
 *      +---------------+
 * </pre>
 *
 * <dl>
 *  <dt><b>bPixelLevel</b></dt>
 *   <dd> Designates whether pixel-level detection is to be performed.
 *        If bPixelLevel is JK_TRUE, perform pixel-level collision detection.<br>
 *        Pixel-level collision detection is performed by comparing the alpha value of each pixel.
 *        Therefore, if the alpha value of each pixel is not 0, it is in a collision state.
 *        for example, --  In case pixel format is 0xAARRGGBB, pixel value 0xFFFFFFFF vs 0x00FFFFFF does not collide.
 *   </dd>
 *  <dt><b>hSprite</b></dt>
 *   <dd>Handle of the sprite to be checked for collision
 *       The value returned by #JkGameCreatePrimitive() is designated.
 *   </dd>
 *  <dt><b>spritePosX, spritePosY</b></dt>
 *   <dd>The x and y coordinates of the sprite virtual position on the screen.
 *       If an image transform option is designated by #JKGAME_SET_TRANSFORM, these coordinates
 *       indicate the sprite frame position after image transformation.
 *   </dd>
 *  <dt><b>nTargetType</b></dt>
 *   <dd>
 *       Type of target object with which sprite collision is to be checked.
 *       One of the following is designated.<br>
 *                       <ul>
 *                        <li>#JKGAME_COLLIDE_WITH_SPRITE <br>
 *                        <li>#JKGAME_COLLIDE_WITH_TILEDLAYER <br>
 *                        <li>#JKGAME_COLLIDE_WITH_OFFSCREEN <br>
 *                        <li>#JKGAME_COLLIDE_WITH_IMMUTABLE <br>
 *                       </ul>
 *   </dd>
 *  <dt><b>nTargetHandle</b></dt>
 *   <dd>
 *       Handle of the target object.
 *       A handle corresponding to the value of nTargetType is designated.
 *                       <ul>
 *                         <li>If #JKGAME_COLLIDE_WITH_SPRITE,
 *                           a sprite handle
 *                         <li>If #JKGAME_COLLIDE_WITH_TILEDLAYER,
 *                           a tiled layer handle
 *                         <li>If #JKGAME_COLLIDE_WITH_OFFSCREEN ,
 *                           an offscreen image handle (#JKOffScreenHandle type)
 *                         <li>If #JKGAME_COLLIDE_WITH_IMMUTABLE,
 *                           an immutable image handle (#JKImageHandle type)
 *                       </ul>
 *   </dd>
 *  <dt><b>targetPosX, targetPosY</b></dt>
 *   <dd>The x and y coordinates of the target object virtual position on the screen.
 *       <ul>
 *        <li>If the target is another sprite and an image transform option is designated in
 *            #JKGAME_SET_TRANSFORM, these coordinates indicate the target sprite frame position
 *            after image transformation.
 *        <li>If the target is a tiled layer, the coordinates indicate the position of the entire
 *            tiled layer.
 *        <li>If the target is an offscreen image or immutable image, the coordinates indicate
 *            the position of the entire image buffer.
 *       </ul>
 *   </dd>
 * </dl>
 *
 * This function corresponds to the javax.microedition.lcdui.game.Sprite class collidesWith() method.
 *
 * <dl>
 *  <dt><b>When the target object is another sprite</b>
 *  (corresponds to collidesWith(Sprite s, boolean pixelLevel) method)</dt>
 *   <dd>
 *    <ul>
 *      <li>If pixel-level detection is to be performed, check for collision of non-transparent
 *         pixels of the sprites located inside the collision rectangles set for each sprite.
 *      <li>If pixel-level detection is not to be performed, check only for overlapping of the
 *         collision rectangles set for each sprite.
 *    </ul>
 *   </dd>
 *
 *  <dt><b>When the target object is a tiled layer</b>
 *  (corresponds to collidesWith(TiledLayer t, boolean pixelLevel) method)</dt>
 *   <dd>
 *    <ul>
 *     <li>If pixel-level detection is to be performed, check for collision of non-transparent pixels
 *        inside the collision rectangle set for the sprite with non-transparent pixels of the tiled layer.
 *     <li>If pixel-level detection is not to be performed, check for collision of the collision rectangle
 *        set for the sprite with non-empty cells of the tiled layer.
 *    </ul>
 *   </dd>
 *
 *  <dt><b>When the collision detection target is an immutable image</b>
 *  (corresponds to collidesWith(Image image, int x, int y, boolean pixelLevel) method)
 *   <dd>
 *     <ul>
 *      <li>If pixel-level detection is to be performed, check for collision of non-transparent pixels
 *        inside the collision rectangle set for the sprite with non-transparent pixels of the screen buffer.
 *      <li>If pixel-level detection is not to be performed, check for collision of the collision rectangle
 *        set for the sprite with the target screen buffer area.
 *     </ul>
 *   </dd>
 * </dl>
 *
 * In all cases, when an image transform option is set for a sprite, check for collision
 * after the image has been rotated or flipped.
 */
JKBool  JkGameCollisionDetect2D (const JKUint32 *pArg);


/**
 * Transfers the <code>GameCanvas</code> offscreen to the real screen.
 *
 * @param g
 *        The handle of the graphics context that can be used as a work buffer.
 * @param hScreen
 *        The handle of the source offscreen.
 * @param rect
 *        A pointer to the #JKT_Rect array holding the positions and sizes (in pixels) of the 
 *        source and destination rectangles for the transfer.
 *        <i>rect[0]</i> holds the source rectangle information in the offscreen coordinate.
 *        <i>rect[1]</i> holds the destination rectangle information in the virtual screen coordinate.
 * 
 * Transfer the region <i>rect[0]</i> in the <code>GameCanvas</code> offscreen <i>hScreen</i> to 
 * the real screen region that corresponds to the virtual screen region <i>rect[1]</i>.
 * Note that only the <i>y</i> members of <i>rect[]</i> elements differ.
 *
 * The graphics context given in <i>g</i> may be used as a work buffer.
 *
 * JBlend does not call #JkVideoBeginPaintOnVirtual() and 
 * #JkVideoEndPaintOnVirtual() before and after the invocation of this function.
 * In no case is the virtual screen handle designated in <i>hScreen</i>. 
 * 
 * This function is called when the JBlend customization property 
 * "midp_enhance_flush_game_graphics" is set as "1." 
 * When the property value is a value other than "1,"  implement
 * this function so that it returns to the caller without perfroming 
 * any processing.
 */
void  JkGameFlushGraphics (JKGraphicsContext g, JKOffScreenHandle hScreen, JKT_Rect* rect);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___MIDPSYS_JK_GAMEAPI_H */

/** @} end of group */
