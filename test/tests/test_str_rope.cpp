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

TEST_CASE("Hierarchy tests", "[rope_node]") {
    using namespace std;

    shared_ptr<rope_node>
            leaf1 = make_shared<rope_node>(string("a")),
            leaf2 = make_shared<rope_node>(string("b")),
            leaf3 = make_shared<rope_node>(string("c"));

    rope_node node;

    SECTION("Balanced root node") {
        node.set_left(leaf1);
        node.set_right(leaf2);

        REQUIRE(*node.to_string() == "ab");
    }

    SECTION("Unbalanced root node") {
        SECTION("No right leaf") {
            node.set_left(leaf1);

            REQUIRE(*node.to_string() == "a");
        }

        SECTION("No left leaf") {
            node.set_right(leaf2);

            REQUIRE(*node.to_string() == "b");
        }
    }

    SECTION("Deeper hierarchy") {
        shared_ptr<rope_node>
                inner1 = make_shared<rope_node>(),
                inner2 = make_shared<rope_node>();

        SECTION("Two levels, balanced") {
            {
                inner1->set_left(leaf1);
                inner1->set_right(leaf2);
            }
            node.set_left(inner1);

            {
                inner2->set_left(leaf2);
                inner2->set_right(leaf3);
            }
            node.set_right(inner2);

            REQUIRE(*node.to_string() == "abbc");
            REQUIRE(node.actual_size == 4);
            REQUIRE(inner1->actual_size == 2);
        }

        SECTION("Two levels, unbalanced") {
            {
                inner2->set_left(leaf1);
                inner2->set_right(leaf2);
            }
            {
                inner1->set_left(inner2);
                inner1->set_right(inner2);
            }
            node.set_left(inner1);

            REQUIRE(*node.to_string() == "abab");
        }
    }
}

TEST_CASE("update_size()", "[rope_node]") {
    using namespace std;

    rope_node node;
    shared_ptr<rope_node>
            inner = make_shared<rope_node>(),
            leaf = make_shared<rope_node>(string("a"));

    node.set_left(inner);
    inner->set_left(leaf);
    inner->set_right(leaf);

    REQUIRE(inner->actual_size == 2);
    REQUIRE(node.actual_size == 0);

    node.update_size();

    REQUIRE(node.actual_size == 2);
}

TEST_CASE("str_rope constructors", "[str_rope]") {
    SECTION("Base constructor") {
        str_rope rope;

        REQUIRE(rope.get_length() == 0);
        REQUIRE(*rope.to_string() == "");
    }

    SECTION("Pre-initialization constructor") {
        str_rope rope(std::string("wowee!"));

        REQUIRE(rope.get_length() == 6);
        REQUIRE(*rope.to_string() == "wowee!");
    }

    SECTION("Copy constructor") {
        str_rope rope1(std::string("hi"));
        str_rope rope2(rope1);

        REQUIRE(rope2.get_length() == 2);
        REQUIRE(*rope2.to_string() == "hi");
    }

    SECTION("Sub-string constructor, no hierarchy") {
        str_rope rope1(std::string("**HI**"));
        str_rope rope2(rope1, 2, 4);

        REQUIRE(rope2.get_length() == 2);
        REQUIRE(*rope2.to_string() == "HI");
    }

    SECTION("Sub-string constructor, hierarchy") {
        str_rope rope1(std::string("Hello, my name is "));
        str_rope rope2(std::string("Caoilin"));
        str_rope rope3(std::string("JOHN CENA"));

        rope2.prepend(rope1);
        rope3.prepend(rope1);

        str_rope rope4(std::string(", and your "));

        rope4.prepend(rope2);

        str_rope rope5(rope3, 10, 27);

        rope4.append(rope5);

        REQUIRE(*rope4.to_string() == "Hello, my name is Caoilin, and your name is JOHN CENA");
    }
}

TEST_CASE("Rope indexing", "[str_rope]") {
    SECTION("Basic indexing (no hierarchy)", "[str_rope]") {
        str_rope rope(std::string("abcde"));

        REQUIRE(rope[0] == 'a');
        REQUIRE(rope[4] == 'e');
    }
}

TEST_CASE("Prepend/append", "[str_rope]") {
    str_rope rope1(std::string("wow"));
    str_rope rope2(std::string("ee!"));

    rope2.prepend(rope1);
    REQUIRE(*rope2.to_string() == "wowee!");

    rope2.append(rope2);
    REQUIRE(*rope2.to_string() == "wowee!wowee!");
}
