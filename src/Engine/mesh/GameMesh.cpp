/*
 * ========================= GameMesh.cpp ==========================
 *                          -- tpr --
 *                                        创建 -- 2018.11.24
 *                                        修改 -- 2018.11.24
 * ----------------------------------------------------------
 *   GameMesh 类, 可以看作 图元类。
 *   一个 GameMesh，负责管理 一张 矩形图元
 * ----------------------------
 */
#include "GameMesh.h" 

//-------------------- C --------------------//
#include <cassert> //-- assert

//-------------------- Engine --------------------//
#include "srcs_engine.h"
#include "VAOVBO.h" 
#include "vector_matrix.h"
#include "GameObj.h"

//#include "debug.h"


namespace{//------------------ namespace ---------------------//

    //-- 3个常量，分别代表 xyz 三个轴，用在 glm::rotate 函数中。
    //const glm::vec3 axle_x( 1.0f, 0.0f, 0.0f );
    //const glm::vec3 axle_y( 0.0f, 1.0f, 0.0f );
    const glm::vec3 axis_z( 0.0f, 0.0f, 1.0f );

}//--------------------- namespace end ------------------------//


/* ===========================================================
 *                  refresh_translate
 * -----------------------------------------------------------
 * -- 此函数 只能在 go.RenderUpdate 阶段被调用
 * -- 其余代码 不应随意调用 此函数!!!
 */
void GameMesh::refresh_translate(){

    const glm::vec2 &goCurrentFPos = goPtr->goPos.get_currentFPos();
    //- 图元帧 左下角 到 rootAnchor 的 off偏移 --
    const IntVec2 &vRef = actionPtr->framePoses.at(actionHandle.currentIdx).get_rootAnchorPos().pposOff;
    translate_val = glm::vec3{  goCurrentFPos.x + (float)pposOff.x - (float)vRef.x, 
                                goCurrentFPos.y + (float)pposOff.y - (float)vRef.y, 
                                -(goCurrentFPos.y + (float)pposOff.y + off_z) }; 
                                    //-- ** 注意！**  z值的计算有不同：
                                    // -1- 取负...
                                    // -2- 没有算入 vRef.y; 因为这个值只代表：
                                    //     图元 和 根锚点的 偏移
                                    //     而 z值 仅仅记录 GameMesh锚点 在 游戏世界中的位置
            //-- 未来拓展：
            //  应当为 每个go 设置一个随机的 z深度 base值
            //  在此 z_base 基础上，再做 深度加减
            //  从而避免同一 z深度的 图元 在渲染时 碰撞
}


/* ===========================================================
 *                  draw
 * -----------------------------------------------------------
 */
void GameMesh::draw(){

    if( isVisible == false ){
        return;
    }

    //---------- refresh texName -------------
    GLuint texName = actionPtr->texNames.at( get_currentActionFrameIdx() );

    //---------- refresh mat4_model -------------
    update_mat4_model();

    //---------- 将 model矩阵的值传入 绑定的 着色器程序 ---------
    assert( shaderPtr != nullptr );
    shaderPtr->send_mat4_model_2_shader( mat4_model );

    //----------- 绑定 本GameMesh对象 唯一的 texture ------------   
    //-- 单次 draw call 最多支持 32 个 texture。（完全够用）
    //   但是， gl本体可以存储 非常多个 tex实例
    glActiveTexture( GL_TEXTURE0 );  //- 激活纹理单元
    assert( texName != 0 ); 
    glBindTexture(GL_TEXTURE_2D, texName ); //- 绑定纹理单元

    //----------- 绑定 本Model对象 的 VAO ----------
    glBindVertexArray( VAO );

    //----------- 正式绘制 ----------
    glDrawArrays( GL_TRIANGLES, 0, 6 ); //-- 绘制 图元(rect). 不依赖 EBO 的写法
}



/* ===========================================================
 *                 update_mat4_model
 * -----------------------------------------------------------
 * -- 当 GameMesh对象的 位移／旋转／缩放 任一维发生变化，就要重新计算 model矩阵
 * -- 目前 优化粒度较粗。一有变化就全盘重算。
 */
void GameMesh::update_mat4_model(){

    //----- translate: regular ------
    // 请确保，输入函数的 translate 值，已经叠加了 go 的 pos。
    mat4_model = glm::translate( normal_mat4, translate_val );

    //----- rotate: only Z-axis ------
    //- pix游戏 只支持 z轴旋转
    mat4_model = glm::rotate( mat4_model, 
                            glm::radians(rotate_z),
                            axis_z );

    //----- scale ------
    mat4_model = glm::scale( mat4_model, scale_val );

    //----- translate: anchor／锚点 修正 ------
    //...
}



/* ===========================================================
 *                 bind_action
 * -----------------------------------------------------------
 */
void GameMesh::bind_action( const std::string &_name ){
    actionName = _name;
    actionPtr = &(esrc::actions.at(_name));
}
