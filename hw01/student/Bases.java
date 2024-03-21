/**
 * CS 2110 Spring 2024 HW1
 * Part 2 - Coding with bases
 *
 * @author Yulin Lu
 *
 * Global rules for this file:
 * 
 * - You cannot use multiplication, division, and modulus operators
 * - You cannot use nested loops
 * - You cannot declare file-level variables
 * - You cannot use switch statements
 * - You cannot use the unsigned right shift operator (>>>)
 * - You cannot use helper methods, call any other methods, or use recursion.
 * 
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 loops per method. This includes
 *   for loops, while loops and do-while loops.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from String literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 */
public class Bases
{
    /**
     * Convert a String containing ASCII characters (in binary) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("110"); // => 6
     */
    public static int binaryStringToInt(String binary)
    {
        int num = 0;

        for (int i = 0; i < binary.length(); i ++) {
            if (binary.charAt(i) == '1') {
                num = num + (0x1 << binary.length() -i -1);
            }
        }
        return num;
    }

    /**
     * Convert a String containing ASCII characters (in decimal) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("46"); // => 46
     */
    public static int decimalStringToInt(String decimal)
    {
        int num = 0;
        for (int i = 0; i < decimal.length(); i ++) {
            num = (num << 1) + (num << 3);
            num += (decimal.charAt(i) - '0');
        }
        return num;
    }

    /**
     * Convert a String containing ASCII characters (in binary) to an a String containing ASCII characters (in octal).
     * The input String will only contain the numbers 0 and 1.
     * You may assume that the length of the binary String is divisible by 3.
     *
     * Example: binaryStringToOctalString("110 100"); // => "64"
     */
    public static String binaryStringToOctalString(String binary)
    {
        int num = 0;
        for (int i = 0; i < binary.length(); i ++) {
            if (binary.charAt(i) == '1') {
                num = num + (0x1 << binary.length() -i -1);
            }
        }

        String ans = "";
        do {
            ans = (char)((num & 0b111) + '0') + ans;
            num = num >> 3;
        } while (num > 0);
        return ans;
    }

    /**
     * Convert a int into a String containing ASCII characters (in hex).
     *
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters
     * necessary to represent the number that was passed in.
     *
     * Example: intToHexString(30); // => "1E"
     */
    public static String intToHexString(int hex)
    {
        String ans = "";
        while(hex > 0) {
            if ((hex & 0xF) <= 9) {
                char curr = (char) ('0' + (hex & 0xF));
                ans = curr + ans;
            } else {
                char curr = (char) ('A' + ((hex & 0xF) - 10));
                ans = curr + ans;
            }
            hex = hex >> 4;
        }
        return ans;
    }

    /**
     * Convert a String containing ASCII characters representing a number in
     * hex into a String containing ASCII characters that represent that same
     * value in binary. The returned binary String should not have any leading
     * zeros, even if there are in the input hex String. If the hex String
     * evaluates to zero, then return the equivalent of zero in binary.
     *
     * The output String should only 0's and 1's.
     *
     * Example: hexStringToBinaryString("0F32A65C"); => "1111001100101010011001011100"
     */
    public static String hexStringToBinaryString(String hex)
    {
        int num = 0;
        int pow = 0;
        for (int i = hex.length() -1; i >=0; i --) {
            if (hex.charAt(i) > '9') {
                num += (hex.charAt(i) - '0' -7) << pow;
            } else {
                num += (hex.charAt(i) - '0') << pow;
            }
            pow += 4;
        }
        String ans = "";
        do {
            if ((num & 1) == 1) {
                ans = '1' + ans;
            } else {
                ans = '0' + ans;
            }
            num = num >> 1;
        } while (num != 0);
        return ans;
    }
}
