/**
 * CS 2110 Spring 2024 HW1
 * Part 3 - Coding with bitwise operators
 *
 * @author Yulin Lu
 *
 * Global rules for this file:
 * - All of these functions must be completed in ONE line. That means they
 *   should be of the form "return [...];". No partial credit will be awarded
 *   for any method that isn't completed in one line.
 *
 * - You may not use conditionals.
 * - You may not declare any variables.
 * - You may not use casting.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any method from this or
 *   another file to implement any method. Recursive solutions are not
 *   permitted.
 * - You may not use addition or subtraction. However, you may use the
 *   unary negation operator (-) to negate a number (except in changeSign).
 * - You may not use multiplication, division or modulus.
 *
 * - Basically, the global rules are you can only use logical (&&, ||) and
 *   bitwise (&, |, ^, >>, <<, ~) operators, as well as the unary negation (-)
 *   operator, all in one line.
 *
 * Method-specific rules for this file:
 * - You may use addition with the number 1 only in changeSign.
 * - You may not use unary negation in changeSign.
 * - You may not use bit shifting or the exclusive OR operator (^) in xor.
 * - You may use subtraction in powerOf2 ONLY.
 * 
 * Some notes:
 * All of these functions accept ints as parameters because if you pass in a
 * number (which is of type int by default) into a Method accepting a byte, then
 * the Java compiler will complain even if the number would fit into that type.
 *
 * Now, keep in mind the return value is also an int. Please read the comments
 * about how many significant bits to return and make sure that the other bits
 * are not set or else you will not get any points for that test case. For
 * example, if we ask you to return 6 bits and you return "0xFFFFFFFF", you will
 * lose points.
 *
 * Definitions of types:
 * nibble - 4 bits
 * byte   - 8 bits
 * short  - 16 bits
 * int    - 32 bits
 */
public class Operations
{

    /**
     * Reverse the sign of an int.
     * For this method, you may NOT use unary negation (-).
     * Hint: Think 2's Complement.
     *
     * @param num The int to reverse the sign of.
     *
     * @return The int with the sign reversed
     */
    int changeSign(int num)
    {
        return ~num + 1;
    }


    /**
     * Get an 8-bit byte from an int.
     *
     * Ints are made of 4 bytes, numbered like so:
     *   |   S3   |   S2   |   S1   |   S0   |
     *
     * For a graphical representation of the bits:
     *
     * bit 31                             bit 0
     *    v                                 v
     *    11011000 00001100 00011111 11011001
     *   +--------+--------+--------+--------+
     *   |   B3   |   B2   |   B1   |   B0   |
     *
     * Examples:
     *     getByte(0x56781234, 0); // => 0x34
     *     getByte(0x56781234, 2); // => 0x78
     *
     * Note: Remember, no multiplication allowed!
     *
     * @param num The int to get a short from.
     * @param which Determines which byte gets returned - 0 for
     *              least-significant byte, going to 3 for the most significant byte.
     *
     * @return A byte corresponding to the "which" parameter from num.
     */
    int getByte(int num, int which)
    {
        return (num >> (which << 3)) & 0xFF;
    }

    /**
     * Swap the 2 shorts in an int.
     *
     * Ints are made of 2 shorts, numbered like so:
     *   |       S1       |       S0       |
     *
     * For a graphical representation of the bits:
     *
     * bit 31                           bit 0
     *    v                               v
     *    1101100000001100 0001111111011001
     *   +----------------+----------------+
     *   |       S1       |       S0       |
     * 
     * Your job is to swap the positions of S1 and S0.
     * Examples:
     *     swapShorts(0x56781234, 0); // => 0x12345678
     *
     * Note: Remember, no multiplication allowed!
     *
     * @param num The int to swap the shorts of.
     *
     * @return The int with its shorts swapped.
     */
    int swapShorts(int num) {
        return ((num & 0xFFFF) << 16) | (((num & ~0xFFFF) >> 16) & 0xFFFF);
    }

    /**
     * Set a specified 4-bit nibble in an int with a provided 4-bit value.
     *
     * Ints are made of 8 nibbles, numbered like so:
     *   | N7 | N6 | N5 | N4 | N3 | N2 | N1 | N0 |
     *
     * For a graphical representation of the bits:
     *
     * bit 31                                 bit 0
     *    v                                     v
     *    1101 1000 0000 1100 0001 1111 1101 1001
     *   +----+----+----+----+----+----+----+----+
     *   | N7 | N6 | N5 | N4 | N3 | N2 | N1 | N0 |
     *
     * Examples:
     *     setNibble(0xAAA5BBC6, 0x2, 2); // =>  0xAAA5B2C6
     *     setNibble(0x56B218F9, 0x0, 5); // =>  0x800218F9
     *
     * Note: Remember, no multiplication allowed!
     *
     * @param num The int that will be modified.
     * @param a_nibble The nibble to insert into the integer.
     * @param which Selects which nibble to modify - 0 for least-significant
     * nibble.
     *
     * @return The modified int.
     */
    int setNibble(int num, int a_nibble, int which)
    {
        return (num & ~(0xF << (which << 2))) | (a_nibble << (which << 2));
    }

    /**
     * Pack a short and 2 bytes into an int.
     *
     * The short and 2 bytes should be placed consecutively in the 32-bit int in
     * the order that they appear in the parameters
     *
     * Example:
     *     pack(0x56, 0x1234, 0x78); // => 0x56123478
     *     pack(0xCO, 0xFFEE, 0x10); // => 0xCOFFEE10
     *
     * @param b2 Most significant byte (will always be a 8-bit number).
     * @param s1 2nd least significant short (will always be a 16-bit number).
     * @param b0 Least Significant byte (will always be a 8-bit number).
     *
     * @return a 32-bit value formatted like so: b2s1b0
     */
    int pack(int b2, int s1, int b0)
    {
        return (b2 << 24) | (s1 << 8) | b0;
    }

    /**
     * Extract a range of bits from a number.
     *
     * Examples:
     *     bitRange(0x00001234, 0, 4);  // => 0x00000004
     *     bitRange(0x00001234, 4, 8);  // => 0x00000023
     *     bitRange(0x12345678, 0, 28); // => 0x02345678
     *     bitRange(0x55555555, 5, 7);  // => 0x0000002A
     *
     * Note: We will only pass in values 1 to 32 for n.
     *
     * @param num An n-bit 2's complement number.
     * @param s The starting bit to grab
     * @param n The number of bits to return.
     * @return The n-bit number num[s:s+n-1].
     */
    int bitRange(int num, int s, int n)
    {
        return (num >> s) & ~(~0 << n);
    }

    /**
     * NOTE: For this method, you may only use &, |, and ~.
     *
     * Perform an exclusive-or on two 32-bit ints.
     *
     * Examples:
     *     xor(0xFF00FF00, 0x00FF00FF); // => 0xFFFFFFFF
     *     xor(0x12345678, 0x87654321); // => 0x95511559
     *
     * @param num1 An int
     * @param num2 Another int
     *
     * @return num1 XOR num2
     */
    int xor(int num1, int num2)
    {
        return (num1 & ~num2) | (~num1 & num2);
    }


    /**
     * Return true if the given number is a multiple of 2.
     *
     * Examples:
     *     multipleOf2(32);   // => true
     *     multipleOf2(13);   // => false
     *
     * Note: Make sure you handle ALL the cases!
     *
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a multiple of 2, else false.
     */

    boolean multipleOf2(int num)
    {
        return (num & 1) == 0;
    }

    /**
     * Return true if the given number is a multiple of 16.
     *
     * Examples:
     *     multipleOf16(256); // => true
     *     multipleOf16(135); // => false
     *     multipleOf16(72);  // => false
     *     multipleOf16(-96);  // => true
     *     multipleOf16(0);  // => true
     *
     * Note: Make sure you handle ALL the cases!
     *
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a multiple of 16, else false.
     */

    boolean multipleOf16(int num)
    {
        return (num & 15) == 0;
    }

    /**
     * Return true if the given number is a power of 2.
     *
     * Examples:
     *     powerOf2(32);   // => true
     *     powerOf2(12);   // => false
     *     powerOf2(1);    // => true
     *     powerOf2(-4);   // => false (a negative power of 2 is not a power of 2)
     *
     * Note: Make sure you handle ALL the cases!
     *
     * Hint: If num is a power of 2:
     *   What is the binary representation of num?
     *   What is the binary representation of num - 1?
     *   How does it differ if num is not a power of 2?
     *
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a multiple of 2, else false.
     */

    boolean powerOf2(int num)
    {
        return ((num & (num - 1)) == 0) && (num > 0);
    }
}
