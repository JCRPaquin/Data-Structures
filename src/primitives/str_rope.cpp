
/**
 * Implementation of a string rope.
 *
 * @author Jean-Claude Paquin
 **/

#include "str_rope.h"
#include <sstream>
#include <cstring>


rope_node::rope_node() {
    memset(&data, 0, sizeof(data));
}

rope_node::rope_node(rope_node& other) : is_leaf(other.is_leaf), actual_size(other.actual_size) {
    if(is_leaf) {
        str.release();
        str = std::make_unique<const std::string>(*other.str.get());
    } else {
        data.len = other.data.len;

        if(other.data.left->is_leaf) {
            data.left = other.data.left;
        } else {
            data.left = std::make_shared<rope_node>(*other.data.left.get());
        }

        if(other.data.right->is_leaf) {
            data.right = other.data.right;
        } else {
            data.right = std::make_shared<rope_node>(*other.data.right.get());
        }
    }
}

rope_node::rope_node(const std::string& str) : is_leaf(true), actual_size(str.length()) {
    this->str.release();
    this->str = std::make_unique<const std::string>(str);
}

void rope_node::set_left(std::shared_ptr<rope_node> left) {
    if(this->is_leaf) return;

    if(this->data.left) {
        actual_size -= this->data.left->actual_size;
    }
    actual_size += left->actual_size;
    data.len = left->actual_size;
    this->data.left = left;
}

void rope_node::set_right(std::shared_ptr<rope_node> right) {
    if(this->is_leaf) return;

    if(this->data.right) {
        actual_size -= this->data.right->actual_size;
    }
    actual_size += right->actual_size;
    this->data.right = right;
}

std::unique_ptr<std::string> rope_node::to_string() const {
    if(is_leaf) {
        return std::make_unique<std::string>(*str.get());
    } else {
        std::ostringstream *stream = new std::ostringstream();

        if(data.left)
            data.left->to_string(*stream);
        if(data.right)
            data.right->to_string(*stream);

        std::unique_ptr<std::string> ret = std::make_unique<std::string>(stream->str());
        delete stream;

        return std::move(ret);
    }
}

void rope_node::to_string(std::ostringstream& stream) {
    if(is_leaf) {
        stream << *str.get();
    } else {
        data.left->to_string(stream);
        data.right->to_string(stream);
    }
}
