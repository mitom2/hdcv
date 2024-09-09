/**
 * @file hdcv.hpp
 * @author Miłosz Tomecki
 * @brief This is a single-header library for converting numbers.
 */

#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

/**
 * @brief All library functions are within hdcv namespace.
 */
namespace hdcv
{

    /**
     * @brief Checks if given character is a number.
     *
     * @param c character to check
     * @return true if it is
     * @return false if it is not
     */
    bool isNumber(const char c)
    {
        return c >= '0' && c <= '9';
    }

    /**
     * @brief Checks if given text is a number.
     *
     * @param str text to check
     * @return true if it is
     * @return false if it is not
     */
    bool isNumber(const std::string &str)
    {
        if (!str.length())
            return false;
        for (std::size_t i = (str[0] == '-' ? 1 : 0); i < str.length(); i++)
        {
            if (!isNumber(str[i]))
                return false;
        }
        return true;
    }

    /**
     * @brief Checks if given character is alphabetical.
     *
     * @param c character to check
     * @return true if it is
     * @return false if it is not
     */
    bool isAlphabet(const char c)
    {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
            return true;
        return false;
    }

    /**
     * @brief Converts letter to lowercase.
     * Has no effect if character is already lowercase.
     *
     * @param c character to convert
     * @return char lowercase character
     * @throws std::invalid_argument if character is not a letter
     */
    char toLower(const char c)
    {
        if (c >= 'A' && c <= 'Z')
            return c + ('a' - 'A');
        if (c >= 'a' && c <= 'z')
            return c;
        throw std::invalid_argument("Conversion failed: character is not a letter.");
    }

    /**
     * @brief Converts text to lowercase. Non-alphabet characters are not modified.
     *
     * @param str text to convert
     * @return std::string lowercase text
     */
    std::string toLower(const std::string &str)
    {
        std::string res;
        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (isAlphabet(str[i]))
                res.push_back(toLower(str[i]));
            else
                res.push_back(str[i]);
        }
        return res;
    }

    /**
     * @brief Converts letter to uppercase.
     * Has no effect if character is already lowercase.
     *
     * @param c character to convert
     * @return char uppercase character
     * @throws std::invalid_argument if character is not a letter
     */
    char toUpper(const char c)
    {
        if (c >= 'A' && c <= 'Z')
            return c;
        if (c >= 'a' && c <= 'z')
            return c - ('a' - 'A');
        throw std::invalid_argument("Conversion failed: character is not a letter.");
    }

    /**
     * @brief Converts text to uppercase. Non-alphabet characters are not modified.
     *
     * @param str text to convert
     * @return std::string uppercase text
     */
    std::string toUpper(const std::string &str)
    {
        std::string res;
        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (isAlphabet(str[i]))
                res.push_back(toUpper(str[i]));
            else
                res.push_back(str[i]);
        }
        return res;
    }

    /**
     * @brief Converts std::string containing a number to long.
     *
     * @param num number to convert
     * @param base number base
     * @return long number
     * @throws std::invalid_argument if num is not a valid number
     */
    long fromString(const std::string &num, unsigned short base)
    {
        if (num.length() == 0)
            throw std::invalid_argument("Conversion failed: empty input.");
        long res = 0;
        bool neg;
        for (std::size_t i = 0; i < num.length(); i++)
        {
            if (i == 0)
            {
                if (neg = (num[i] == '-'))
                    continue;
            }
            if (isNumber(num[i]))
            {
                if (num[i] - '0' >= base)
                    throw std::invalid_argument("Conversion failed: number is not base-" + std::to_string(base) + ".");
                res = res * base + num[i] - '0';
            }
            else if (base > 10)
            {
                unsigned short val = toLower(num[i]) - 'a' + 10;
                if (val >= base)
                    throw std::invalid_argument("Conversion failed: number is not base-" + std::to_string(base) + ".");
                res = res * base + val;
            }
            else
            {
                throw std::invalid_argument("Conversion failed: number is not base-" + std::to_string(base) + ".");
            }
        }
        return neg ? -res : res;
    }

    /**
     * @brief Converts long number to std::string representation in given base.
     *
     * @param num number to convert
     * @param base number base
     * @return std::string with number
     * @throws std::invalid_argument if base<2 or base>36
     */
    std::string toString(long num, unsigned short base)
    {
        if (base < 2)
            throw std::invalid_argument("Conversion failed: base can not be lower than 2.");
        if (base > 36)
            throw std::invalid_argument("Conversion failed: base can not be higher than 36.");
        std::string res;
        bool neg = num < 0;
        num = neg ? -num : num;
        do
        {
            unsigned short rem = num % base;
            num /= base;
            if (rem < 10)
                res.insert(0, 1, '0' + rem);
            else
                res.insert(0, 1, 'a' + rem - 10);
        } while (num > 0);
        return neg ? "-" + res : res;
    }

    /**
     * @brief Uses std::cout to display usage information to the user.
     *
     */
    void displayHelp()
    {
        std::cout << "hdcv [number] [number base] [target base] [OPTION]...\nConverts number between bases.\n\n\tOptions:\n\t-h\tdisplay help\n\t-u\tforce uppercase for results with base>10\n\nExit status:\n 0 if OK,\n non-zero otherwise.";
    }

    /**
     * @brief This functions performs conversion based on arguments stored in argv, or displays help.
     * Uses std::cout to output results.
     *
     * @param argc number of arguments
     * @param argv arguments
     * @return 0 if no errors were encountered, non-zero otherwise
     */
    int converter(int argc, char **argv)
    {
        try
        {
            bool forceUppercase = false;
            for (int i = 0; i < argc; i++)
            {
                if (static_cast<std::string>(argv[i]) == "-u")
                {
                    forceUppercase = true;
                }
                else if (static_cast<std::string>(argv[i]) == "-h")
                {
                    displayHelp();
                    return 0;
                }
                else if (i > 3)
                {
                    std::cout << "Unknown argument: " << argv[i] << ". See hdcv -h for usage.";
                    return 2;
                }
            }
            if (argc < 4)
            {
                std::cout << "Too few arguments. See hdcv -h for help.";
                return 1;
            }
            if (!isNumber(argv[2]) || !isNumber(argv[3]))
                return 3;
            auto res = toString(fromString(argv[1], std::stoi(argv[2])), std::stoi(argv[3]));
            std::cout << (forceUppercase ? toUpper(res) : res);
        }
        catch (std::invalid_argument &e)
        {
            std::cout << e.what();
            return 4;
        }
        catch (std::exception &e)
        {
            std::cout << e.what();
            return 5;
        }
        catch (...)
        {
            return 6;
        }
        return 0;
    }

}