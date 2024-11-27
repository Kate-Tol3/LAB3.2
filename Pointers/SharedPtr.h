#pragma once

#include <stdexcept>

template <typename T>
struct ControlBlock {
    T* s_ptr;             // Pointer to the managed object or array
    int ref_count;        // Strong reference count (SharedPtr)
    int weak_count;       // Weak reference count (WeakPtr)
    bool is_array;        // Flag to indicate if s_ptr is an array

    ControlBlock(T* ptr = nullptr, bool isArray = false)
        : s_ptr(ptr), ref_count(1), weak_count(0), is_array(isArray) {}

    // Destroy the managed object or array, but not the control block itself
    void deleteObject() {
        if (is_array) {
            delete[] s_ptr;
        } else {
            delete s_ptr;
        }
        s_ptr = nullptr;
    }
};

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
private:
    ControlBlock<T>* control_block;

public:
    // Constructor for single objects
    explicit SharedPtr(T* p = nullptr)
        : control_block(p ? new ControlBlock<T>(p, false) : nullptr) {}

    // Constructor for arrays
    explicit SharedPtr(T* p, bool isArray)
        : control_block(p ? new ControlBlock<T>(p, isArray) : nullptr) {}

    // Copy constructor
    SharedPtr(const SharedPtr& other) : control_block(other.control_block) {
        if (control_block) {
            ++(control_block->ref_count);
        }
    }

    // Move constructor
    SharedPtr(SharedPtr&& other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    // Construct from a WeakPtr
    SharedPtr(const WeakPtr<T>& weak) : control_block(weak.control_block) {
        if (control_block) {
            ++control_block->ref_count;
        }
    }

    ~SharedPtr() {
        release();
    }

    // Copy assignment
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            control_block = other.control_block;
            if (control_block) {
                ++(control_block->ref_count);
            }
        }
        return *this;
    }

    // Move assignment
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            control_block = other.control_block;
            other.control_block = nullptr;
        }
        return *this;
    }

    // Resource release
    void release() {
        if (control_block) {
            if (--control_block->ref_count == 0) {
                control_block->deleteObject();  // Delete the managed object or array
                if (control_block->weak_count == 0) {
                    delete control_block;  // Delete the control block if no weak references exist
                }
            }
            control_block = nullptr;
        }
    }

    // Access the object (for non-arrays)
    const T& operator*() const {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return *control_block->s_ptr;
    }
    T& operator*() {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return *control_block->s_ptr;
    }

    // Access the object or array element via pointer (for arrays)
    const T* operator->() const {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return control_block->s_ptr;
    }
    T* operator->() {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return control_block->s_ptr;
    }

    // Array subscript operator (only for arrays)
    T& operator[](size_t index) {
        if (!control_block || !control_block->is_array) {
            throw std::out_of_range("Not managing an array.\n");
        }
        return control_block->s_ptr[index];
    }

    // Get the raw pointer
    const T* get() const { return control_block ? control_block->s_ptr : nullptr; }
    T* get() { return control_block ? control_block->s_ptr : nullptr; }

    const int useCount() const { return control_block ? control_block->ref_count : 0; }
    int useCount() { return control_block ? control_block->ref_count : 0; }

    const bool isNull() const { return control_block == nullptr || control_block->s_ptr == nullptr; }
    bool isNull() { return control_block == nullptr || control_block->s_ptr == nullptr; }

    void swap(SharedPtr& other) noexcept {
        std::swap(control_block, other.control_block);
    }

    const bool expired() const {
        return !control_block || control_block->ref_count == 0;
    }

    const bool unique() const {
        return control_block && control_block->ref_count == 1;
    }

    friend class WeakPtr<T>;
};