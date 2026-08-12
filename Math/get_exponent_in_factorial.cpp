/*
 * Calculates the highest exponent of a prime number 'p' in 'n!' (Legendre's Formula).
 * 
 * Concept:
 * Imagine multiplying all numbers from 1 up to n (n!).
 * For example, 5! = 1 * 2 * 3 * 4 * 5 = 120.
 * 
 * This code answers one question: 
 * "How many times is prime 'p' multiplied inside n!?"
 * Or: "How many consecutive times can I divide n! by 'p' without a fraction?"
 * 
 * Example breakdown for n = 5, p = 2:
 *   - 1: Contains no factors of 2
 *   - 2: Contains one 2
 *   - 3: Contains no factors of 2
 *   - 4: 2 * 2 -> Contains two 2s
 *   - 5: Contains no factors of 2
 * 
 * Total count: 1 + 2 = 3 factors of 2 (meaning 2^3 = 8 divides 120 cleanly).
 */
  
int64_t get_exponent_in_factorial(int n, int p)
{
    int64_t exponent = 0;
    int64_t temp = p;

    while (temp <= n)
    {
        exponent += n / temp;
        if (n / temp < p)
        {
            break;
        }
        temp *= p;
    }
    return exponent;
}
