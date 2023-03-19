#include <cmath>
#include <vector>

std::vector<int> getDigitOfNumber(const int srcNumber){
    // get number of digits
    int numDigits = srcNumber > 0 ? std::floor(std::log10(srcNumber) + 1) : 1;

    std::vector<int> digits(numDigits, 0);
    // for holding the result

    int temp = srcNumber;
    for(int i = numDigits - 1; i >= 0; --i){
        digits[i] = temp % 10;
        temp = temp / 10;
    }

    return digits;
}
