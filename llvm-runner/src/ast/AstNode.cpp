//
// Created by 刘丰恺 on 2018/8/1.
//

#include "AstNode.h"

AstNode::AstNode(const json &load_json) {
    this->load_json = load_json;
    this->tag = load_json["tag"];
}

const json &AstNode::get_json() {
    return load_json;
}