/**
 * Tests of str_rope and rope_node.
 *
 * @author Jean-Claude Paquin
 **/

#include <catch.hpp>
#include <primitives/str_rope.h>

TEST_CASE("Empty rope_node", "[rope_node]") {
    rope_node node;

    SECTION("Empty node has nullptr left & right") {
        REQUIRE(!node.data.left);
        REQUIRE(!node.data.right);
    }

    SECTION("Empty node to string") {
        REQUIRE(*node.to_string() == "");
    }

    SECTION("Empty node is not a leaf") {
        REQUIRE(!node.is_leaf);
    }
}

TEST_CASE("String rope_node", "[rope_node]") {
    rope_node node(std::string("wow!"));

    SECTION("String node is a leaf") {
        REQUIRE(node.is_leaf);
    }
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

