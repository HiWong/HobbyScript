//
// Created by 刘丰恺 on 2018/8/2.
//

#include "unitcpp/UnitTest++.h"
#include "AstVisitor.h"
#include "json.hpp"

using json = nlohmann::json;

TEST (TestPrintNumeric1) {
    json testJson = json::parse(
            R"({"token":{"value":1,"lineNumber":1,"tag":270},"tag":270,"type":"NumberLiteral"})");
    AstVisitor visitor(testJson);
    AstNodePointer node_pointer = visitor.visit();
    NumberLiteralPointer literal = std::static_pointer_cast<NumberLiteral>(node_pointer);
    UNITTEST_CHECK(literal);
    UNITTEST_CHECK_EQUAL(1, literal->getValue());
}


TEST (TestPrintAstLeaf) {
    json testJson = json::parse(
            R"({"token":{"text":"+","lineNumber":1,"tag":264},"tag":264,"type":"AstLeaf"})");
    AstVisitor visitor(testJson);
    AstNodePointer node_pointer = visitor.visit();
    AstLeafPointer leaf = std::static_pointer_cast<AstLeaf>(node_pointer);
    UNITTEST_CHECK(leaf);
    UNITTEST_CHECK_EQUAL("+", leaf->get_text());
}

TEST (TestPrintAstList) {
    json testJson = json::parse(
            R"(
{
    "afterPoint":0,
    "children":[
        {
            "token":{
                "value":1,
                "lineNumber":1,
                "tag":270
            },
            "tag":270,
            "type":"NumberLiteral"
        },
        {
            "token":{
                "text":"+",
                "lineNumber":1,
                "tag":264
            },
            "tag":264,
            "type":"AstLeaf"
        },
        {
            "token":{
                "value":1111,
                "lineNumber":1,
                "tag":270
            },
            "tag":270,
            "type":"NumberLiteral"
        }
    ],
    "tag":277,
    "type":"AstList"
}
            )");

    AstVisitor visitor(testJson);
    AstNodePointer node_pointer = visitor.visit();
    AstListPointer list = std::static_pointer_cast<AstList>(node_pointer);
    UNITTEST_CHECK(list);
    UNITTEST_CHECK_EQUAL(3, list->get_children()->size());
}

TEST (TestPrintBinaryExpr) {
    json testJson = json::parse(
            R"(
{
    "afterPoint":0,
    "children":[
        {
            "token":{
                "value":1,
                "lineNumber":1,
                "tag":270
            },
            "tag":270,
            "type":"NumberLiteral"
        },
        {
            "token":{
                "text":"+",
                "lineNumber":1,
                "tag":264
            },
            "tag":264,
            "type":"AstLeaf"
        },
        {
            "token":{
                "value":1111,
                "lineNumber":1,
                "tag":270
            },
            "tag":270,
            "type":"NumberLiteral"
        }
    ],
    "tag":279,
    "type":"AstList"
}
            )");

    AstVisitor visitor(testJson);
    AstNodePointer node_pointer = visitor.visit();
    BinaryExprPointer binaryExpr = std::static_pointer_cast<BinaryExpr>(node_pointer);
    UNITTEST_CHECK(binaryExpr);
    UNITTEST_CHECK_EQUAL(3, binaryExpr->get_children()->size());

    NumberLiteralPointer literal = std::static_pointer_cast<NumberLiteral>(binaryExpr->get_left_node());
    UNITTEST_CHECK(literal);
    UNITTEST_CHECK_EQUAL(1, literal->getValue());

    AstLeafPointer leaf = std::static_pointer_cast<AstLeaf>(binaryExpr->get_mid_op());
    UNITTEST_CHECK(leaf);
    UNITTEST_CHECK_EQUAL("+", leaf->get_text());

    NumberLiteralPointer literal2 = std::static_pointer_cast<NumberLiteral>(binaryExpr->get_right_node());
    UNITTEST_CHECK(literal2);
    UNITTEST_CHECK_EQUAL(1111, literal2->getValue());
}