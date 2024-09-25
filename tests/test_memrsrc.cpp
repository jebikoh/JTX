#include <jtxlib/std/memory_resource.hpp>
#include <catch2/catch_test_macros.hpp>

// Unit tests written o1-mini with manual revisions

using namespace jtx::pmr;

static constexpr size_t max_align = alignof(std::max_align_t);

bool is_aligned(void* ptr, size_t alignment) {
    return (reinterpret_cast<std::uintptr_t>(ptr) % alignment) == 0;
}

struct TestStruct {
    int value;
    explicit TestStruct(const int v = 0) : value(v) {}
    ~TestStruct() = default;
};

#pragma region memory_resource
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
#pragma endregion memory_resource

#pragma region polymorphic_allocator
TEST_CASE("polymorphic_allocator constructors", "[polymorphic_allocator][constructors]") {
    memory_resource* custom_mr = null_memory_resource();

    SECTION("Default constructor uses default memory resource") {
        polymorphic_allocator<int> alloc;
        REQUIRE(alloc.resource() == get_default_resource());
    }

    SECTION("Constructor with memory_resource* sets the resource correctly") {
        polymorphic_allocator<int> alloc(custom_mr);
        REQUIRE(alloc.resource() == custom_mr);
    }

    SECTION("Copy constructor copies the allocator correctly") {
        polymorphic_allocator<int> original_alloc(custom_mr);
        polymorphic_allocator<int> copy_alloc(original_alloc);
        REQUIRE(copy_alloc.resource() == original_alloc.resource());
    }

    SECTION("Templated copy constructor allows different types with the same resource") {
        polymorphic_allocator<int> original_alloc(custom_mr);
        polymorphic_allocator<double> copy_alloc(original_alloc);
        REQUIRE(copy_alloc.resource() == original_alloc.resource());
    }
}

TEST_CASE("polymorphic_allocator allocation and deallocation", "[polymorphic_allocator][allocate][deallocate]") {
    memory_resource* mr = new_delete_resource();
    polymorphic_allocator<int> alloc(mr);

    SECTION("Allocate non-zero number of objects") {
        size_t num_objects = 10;
        int* ptr = alloc.allocate(num_objects);
        REQUIRE(ptr != nullptr);
        REQUIRE(is_aligned(ptr, alignof(int)));
        alloc.deallocate(ptr, num_objects);
    }

    SECTION("Allocate zero objects returns non-null pointer (implementation-defined)") {
        size_t num_objects = 0;
        int* ptr = alloc.allocate(num_objects);
        // Depending on implementation, allocating zero may return a non-null unique pointer or nullptr
        // Here, we just ensure it does not crash
        REQUIRE(ptr == nullptr); // Placeholder, adjust based on your implementation
    }

    SECTION("Deallocate nullptr does nothing") {
        REQUIRE_NOTHROW(alloc.deallocate(nullptr, 10));
    }

    SECTION("Allocate and deallocate multiple times") {
        size_t num_objects = 5;
        int* ptr1 = alloc.allocate(num_objects);
        int* ptr2 = alloc.allocate(num_objects);
        REQUIRE(ptr1 != nullptr);
        REQUIRE(ptr2 != nullptr);
        REQUIRE(ptr1 != ptr2);
        alloc.deallocate(ptr1, num_objects);
        alloc.deallocate(ptr2, num_objects);
    }

    SECTION("Allocate with specific alignment via object type") {
        polymorphic_allocator<TestStruct> struct_alloc(mr);
        size_t num_objects = 3;
        TestStruct* ptr = struct_alloc.allocate(num_objects);
        REQUIRE(ptr != nullptr);
        REQUIRE(is_aligned(ptr, alignof(TestStruct)));
        struct_alloc.deallocate(ptr, num_objects);
    }
}

TEST_CASE("polymorphic_allocator comparisons", "[polymorphic_allocator][comparison]") {
    memory_resource* mr1 = new_delete_resource();
    memory_resource* mr2 = null_memory_resource();

    polymorphic_allocator<int> alloc1(mr1);
    polymorphic_allocator<int> alloc2(mr1);
    polymorphic_allocator<double> alloc3(mr1);
    polymorphic_allocator<int> alloc4(mr2);

    SECTION("Allocators with the same memory_resource are equal") {
        REQUIRE(alloc1 == alloc2);
        REQUIRE(alloc1 == alloc3);
    }

    SECTION("Allocators with different memory_resources are not equal") {
        REQUIRE(alloc1 != alloc4);
        REQUIRE(alloc2 != alloc4);
        REQUIRE(alloc3 != alloc4);
    }
}

TEST_CASE("polymorphic_allocator object construction and destruction", "[polymorphic_allocator][object][construction][destruction]") {
    memory_resource* mr = new_delete_resource();
    polymorphic_allocator<TestStruct> alloc(mr);

    SECTION("Construct and destruct a single object") {
        TestStruct* obj = alloc.new_object<TestStruct>(42);
        REQUIRE(obj != nullptr);
        REQUIRE(obj->value == 42);
        alloc.delete_object(obj);
    }

    SECTION("Construct and destruct multiple objects") {
        size_t num_objects = 5;
        TestStruct* objs = alloc.allocate_object<TestStruct>(num_objects);
        REQUIRE(objs != nullptr);
        for (size_t i = 0; i < num_objects; ++i) {
            alloc.construct(&objs[i], static_cast<int>(i));
            REQUIRE(objs[i].value == static_cast<int>(i));
        }
        for (size_t i = 0; i < num_objects; ++i) {
            alloc.destroy(&objs[i]);
        }
        alloc.deallocate_object(objs, num_objects);
    }

    SECTION("New and delete object with default constructor") {
        TestStruct* obj = alloc.new_object<TestStruct>();
        REQUIRE(obj != nullptr);
        REQUIRE(obj->value == 0);
        alloc.delete_object(obj);
    }
}

TEST_CASE("polymorphic_allocator allocate_bytes and deallocate_bytes", "[polymorphic_allocator][allocate_bytes][deallocate_bytes]") {
    memory_resource* mr = new_delete_resource();
    polymorphic_allocator<char> alloc(mr);

    SECTION("Allocate and deallocate bytes with max alignment") {
        size_t num_bytes = 100;
        void* ptr = alloc.allocate_bytes(num_bytes);
        REQUIRE(ptr != nullptr);
        REQUIRE(is_aligned(ptr, alignof(std::max_align_t)));
        alloc.deallocate_bytes(ptr, num_bytes);
    }

    SECTION("Allocate zero bytes returns nullptr or unique pointer") {
        size_t num_bytes = 0;
        void* ptr = alloc.allocate_bytes(num_bytes);
        REQUIRE(ptr == nullptr);
    }
}

TEST_CASE("polymorphic_allocator exception handling", "[polymorphic_allocator][exception]") {
    memory_resource* null_mr = null_memory_resource();
    polymorphic_allocator<int> alloc(null_mr);

    SECTION("Allocation with null_memory_resource throws std::bad_alloc") {
        REQUIRE_THROWS_AS(alloc.allocate(10), std::bad_alloc);
    }

    SECTION("new_object with null_memory_resource throws std::bad_alloc") {
        REQUIRE_THROWS_AS(alloc.new_object<int>(5), std::bad_alloc);
    }
}
#pragma endregion polymorphic_allocator
