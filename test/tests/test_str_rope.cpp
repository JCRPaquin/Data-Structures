/**
 * Tests of str_rope and rope_node.
 *
 * @author Jean-Claude Paquin
 **/

#include <catch.hpp>
#include <primitives/str_rope.h>

TEST_CASE("Empty rope_node", "[rope_node]") {
    std::unique_ptr<rope_node> node = std::make_unique<rope_node>();

    SECTION("Empty node has nullptr left & right") {
        REQUIRE(!node->data.left);
        REQUIRE(!node->data.right);
    }

    SECTION("Empty node to string") {
        REQUIRE(*node->to_string().get() == "");
    }
}

TEST_CASE("String rope_node", "[rope_node]") {
    std::unique_ptr<rope_node> node = std::make_unique<rope_node>(std::string("wow!"));
}

TEST_CASE("Copy constructor for rope_node", "[rope_node]") {
    std::unique_ptr<rope_node> node = std::make_unique<rope_node>(std::string("that's a low price!"));

    std::unique_ptr<rope_node> dupl = std::make_unique<rope_node>(*node.get());

    REQUIRE(*dupl->to_string().get() == *node->to_string().get());
}

