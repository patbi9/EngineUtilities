/**
 * @file EngineMath.h
 * @brief General math function bunch to use in game engines.
 *
 * Has common functions manually implemented, including arithmetic, trigonometric, geometric, and conversion operations.
 * And other utilities such as interpolation, round methods, and factorial.
 * All functions are contained inside EngineMath namespace.
 */

#pragma once
namespace EngineMath {
    /** pi */
    float pi = 3.14159265358979323846f;
    /** Euler */
    float e = 2.71828182845904523536f;
    /**
     * @brief Calculates square root using Newton Rhapson.
     * @param number Value to applu operation to.
     * @return number's approximate square root.
     */
    inline float
        sqrt(float number) {
        if (number <= 0) {
            return 0;
        }
        float xi = number / 2;
        for (int i = 0; i < 10; i++) {
            xi = xi - (square(xi) - number) / (2 * xi);
        }
        return xi;
    }
    /** Returns number squared*/
    inline float
        square(float number) {
        return number * number;
    }
    /** Returns number cubed */
    inline float
        cube(float number) {
        return number * number * number;
    }
    /**
     * @brief Positive power.
     * @param base Power base.
     * @param exponent Positive exponent.
     * @return Base result to the power of exponent.
     */
    inline float
        power(float base, float exponent) {
        float result = 1.0f;
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    }
    /** int absolute */
    inline int
        abs(int number) {
        if (number < 0) {
            return -1 * number;
        }
        else {
            return number;
        }
    }
    /** Max value between two floats */
    inline float
        eMax(float a, float b) {
        if (a > b) {
            return a;
        }
        else {
            return b;
        }
    }
    /** Min value between two floats */
    inline float
        eMin(float a, float b) {
        if (a < b) {
            return a;
        }
        else {
            return b;
        }
    }
    /** Rounds a float to nearest int */
    inline int
        round(float number) {
        int intPart = static_cast<int>(number);
        float fPart = number - intPart;
        if (fPart >= 0.5f) {
            return intPart + 1;
        }
        else {
            return intPart;
        }
    }
    /** Round float to nearest inferior int (floor) */
    inline int
        floor(float number) {
        return static_cast<int>(number);
    }
    /** Round float to nearest superior int (ceil) */
    inline int
        ceil(float number) {
        return static_cast<int>(number) + 1;
    }
    /** Float absoulte */
    inline float
        fabs(float number) {
        if (number < 0.0f) {
            return number * -1;
        }
        else {
            return number;
        }
    }
    /** Rest of division between two floats */
    inline float
        mod(float a, float b) {
        if (b == 0) {
            return 0;
        }
        return (a / b) - (static_cast<int>(a / b));
    }
    /** Calculates e^x using power function */
    inline float
        exp(float exponent) {
        return power(e, exponent);
    }
    /** Angle's sin in radians using Taylor's series */
    inline float
        sin(float angle) {
        int n = 0;
        float result = 0;
        float currentTerm = angle;
        while (fabs(currentTerm) >= 0.0000001 || n == 0) {
            result += currentTerm;
            n++;
            currentTerm *= (-1.0 * angle * angle) / ((2.0 * n) * (2.0 * n + 1.0));
        }
        return result;
    }
    /**
     * @brief Computes the cosine of the given angle in radians using Taylor series approximation.
     * @param radians Angle in radians.
     * @return Approximated cosine of the angle.
     */
    inline float cos(float radians) {
        // Normalize the angle to [-π, π] for better precision
        while (radians > 3.14159265f) radians -= 6.28318530f;
        while (radians < -3.14159265f) radians += 6.28318530f;
        float result = 1.0f;
        float term = 1.0f;
        float x2 = radians * radians;
        int sign = -1;
        // Use 6 terms of the Taylor series: enough for good approximation
        for (int i = 2; i <= 10; i += 2) {
            term *= x2 / (i * (i - 1));
            result += sign * term;
            sign *= -1;
        }
        return result;
    }
    /** Converts degree to radians */
    inline float
        radians(float degrees) {
        return (degrees * pi) / 180.0f;
    }
    /** Converts radians to degree */
    inline float
        degrees(float radian) {
        return (radian * 180) / pi;
    }
    /** Calculates circle area */
    inline float
        circleArea(float radius) {
        return pi * radius * radius;
    }
    /** Calculates circle circunference */
    inline float
        circleCircumference(float radius) {
        return 2.0f * pi * radius;
    }
    /** Calculates rectangle area */
    inline float
        rectArea(float width, float height) {
        return width * height;
    }
    /** Calculates circle perimeter */
    inline float
        rectPerimeter(float width, float height) {
        return 2.0f * (width + height);
    }
    /** Calculates triangle area */
    inline float
        triArea(float base, float height) {
        return 0.5f * base * height;
    }
    /** Calculates triangle perimeter */
    inline float
        triPerimeter(float side1, float side2, float side3) {
        return side1 + side2 + side3;
    }
    /** Calculates equilateral triangle perimeter */
    inline float
        triPerimeter(float side) {
        return 3 * side;
    }
    /**
     * @brief Distance between two 2D points.
     * @param x1 X Coordinate first point.
     * @param x1 Y Coordinate first point.
     * @param x1 X Coordinate second point.
     * @param x1 Y Coordinate second point.
     * @return Distance between both points.
     */
    inline float
        distance(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return sqrt(dx * dx + dy * dy);
    }
    /**
         * @brief Linear Interpolation
         * @param start Initial Value.
         * @param end Final Value.
         * @param t Interpolant value (0-1).
         * @return Interpolated value.
         */
    inline float
        lerp(float start, float end, float t) {
        return start + (end - start) * t;
    }
    /** Positive integer factorial */
    inline long
        factorial(int number) {
        int result = 1;
        for (int i = number; i > 0; i--) {
            result *= i;
        }
        return result;
    }
}