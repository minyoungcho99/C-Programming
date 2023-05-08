public class BitVector
{
    private int bits;
    /**
     * Sets the bit (sets to 1) pointed to by index.
     * @param index index of which bit to set.
     *              0 for the least significant bit (right most bit).
     *              31 for the most significant bit.
     */
    public void set(int index) { bits = bits | (1 << index); }

    /**
     * Clears the bit (sets to 0) pointed to by index.
     * @param index index of which bit to set.
     *              0 for the least significant bit (right most bit).
     *              31 for the most significant bit.
     */
    public void clear(int index) { bits = bits & ~(1 << index); }

    /**
     * Toggles the bit (sets to the opposite of its current value) pointed to by
     * index.
     * @param index index of which bit to set.
     *              0 for the least significant bit (right most bit).
     *              31 for the most significant bit.
     */
    public void toggle(int index) { bits = bits ^ (1 << index); }

    /**
     * Returns true if the bit pointed to by index is currently set.
     * @param index index of which bit to check.
     *              0 for the least significant bit (right-most bit).
     *              31 for the most significant bit.
     * @return true if the bit is set, false if the bit is clear.
     *         If the index is out of range (index >= 32), then return false.
     */
    public boolean isSet(int index) { return (!(index >= 32) && ((bits & (1 << index)) == (1 << index))); }

    /**
     * Returns true if the bit pointed to by index is currently clear.
     * @param index index of which bit to check.
     *              0 for the least significant bit (right-most bit).
     *              31 for the most significant bit.
     * @return true if the bit is clear, false if the bit is set.
     *         If the index is out of range (index >= 32), then return true.
     */
    public boolean isClear(int index) {
        return ((index >= 32) || ((bits & (1 << index)) != (1 << index)));
    }

    /**
     * Returns the number of bits currently set (=1) in this bit vector.
     */
    public int onesCount() {
        int counter = 0;
        for (int i = 0; i < 32; i++) {
            if ((bits & (1 << i)) == (1 << i)) {
                counter++;
            }
        }
        return counter;
    }

    /**
     * Returns the number of bits currently clear (=0) in this bit vector.
     */
    public int zerosCount() {
        int counter = 0;
        for (int i = 0; i < 32; i++) {
            if ((bits & (1 << i)) != (1 << i)) {
                counter++;
            }
        }
        return counter;

    }

    /**
     * Returns the "size" of this BitVector. The size of this bit vector is
     * defined to be the minimum number of bits that will represent all of the
     * ones.
     */
    public int size() {
        for (int i = 31; i >= 0; i--) {
            if ((bits & (1 << i)) != 0) {
                return i + 1;
            }
        }
        return 1;
    }
}