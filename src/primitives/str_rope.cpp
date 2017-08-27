
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

str_rope::str_rope(const str_rope &other, size_t start, size_t end) {
    root = std::make_shared<rope_node>();

    if(start == end)
        return;


    size_t start_idx = 0;
    auto nodes = other.nodes_between(start, end, start_idx);

    if(nodes->size() == 1) {
        auto leaf = std::make_shared<rope_node>(nodes->at(0)->str->substr(start_idx, end - start));

        root->set_left(leaf);
    } else {
        auto construct_from = std::make_unique<std::vector<std::shared_ptr<rope_node>>>();
        size_t new_len = end - start;

        {
            const std::string &base = *nodes->at(0)->str;
            construct_from->push_back(std::make_shared<rope_node>(base.substr(start_idx, base.length() - start_idx)));
            new_len -= base.length() - start_idx;
        }

        for(size_t i = 1; i < nodes->size(); i++) {
            std::shared_ptr<rope_node> &node = nodes->at(i);
            if(node->str->length() < new_len) {
                construct_from->push_back(node);
            } else {
                const std::string &base = *node->str;
                construct_from->push_back(std::make_shared<rope_node>(base.substr(0, new_len)));
            }
        }

        reconstruct(*construct_from);
    }
}

void str_rope::reconstruct(std::vector<std::shared_ptr<rope_node>> &leaves) {
    auto buffer1 = std::make_unique<std::vector<std::shared_ptr<rope_node>>>();
    auto buffer2 = std::make_unique<std::vector<std::shared_ptr<rope_node>>>();

    for(size_t i = 0; i < leaves.size(); i += 2) {
        if(i+1 < leaves.size()) {
            auto node = std::make_shared<rope_node>();
            node->set_left(leaves[i]);
            node->set_right(leaves[i+1]);
            buffer1->push_back(node);
        } else {
            buffer1->push_back(leaves[i]);
        }
    }

    std::vector<std::shared_ptr<rope_node>>
            *current = buffer1.get(),
            *other = buffer2.get();
    while(current->size() > 1) {
        for(size_t i = 0; i < current->size(); i += 2) {
            if(i+1 < current->size()) {
                auto node = std::make_shared<rope_node>();
                node->set_left(current->at(i));
                node->set_right(current->at(i+1));
                other->push_back(node);
            } else {
                other->push_back(current->at(i));
            }
        }

        auto temp = other;
        other = current;
        current = temp;
    }

    root = current->at(0);
}

std::unique_ptr<std::vector<std::shared_ptr<rope_node>>>
str_rope::nodes_between(size_t start, size_t end, size_t &start_idx) const {
    if(end > root->actual_size)
        throw std::invalid_argument("end index > length of rope");
    if(start > end)
        throw std::invalid_argument("start index > end index");

    auto nodes = std::make_unique<std::vector<std::shared_ptr<rope_node>>>();
    start_idx = start;

    std::function<bool (std::shared_ptr<rope_node>, bool, size_t)> add_nodes =
            [&](std::shared_ptr<rope_node> current,
                                 bool towards_end,
                                 size_t end_idx) {
        if(nodes->empty()) {
            // If `nodes` is empty then we haven't found the start node.
            std::shared_ptr<rope_node> next;

            if(start_idx > current->data.len) {
                start_idx -= current->data.len;
                next = current->data.right;

                if(next->is_leaf) {
                    // Start node is also the end node if we haven't diverged.
                    nodes->push_back(next);
                    return towards_end;
                }

                /*
                 * If we're going down the right sub-tree to find the start then we must go right
                 *   to find the end because the end is guaranteed to be after or at the start.
                 *
                 * Therefore, if we haven't diverged then towards_end is the same we, and must adjust
                 *   the end_idx.
                 * If we have diverged then towards_end is the same, and end_idx doesn't matter.
                 */
                return add_nodes(next, towards_end, end_idx - current->data.len);
            } else {
                next = current->data.left;

                /*
                 * If (the next node is a leaf, we have not diverged, and the end node is in the
                 *   same direction [left sub-tree]), then this is both the start and end node.
                 */
                if(next->is_leaf && towards_end && end_idx <= current->data.len) {
                    nodes->push_back(next);
                    return true;
                } else if(next->is_leaf) {
                    nodes->push_back(next);
                    return false;
                }

                // If we were going towards the end, and the end is also in the left sub tree,
                //   then we are still going towards the end.
                if(!add_nodes(next, towards_end && end_idx <= current->data.len, end_idx)) {
                    /*
                     * If we're in this branch then either we already diverged (towards_end = F),
                     *   or the end node is to the right (because we just checked the left).
                     *
                     * If we didn't diverge before this (towards_end = T) then towards_end will
                     *   be appropriate, and end_idx must be adjusted.
                     * If we did diverge before this then towards_end will be appropriate, and
                     *   end_idx doesn't matter.
                     */
                    if(current->data.right)
                        return add_nodes(current->data.right, towards_end, end_idx - current->data.len);
                    else
                        return false;
                } else {
                    return true;
                }
            }
        } else {
            // Adding nodes (in order) until we find the end node
            //   Basically: submit the correct towards_end
            if(!towards_end) {
                if(current->is_leaf) {
                    nodes->push_back(current);
                    return false;
                }

                if(current->data.left)
                    add_nodes(current->data.left, false, end_idx);
                if(current->data.right)
                    add_nodes(current->data.right, false, end_idx);
                return false;
            } else {
                if(current->is_leaf) {
                    nodes->push_back(current);
                    return true;
                }

                if(end_idx <= current->data.len) {
                    // End is to the left, don't worry about the right sub-tree
                    return add_nodes(current->data.left, true, end_idx);
                } else {
                    // End is to the right, add the left sub-tree
                    if(current->data.left)
                        add_nodes(current->data.left, false, end_idx);
                    return add_nodes(current->data.right, true, end_idx - current->data.len);
                }
            }
        }
    };

    if(end <= root->data.len) {
        // If the end is to the left, then the start must also be to the left.
        add_nodes(root, true, end);
    } else {
        // Otherwise, the end is to the right (adjust the index), and the start may
        //   not be in the same direction.
        add_nodes(root, start > root->data.len, end - root->data.len);
    }

    return nodes;
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

void str_rope::prepend(str_rope &other) {
    auto new_root = std::make_shared<rope_node>();
    new_root->set_left(other.root);
    new_root->set_right(root);

    root = new_root;
}

void str_rope::append(str_rope &other) {
    auto new_root = std::make_shared<rope_node>();
    new_root->set_left(root);
    new_root->set_right(other.root);

    root = new_root;
}

