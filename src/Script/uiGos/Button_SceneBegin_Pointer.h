/*
 * ================ Button_SceneBegin_Pointer.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.08.25
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 */
#ifndef TPR_BUTTON_SCENE_BEGIN_POINTER_2_H
#define TPR_BUTTON_SCENE_BEGIN_POINTER_2_H

//-------------------- CPP --------------------//
#include <string>
#include <vector>
#include <functional>

//-------------------- Engine --------------------//
#include "tprAssert.h"
#include "GameObj.h"
#include "GameObjMesh.h"
#include "AnimFrameSet.h"
#include "MapAltitude.h"
#include "Density.h"
#include "ParamBinary.h"


namespace uiGos{//------------- namespace uiGos ----------------


class Button_SceneBegin_Pointer{
public:
    Button_SceneBegin_Pointer() = default;

    //--- 延迟init ---//
    static void init_in_autoMod( GameObj &goRef_,
                                 const ParamBinary &dyParams_ );

private:
    //--- callback ---//
    static void OnRenderUpdate( GameObj &goRef_ ); 
    static void OnActionSwitch( GameObj &goRef_, ActionSwitchType type_ );
};


}//------------- namespace uiGos: end ----------------
#endif 
