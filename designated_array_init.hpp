/// @file  designated_array_init.hpp
/// @brief Имитация инициализатора массива с указанием индексов или диапазонов индексов (есть в C99, нет в C++23).
#ifndef KUVSHINOVDR_DESIGNATED_ARRAY_INIT_HPP_INCLUDED
#define KUVSHINOVDR_DESIGNATED_ARRAY_INIT_HPP_INCLUDED

#include <array>
#include <utility>
#include <type_traits>
#include <concepts>

namespace designated_array_init
{

    namespace detail
    {

        template <typename T>
        concept Enum =
            std::is_enum_v<T>;

        template <typename>
        struct ToInteger {};

        template <std::integral Value>
        struct ToInteger<Value>
        {
            using type = Value;
        };

        template <Enum Value>
        struct ToInteger<Value>
        {
            using type = std::underlying_type_t<Value>;
        };

        template <typename T>
        constexpr bool IsGenericInteger =
            std::is_enum_v<T> || std::is_integral_v<T>;

    }

    template <typename T>
    using ToInteger =
        typename detail::ToInteger<T>::type;

    [[nodiscard]] constexpr auto toInteger(auto value) noexcept
    {
        return static_cast<ToInteger<decltype(value)>>(value);
    }


    /// @brief       Задать размер массива.
    /// @tparam Size размер массива
    template <auto Size>
    struct OfSize
    {
        using type = decltype(Size);
        static_assert(detail::IsGenericInteger<type>);
        static constexpr auto value { Size };
    };

    /// @brief        Задать конкретный индекс.
    /// @tparam Index значение индекса
    template <auto Index>
    struct At
    {
        using type = decltype(Index);
        static_assert(detail::IsGenericInteger<type>);
        static constexpr auto value { toInteger(Index) };
    };

    /// @brief       Задать все индексы, начиная с какого-то и "до конца".
    /// @tparam From начальное значение диапазона
    template <auto From_>
    struct From
    {
        using type = decltype(From_);
        static_assert(detail::IsGenericInteger<type>);
        static constexpr auto value { toInteger(From_) };
    };

    /// @brief       Задать полуинтервал индексов.
    /// @tparam From начальное значение полуинтервала
    /// @tparam To   значение сразу за последним значением диапазона
    template <auto From, auto To>
    struct FromTo
    {
        using FromType = decltype(From);
        using ToType   = decltype(To);
        static_assert(detail::IsGenericInteger<FromType>);
        static_assert(detail::IsGenericInteger<ToType>);

        using type =
            std::common_type_t<ToInteger<FromType>, ToInteger<ToType>>;

        static constexpr auto from { static_cast<type>(From) };
        static constexpr auto to   { static_cast<type>(To)   };
    };

    /// @brief      Задать полуинтервал от нуля до заданного значения.
    /// @tparam To_ значение сразу за последним значением диапазона
    template <auto To_>
    using To =
        FromTo<0, To_>;

    namespace detail
    {

        [[nodiscard]] constexpr auto min(auto a, auto b) noexcept
        {
            auto const av { toInteger(a) };
            auto const bv { toInteger(b) };
            return std::cmp_less(av, bv)? av: bv;
        }

        [[nodiscard]] constexpr auto max(auto a, auto b) noexcept
        {
            auto const av { toInteger(a) };
            auto const bv { toInteger(b) };
            return std::cmp_less(bv, av)? av: bv;
        }

        [[nodiscard]] constexpr auto lowest(auto head, auto... tail) noexcept
        {
            auto const hv { toInteger(head) };
            if constexpr (sizeof...(tail) == 0) {
                return hv;
            }

            return min(head, lowest(tail...));
        }

        [[nodiscard]] constexpr auto highest(auto head, auto... tail) noexcept
        {
            auto const hv { toInteger(head) };
            if constexpr (sizeof...(tail) == 0) {
                return hv;
            }

            return max(head, highest(tail...));
        }

        template <auto Sz>
        [[nodiscard]] constexpr auto lower(OfSize<Sz>) noexcept
        {
            return static_cast<designated_array_init::ToInteger<Sz>>(0);
        }

        template <auto Index>
        [[nodiscard]] constexpr auto lower(At<Index>) noexcept
        {
            return toInteger(Index);
        }

        template <auto Fr>
        [[nodiscard]] constexpr auto lower(From<Fr>) noexcept
        {
            return toInteger(Fr);
        }

        template <auto Fr, auto To>
        [[nodiscard]] constexpr auto lower(FromTo<Fr, To>) noexcept
        {
            return toInteger(Fr);
        }

        template <auto Sz>
        [[nodiscard]] constexpr auto higher(OfSize<Sz>) noexcept
        {
            constexpr auto sz { toInteger(Sz) };
            static_assert(sz != 0);
            return sz - 1;
        }

        template <auto Index>
        [[nodiscard]] constexpr auto higher(At<Index>) noexcept
        {
            return toInteger(Index);
        }

        template <auto Fr>
        [[nodiscard]] constexpr auto higher(From<Fr>) noexcept
        {
            return toInteger(Fr); // minimal placeholder, no actual higher bound
        }

        template <auto Fr, auto To>
        [[nodiscard]] constexpr auto higher(FromTo<Fr, To>) noexcept
        {
            constexpr auto to { toInteger(To) };
            static_assert(std::is_signed_v<decltype(to)> || to > 0);
            return to - 1;
        }

        template <auto Sz>
        [[nodiscard]] constexpr auto sizeOf(OfSize<Sz>) noexcept
        {
            return toInteger(Sz);
        }

        [[nodiscard]] constexpr auto sizeOf(auto) noexcept
        {
            return 0;
        }

    }

    [[nodiscard]] constexpr auto lowOf(auto... args) noexcept
    {
        constexpr auto result { detail::lowest(detail::lower(args)...) };
        static_assert(std::cmp_less_equal(0, result));
        return result;
    }

    [[nodiscard]] constexpr auto highOf(auto... args) noexcept
    {
        constexpr auto result { detail::highest(detail::higher(args)...) };
        static_assert(std::cmp_less_equal(lowOf(args...), result));
        return result;
    }

    [[nodiscard]] constexpr auto sizeOf(auto... args) noexcept
    {
        constexpr auto result { detail::highest(detail::sizeOf(args)...) };
        constexpr auto hi     { highOf(args...) };
        static_assert(result == 0 || std::cmp_less(hi, result));
        return result == 0? hi + 1: result;
    }

    namespace detail
    {

        template <std::size_t Index, auto DefaultValue, typename... Args>
        struct FindValue {};

        template <std::size_t Index, auto DefaultValue>
        struct FindValue<Index, DefaultValue>
        {
            inline constexpr static value = DefaultValue;
        };

        // ...

    }

    template <typename... Args>
    [[nodiscard]] constexpr auto makeArray(Args... args) noexcept
    {
        // ...
    }

}

#endif//KUVSHINOVDR_DESIGNATED_ARRAY_INIT_HPP_INCLUDED
