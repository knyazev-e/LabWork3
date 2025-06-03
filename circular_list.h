#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H


#include <stdexcept>
#include <iterator>
#include <utility>

template <typename T>

class CircularLinkedList {
private:
    struct Element {
        T value;
        Element* next_element;

        Element(const T& val, Element* next) : value(val), next_element(next) {}
    };

    Element* head;
    size_t list_size;

public:
    // iterator

    friend class iterator;
    friend class const_iterator;


    class iterator {
        friend class CircularLinkedList;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        iterator(Element* elem, Element* head, bool end) : element(elem), head_ptr(head), isEnd(end) {}
        ~iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;

        T& operator*() const {
            if (!element || isEnd) throw std::out_of_range("Dereferencing invalid iterator");
            return element->value;
        }

        T* operator->() const {
            if (!element || isEnd) throw std::out_of_range("Dereferencing invalid iterator");
            return &(element->value);
        }

        iterator& operator++() {
            if (!element || isEnd) throw std::out_of_range("Advancing invalid iterator");
            element = element->next_element;
            if (element == head_ptr) isEnd = true;
            return *this;
        }

        iterator operator++(int) {
            if (!element || isEnd) throw std::out_of_range("Advancing invalid iterator");
            iterator initial = *this;
            ++(*this);
            return initial;

        }

        bool operator==(const iterator& other) const {
            return element == other.element && isEnd == other.isEnd;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        Element* element;
        Element* head_ptr;
        bool isEnd;

    };


    //the constant iterator
    class const_iterator {
        friend class CircularLinkedList;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T*;
        using reference = const T&;

        const_iterator(const Element* elem, const Element* head, bool end) : element(elem), head_ptr(head), isEnd(end) {}
        ~const_iterator() = default;
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;

        const T& operator*() const {
            if (!element || isEnd) throw std::out_of_range("Dereferencing invalid iterator");
            return element->value;
        }

        const T* operator->() const {
            if (!element || isEnd) throw std::out_of_range("Dereferencing invalid iterator");
            return &(element->value);
        }

        const_iterator& operator++() {
            if (!element || isEnd) throw std::out_of_range("Advancing invalid iterator");
            element = element->next_element;
            if (element == head_ptr) isEnd = true;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator initial = *this;
            ++(*this);
            return initial;
        }

        bool operator==(const const_iterator& other) const {
            return element == other.element && isEnd == other.isEnd;
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }

    private:
        const Element* element;
        const Element* head_ptr;
        bool isEnd;
    };


    // the list's fields, methods and operators
    CircularLinkedList() : head(nullptr), list_size(0) {}

    ~CircularLinkedList() {
        clear();
    }

    iterator begin() {
        return iterator(head, head, false);
    }

    iterator end() {
        return iterator(head, head, true);
    }

    const_iterator begin() const {
        return const_iterator(head, head, false);
    }

    const_iterator end() const {
        return const_iterator(head, head, true);
    }

    const_iterator cbegin() const {
        return begin();
    }

    const_iterator cend() const {
        return end();
    }

    void push_front(const T& value) {
        if (!head) {
            head = new Element(value, nullptr);
            head->next_element = head;
        }
        else {
            Element* new_element = new Element(value, head->next_element);
            head->next_element = new_element;
            std::swap(head->value, new_element->value);
        }
        ++list_size;
    }

    void pop_front() {
        if (!head) throw std::out_of_range("List is empty");
        if (head->next_element == head) {
            delete head;
            head = nullptr;
        }
        else {
            head->value = head->next_element->value;
            Element* to_pop = head->next_element;
            head->next_element = head->next_element->next_element;
            delete to_pop;
        }
        --list_size;
    }

    T& front() {
        if (!head) throw std::out_of_range("List is empty");
        return head->value;
    }

    const T& front() const {
        if (!head) throw std::out_of_range("List is empty");
        return head->value;
    }

    bool empty() const {
        return head == nullptr;
    }

    size_t size() const {
        return list_size;
    }

    iterator insert_after(const iterator pos, const T& value) {
        if (!pos.element || pos.isEnd) throw std::invalid_argument("Invalid iterator");
        Element* new_element = new Element(value, pos.element->next_element);
        pos.element->next_element = new_element;
        ++list_size;
        return iterator(new_element, head, false);
    }

    iterator erase_after(const iterator pos) {
        if (!pos.element || pos.element->next_element == head) throw std::invalid_argument("Invalid iterator or nothing to erase");
        Element* to_erase = pos.element->next_element;
        pos.element->next_element = pos.element->next_element->next_element;
        delete to_erase;
        --list_size;
        return iterator(pos.element->next_element, head, false);
    }

    void clear() {
    if (!head) return;
    Element* to_erase = head->next_element;
    while (to_erase != head) {
        Element* next = to_erase->next_element;
        delete to_erase;
        to_erase = next;
    }
    delete head;
    head = nullptr;
    list_size = 0;
    }

    CircularLinkedList(const CircularLinkedList& other) : head(nullptr), list_size(0) {
        if (other.head) {
            head = new Element(other.head->value, nullptr);
            Element* current = head;
            Element* other_current = other.head->next_element;

            while (other_current != other.head) {
                current->next_element = new Element(other_current->value, nullptr);
                current = current->next_element;
                other_current = other_current->next_element;
            }
            current->next_element = head;
            list_size = other.list_size;
        }
    }

    CircularLinkedList& operator=(const CircularLinkedList& other) {
        if (this != &other) {
            clear();

            if (other.head) {
                head = new Element(other.head->value, nullptr);
                Element* current = head;
                Element* other_current = other.head->next_element;

                while (other_current != other.head) {
                    current->next_element = new Element(other_current->value, nullptr);
                    current = current->next_element;
                    other_current = other_current->next_element;
                }
                current->next_element = head;
                list_size = other.list_size;
            }
        }
        return *this;
    }

    bool operator==(const CircularLinkedList& other) const {
        if (list_size != other.list_size) return false;
        if (head == nullptr && other.head == nullptr) return true;
        if (head == nullptr || other.head == nullptr) return false;

        Element* this_current = head;
        Element* other_current = other.head;

        for (size_t i = 0; i < list_size; ++i) {
            if (this_current->value == other_current->value) {
                Element* this_temp = this_current->next_element;
                Element* other_temp = other_current->next_element;
                bool is_match = true;

                for (size_t j = 1; j < list_size; ++j) {
                    if (this_temp->value != other_temp->value) {
                        is_match = false;
                        break;
                    }
                    this_temp = this_temp->next_element;
                    other_temp = other_temp->next_element;
                }

                if (is_match) return true;
            }
            other_current = other_current->next_element;
        }
        return false;
    }

    bool operator!=(const CircularLinkedList& other) const {
        return !(*this == other);
    }

};


#endif
