#pragma once

#include <tuple>
#include <jtxlib.hpp>
#include <jtxlib/util/assert.hpp>

/**
 * This is a similar approach to the tagged pointer pattern used in PBRTv4.
 * The main difference is I do not store/mask the tag in the pointer itself.
 * https://github.com/mmp/pbrt-v4/blob/39e01e61f8de07b99859df04b271a02a53d9aeb2/src/pbrt/util/taggedptr.h
 *
 * TODO:
 *  - Look into using std::variant
 *  - Look into using std::forward and std::visit
 *  - Profile on CUDA
*/
namespace jtx {
    namespace detail {
        //region const dispatch
        template<typename F, typename R, typename T>
        JTX_HOSTDEV R dispatch(F &&f, const void *ptr, int tag) {
            ASSERT(tag == 0);
            return func((const T *)ptr);
        }

        template<typename F, typename R, typename T0, typename T1>
        JTX_HOSTDEV R dispatch(F &&f, const void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 1);
            if (tag == 0) {
                return f((const T0 *)ptr);
            } else {
                return f((const T1 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2>
        JTX_HOSTDEV R dispatch(F &&f, const void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 2);
            switch(tag) {
                case 0:
                    return f((const T0 *)ptr);
                case 1:
                    return f((const T1 *)ptr);
                default:
                    return f((const T2 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2, typename T3>
        JTX_HOSTDEV R dispatch(F &&f, const void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 3);
            switch(tag) {
                case 0:
                    return f((const T0 *)ptr);
                case 1:
                    return f((const T1 *)ptr);
                case 2:
                    return f((const T2 *)ptr);
                default:
                    return f((const T3 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2, typename T3, typename T4>
        JTX_HOSTDEV R dispatch(F &&f, const void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 4);
            switch(tag) {
                case 0:
                    return f((const T0 *)ptr);
                case 1:
                    return f((const T1 *)ptr);
                case 2:
                    return f((const T2 *)ptr);
                case 3:
                    return f((const T3 *)ptr);
                default:
                    return f((const T4 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        JTX_HOSTDEV R dispatch(F &&f, const void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 5);
            switch(tag) {
                case 0:
                    return f((const T0 *)ptr);
                case 1:
                    return f((const T1 *)ptr);
                case 2:
                    return f((const T2 *)ptr);
                case 3:
                    return f((const T3 *)ptr);
                case 4:
                    return f((const T4 *)ptr);
                default:
                    return f((const T5 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        JTX_HOSTDEV R dispatch(F &&f, const void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 6);
            switch(tag) {
                case 0:
                    return f((const T0 *)ptr);
                case 1:
                    return f((const T1 *)ptr);
                case 2:
                    return f((const T2 *)ptr);
                case 3:
                    return f((const T3 *)ptr);
                case 4:
                    return f((const T4 *)ptr);
                case 5:
                    return f((const T5 *)ptr);
                default:
                    return f((const T6 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        JTX_HOSTDEV R dispatch(F &&f, const void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 7);
            switch(tag) {
                case 0:
                    return f((const T0 *)ptr);
                case 1:
                    return f((const T1 *)ptr);
                case 2:
                    return f((const T2 *)ptr);
                case 3:
                    return f((const T3 *)ptr);
                case 4:
                    return f((const T4 *)ptr);
                case 5:
                    return f((const T5 *)ptr);
                case 6:
                    return f((const T6 *)ptr);
                default:
                    return f((const T7 *)ptr);
            }
        }
        //endregion

        //region non-const dispatch
        template<typename F, typename R, typename T>
        JTX_HOSTDEV R dispatch(F &&f, void *ptr, int tag) {
            ASSERT(tag == 0);
            return func((T *)ptr);
        }

        template<typename F, typename R, typename T0, typename T1>
        JTX_HOSTDEV R dispatch(F &&f, void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 1);
            if (tag == 0) {
                return f((T0 *)ptr);
            } else {
                return f((T1 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2>
        JTX_HOSTDEV R dispatch(F &&f, void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 2);
            switch(tag) {
                case 0:
                    return f((T0 *)ptr);
                case 1:
                    return f((T1 *)ptr);
                default:
                    return f((T2 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2, typename T3>
        JTX_HOSTDEV R dispatch(F &&f, void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 3);
            switch(tag) {
                case 0:
                    return f((T0 *)ptr);
                case 1:
                    return f((T1 *)ptr);
                case 2:
                    return f((T2 *)ptr);
                default:
                    return f((T3 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2, typename T3, typename T4>
        JTX_HOSTDEV R dispatch(F &&f, void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 4);
            switch(tag) {
                case 0:
                    return f((T0 *)ptr);
                case 1:
                    return f((T1 *)ptr);
                case 2:
                    return f((T2 *)ptr);
                case 3:
                    return f((T3 *)ptr);
                default:
                    return f((T4 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        JTX_HOSTDEV R dispatch(F &&f, void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 5);
            switch(tag) {
                case 0:
                    return f((T0 *)ptr);
                case 1:
                    return f((T1 *)ptr);
                case 2:
                    return f((T2 *)ptr);
                case 3:
                    return f((T3 *)ptr);
                case 4:
                    return f((T4 *)ptr);
                default:
                    return f((T5 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        JTX_HOSTDEV R dispatch(F &&f, void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 6);
            switch(tag) {
                case 0:
                    return f((T0 *)ptr);
                case 1:
                    return f((T1 *)ptr);
                case 2:
                    return f((T2 *)ptr);
                case 3:
                    return f((T3 *)ptr);
                case 4:
                    return f((T4 *)ptr);
                case 5:
                    return f((T5 *)ptr);
                default:
                    return f((T6 *)ptr);
            }
        }

        template<typename F, typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        JTX_HOSTDEV R dispatch(F &&f, void *ptr, int tag) {
            ASSERT(tag >= 0 && tag <= 7);
            switch(tag) {
                case 0:
                    return f((T0 *)ptr);
                case 1:
                    return f((T1 *)ptr);
                case 2:
                    return f((T2 *)ptr);
                case 3:
                    return f((T3 *)ptr);
                case 4:
                    return f((T4 *)ptr);
                case 5:
                    return f((T5 *)ptr);
                case 6:
                    return f((T6 *)ptr);
                default:
                    return f((T7 *)ptr);
            }
        }
        //endregion

        template<typename... Ts>
        struct IsSameType;

        template<>
        struct IsSameType<> {
            static constexpr bool val = true;
        };

        template<typename T>
        struct IsSameType<T> {
            static constexpr bool val = true;
        };

        template<typename T, typename U, typename...Ts>
        struct IsSameType<T, U, Ts...> {
            static constexpr bool val = (std::is_same_v<T, U> && IsSameType<U, Ts...>::val);
        };

        template<typename... Ts>
        struct SameType;

        template<typename T, typename... Ts>
        struct SameType<T, Ts...> {
            using type = T;
            static_assert(IsSameType<T, Ts...>::val, "Not all types are the same");
        };

        template<typename F, typename ...Ts>
        struct ReturnType {
            using type = typename SameType<typename std::invoke_result_t<F, Ts *>...>::type;
        };

        template<typename F, typename... Ts>
        struct ReturnTypeConst {
            using type = typename SameType<typename std::invoke_result_t<F, const Ts *>...>::type;
        };
    }

    template<typename... Ts>
    class TaggedPtr {
    public:
        TaggedPtr() = default;

        template<typename T>
        JTX_HOSTDEV TaggedPtr(T *ptr) : ptr(ptr), tag(tagIndex<T>()) {}

        JTX_HOSTDEV TaggedPtr(std::nullptr_t ptr) : ptr(nullptr), tag(0) {}

        JTX_HOSTDEV TaggedPtr(const TaggedPtr &other) : ptr(other.ptr), tag(other.tag) {}

        JTX_HOSTDEV TaggedPtr &operator=(const TaggedPtr &other) {
            this->ptr = other.ptr;
            this->tag = other.tag;
            return *this;
        }

        [[nodiscard]] JTX_HOSTDEV unsigned int getTag() const { return tag; }

        template<typename T>
        [[nodiscard]] JTX_HOSTDEV bool is() const {
            return tag == tagIndex<T>();
        }

        JTX_HOSTDEV bool operator==(const TaggedPtr &other) const {
            return ptr == other.ptr && tag == other.tag;
        }

        JTX_HOSTDEV bool operator!=(const TaggedPtr &other) const {
            return ptr != other.ptr || tag != other.tag;
        }

        JTX_HOSTDEV void *getPtr() { return ptr; }
        [[nodiscard]] JTX_HOSTDEV void *getPtr() const { return ptr; }

        template<typename T>
        [[nodiscard]] JTX_HOSTDEV constexpr unsigned int tagIndex() const {
            using type = std::remove_cv_t<T>;
            if constexpr (std::is_same_v<type, std::nullptr_t>) return 0;
            else return 1 + getTagIndex<type, Ts...>();
        }

        template<typename F>
        JTX_HOSTDEV decltype(auto) dispatch(F &&f) {
            using R = typename detail::ReturnType<F, Ts...>::type;
            return detail::dispatch<F, R, Ts...>(f, ptr, tag - 1);
        }
    private:
        void *ptr;
        unsigned int tag;

        template<typename T, typename U, typename...Rest>
        [[nodiscard]] JTX_HOSTDEV constexpr unsigned int tagIndex() const {
            if constexpr (std::is_same_v<T, U>) return 0;
            else if constexpr (sizeof...(Rest) == 0) return -1;
            else return 1 + getTagIndex<T, Rest...>();
        }
    };
}