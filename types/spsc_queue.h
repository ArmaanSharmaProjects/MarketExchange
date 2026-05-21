#pragma once

#include <atomic>
#include <cstddef>
#include <vector>

#include "macros.h"

namespace utils
{
    template <typename T, std::size_t Capacity>
    class SPSCQueue final
    {
        // Ensure queue size is a power of two
        static_assert((Capacity != 0) && ((Capacity & (Capacity - 1)) == 0), "Capacity must be a strict power of 2 for bitwise masking");

    public:
        // Pre-allocate the vector to the exact capacity immediately
        SPSCQueue() : store_(Capacity, T()) {}

        // Prevent accidental copying or moving of the lock-free queue
        SPSCQueue(const SPSCQueue &) = delete;
        SPSCQueue(SPSCQueue &&) = delete;
        SPSCQueue &operator=(const SPSCQueue &) = delete;
        SPSCQueue &operator=(SPSCQueue &&) = delete;

        // PRODUCER METHODS
        auto getNextToWriteTo() noexcept -> T *
        {
            auto write_index = next_write_index_.load(std::memory_order_relaxed);
            auto read_index = next_read_index_.load(std::memory_order_acquire);

            if (write_index - read_index == Capacity)
            {
                return nullptr; // Queue is completely full
            }

            return &store_[write_index & Mask_];
        }

        auto updateWriteIndex() noexcept -> void
        {
            auto current = next_write_index_.load(std::memory_order_relaxed);
            next_write_index_.store(current + 1, std::memory_order_release);
        }

        // CONSUMER METHODS

        auto getNextToRead() const noexcept -> const T *
        {
            auto read_index = next_read_index_.load(std::memory_order_relaxed);
            auto write_index = next_write_index_.load(std::memory_order_acquire);

            if (read_index == write_index)
            {
                return nullptr; // Queue is entirely empty
            }

            return &store_[read_index & Mask_];
        }

        auto updateReadIndex() noexcept -> void
        {
            auto current = next_read_index_.load(std::memory_order_relaxed);
            next_read_index_.store(current + 1, std::memory_order_release);
        }

        // HELPER

        auto size() const noexcept -> std::size_t
        {
            auto write_index = next_write_index_.load(std::memory_order_acquire);
            auto read_index = next_read_index_.load(std::memory_order_relaxed);
            return write_index - read_index;
        }

    private:
        // This forces wrap around for read and write indexes based on the size of the array
        static constexpr std::size_t Mask_ = Capacity - 1;

        std::vector<T> store_;

        // Align indices to separate 64-byte cache lines to prevent false sharing
        alignas(64) std::atomic<std::size_t> next_write_index_{0};
        alignas(64) std::atomic<std::size_t> next_read_index_{0};
    };
}