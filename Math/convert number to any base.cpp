string toBase(long long num, int base) {
    if (num == 0) return "0";

    const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result = "";

    while (num > 0) {
        result = digits[num % base] + result;
        num /= base;
    }

    return result;
}
