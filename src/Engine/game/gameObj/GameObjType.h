/*
 * ===================== GameObjType.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2018.12.11
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *    GameObj 各种数据 结构
 * ----------------------------
 */
#ifndef _TPR_GAME_OBJ_TYPE_H_
#define _TPR_GAME_OBJ_TYPE_H_

//-------------------- CPP --------------------//
#include <string>
#include <vector>

//------------------- Libs --------------------//
#include "tprDataType.h" 


using goid_t     = u64_t; //- gameObj id type
using goSpecId_t = u32_t; //- gameObj species id type


//-- go move state／运动状态 --
enum class GameObjMoveState{
    AbsFixed  = 1, //- 固定于地面，绝对静止
    BeMovable = 2, //- 静止，但可被移动（通过外部 forse 施加的影响）
    Movable   = 3  //- 可移动。本go 可启动移动操作。
};


//-- go state / go 常规状态 --
enum class GameObjState{
    Sleep = 1, //- 休眠状态，不主动行动，（但可被动回应）
    Waked = 2  //- 活跃状态，主动发起行动。 
};

//- 三大 go 类群 --
//  这套系统使用使用，暂未确定
enum class GameObjFamily{
    Major   = 1, //- 主go： 活体，树，建筑...
    Item    = 2, //- 道具go： 武器，药剂
    Surface = 3  //- 表面go： 液体，火焰...
};

#endif

