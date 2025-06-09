#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H


#include <stdexcept>
#include <iterator>
#include <utility>


/**
 * @class CircularLinkedList
 * @brief A circular singly linked list container.
 *
 * This class implements a circular singly linked list similar in interface
 * to std::forward_list. The list elements are linked in a circle, where the
 * last element points back to the head.
 *
 * @tparam T Type of elements stored in the list.
 */
template <typename T>
class CircularLinkedList {
private:
    /**
     * @struct Element
     * @brief Represents a node in the circular linked list.
     *
     * Holds the value of type T and a pointer to the next element in the list.
     */
    struct Element {
        T value;               ///< Value stored in the node.
        Element* next_element; ///< Pointer to the next node.

        /**
         * @brief Constructs an Element with a value and next pointer.
         * @param val Value to store.
         * @param next Pointer to the next element.
         */
        Element(const T& val, Element* next) : value(val), next_element(next) {}
    };

    Element* head;      ///< Pointer to the head (start) of the list.
    size_t list_size;   ///< Number of elements in the list.

public:
    /// Forward declaration of iterator classes as friends.
    friend class iterator;
    friend class const_iterator;

    /**
     * @class iterator
     * @brief Forward iterator for CircularLinkedList.
     *
     * Supports traversal of the list from head to end (one past last element).
     */
    class iterator {
        friend class CircularLinkedList;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        /**
         * @brief Constructs an iterator.
         * @param elem Pointer to current element.
         * @param head Pointer to the head element of the list.
         * @param end Flag indicating if this is the end iterator.
         */
        iterator(Element* elem, Element* head, bool end) : element(elem), head_ptr(head), isEnd(end) {}

        ~iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;

        /**
         * @brief Dereference operator.
         * @return Reference to the value of the current element.
         * @throws std::out_of_range if iterator is invalid or at end.
         */
        T& operator*() const {
            if (!element || isEnd) throw std::out_of_range("Dereferencing invalid iterator");
            return element->value;
        }

        /**
         * @brief Member access operator.
         * @return Pointer to the value of the current element.
         * @throws std::out_of_range if iterator is invalid or at end.
         */
        T* operator->() const {
            if (!element || isEnd) throw std::out_of_range("Dereferencing invalid iterator");
            return &(element->value);
        }

        /**
         * @brief Pre-increment operator.
         * Advances the iterator to the next element.
         * @return Reference to the incremented iterator.
         * @throws std::out_of_range if iterator is invalid or at end.
         */
        iterator& operator++() {
            if (!element || isEnd) throw std::out_of_range("Advancing invalid iterator");
            element = element->next_element;
            if (element == head_ptr) isEnd = true;
            return *this;
        }

        /**
         * @brief Post-increment operator.
         * Advances the iterator but returns the previous state.
         * @return Iterator before increment.
         * @throws std::out_of_range if iterator is invalid or at end.
         */
        iterator operator++(int) {
            if (!element || isEnd) throw std::out_of_range("Advancing invalid iterator");
            iterator initial = *this;
            ++(*this);
            return initial;
        }

        /**
         * @brief Equality comparison.
         * @param other Iterator to compare with.
         * @return True if both iterators point to the same element and end state.
         */
        bool operator==(const iterator& other) const {
            return element == other.element && isEnd == other.isEnd;
        }

        /**
         * @brief Inequality comparison.
         * @param other Iterator to compare with.
         * @return True if iterators differ.
         */
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        Element* element;   ///< Current element pointer.
        Element* head_ptr;  ///< Head of the list pointer.
        bool isEnd;        ///< True if iterator is the end iterator.
    };

    /**
     * @class const_iterator
     * @brief Constant forward iterator for CircularLinkedList.
     *
     * Provides read-only access to list elements.
     */
    class const_iterator {
        friend class CircularLinkedList;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = const T;
        using pointer           = const T*;
        using reference         = const T&;

        /**
         * @brief Constructs a const_iterator.
         * @param elem Pointer to current element.
         * @param head Pointer to the head element of the list.
         * @param end Flag indicating if this is the end iterator.
         */
        const_iterator(const Element* elem, const Element* head, bool end) : element(elem), head_ptr(head), isEnd(end) {}

        ~const_iterator() = default;
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;

        /**
         * @brief Dereference operator.
         * @return Const reference to the value of the current element.
         * @throws std::out_of_range if iterator is invalid or at end.
         */
        const T& operator*() const {
            if (!element || isEnd) throw std::out_of_range("Dereferencing invalid iterator");
            return element->value;
        }

        /**
         * @brief Member access operator.
         * @return Const pointer to the value of the current element.
         * @throws std::out_of_range if iterator is invalid or at end.
         */
        const T* operator->() const {
            if (!element || isEnd) throw std::out_of_range("Dereferencing invalid iterator");
            return &(element->value);
        }

        /**
         * @brief Pre-increment operator.
         * Advances the iterator to the next element.
         * @return Reference to the incremented iterator.
         * @throws std::out_of_range if iterator is invalid or at end.
         */
        const_iterator& operator++() {
            if (!element || isEnd) throw std::out_of_range("Advancing invalid iterator");
            element = element->next_element;
            if (element == head_ptr) isEnd = true;
            return *this;
        }

        /**
         * @brief Post-increment operator.
         * Advances the iterator but returns the previous state.
         * @return Iterator before increment.
         * @throws std::out_of_range if iterator is invalid or at end.
         */
        const_iterator operator++(int) {
            if (!element || isEnd) throw std::out_of_range("Advancing invalid iterator");
            const_iterator initial = *this;
            ++(*this);
            return initial;
        }

        /**
         * @brief Equality comparison.
         * @param other Iterator to compare with.
         * @return True if both iterators point to the same element and end state.
         */
        bool operator==(const const_iterator& other) const {
            return element == other.element && isEnd == other.isEnd;
        }

        /**
         * @brief Inequality comparison.
         * @param other Iterator to compare with.
         * @return True if iterators differ.
         */
        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }

    private:
        const Element* element;   ///< Current element pointer.
        const Element* head_ptr;  ///< Head of the list pointer.
        bool isEnd;              ///< True if iterator is the end iterator.
    };

    /**
     * @brief Default constructor. Creates an empty CircularLinkedList.
     */
    CircularLinkedList() : head(nullptr), list_size(0) {}

    /**
     * @brief Destructor. Clears the list and releases memory.
     */
    ~CircularLinkedList() {
        clear();
    }

    /**
     * @brief Returns an iterator to the first element.
     * @return iterator pointing to the head element.
     */
    iterator begin() {
        return iterator(head, head, false);
    }

    /**
     * @brief Returns an iterator to one past the last element.
     * @return iterator representing the end of the list.
     */
    iterator end() {
        return iterator(head, head, true);
    }

    /**
     * @brief Returns a const_iterator to the first element.
     * @return const_iterator pointing to the head element.
     */
    const_iterator begin() const {
        return const_iterator(head, head, false);
    }

    /**
     * @brief Returns a const_iterator to one past the last element.
     * @return const_iterator representing the end of the list.
     */
    const_iterator end() const {
        return const_iterator(head, head, true);
    }

    /**
     * @brief Returns a const_iterator to the first element.
     * @return const_iterator pointing to the head element.
     */
    const_iterator cbegin() const {
        return begin();
    }

    /**
     * @brief Returns a const_iterator to one past the last element.
     * @return const_iterator representing the end of the list.
     */
    const_iterator cend() const {
        return end();
    }

    /**
     * @brief Inserts a new element at the front of the list.
     * @param value Value to insert.
     */
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

    /**
     * @brief Removes the first element of the list.
     * @throws std::out_of_range if the list is empty.
     */
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

    /**
     * @brief Accesses the first element.
     * @return Reference to the first element's value.
     * @throws std::out_of_range if the list is empty.
     */
    T& front() {
        if (!head) throw std::out_of_range("List is empty");
        return head->value;
    }

    /**
     * @brief Accesses the first element (const version).
     * @return Const reference to the first element's value.
     * @throws std::out_of_range if the list is empty.
     */
    const T& front() const {
        if (!head) throw std::out_of_range("List is empty");
        return head->value;
    }

    /**
     * @brief Checks whether the list is empty.
     * @return True if the list contains no elements.
     */
    bool empty() const {
        return head == nullptr;
    }

    /**
     * @brief Returns the number of elements in the list.
     * @return Size of the list.
     */
    size_t size() const {
        return list_size;
    }

    /**
     * @brief Inserts a new element after the given position.
     * @param pos Iterator pointing to the element after which to insert.
     * @param value Value to insert.
     * @return Iterator pointing to the newly inserted element.
     * @throws std::invalid_argument if pos is invalid or end iterator.
     */
    iterator insert_after(const iterator pos, const T& value) {
        if (!pos.element || pos.isEnd) throw std::invalid_argument("Invalid iterator");
        Element* new_element = new Element(value, pos.element->next_element);
        pos.element->next_element = new_element;
        ++list_size;
        return iterator(new_element, head, false);
    }

    /**
     * @brief Erases the element following the given position.
     * @param pos Iterator pointing to the element before the one to erase.
     * @return Iterator pointing to the element following the erased element.
     * @throws std::invalid_argument if pos is invalid or nothing to erase.
     */
    iterator erase_after(const iterator pos) {
        if (!pos.element || pos.element->next_element == head) throw std::invalid_argument("Invalid iterator or nothing to erase");
        Element* to_erase = pos.element->next_element;
        pos.element->next_element = pos.element->next_element->next_element;
        delete to_erase;
        --list_size;
        return iterator(pos.element->next_element, head, false);
    }

    /**
     * @brief Clears the list, deleting all elements.
     */
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

    /**
     * @brief Copy constructor.
     * Creates a deep copy of another CircularLinkedList.
     * @param other The list to copy from.
     */
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

    /**
     * @brief Copy assignment operator.
     * Replaces the contents with a copy of another list.
     * @param other The list to copy from.
     * @return Reference to this list.
     */
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

    /**
     * @brief Equality comparison operator.
     * Checks if two circular lists contain the same elements in the same order,
     * accounting for circular rotation.
     * @param other The list to compare with.
     * @return True if lists are equal.
     */
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

    /**
     * @brief Inequality comparison operator.
     * @param other The list to compare with.
     * @return True if lists are not equal.
     */
    bool operator!=(const CircularLinkedList& other) const {
        return !(*this == other);
    }
};

#endif
