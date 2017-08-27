/**
 * Represents strings using a "rope" data structure.
 *
 * What is a rope?
 *   It is a way of representing a string as a collection (tree) of smaller strings.
 *
 * Why is this useful?
 *   Strings are usually implemented as flat arrays of characters in memory. Insertion/deletion within the string
 *   forces reallocation, copying, etc..
 *
 *   Ropes minimize the overhead caused by these applications. Instead of reallocating the entire string we can simply
 *   (de)allocate a subtree, or shuffle smaller strings around.
 *
 * How is it implemented?
 *   A rope consists of a tree where all leaves contain a short string, and all internal nodes contain the length of
 *   the substring represented by all leaves under their left child.
 *
 * @author Jean-Claude Paquin
 **/

#ifndef DATA_STRUCTURES_STR_ROPE_H
#define DATA_STRUCTURES_STR_ROPE_H


#include <cstdio>
#include <string>
#include <memory>
#include <vector>

struct rope_node {
    rope_node();
    rope_node(rope_node&);
    rope_node(const std::string&);

    ~rope_node() {};

    void set_left(std::shared_ptr<rope_node>);
    void set_right(std::shared_ptr<rope_node>);
    void update_size();

    std::unique_ptr<std::string> to_string() const;

    bool is_leaf = false;
    size_t actual_size = 0;
    union {
        struct {
            size_t len;
            std::shared_ptr<rope_node> left, right;
        } data;
        std::unique_ptr<const std::string> str;
    };

private:
    void to_string(std::ostringstream&);
};

class str_rope {
public:
    /**
     * Construct an empty rope.
     */
    str_rope();
    /**
     * Construct a rope with a given base string.
     *
     * @param str base string to use
     */
    str_rope(const std::string& str);
    /**
     * Copy the contents of `other`.
     *
     * @param other rope to copy
     */
    str_rope(const str_rope& other);
    /**
     * Constructs a rope by copying a substring from `other`.
     *
     * @param other rope to copy
     */
    str_rope(const str_rope& other, size_t start, size_t end);


    /**
     * @return the character at `index`
     */
    char operator[](size_t index) const;
    /**
     * Set rope[index] to `c`.
     */
    void set_char(size_t index, char c);


    /**
     * Prepends another rope to this rope.
     */
    void prepend(str_rope& other);
    /**
     * Appends another rope to this rope.
     */
    void append(str_rope& other);


    /**
     * Inserts a raw string into the rope.
     *
     * @param index where to insert the string
     * @param str what string to insert
     */
    void insert_str(size_t index, const std::string& str);
    /**
     * Deletes the substring from [start,end) from the rope.
     */
    void delete_str(size_t start, size_t end);


    /**
     * @return this rope as a string
     */
    std::unique_ptr<std::string> to_string() const;
    /**
     * Constructs a string representation of a substring within the rope.
     *
     * @return the substring from [start,end)
     */
    std::unique_ptr<std::string> to_string(size_t start, size_t end) const;


    /**
     * @return the length of the rope
     */
    size_t get_length() const;

private:
    std::shared_ptr<rope_node> root;

    std::unique_ptr<std::vector<std::shared_ptr<rope_node>>>
    nodes_between(size_t start, size_t end, size_t& start_idx) const;
    
    void reconstruct(std::vector<std::shared_ptr<rope_node>>& leaves);
};


#endif //DATA_STRUCTURES_STR_ROPE_H
