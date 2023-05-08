public class Operations
{
    /**
     * Get an 16-bit short from an int.
     * @param num The int to get a short from.
     * @param which Determines which short gets returned - 0 for
     *              least-significant short.
     * @return A short corresponding to the "which" parameter from num.
     */
    int getShort(int num, int which) {
        return (num >> (which << 4)) & 0xFFFF;
    }

    /**
     * Set a specified 8-bit byte in an int with a provided 8-bit value.
     * @return The modified int.
     */
    int setByte(int num, int a_byte, int which) {
        return (a_byte << (which << 3)) | (num & (~(0xFF << (which << 3))));
    }

    /**
     * Pack a short and 2 bytes into an int.
     * @param s2 Most significant short (will always be a 16-bit number).
     * @param b1 2nd least significant byte (will always be a 8-bit number).
     * @param b0 Least Significant byte (will always be a 8-bit number).
     * @return a 32-bit value formatted like so: s2b1b0
     */
    int pack(int s2, int b1, int b0) {
        return (s2 << 16) | ((0xFF & b1) << 8) | (0xFF & b0);
    }

    /**
     * Extract a range of bits from a number.
     * @param num An n-bit 2's complement number.
     * @param s The starting bit to grab
     * @param n The number of bits to return.
     * @return The n-bit number num[s:s+n-1].
     */
    int bitRange(int num, int s, int n)
    {
        return ((num >> s) & ~(~0 << n));
    }

    /**
     * Perform an exclusive-nor on two 32-bit ints. That is, take their
     * exclusive-or and bitwise-not the result.
     * @param num1 An int
     * @param num2 Another int
     * @return num1 XNOR num2
     */
    int xnor(int num1, int num2) { return ~((num1 & ~ num2) | (num2 & ~ num1)); }

    /**
     * Return true if the given number is a multiple of 2.
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a multiple of 2 else false.
     */

    boolean multipleOf2(int num) { return ((num & 1) == 0); }

    /**
     * Return true if the given number is a multiple of 8.
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a multiple of 8 else false.
     */

    boolean multipleOf8(int num) {
        return ((num & 7) == 0);
    }

    /**
     * Return true if the given number is a power of 2.
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a multiple of 2 else false.
     */

    boolean powerOf2(int num) {
        return ((num >= 1) && ((num & (num - 1)) == 0));
    }
}