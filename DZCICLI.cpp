#include <iostream>
using namespace std;

// Максимальная и минимальная цифра числа и их произведение
void max_min_digit_for() {
    int n;
    cout << "Enter number: ";
    cin >> n;
    
    if (n == 0) {
        cout << "Max: 0, Min: 0, Product: 0" << endl;
        return;
    }
    
    int temp = abs(n);
    int max_digit = temp % 10, min_digit = temp % 10;
    
    for (temp /= 10; temp > 0; temp /= 10) {
        int digit = temp % 10;
        if (digit > max_digit) max_digit = digit;
        if (digit < min_digit) min_digit = digit;
    }
    cout << "Max: " << max_digit << ", Min: " << min_digit << ", Product: " << max_digit * min_digit << endl;
}

void max_min_digit_while() {
    int n;
    cout << "Enter number: ";
    cin >> n;
    
    if (n == 0) {
        cout << "Max: 0, Min: 0, Product: 0" << endl;
        return;
    }
    
    int temp = abs(n);
    int max_digit = temp % 10, min_digit = temp % 10;
    temp /= 10;
    
    while (temp > 0) {
        int digit = temp % 10;
        if (digit > max_digit) max_digit = digit;
        if (digit < min_digit) min_digit = digit;
        temp /= 10;
    }
    cout << "Max: " << max_digit << ", Min: " << min_digit << ", Product: " << max_digit * min_digit << endl;
}

void max_min_digit_dowhile() {
    int n;
    cout << "Enter number: ";
    cin >> n;
    
    int temp = abs(n);
    int max_digit = temp % 10, min_digit = temp % 10;
    temp /= 10;
    
    if (temp > 0) {
        do {
            int digit = temp % 10;
            if (digit > max_digit) max_digit = digit;
            if (digit < min_digit) min_digit = digit;
            temp /= 10;
        } while (temp > 0);
    }
    cout << "Max: " << max_digit << ", Min: " << min_digit << ", Product: " << max_digit * min_digit << endl;
}

// Сумма последовательности до 0
void sum_sequence_for() {
    int sum = 0, num;
    cout << "Enter numbers (0 to stop): ";
    
    for (cin >> num; num != 0; cin >> num) {
        sum += num;
    }
    cout << "Sum: " << sum << endl;
}

void sum_sequence_while() {
    int sum = 0, num;
    cout << "Enter numbers (0 to stop): ";
    cin >> num;
    
    while (num != 0) {
        sum += num;
        cin >> num;
    }
    cout << "Sum: " << sum << endl;
}

void sum_sequence_dowhile() {
    int sum = 0, num;
    cout << "Enter numbers (0 to stop): ";
    
    do {
        cin >> num;
        sum += num;
    } while (num != 0);
    cout << "Sum: " << sum << endl;
}

// Удалить заданную цифру из числа
void remove_digit_for() {
    int n, digit;
    cout << "Enter number and digit to remove: ";
    cin >> n >> digit;
    
    if (n == 0) {
        cout << (digit == 0 ? 0 : n) << endl;
        return;
    }
    
    int result = 0, multiplier = 1;
    for (int temp = abs(n); temp > 0; temp /= 10) {
        int d = temp % 10;
        if (d != digit) {
            result += d * multiplier;
            multiplier *= 10;
        }
    }
    if (n < 0) result = -result;
    cout << "Result: " << result << endl;
}

void remove_digit_while() {
    int n, digit;
    cout << "Enter number and digit to remove: ";
    cin >> n >> digit;
    
    if (n == 0) {
        cout << (digit == 0 ? 0 : n) << endl;
        return;
    }
    
    int result = 0, multiplier = 1;
    int temp = abs(n);
    
    while (temp > 0) {
        int d = temp % 10;
        if (d != digit) {
            result += d * multiplier;
            multiplier *= 10;
        }
        temp /= 10;
    }
    if (n < 0) result = -result;
    cout << "Result: " << result << endl;
}

void remove_digit_dowhile() {
    int n, digit;
    cout << "Enter number and digit to remove: ";
    cin >> n >> digit;
    
    int result = 0, multiplier = 1;
    int temp = abs(n);
    
    if (temp == 0) {
        result = (digit == 0 ? 0 : n);
    } else {
        do {
            int d = temp % 10;
            if (d != digit) {
                result += d * multiplier;
                multiplier *= 10;
            }
            temp /= 10;
        } while (temp > 0);
    }
    if (n < 0) result = -result;
    cout << "Result: " << result << endl;
}

// Делители чисел от N до M
void find_divisors_for() {
    int N, M;
    cout << "Enter N and M: ";
    cin >> N >> M;
    
    for (int i = N; i <= M; i++) {
        cout << i << ": ";
        bool found = false;
        
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                if (found) cout << ", ";
                cout << j;
                found = true;
            }
        }
        if (!found) cout << "none";
        cout << endl;
    }
}

void find_divisors_while() {
    int N, M;
    cout << "Enter N and M: ";
    cin >> N >> M;
    int i = N;
    
    while (i <= M) {
        cout << i << ": ";
        int j = 2;
        bool found = false;
        
        while (j < i) {
            if (i % j == 0) {
                if (found) cout << ", ";
                cout << j;
                found = true;
            }
            j++;
        }
        if (!found) cout << "none";
        cout << endl;
        i++;
    }
}

void find_divisors_dowhile() {
    int N, M;
    cout << "Enter N and M: ";
    cin >> N >> M;
    int i = N;
    
    if (i <= M) {
        do {
            cout << i << ": ";
            int j = 2;
            bool found = false;
            
            if (j < i) {
                do {
                    if (i % j == 0) {
                        if (found) cout << ", ";
                        cout << j;
                        found = true;
                    }
                    j++;
                } while (j < i);
            }
            if (!found) cout << "none";
            cout << endl;
            i++;
        } while (i <= M);
    }
}

// Таблица умножения
void mult_table_for() {
    cout << "Multiplication Table:" << endl;
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            cout << i * j << "\t";
        }
        cout << endl;
    }
}

void mult_table_while() {
    cout << "Multiplication Table:" << endl;
    int i = 1;
    
    while (i <= 10) {
        int j = 1;
        while (j <= 10) {
            cout << i * j << "\t";
            j++;
        }
        cout << endl;
        i++;
    }
}

void mult_table_dowhile() {
    cout << "Multiplication Table:" << endl;
    int i = 1;
    
    do {
        int j = 1;
        do {
            cout << i * j << "\t";
            j++;
        } while (j <= 10);
        cout << endl;
        i++;
    } while (i <= 10);
}
