int greatest_common_divisor(int num1, int num2){
    int prev_b = 0;// just init
    while(num2 != 0){
        prev_b = num2;
        num2 = num1 % num2;
        num1 = prev_b;
    }
    return num1;
}
