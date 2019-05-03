/*
 * ========================= dataBase_inn.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.04.29
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 * only in dataBase inner
 */
#ifndef _TPR_DATA_BASE_INN_H_
#define _TPR_DATA_BASE_INN_H_

//-------------------- CPP --------------------//
#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>


//-------------------- Engine --------------------//
#include "wrapSqlite3.h"
#include "global.h"
#include "GameArchive.h"



namespace db{//---------------- namespace: db ----------------------//



//-- 常用的 调用者端数据类型 （不是 sqlite 自己的数据类型）--
/*
enum class SqliteUserType : int{
    Int,
    U32,
    I64,
    U64
};
*/



//-- 全游戏唯一的 db connect 实例 --
inline sqlite3 *dbConnect;
inline char    *zErrMsg {nullptr};
inline int      rc;

inline std::mutex dbMutex;


//===== funcs =====//
int callback_1(void *_data, int _argc, char **_argv, char **_azColNames);




//-- prepare_v2 --
//-- 注意，参数 _ppStmt 必须为 pp，
inline void sqlite3_prepare_v2_inn_( const std::string &_sql_str, sqlite3_stmt **_ppStmt ){
    w_sqlite3_prepare_v2(   dbConnect, 
                            _sql_str.c_str(), 
                            _sql_str.size()+1,
                            _ppStmt,
                            NULL );
}



//---- bind vals ----
//  注意：下面这组操作，必须在一个 atom 函数内被调用 --
inline sqlite3_stmt *stmt_for_bindFuncs {nullptr};

inline void reset_stmt_for_bindFuncs_inn_( sqlite3_stmt *_newStmt ){
    stmt_for_bindFuncs = _newStmt;
}

inline void sqlite3_bind_int_inn_( const std::string &_paramStr, const int &_val ){
    w_sqlite3_bind_int( dbConnect, stmt_for_bindFuncs, 
                        w_sqlite3_bind_parameter_index( stmt_for_bindFuncs, _paramStr.c_str() ),  
                        _val );
}
inline void sqlite3_bind_int64_inn_( const std::string &_paramStr, const i64_t &_val ){
    w_sqlite3_bind_int64( dbConnect, stmt_for_bindFuncs, 
                        w_sqlite3_bind_parameter_index( stmt_for_bindFuncs, _paramStr.c_str() ),  
                        _val );
}
inline void sqlite3_bind_double_inn_( const std::string &_paramStr, const double &_val ){
    w_sqlite3_bind_double( dbConnect, stmt_for_bindFuncs, 
                        w_sqlite3_bind_parameter_index( stmt_for_bindFuncs, _paramStr.c_str() ),  
                        _val );
}





//=============================//
//      table_gameArchive 
//=============================//
// 主table，存储一切 全局性的数据
inline const std::string sql_create_table_gameArchive  {
    "CREATE TABLE IF NOT EXISTS table_gameArchive("  \
    "id               INT     PRIMARY KEY     NOT NULL," \
    "baseSeed         INT     NOT NULL, " \
    "playerGoId       INTEGER  NOT NULL, " \
    "playerGoMPosX    INT         NOT NULL,  " \
    "playerGoMPosY    INT         NOT NULL,  " \
    "maxGoId          INTEGER     NOT NULL  " \
    ");" \

    "PRAGMA journal_mode=WAL;" 
    "SELECT * FROM table_gameArchive" 
    };


//-- 游戏启动初期，将 table_gameArchive 中数据全部读取。
//   由玩家选择，进入哪个存档
inline const std::string sql_select_all_from_table_gameArchive  {
    "SELECT "\
        "id, "\
        "baseSeed,   "\
        "playerGoId,   "\
        "playerGoMPosX, "\
        "playerGoMPosY,  "\
        "maxGoId  "\
        "FROM table_gameArchive;" 
    };
inline sqlite3_stmt *stmt_select_all_from_table_gameArchive {nullptr};



inline const std::string sql_insert_or_replace_to_table_gameArchive  {
    "INSERT OR REPLACE INTO table_gameArchive (id, baseSeed, playerGoId, playerGoMPosX, playerGoMPosY, maxGoId ) " \
    "VALUES ( :id, :baseSeed, :playerGoId, :playerGoMPosX, :playerGoMPosY, :maxGoId );" 
    };
inline sqlite3_stmt *stmt_insert_or_replace_to_table_gameArchive {nullptr};




//=============================//
//      table_chunks
//=============================//
inline const std::string sql_create_table_chunks  {
    "CREATE TABLE IF NOT EXISTS table_chunks("  \
    "chunkKey       INTEGER     PRIMARY KEY     NOT NULL," \
    "padding        INT         NOT NULL " \
    ");" 
    //"PRAGMA journal_mode=WAL;" 
    //"SELECT * FROM table_chunks" 
    };









//=============================//
//        table_goes
//=============================//
inline const std::string sql_create_table_goes  {
    "CREATE TABLE IF NOT EXISTS table_goes("  \
    "goid           INTEGER     PRIMARY KEY     NOT NULL," \
    "goSpecId       INT         NOT NULL,  " \
    "mposX          INT         NOT NULL,  " \
    "mposY          INT         NOT NULL  " \
    ");" 
    //"PRAGMA journal_mode=WAL;" 
    //"SELECT * FROM table_goes" 
    };

inline const std::string sql_select_one_from_table_goes  {
    "SELECT  "\
        "goSpecId, "\
        "mposX,  "\
        "mposY  "\
        "FROM table_goes WHERE goid = ?;" 
    };
inline sqlite3_stmt *stmt_select_one_from_table_goes {nullptr};


inline const std::string sql_insert_or_replace_to_table_goes  {
    "INSERT OR REPLACE INTO table_goes ( goid, goSpecId, mposX, mposY ) " \
    "VALUES ( :goid, :goSpecId, :mposX, :mposY );" 
    };
inline sqlite3_stmt *stmt_insert_or_replace_to_table_goes {nullptr};





//--- old test --
/*
inline const std::string sql_select_all  {
    "SELECT * FROM table_test" 
    };


inline const std::string sql_insert_or_replace  {
    "INSERT OR REPLACE INTO table_test (ID, AGE, SALARY, NAME, BINARY) " \
    "VALUES ( :ID, :AGE, :SALARY, :NAME, :BINARY );" 
    };


inline const std::string sql_select_to_read  {
    "SELECT AGE, SALARY, NAME, BINARY FROM table_test WHERE ID = ?;" 
    };
*/




}//----------------------- namespace: db end ----------------------//
#endif 

