// دالة لحساب عدد الاضطرابات (Derangements) لعنصر m
// وظيفتها: تحسب كم طريقة لترتيب m من العناصر بحيث "ولا عنصر" يرجع لمكانه الأصلي
long long get_derangement(int m) {
    if (m == 0) return 1;
    if (m == 1) return 0;
    
    long long prev2 = 1; // D(0)
    long long prev1 = 0; // D(1)
    long long current = 0;
    
    for (int i = 2; i <= m; ++i) {
        current = (i - 1) * (prev1 + prev2);
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}
