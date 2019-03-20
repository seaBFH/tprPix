/*
 * ========================= FramePos.cpp ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.01.15
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *    
 * ----------------------------
 */
#include "FramePos.h"

//-------------------- C --------------------//
#include <cassert>

//-------------------- CPP --------------------//
//#include <string>

//------------------- Engine --------------------//
#include "config.h" 
#include "srcs_engine.h"


//#include "debug.h" 



/* ===========================================================
 *             calc_ceh_pposOff_fromRootAnchor
 * -----------------------------------------------------------
 */
void FramePos::calc_ceh_pposOff_fromRootAnchor(){
    assert( is_rootAnchorPos_set == true );
    for( auto &i : colliEntHeads ){
        i.pposOff_fromRootAnchor -= rootAnchorPos.pposOff;
    }
}


/* ===========================================================
 *                      check
 * -----------------------------------------------------------
 */
void FramePos::check(){

    //--- 确保关键数据已载入 ---//
    assert( is_rootAnchorPos_set &&
            is_rootColliEntHeadIdx_set &&
            (!colliEntHeads.empty()) );
    
    //-- 检测 animFrameSet.rootAnchor 与 root ceh 是否对齐 --//
    ColliEntHead &rootCehRef = colliEntHeads.at(rootColliEntHeadIdx);
    //--
    const MapEntCompass &centerCompass = esrc::colliEntSets.at( rootCehRef.colliEntSetIdx ).get_centerCompass();
    assert( centerCompass == rootAnchorPos.compass ); //- 确保对齐 ！！！ --

    //-- 检测 regular ceh 是否与 root ceh 对齐 --//
    IntVec2 pposOff;
    for( size_t i=0; i<colliEntHeads.size(); i++ ){

        if( i == rootColliEntHeadIdx ){
            continue;
        }

        pposOff = colliEntHeads.at(i).pposOff_fromRootAnchor - rootCehRef.pposOff_fromRootAnchor;
        assert( (pposOff.x%PIXES_PER_MAPENT==0) && (pposOff.y%PIXES_PER_MAPENT==0) );
    }
}
