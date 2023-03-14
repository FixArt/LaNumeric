#ifndef LANUMERIC_USED_DYNAMIC
#pragma once 

//#include <cstdint>
#include <string>
#include <vector>
// #include <utility>
// #include <type_traits>
// #include <errno.h>

#include "numeric.hpp"

/**
 * @brief Namespace of LaNumeric.
 * 
 */
namespace LANUM
{
    template<> struct auint_t<0>
    {
        private:

        bool postBound(const size_t& index) const
        {
            if(index >= itself.size()) return false;
            return itself[index];
        }

        void equalize(auint_t& given)
        {
            if(this == &given) return;
            if(given.itself.size() > itself.size())
            {
                size_t previous = given.itself.size();
                itself.resize(given.itself.size());
                for(size_t i = previous; i < itself.size(); ++i)
                {
                    itself[i] = false;
                }
            }
            else
            {
                size_t previous = itself.size();
                given.itself.resize(itself.size());
                for(size_t i = previous; i < given.itself.size(); ++i)
                {
                    given.itself[i] = false;
                }
            }
        }

        size_t countSet() const
        {
            size_t returned = 0;
            for(const auto& checked : itself)
            {
                if(checked) ++returned;
            }
            return returned;
        }

        static size_t countSet(const std::vector<bool>& tested)
        {
            size_t returned = 0;
            for(const auto& checked : tested)
            {
                if(checked) ++returned;
            }
            return returned;
        }

        std::vector<bool> itself;

        static constexpr inline size_t biggestFrom(const size_t& first, const size_t& second)
        {
            return (first > second)?(first):(second);
        }

        static constexpr inline size_t smallestFrom(const size_t& first, const size_t& second)
        {
            return (first < second)?(first):(second);
        }

        unsigned long convert() const
        {
            if(itself.size() == 0) return 0;
            std::bitset<sizeof(unsigned long)*8> returned;
            returned.reset();
            for(size_t i = 0; i < sizeof(unsigned long)*8 && i < itself.size(); ++i)
            {
                returned[i] = itself[i];
            }
            return returned.to_ulong();
        }

        unsigned long long convertll() const
        {
            if(itself.size() == 0) return 0;
            std::bitset<sizeof(unsigned long long)*8> returned;
            returned.reset();
            for(size_t i = 0; i < sizeof(unsigned long long)*8 && i < itself.size(); ++i)
            {
                returned[i] = itself[i];
            }
            return returned.to_ulong();
        }

        static size_t highestSet(const std::vector<bool>& checked) noexcept
        {
            size_t i = 0;
            for(i = checked.size(); i > 0; --i)
            {
                if(checked[i - 1]) return i - 1;
            }
            return i;
        }

        static std::vector<bool> deconvert(const unsigned long long& given)
        {
            if(given == 0) return {};
            std::bitset<sizeof(unsigned long long)*8> checked{given};
            std::vector<bool> returned; returned.resize(sizeof(unsigned long long)*8);
            for(size_t i = 0; i < sizeof(unsigned long long)*8; ++i)
            {
                returned[i] = checked[i];
            }
            size_t i = 0;
            returned.resize(highestSet(returned) + 1);
            return returned;
        }

        void invert() noexcept
        {
            for(std::size_t i = 0; i < itself.size()/2; ++i)
            {
                bool temp = itself[i];
                itself[i] = itself[itself.size() - i - 1];
                itself[itself.size() - i - 1] = temp;
            }
        }

        size_t highestSet() const noexcept
        {
            size_t i = 0;
            for(i = itself.size(); i > 0; --i)
            {
                if(itself[i - 1]) return i - 1;
            }
            return i;
        }

        constexpr inline static char digitToCharacter(const unsigned short& digit) noexcept
        {
            return '0' + digit;
        }

        constexpr inline static unsigned short characterToDigit(const char& character) noexcept
        {
            return (short)(character - '0');
        }

        public:
        auint_t() = default;

        size_t digits() const noexcept
        {
            if(*this == 0 || itself.size() < 4) return 1;
            size_t count = 0;
            auint_t<0> checkedNumber = *this;
            while(checkedNumber != 0)
            {
                checkedNumber /= 10;
                ++count;
                // for(const auto& outputted : (std::vector<bool>)checkedNumber)
                // {
                //     std::cout << outputted;
                // }
                // std::cout << '\n';
            }
            return count;
        }

        /**
         * @brief Get digit as if number was read from right to left.
         * 
         * @param index Placement of digit.
         * @return unsigned short Digit itself. 
         */
        unsigned short digitrl(const size_t& index) const noexcept
        {
            if(itself.size() < 4)
            {
                const unsigned short tested = convert();
                switch(tested)
                {
                    default: return 0;
                    case 1: return 1;
                    case 2: return 2;
                    case 3: return 3;
                    case 4: return 4;
                    case 5: return 5;
                    case 6: return 6;
                    case 7: return 7;
                }
            }
            auint_t<0> newNumber = *this;
            for(size_t i = 0; i < (index + 1); ++i)
            {
                newNumber /= 10;
            }
            newNumber %= 10;
            return newNumber.convert();
        }

        /**
         * @brief Get digit as if number was read from left to right.
         * 
         * @param index Placement of digit.
         * @return unsigned short Digit itself. 
         */
        inline unsigned short digitlr(const size_t& index) const noexcept
        {
            return digitrl(digits() - 1 - index);
        }

        // std::vector<bool> max() const
        // {
        //     std::vector<bool> returned;
        //     returned.set(true);
        //     return returned;
        // }

        // std::vector<bool> min() const
        // {
        //     std::vector<bool> returned;
        //     returned.set(false);
        //     return returned;
        // }

        // template<typename = typename std::enable_if<(itself.size() <= (sizeof(unsigned long long) * 8))>>
        // constexpr inline operator unsigned long long() const
        // {
        //     return itself.to_ullong();
        // }

        inline auint_t(const unsigned long long& copied) noexcept : itself{deconvert(copied)}
        {
            //invert();
            //itself <<= (itself.size() - (sizeof(unsigned long long) * 8));
        }

        auint_t& operator=(const unsigned long long& copied) noexcept
        {
            itself = {deconvert(copied)};
            //invert();
            //itself <<= (size - (sizeof(unsigned long long) * 8));
            return *this;
        }

        auint_t(const std::vector<bool>& copied) noexcept : itself{copied} {}

        template<size_t bits>
        constexpr auint_t(const auint_t<bits>& copied) noexcept
        {
            // itself.reset();
            // for(size_t i = 0; i < ((size > bits)?(bits):(size)); ++i)
            // {
            //     itself[i] = ((std::bitset<bits>)copied)[i];
            // }
            itself.resize(bits);
            for(size_t i = 0; i < itself.size(); ++i)
            {
                if(i < bits) itself[i] = ((std::bitset<bits>)copied)[i];
            }
        }

        template<size_t bits>
        constexpr auint_t& operator=(const auint_t<bits>& copied) noexcept
        {
            // itself.reset();
            // for(size_t i = 0; i < ((size > bits)?(bits):(size)); ++i)
            // {
            //     itself[i] = ((std::bitset<bits>)copied)[i];
            // }
            itself.resize(bits);
            for(size_t i = 0; i < itself.size(); ++i)
            {
                if(i < bits) itself[i] = ((std::bitset<bits>)copied)[i];
            }
            return *this;
        }

        auint_t(const auint_t&) = default;

        auint_t(auint_t&&) = default;

        auint_t& operator=(const auint_t&) = default;

        auint_t& operator=(auint_t&&) = default;

        bool operator==(const auint_t& compared) const noexcept
        {
            for(size_t i = 0; i < biggestFrom(itself.size(), compared.itself.size()); ++i)
            {
                if(postBound(i) != compared.postBound(i)) return false;
            }
            return true;
        }

        inline bool operator!=(const auint_t& compared) const noexcept
        {
            for(size_t i = 0; i < biggestFrom(itself.size(), compared.itself.size()); ++i)
            {
                if(postBound(i) != compared.postBound(i)) return true;
            }
            return false;
        }

        bool operator>(const auint_t& compared) const noexcept
        {
            //for(size_t i = 0; i < size; ++i)
            for(size_t i = biggestFrom(itself.size(), compared.itself.size()); i > 0; --i)
            {
                if(postBound(i - 1) and (!compared.postBound(i - 1)))
                {
                    return true;
                }
                if((!postBound(i - 1)) and compared.postBound(i - 1))
                {
                    return false;
                }
            }
            return false;
        }

        bool operator<(const auint_t& compared) const noexcept
        {
            // for(size_t i = 0; i < size; ++i)
            for(size_t i = biggestFrom(itself.size(), compared.itself.size()); i > 0; --i)
            {
                if((!postBound(i - 1)) and compared.postBound(i - 1))
                {
                    return true;
                }
                if(postBound(i - 1) and (!compared.postBound(i - 1)))
                {
                    return false;
                }
            }
            return false;
        }

        bool operator>=(const auint_t& compared) const noexcept
        {
            // for(size_t i = 0; i < size; ++i)
            for(size_t i = biggestFrom(itself.size(), compared.itself.size()); i > 0; --i)
            {
                if(postBound(i - 1) and (!compared.postBound(i - 1)))
                {
                    return true;
                }
                if((!postBound(i - 1)) and compared.postBound(i - 1))
                {
                    return false;
                }
            }
            return true;
        }

        bool operator<=(const auint_t& compared) const noexcept
        {
            // for(size_t i = 0; i < size; ++i)
            for(size_t i = biggestFrom(itself.size(), compared.itself.size()); i > 0; --i)
            {
                if((!postBound(i - 1)) and compared.postBound(i - 1))
                {
                    return true;
                }
                if(postBound(i - 1) and (!compared.postBound(i - 1)))
                {
                    return false;
                }
            }
            return true;
        }

        inline bool operator>(const intmax_t& compared) const noexcept
        {
            return (compared < 0)?(true):(*this > ((auint_t)compared));
        }

        inline bool operator<(const intmax_t& compared) const noexcept
        {
            return (compared < 0)?(false):(*this < ((auint_t)compared));
        }

        inline bool operator>=(const intmax_t& compared) const noexcept
        {
            return (compared < 0)?(true):(*this >= ((auint_t)compared));
        }

        inline bool operator<=(const intmax_t& compared) const noexcept
        {
            return (compared < 0)?(false):(*this <= ((auint_t)compared));
        }

        inline auint_t operator+() const noexcept
        {
            return {itself};
        }

        auint_t operator&=(const auint_t& processed) noexcept
        {
            itself.resize(biggestFrom(itself.size(), processed.itself.size()));
            for(size_t i = 0; i < biggestFrom(itself.size(), processed.itself.size()); ++i)
            {
                if(i >= processed.itself.size() || i >= itself.size())
                {
                    for(;i < itself.size(); ++i)
                    {
                        itself[i] = false;
                    }
                    break;
                }
                itself[i] = itself[i] & processed.itself[i];
            }
            return *this;
        }

        auint_t operator|=(const auint_t& processed) noexcept
        {
            itself.resize(biggestFrom(itself.size(), processed.itself.size()));
            for(size_t i = 0; i < biggestFrom(itself.size(), processed.itself.size()); ++i)
            {
                if(i >= processed.itself.size() || i >= itself.size())
                {
                    for(;i < itself.size(); ++i)
                    {
                        itself[i] = false;
                    }
                    break;
                }
                itself[i] = itself[i] | processed.itself[i];
            }
            return *this;
        }

        auint_t operator^=(const auint_t& processed) noexcept
        {
            itself.resize(biggestFrom(itself.size(), processed.itself.size()));
            for(size_t i = 0; i < biggestFrom(itself.size(), processed.itself.size()); ++i)
            {
                if(i >= processed.itself.size() || i >= itself.size())
                {
                    for(;i < itself.size(); ++i)
                    {
                        itself[i] = true;
                    }
                    break;
                }
                itself[i] = itself[i] ^ processed.itself[i];
            }
            return *this;
        }

        inline auint_t operator&(const auint_t& processed) const noexcept
        {
            auint_t returned{itself};
            returned &= processed;
            return returned;
        }

        inline auint_t operator|(const auint_t& processed) const noexcept
        {
            auint_t returned{itself};
            returned |= processed;
            return returned;
        }

        inline auint_t operator^(const auint_t& processed) const noexcept
        {
            auint_t returned{itself};
            returned ^= processed;
            return returned;
        }

        inline auint_t operator~() const noexcept
        {
            auint_t returned;
            returned.itself.resize(itself.size());
            for(size_t i = 0; i < itself.size(); ++i)
            {
                returned.itself[i] = !itself[i];
            }
            return returned;
        }

        auint_t& operator+=(auint_t processed) noexcept
        {
            equalize(processed);
            itself.resize(itself.size() + 1);
            size_t more = 0;
            // for(size_t i = size - 1; i > 0; --i)
            // bool carry = false;
            for(size_t i = 0; i < itself.size(); ++i)
            {
                if(more > 0)
                {
                    if(!itself[i]) --more;
                    itself[i] = !itself[i];
                }
                if(itself[i] && processed.postBound(i)) ++more;
                itself[i] = itself[i] ^ processed.postBound(i);
                // itself[i] = (bool)((itself[i] ^ processed.itself[i]) ^ carry);
                // carry = (((bool)itself[i] && processed.itself[i]) || ((bool)itself[i] && carry) || ((bool)processed.itself[i] && carry));
            }
            itself.resize(highestSet() + 1);
            return *this;
        }

        auint_t& operator-=(auint_t processed) noexcept
        {
            equalize(processed);
            size_t more = 0;
            //for(size_t i = size - 1; i > 0; --i)
            for(size_t i = 0; i < itself.size(); ++i)
            {
                if(more > 0)
                {
                    if(itself[i]) --more;
                    itself[i] = !itself[i];
                }
                if((!itself[i]) && processed.postBound(i)) ++more;
                itself[i] = itself[i] ^ processed.postBound(i);
            }
            itself.resize(highestSet() + 1);
            return *this;
        }

        auint_t& operator*=(auint_t processed) noexcept
        {
            if(processed == 10)
            {
                *this = (*this << 3) + (*this << 1);
                return *this;
            }
            auint_t temporary = itself;
            // itself.reset();
            itself.resize(processed.itself.size());
            for(auto given : itself)
            {
                given = false;
            }
            if(temporary.countSet() < processed.countSet())
            {
                for(size_t i = 0; i < temporary.itself.size(); ++i)
                {
                    if(temporary.itself[i])
                    {
                        *this += (processed << i);
                    }
                }
            }
            else
            {
                for(size_t i = 0; i < processed.itself.size(); ++i)
                {
                    if(processed.itself[i])
                    {
                        *this += (temporary << i);
                    }
                }
            }
            itself.resize(highestSet() + 1);
            return *this;
        }

        inline auint_t distance(auint_t number) const noexcept
        {
            // if(*this > number)
            // {
            //     return *this - number;
            // }
            // else
            // {
            //     return number - *this;
            // }
            return (*this > number)?(*this - number):(number - *this);
        }

        // auint_t& operator/=(const auint_t& processed)
        // {
        //     if(processed == 0)
        //     {
        //         throw(EINVAL);
        //     }
        //     auint_t quotient = 0;
        //     auint_t temporaryProcessed = processed;

        //     while(true)
        //     {
        //         auint_t temporaryQuotient = 1;
        //         if (temporaryProcessed == *this)
        //         {
        //             quotient += 1;
        //             break;
        //         }
        //         else if (*this < temporaryProcessed)
        //         {
        //             break;
        //         }
        //         while ((temporaryProcessed << 1) <= *this)
        //         {
        //             temporaryProcessed <<= 1;
        //             temporaryQuotient <<= 1;
        //         }

        //         *this -= temporaryProcessed;
        //         temporaryProcessed = processed;
        //         quotient += temporaryQuotient;
        //     }

        //     itself = quotient.itself;
            
        //     return *this;
        // }

        auint_t& operator/=(const auint_t& processed) noexcept
        {
            if(processed == 0)
            {
                // throw(std::overflow_error("Division by zero."));
                return *this = 0;
            }
            auint_t<0> quotient = 0;
            auint_t<0> temporaryProcessed = processed;

            while(true)
            {
                auint_t<0> temporaryQuotient = 1;
                if(temporaryProcessed == *this)
                {
                    ++quotient;
                    break;
                }
                else if(*this < temporaryProcessed)
                {
                    break;
                }
                while((temporaryProcessed << 1) <= *this)
                {
                    temporaryProcessed <<= 1;
                    temporaryQuotient <<= 1;
                }

                *this -= temporaryProcessed;
                temporaryProcessed = processed;
                quotient += temporaryQuotient;
            }

            itself = quotient.itself;
            // itself = (std::vector<bool>)((auint_t<size>)quotient);
            itself.resize(highestSet() + 1);
            
            return *this;
        }

        auint_t& divideWithRemainder(const auint_t& processed, auint_t& remainder) noexcept
        {
            if(processed == 0)
            {
                // throw(std::overflow_error("Division by zero."));
                remainder = 0;
                return *this = 0;
            }
            auint_t quotient = 0;
            auint_t<0> temporaryProcessed = processed;

            while(true)
            {
                auint_t temporaryQuotient = 1;
                if (temporaryProcessed == *this)
                {
                    remainder = 0;
                    quotient += 1;
                    break;
                }
                else if (*this < temporaryProcessed)
                {
                    remainder = *this;
                    break;
                }
                while ((temporaryProcessed << 1) <= *this)
                {
                    temporaryProcessed <<= 1;
                    temporaryQuotient <<= 1;
                }

                *this -= temporaryProcessed;
                temporaryProcessed = processed;
                quotient += temporaryQuotient;
            }

            itself = quotient.itself;
            // itself = (std::vector<bool>)((auint_t<size>)quotient);
            
            return *this;
        }

        auint_t& operator%=(auint_t processed) noexcept
        {
            // equalize(processed);
            // auint_t<size> remainder;
            // for(remainder = itself; remainder >= processed; remainder -= processed) {}
            // itself = remainder.itself;
            const size_t first = highestSet();
            const size_t second = processed.highestSet();
            // if(second > first) return *this;
            // if(second == first && (*this < processed)) return *this;
            // if(first > second) return *this = 0;

            const size_t shift = (second > first)?(second - first):(first - second);
            processed <<= shift;

            for(size_t i = 0; i <= shift; ++i)
            {
                if(*this == processed)
                {
                    itself.resize(0);
                    return *this;
                }
                if(*this > processed)
                {
                    *this -= processed;
                }
                processed >>= 1;
            }

            return *this;
        }

        inline auint_t<0> mod(const auint_t<0>& number) const noexcept
        {
            return *this % number;
        }

        inline auint_t<0> mod2() const noexcept
        {
            return (itself[0])?(1):(0);
        }

        inline auint_t<0> mod10() const noexcept
        {
            return *this % 10;
        }

        auint_t<0> log(const auint_t<0>& previous) const noexcept
        {
            // if(*this == 1)
            // {
            //     return (previous == 1)?(1):(0);
            // }
            // if(previous > *this)
            // {
            //     throw(EINVAL);
            // }
            // // auint_t<size> returned = 1;
            // auint_t<size> returned = 1;
            // bool beforeLast = (previous.pow(returned) > *this)?(true):(false);
            // bool lastOperation = beforeLast;
            // while(previous.pow(returned) != *this)
            // {
            //     if(previous.pow(returned) > *this)
            //     {
            //         --returned;
            //         if(lastOperation && !beforeLast) break;
            //         beforeLast = lastOperation;
            //         lastOperation = false;
            //     }
            //     else
            //     {
            //         ++returned;
            //         if(!lastOperation && beforeLast) break;
            //         beforeLast = lastOperation;
            //         lastOperation = true;
            //     }
            // }
            // return returned;
            if(*this == 1)
            {
                return (previous == 1)?(1):(0);
            }
            if(previous > *this)
            {
                return 0;
            }
            auint_t high, low;
            low = 1;
            high = *this >> 1;
            // high = sqrt(); // May be too slow.
            auint_t guess = (low + high) >> 1;
            while(previous.pow(guess) != *this)
            {
                if(previous.pow(guess) > *this)
                {
                    if(high == guess) break;
                    high = guess;
                }
                else
                {
                    if(low == guess) break;
                    low = guess;
                }
                guess = (low + high) >> 1;
            }
            return guess;
        }

        inline auint_t log2() const noexcept
        {
            return log(2);
        }

        inline auint_t log10() const noexcept
        {
            return log(10);
        }

        inline auint_t operator+(const auint_t& processed) const noexcept
        {
            auint_t<0> returned = *this;
            returned += processed;
            return returned;
        }

        inline auint_t operator-(const auint_t& processed) const noexcept
        {
            auint_t<0> returned = *this;
            returned -= processed;
            return returned;
        }

        inline auint_t operator*(const auint_t& processed) const noexcept
        {
            auint_t<0> returned = *this;
            returned *= processed;
            return returned;
        }

        inline auint_t operator/(const auint_t& processed) const noexcept
        {
            auint_t<0> returned = *this;
            returned /= processed;
            return returned;
        }

        auint_t pow(const auint_t& power) const noexcept
        {
            if(power == 0) return 1;
            auint_t<0> additional = *this;
            auint_t<0> resolution = 1;
            auint_t copiedPower = power;
            while(copiedPower > 0)
            {
                // if((copiedPower & 1) == 1)
                // if((copiedPower % 2) != 0)
                if(copiedPower.isOdd())
                {
                    resolution *= additional;
                }
                additional *= additional;
                copiedPower >>= 1;
                // copiedPower /= 2;
            }
            return resolution;
        }

        auint_t sqrt() const noexcept
        {
            auint_t<0> temporary, returned, preturned;
            preturned.itself.resize(1); preturned.itself[0] = (returned.itself[0])?(false):(true);
            returned = *this >> 1;
            temporary = 0;
            while(returned != temporary && preturned != returned)
            {
                temporary = returned;
                // auint_t calculation = (*this / temporary + temporary) >> 1;
                // if(calculation == temporary) break;
                // returned = calculation;
                // if(returned == (*this / temporary + temporary) / 2) break;
                if(returned.itself[0]) preturned = returned;
                returned = (*this / temporary + temporary) >> 1;
            }
            return returned;
        }

        auint_t root(auint_t<0> power) const noexcept
        {
            if(power == 2) return sqrt();
            // auint_t<size> low, high, plow, phigh;
            auint_t<0> low, high;
            low = (*this == 0)?(0):(1);
            high = (*this == 0)?(1):(*this);

            // // Any fast operation, which will make them differ. (initialization of all values is unneeded)
            // plow.itself.set(0, (low.itself[0])?(false):(true));
            // phigh.itself.set(0, (high.itself[0])?(false):(true));

            auint_t<0> guess = (low + high) >> 1;
            // while((guess.pow(power) - *this) > 0 and (high != phigh && low != plow))
            while((guess.pow(power) - *this) > 0)
            {
                if(guess.pow(power) > *this)
                {
                    // phigh = high;
                    if(high == guess) break;
                    high = guess;
                }
                else
                {
                    // plow = low;
                    if(low == guess) break;
                    low = guess;
                }
                guess = (low + high) >> 1;
            }

            return guess;
        }

        // /**
        //  * @brief Very broken exponent function.
        //  * 
        //  * @return constexpr auint_t Returned value.
        //  */
        // constexpr inline auint_t exp()
        // {
        //     auint_t<(size > 15)?(size):(16)> e = 27183;
        //     return (auint_t<size>)(e.pow((auint_t<(size > 15)?(size):(16)>)*this) / (((auint_t<(size > 15)?(size):(16)>)10000).pow((auint_t<(size > 15)?(size):(16)>)*this)));
        // }

        auint_t factorial() const noexcept
        {
            auint_t returned = 1;
            for(auint_t i = 2; i <= *this; ++i)
            {
                returned *= i;
            }
            return returned;
        }

        inline auint_t operator%(const auint_t& processed) const noexcept
        {
            auint_t<0> returned = *this;
            returned %= processed;
            return returned;
        }

        inline auint_t& operator++() noexcept
        {
            return *this += 1;
        }

        inline auint_t& operator--() noexcept
        {
            return *this -= 1;
        }

        inline auint_t operator++(int) noexcept
        {
            *this += 1;
            return *this + 1;
        }

        inline auint_t operator--(int) noexcept
        {
            *this -= 1;
            return *this - 1;
        }

        inline auint_t& operator>>=(size_t number) noexcept
        {
            if(number == 0) return *this;
            if(number >= itself.size())
            {
                itself.resize(0);
                return *this;
            }
            // itself >>= number;
            itself.resize(highestSet() + 1);
            for(size_t i = 0; i < itself.size(); ++i)
            {
                itself[i] = postBound(i + number);
            }
            itself.resize(itself.size() - number);
            return *this;
        }

        inline auint_t& operator<<=(size_t number) noexcept
        {
            // if(number == itself.size()) return *this;
            // itself <<= number;
            if(number == 0) return *this;
            size_t previous = itself.size();
            itself.resize(itself.size() + number);
            for(size_t i = previous + 1; i > 0; --i)
            {
                itself[i + number - 1] = itself[i - 1];
                itself[i - 1] = false;
            }
            return *this;
        }

        inline auint_t operator>>(size_t number) const noexcept
        {
            auint_t<0> returned = *this;
            returned >>= number;
            return returned;
        }

        inline auint_t operator<<(size_t number) const noexcept
        {
            auint_t<0> returned = *this;
            returned <<= number;
            return returned;
        }

        // operator std::vector<bool>() const
        // {
        //     return itself;
        // }

        inline explicit operator const std::vector<bool>&() const noexcept
        {
            return itself;
        }

        // template<size_t bits>
        // explicit operator std::bitset<bits>() const
        // {
        //     return itself;
        // }

        // explicit auint_t(const char* const copied)
        // {
        //     *this = 0;
        //     for(size_t i = 0; i < strlen(copied); ++i)
        //     {
        //         *this += (auint_t<size>{10}).pow(strlen(copied) - i - 1) * auint_t<size>{characterToDigit(copied[i])};
        //     }
        // }

        auint_t(const std::string& copied) noexcept
        {
            *this = 0;
            for(size_t i = 0; i < copied.size(); ++i)
            {
                *this += (auint_t<0>{10}).pow(copied.size() - i - 1) * auint_t<0>{characterToDigit(copied[i])};
            }
            // *this /= 2;
        }

        auint_t& operator=(const std::string& copied) noexcept
        {
            *this = 0;
            for(size_t i = 0; i < copied.size(); ++i)
            {
                *this += (auint_t<0>{10}).pow(copied.size() - i - 1) * auint_t<0>{characterToDigit(copied[i])};
            }
            // *this /= 2;
            return *this;
        }

        operator std::string() const noexcept
        {
            // if(*this == 0)
            // {
            //     return "0";
            // }
            // if(size < 4)
            // {
            //     return {digitToCharacter(digitrl(0))};
            // }
            // std::string returned; returned.resize(digits());
            // auint_t<size> worked = itself;
            // for(size_t i = 0; worked != 0; ++i)
            // {
            //     returned[i] = digitToCharacter(((worked % 10).itself.to_ulong()));
            //     worked /= 10;
            // }
            // return {returned.rbegin(), returned.rend()};
            if(*this == 0)
            {
                return "0";
            }
            if(itself.size() < 4)
            {
                return {digitToCharacter(digitrl(0))};
            }
            // else if(itself.size() < 64)
            // {
            //     std::string returned; returned.resize(digits());
            //     auint_t<0> worked = itself;
            //     for(size_t i = 0; worked != 0; ++i)
            //     {
            //         returned[i] = digitToCharacter(((worked % 10).convert()));
            //         worked /= 10;
            //     }
            //     return {returned.rbegin(), returned.rend()};
            // }
            else
            {
                std::string returned; // returned.resize(numberSize);
                auint_t<0> worked = itself;
                for(size_t i = 0; worked != 0; i += 19)
                {
                    // returned.insert(0, std::to_string((worked % 10000000000000000000ULL).itself.to_ullong()));
                    // worked /= 10000000000000000000ULL;
                    auint_t<0> numbers;
                    worked.divideWithRemainder(10000000000000000000ULL, numbers);
                    returned.insert(0, std::to_string(numbers.convertll()));
                }
                return returned;
            }
            }

        explicit inline operator bool() const noexcept
        {
            for(const auto& checked : itself)
            {
                if(checked != false) return true;
            }
            return false;
            // return !(itself.none());
        }

        ~auint_t() = default;

        inline bool isEven() const noexcept
        {
            if(itself.size() == 0) return true;
            return !itself[0];
        }

        inline bool isOdd() const noexcept
        {
            if(itself.size() == 0) return false;
            return itself[0];
        }

        bool isPrime() const noexcept
        {
            if(*this == 2) return true;
            if(*this < 2)
            {
                return false;
            }
            if(isEven()) return false;
            for(auint_t<0> i = 2; i <= sqrt(); ++i)
            {
                if(*this % i == 0)
                {
                    return false;
                }
            }
            return true;
        }

        bool isPowerOf2() const noexcept
        {
            bool found = false;
            for(const bool& checked : itself)
            {
                if(checked)
                {
                    if(found)
                    {
                        return false;
                    }
                    found = true;
                }
            }
            return found;
        }
    };

    typedef auint_t<0> auint0_t;
};
#define LANUMERIC_USED_DYNAMIC 1
#endif
