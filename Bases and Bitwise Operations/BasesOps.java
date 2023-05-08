public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     */
    public static int binaryStringToInt(String binary) {
        int value = 0;
        for (int i = 0; i < binary.length(); i++) {
            if (binary.charAt(i) == '1') {
                value += (1 << binary.length() - i - 1);
            }
        }
        return value;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     */
    public static int decimalStringToInt(String decimal) {
        int value = 0;
        int _10 = 1;
        for (int i = decimal.length() - 1; i >= 0; i--) {
            value += _10 * (decimal.charAt(i) - '0');
            _10 *= 10;
        }
        return value;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     */
    public static int hexStringToInt(String hex) {
        int value = 0;
        int base = 0;
        for (int i = 0; i < hex.length(); i++) {
            char c = hex.charAt(hex.length() - i - 1);
            if (c > 58) {
                value += ((c - 55) << base);
            } else {
                value += ((c - 48) << base);
            }
            base += 4;
        }
        return value;
    }

    /**
     * Convert a int into a String containing ASCII characters (in octal).
     */
    public static String intToOctalString(int octal) {
        if (octal == 0) {
            return "0";
        }
        String value = "";
        while (octal != 0) {
            int octalInt = octal & 0b111;
            value = ((char) (octalInt + 48)) + value;
            octal = octal >> 3;
        }
        return value;
    }

    /**
     * Convert a String containing ASCII characters representing a number in
     * binary into a String containing ASCII characters that represent that same
     * value in hex.
     */
    public static String binaryStringToHexString(String binary) {
        String value = "";
        int binaryInt = 0;
        for (int i = 31; i >= 0; i--) {
            if (binary.charAt(i) == 49) {
                binaryInt = binaryInt | (1 << (31 - i));
            }
        }
        int counter = 8;
        while (counter != 0) {
            int b = binaryInt & 0xF;
            if (b + 48 > 57) {
                value = ((char) (b + 55)) + value;
            } else {
                value = ((char) (b + 48)) + value;
            }
            binaryInt = binaryInt >> 4;
            counter--;
        }
        return value;
    }
}