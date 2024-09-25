#include <jtxlib/std/memory_resource.hpp>
#include <catch2/catch_test_macros.hpp>

// Unit tests written o1-mini with manual revisions

using namespace jtx::pmr;

static constexpr size_t max_align = alignof(std::max_align_t);

bool is_aligned(void* ptr, size_t alignment) {
    return (reinterpret_cast<std::uintptr_t>(ptr) % alignment) == 0;
}

TEST_CASE("Singleton behavior of memory resources", "[memory_resource][singleton]") {
    memory_resource* mr1 = new_delete_resource();
    memory_resource* mr2 = new_delete_resource();
    memory_resource* mr_null1 = null_memory_resource();
    memory_resource* mr_null2 = null_memory_resource();

    SECTION("new_delete_resource returns the same instance") {
        REQUIRE(mr1 == mr2);
    }

    SECTION("null_memory_resource returns the same instance") {
        REQUIRE(mr_null1 == mr_null2);
    }

    SECTION("new_delete_resource and null_memory_resource return different instances") {
        REQUIRE(mr1 != mr_null1);
    }
}

TEST_CASE("Exception handling in null_memory_resource", "[memory_resource][null_resource]") {
    memory_resource* null_mr = null_memory_resource();

    SECTION("Allocation with null_memory_resource throws std::bad_alloc") {
        REQUIRE_THROWS_AS(null_mr->allocate(128), std::bad_alloc);
    }

    SECTION("Deallocate with null_memory_resource does not throw, even with non-null pointer") {
        // To test deallocate with a non-null pointer, we'll allocate using new_delete_resource
        memory_resource* newdel_mr = new_delete_resource();
        void* ptr = nullptr;
        REQUIRE_NOTHROW(ptr = newdel_mr->allocate(64));
        REQUIRE(ptr != nullptr);
        // Now deallocate using null_memory_resource
        REQUIRE_NOTHROW(null_mr->deallocate(ptr, 64));
        // Deallocate the pointer properly to avoid memory leak
        newdel_mr->deallocate(ptr, 64);
    }
}

TEST_CASE("Global memory resource functions", "[memory_resource][global_functions]") {
    // Ensure default resource is new_delete_resource at start
    memory_resource* initial_default = get_default_resource();
    REQUIRE(initial_default == new_delete_resource());

    // Set default to null_memory_resource
    memory_resource* old_default = set_default_resource(null_memory_resource());
    REQUIRE(old_default == new_delete_resource());
    REQUIRE(get_default_resource() == null_memory_resource());

    // Set default back to new_delete_resource
    memory_resource* reset_default = set_default_resource(new_delete_resource());
    REQUIRE(reset_default == null_memory_resource());
    REQUIRE(get_default_resource() == new_delete_resource());
}

TEST_CASE("Allocation and deallocation with new_delete_resource", "[memory_resource][new_delete_resource]") {
    memory_resource* mr = new_delete_resource();

    SECTION("Allocate non-zero bytes with default alignment") {
        size_t bytes = 64;
        void* ptr = mr->allocate(bytes);
        REQUIRE(ptr != nullptr);
        REQUIRE(is_aligned(ptr, max_align));
        mr->deallocate(ptr, bytes);
    }

    SECTION("Allocate zero bytes returns nullptr") {
        size_t bytes = 0;
        void* ptr = mr->allocate(bytes);
        REQUIRE(ptr == nullptr);
    }

    SECTION("Deallocate nullptr does nothing") {
        REQUIRE_NOTHROW(mr->deallocate(nullptr, 64));
    }

    SECTION("Allocate with specific alignment") {
        size_t bytes = 128;
        size_t alignment = 32;
        void* ptr = mr->allocate(bytes, alignment);
        REQUIRE(ptr != nullptr);
        REQUIRE(is_aligned(ptr, alignment));
        mr->deallocate(ptr, bytes, alignment);
    }

    SECTION("Deallocate with different alignment is handled correctly") {
        size_t bytes = 256;
        size_t alignment_alloc = 64;
        size_t alignment_dealloc = 16;
        void* ptr = mr->allocate(bytes, alignment_alloc);
        REQUIRE(ptr != nullptr);
        REQUIRE(is_aligned(ptr, alignment_alloc));
        REQUIRE_NOTHROW(mr->deallocate(ptr, bytes, alignment_dealloc));
    }

    SECTION("Multiple allocations and deallocations") {
        constexpr size_t num_allocs = 10;
        constexpr size_t alloc_size = 64;
        void* ptrs[num_allocs] = {nullptr};

        // Allocate multiple blocks
        for (size_t i = 0; i < num_allocs; ++i) {
            ptrs[i] = mr->allocate(alloc_size);
            REQUIRE(ptrs[i] != nullptr);
            REQUIRE(is_aligned(ptrs[i], max_align));
        }

        // Deallocate in reverse order
        for (size_t i = num_allocs; i > 0; --i) {
            REQUIRE_NOTHROW(mr->deallocate(ptrs[i - 1], alloc_size));
        }
    }

    SECTION("Allocation with maximum alignment") {
        size_t bytes = 1024;
        size_t alignment = max_align;
        void* ptr = mr->allocate(bytes, alignment);
        REQUIRE(ptr != nullptr);
        REQUIRE(is_aligned(ptr, alignment));
        mr->deallocate(ptr, bytes, alignment);
    }
}

TEST_CASE("Equality comparisons of memory resources", "[memory_resource][equality]") {
    memory_resource* mr1 = new_delete_resource();
    memory_resource* mr2 = new_delete_resource();
    memory_resource* mr3 = null_memory_resource();
    memory_resource* mr4 = set_default_resource(mr3); // Set default to null_memory_resource

    SECTION("Same resource instances are equal") {
        REQUIRE(*mr1 == *mr1);
        REQUIRE(*mr3 == *mr3);
    }

    SECTION("Different instances of the same type are equal based on is_equal") {
        REQUIRE(*mr1 == *mr2);
    }

    SECTION("Different types of memory resources are not equal") {
        REQUIRE(*mr1 != *mr3);
    }

    SECTION("Operator!= works correctly") {
        REQUIRE_FALSE(*mr1 != *mr2);
        REQUIRE(*mr1 != *mr3);
    }

    SECTION("After setting default resource, equality is maintained correctly") {
        memory_resource* default_before = set_default_resource(mr1);
        memory_resource* default_after = get_default_resource();
        REQUIRE(default_after == mr1);
        REQUIRE(default_before == mr3);
        REQUIRE(*default_before != *default_after);
    }
}

TEST_CASE("null_memory_resource behavior", "[memory_resource][null_resource]") {
    memory_resource* mr = null_memory_resource();

    SECTION("Allocate throws std::bad_alloc") {
        REQUIRE_THROWS_AS(mr->allocate(100), std::bad_alloc);
    }

    SECTION("Deallocate nullptr does nothing") {
        REQUIRE_NOTHROW(mr->deallocate(nullptr, 100));
    }

    SECTION("Deallocate with non-null pointer does nothing or handles gracefully") {
        memory_resource* newdel_mr = new_delete_resource();
        void* ptr = nullptr;
        REQUIRE_NOTHROW(ptr = newdel_mr->allocate(64));
        REQUIRE(ptr != nullptr);
        REQUIRE_NOTHROW(mr->deallocate(ptr, 64));
        newdel_mr->deallocate(ptr, 64);
    }
}

TEST_CASE("Memory resource allocation consistency", "[memory_resource][consistency]") {
    memory_resource* mr = new_delete_resource();

    SECTION("Repeated allocations and deallocations do not interfere") {
        constexpr size_t num_iterations = 100;
        constexpr size_t alloc_size = 32;
        void* ptrs[num_iterations] = {nullptr};

        // Allocate multiple times
        for (auto & ptr : ptrs) {
            ptr = mr->allocate(alloc_size);
            REQUIRE(ptr != nullptr);
            REQUIRE(is_aligned(ptr, max_align));
        }

        // Deallocate all
        for (auto & ptr : ptrs) {
            REQUIRE_NOTHROW(mr->deallocate(ptr, alloc_size));
        }
    }

    SECTION("Allocate with varying alignments") {
        size_t bytes = 128;
        size_t alignments[] = {8, 16, 32, 64, 128, alignof(std::max_align_t)};
        for (size_t alignment : alignments) {
            void* ptr = mr->allocate(bytes, alignment);
            REQUIRE(ptr != nullptr);
            REQUIRE(is_aligned(ptr, alignment));
            mr->deallocate(ptr, bytes, alignment);
        }
    }

    SECTION("Allocate and deallocate with maximum alignment") {
        size_t bytes = 256;
        size_t alignment = alignof(std::max_align_t);
        void* ptr = mr->allocate(bytes, alignment);
        REQUIRE(ptr != nullptr);
        REQUIRE(is_aligned(ptr, alignment));
        mr->deallocate(ptr, bytes, alignment);
    }
}

TEST_CASE("Memory resource behavior under stress", "[memory_resource][stress]") {
    memory_resource* mr = new_delete_resource();

    constexpr size_t num_allocs = 1000;
    constexpr size_t alloc_size = 64;
    void* ptrs[num_allocs] = {nullptr};

    SECTION("Stress test with multiple allocations and deallocations") {
        // Allocate
        for (auto & ptr : ptrs) {
            ptr = mr->allocate(alloc_size);
            REQUIRE(ptr != nullptr);
            REQUIRE(is_aligned(ptr, max_align));
        }

        // Shuffle deallocation order
        for (size_t i = 0; i < num_allocs; ++i) {
            size_t index = num_allocs - 1 - i;
            REQUIRE_NOTHROW(mr->deallocate(ptrs[index], alloc_size));
        }
    }
}
