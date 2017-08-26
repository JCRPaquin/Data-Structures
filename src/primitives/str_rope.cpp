
/**
 * Implementation of a string rope.
 *
 * @author Jean-Claude Paquin
 **/

#include "str_rope.h"
#include <sstream>


// Define rope_node helper struct

rope_node::rope_node() {
    memset(&data, 0, sizeof(data));
}

rope_node::rope_node(rope_node& other) : is_leaf(other.is_leaf), actual_size(other.actual_size) {
    if(is_leaf) {
        str.release();
        str = std::make_unique<const std::string>(*other.str);
    } else {
        memset(&data, 0, sizeof(data));
        data.len = other.data.len;

        if(other.data.left) {
            if(other.data.left->is_leaf) {
                data.left = other.data.left;
            } else {
                data.left = std::make_shared<rope_node>(*other.data.left);
            }
        }

        if(other.data.right) {
            if(other.data.right && other.data.right->is_leaf) {
                data.right = other.data.right;
            } else {
                data.right = std::make_shared<rope_node>(*other.data.right);
            }
        }
    }
}

rope_node::rope_node(const std::string& str) : is_leaf(true), actual_size(str.length()) {
    this->str.release();
    this->str = std::make_unique<const std::string>(str);
}

void rope_node::set_left(std::shared_ptr<rope_node> left) {
    if(is_leaf) return;

    if(data.left) {
        actual_size -= data.left->actual_size;
    }
    actual_size += left->actual_size;
    data.len = left->actual_size;
    data.left = left;
}

void rope_node::set_right(std::shared_ptr<rope_node> right) {
    if(is_leaf) return;

    if(data.right) {
        actual_size -= data.right->actual_size;
    }
    actual_size += right->actual_size;
    data.right = right;
}

void rope_node::update_size() {
    if(this->is_leaf) {
        actual_size = str->length();
    } else {
        actual_size = 0;

        if(data.left) {
            data.left->update_size();
            actual_size += data.left->actual_size;
        }

        if(data.right) {
            if(data.right != data.left)
                data.right->update_size();
            actual_size += data.right->actual_size;
        }
    }
}

std::unique_ptr<std::string> rope_node::to_string() const {
    if(is_leaf) {
        return std::make_unique<std::string>(*str);
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
        stream << *str;
    } else {
        if(data.left)
            data.left->to_string(stream);
        if(data.right)
            data.right->to_string(stream);
    }
}

// End of rope_node definitions


// Define str_rope

str_rope::str_rope() {
    root = std::make_shared<rope_node>();
}

str_rope::str_rope(const std::string &str) {
    root = std::make_shared<rope_node>();
    auto leaf = std::make_shared<rope_node>(str);

    root->set_left(leaf);
}

str_rope::str_rope(const str_rope &other) {
    root = std::make_shared<rope_node>(*other.root);
}

char str_rope::operator[](size_t index) const {
    std::shared_ptr<rope_node> current = root;
    size_t node_index = index;

    while(current) {
        if(current->is_leaf) {
            return (*current->str)[node_index];
        }

        if(node_index >= current->data.len) {
            node_index -= current->data.len;
            current = current->data.right;
        } else {
            current = current->data.left;
        }
    }

    return 0;
}

std::unique_ptr<std::string> str_rope::to_string() const {
    return root->to_string();
}

size_t str_rope::get_length() const {
    return root->actual_size;
}

