//
// Created by 刘丰恺 on 2018/8/8.
//

#include "DefBlockStmt.h"

DefBlockStmt::DefBlockStmt(const json &load_json,
                           const pointer<ast_node_list> children) : ast_list(
        load_json, children) {

}