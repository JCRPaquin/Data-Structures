
/**
 * Implementation of a string rope.
 *
 * @author Jean-Claude Paquin
 **/

#include "str_rope.h"

struct rope_node {
    rope_node() : len(0), left(nullptr), right(nullptr) {}

    rope_node(rope_node& other) : isLeaf(other.isLeaf) {
        if(isLeaf) {
            str = std::make_unique(other.str);
        } else {
            len = other.len;

            if(other.left->isLeaf) {
                left = other.left;
            } else {
                left = std::make_shared(rope_node(*other.left.get()));
            }

            if(other.right->isLeaf) {
                right = other.right;
            } else {
                right = std::make_shared(rope_node(*other.right.get()));
            }
        }
    }

    rope_node(const std::string& str) : isLeaf(true) {
        this->str = std::make_unique(str);
    }

    bool isLeaf = false;
    union {
        struct {
            size_t len;
            std::shared_ptr<rope_node> left, right;
        };
        std::unique_ptr<std::string> str;
    };
};
