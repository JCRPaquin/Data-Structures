/**
 * Tests of str_rope and rope_node.
 *
 * @author Jean-Claude Paquin
 **/

#include <catch.hpp>
#include <primitives/str_rope.h>

TEST_CASE("Empty rope_node", "[rope_node]") {
    rope_node node;

    REQUIRE(!node.data.left);
    REQUIRE(!node.data.right);

    REQUIRE(*node.to_string() == "");

    REQUIRE(!node.is_leaf);

    REQUIRE(node.actual_size == 0);
}

TEST_CASE("String rope_node", "[rope_node]") {
    rope_node node(std::string("wow!"));

    REQUIRE(*node.to_string() == "wow!");

    REQUIRE(node.is_leaf);

    REQUIRE(node.actual_size == 4);
}

TEST_CASE("Copy constructor for rope_node", "[rope_node]") {
    SECTION("Copied node is a leaf node") {
        rope_node node(std::string("that's a low price!"));
        rope_node dupl(node);

        REQUIRE(*dupl.to_string() == *node.to_string());
        REQUIRE(dupl.is_leaf);
    }

    SECTION("Copied node is not a leaf node") {
        rope_node node;
        rope_node dupl(node);

        REQUIRE(!dupl.is_leaf);
    }
}

