#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(char a[], char b[], int start, int stop) {
    int maxa = 0, maxb = 0;
    for (int i = start; i < stop; i++) {
        if (a[i] - '0' < b[i] - '0') {
            // b e mai mare
            maxb = 1;
            break;
        } else if (a[i] - '0' == b[i] - '0') {
            continue;
        } else if (a[i] - '0' > b[i] - '0') {
            // a e mai mare
            maxa = 1;
            break;
        }
    }
    if (maxa == 0 && maxb == 0) return 0;  // egale
    if (maxa == 1) return 1;               // pt a>
    if (maxb == 1) return 2;               // pt b>
    return 0;
}
void scadere(char a[], char b[], int length) {
    int bita_IM = a[length / 2];  // bitul de semn al partii IMAGINARE pentru a
    int bita_RE = a[0];           // bit semn parte REAlA pentru a
    int bitb_IM = b[length / 2];  // bit semn parte IMAGINARA pentru b
    int bitb_RE = b[0];           // bit semn parte REALA pentru b

    // partea imaginara
    if (bita_IM == '0' && bitb_IM == '1') {  // + si -
        int carry = 0;
        for (int i = length - 1; i > length / 2; i--) {
            int sum = (a[i] - '0' + b[i] - '0') + carry;
            if (sum <= 9) {
                a[i] = sum + '0';
                carry = 0;
            } else {
                a[i] = (sum % 10) + '0';
                carry = 1;
            }
        }
        // bitul de semn ramane +
    }
    if (bita_IM == '0' && bitb_IM == '0') {  // + si +
        int carry = 0;
        int greater;
        if (compare_strings(a, b, length / 2 + 1, length) == 1) {
            a[length / 2] = bita_IM;
            greater = 1;
        }  // a > b
        if (compare_strings(a, b, length / 2 + 1, length) == 2) {
            a[length / 2] = '1';
            greater = 2;
        }
        if (compare_strings(a, b, length / 2 + 1, length) == 0) {
            a[length / 2] = '0';
            greater = 0;
        }
        for (int i = length - 1; i > length / 2; i--) {
            if (greater == 1) {  // a > b
                int sum = (a[i] - '0') - (b[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 2) {  // a < b
                int sum = (b[i] - '0') - (a[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 0) {  // a == b
                a[i] = '0';
            }
        }
    }
    if (bita_IM == '1' && bitb_IM == '1') {  // - si -
        int carry = 0;
        int greater;
        if (compare_strings(a, b, length / 2 + 1, length) == 1) {
            a[length / 2] = bita_IM;
            greater = 1;
        }  // a > b
        if (compare_strings(a, b, length / 2 + 1, length) == 2) {
            a[length / 2] = '0';
            greater = 2;
        }  // a < b
        if (compare_strings(a, b, length / 2 + 1, length) == 0) {
            a[length / 2] = '0';
            greater = 0;
        }  // a == b
        for (int i = length - 1; i > length / 2; i--) {
            if (greater == 1) {  // a>b
                int sum = (a[i] - '0') - (b[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 2) {  // a<b
                int sum = (b[i] - '0') - (a[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 0) {  // a == b
                a[i] = '0';
            }
        }
    }
    if (bita_IM == '1' && bitb_IM == '0') {  // - si +
        int carry = 0;
        for (int i = length - 1; i > length / 2; i--) {
            int sum = (a[i] - '0' + b[i] - '0') + carry;
            if (sum <= 9) {
                a[i] = sum + '0';
                carry = 0;
            } else {
                a[i] = (sum % 10) + '0';
                carry = 1;
            }
        }
        // bitul de semn ramane -
    }
    // partea reala
    if (bita_RE == '0' && bitb_RE == '1') {  // + si -
        int carry = 0;
        for (int i = length / 2 - 1; i > 0; i--) {
            int sum = (a[i] - '0' + b[i] - '0') + carry;
            if (sum <= 9) {
                a[i] = sum + '0';
                carry = 0;
            } else {
                a[i] = (sum % 10) + '0';
                carry = 1;
            }
        }
        // bit de semn ramane +
    }
    if (bita_RE == '0' && bitb_RE == '0') {  // + si +
        int carry = 0;
        int greater;
        if (compare_strings(a, b, 1, length / 2) == 1) {
            a[0] = bita_RE;
            greater = 1;
        }  // a > b
        if (compare_strings(a, b, 1, length / 2) == 2) {
            a[0] = '1';
            greater = 2;
        }  // a < b
        if (compare_strings(a, b, 1, length / 2) == 0) {
            a[0] = '0';
            greater = 0;
        }  // a == b
        for (int i = length / 2 - 1; i > 0; i--) {
            if (greater == 1) {  // a>b
                int sum = (a[i] - '0') - (b[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 2) {  // a<b
                int sum = (b[i] - '0') - (a[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 0) {  // a == b
                a[i] = '0';
            }
        }
    }
    if (bita_RE == '1' && bitb_RE == '1') {  // - si -
        int carry = 0;
        int greater;
        if (compare_strings(a, b, 1, length / 2) == 1) {
            a[0] = bita_RE;
            greater = 1;
        }  // a > b
        if (compare_strings(a, b, 1, length / 2) == 2) {
            a[0] = '0';
            greater = 2;
        }  // a < b
        if (compare_strings(a, b, 1, length / 2) == 0) {
            a[0] = '0';
            greater = 0;
        }  // a == b
        for (int i = length / 2 - 1; i > 0; i--) {
            if (greater == 1) {  // a>b
                int sum = (a[i] - '0') - (b[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 2) {  // a<b
                int sum = (b[i] - '0') - (a[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 0) {  // a == b
                a[i] = '0';
            }
        }
    }
    if (bita_RE == '1' && bitb_RE == '0') {  // - si +
        int carry = 0;
        for (int i = length / 2 - 1; i > 0; i--) {
            int sum = (a[i] - '0' + b[i] - '0') + carry;
            if (sum <= 9) {
                a[i] = sum + '0';
                carry = 0;
            } else {
                a[i] = (sum % 10) + '0';
                carry = 1;
            }
        }
        // bitul de semn ramane -
    }
    puts(a);
}

void adunare(char a[], char b[], int length) {
    int bita_IM = a[length / 2];  // bit de semn parte IMAGINARA pentru a
    int bita_RE = a[0];           // bit de semn parte REALA pentru a
    int bitb_IM = b[length / 2];  // bit de semn parte IMAGINARA pentru b
    int bitb_RE = b[0];           // bit de semn parte REALA pentru b

    // partea imaginara
    if (bita_IM == '0' && bitb_IM == '0') {  // + si +
        int carry = 0;
        for (int i = length - 1; i > length / 2; i--) {
            int sum = (a[i] - '0' + b[i] - '0') + carry;
            if (sum <= 9) {
                a[i] = sum + '0';
                carry = 0;
            } else {
                a[i] = (sum % 10) + '0';
                carry = 1;
            }
        }
        // bitul de semn ramane +
    }
    if (bita_IM == '0' && bitb_IM == '1') {  // + si -
        int carry = 0;
        int greater;
        if (compare_strings(a, b, length / 2 + 1, length) == 1) {
            a[length / 2] = bita_IM;
            greater = 1;
        }  // a > b
        if (compare_strings(a, b, length / 2 + 1, length) == 2) {
            a[length / 2] = bitb_IM;
            greater = 2;
        }  // a < b
        if (compare_strings(a, b, length / 2 + 1, length) == 0) {
            a[length / 2] = '0';
            greater = 0;
        }  // a == b
        for (int i = length - 1; i > length / 2; i--) {
            if (greater == 1) {  // a > b
                int sum = (a[i] - '0') - (b[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 2) {  // a < b
                int sum = (b[i] - '0') - (a[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 0) {  // a == b
                a[i] = '0';
            }
        }
    }
    if (bita_IM == '1' && bitb_IM == '0') {  //-si +
        int carry = 0;
        int greater;
        if (compare_strings(a, b, length / 2 + 1, length) == 1) {
            a[length / 2] = bita_IM;
            greater = 1;
        }  // a > b
        if (compare_strings(a, b, length / 2 + 1, length) == 2) {
            a[length / 2] = bitb_IM;
            greater = 2;
        }  // a < b
        if (compare_strings(a, b, length / 2 + 1, length) == 0) {
            a[length / 2] = '0';
            greater = 0;
        }  // a == b
        for (int i = length - 1; i > length / 2; i--) {
            if (greater == 1) {  // a>b
                int sum = (a[i] - '0') - (b[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 2) {  // a<b
                int sum = (b[i] - '0') - (a[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 0) {  // a == b
                a[i] = '0';
            }
        }
    }
    if (bita_IM == '1' && bitb_IM == '1') {  // - si -
        int carry = 0;
        for (int i = length - 1; i > length / 2; i--) {
            int sum = (a[i] - '0' + b[i] - '0') + carry;
            if (sum <= 9) {
                a[i] = sum + '0';
                carry = 0;
            } else {
                a[i] = (sum % 10) + '0';
                carry = 1;
            }
        }
        // bitul de semn ramane -
    }

    // partea reala

    if (bita_RE == '0' && bitb_RE == '0') {  // + si +
        int carry = 0;
        for (int i = length / 2 - 1; i > 0; i--) {
            int sum = (a[i] - '0' + b[i] - '0') + carry;
            if (sum <= 9) {
                a[i] = sum + '0';
                carry = 0;
            } else {
                a[i] = (sum % 10) + '0';
                carry = 1;
            }
        }
        // bit de semn ramane +
    }
    if (bita_RE == '0' && bitb_RE == '1') {  // + si -
        int carry = 0;
        int greater;
        if (compare_strings(a, b, 1, length / 2) == 1) {
            a[0] = bitb_RE;
            greater = 1;
        }  // a > b
        if (compare_strings(a, b, 1, length / 2) == 2) {
            a[0] = bitb_RE;
            greater = 2;
        }  // a < b
        if (compare_strings(a, b, 1, length / 2) == 0) {
            a[0] = '0';
            greater = 0;
        }  // a == b
        for (int i = length / 2 - 1; i > 0; i--) {
            if (greater == 1) {  // a>b
                a[0] = bita_RE;
                int sum = (a[i] - '0') - (b[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 2) {  // a<b
                a[0] = bitb_RE;
                int sum = (b[i] - '0') - (a[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 0) {  // a == b
                a[i] = '0';
            }
        }
    }
    if (bita_RE == '1' && bitb_RE == '0') {  //-si +
        int carry = 0;
        int greater;
        if (compare_strings(a, b, 1, length / 2) == 1) {
            a[0] = bita_RE;
            greater = 1;
        }  // a > b
        if (compare_strings(a, b, 1, length / 2) == 2) {
            a[0] = bitb_RE;
            greater = 2;
        }  // a < b
        if (compare_strings(a, b, 1, length / 2) == 0) {
            a[0] = '0';
            greater = 0;
        }  // a == b
        for (int i = length / 2 - 1; i > 0; i--) {
            if (greater == 1) {  // a>b
                int sum = (a[i] - '0') - (b[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 2) {  // a<b
                int sum = (b[i] - '0') - (a[i] - '0') + carry;
                if (sum < 0) {
                    carry = -1;
                    sum += 10;
                    a[i] = sum + '0';
                } else {
                    carry = 0;
                    a[i] = sum + '0';
                }
            } else if (greater == 0) {  // a == b
                a[i] = '0';
            }
        }
    }
    if (bita_RE == '1' && bitb_RE == '1') {  // - si -
        int carry = 0;
        for (int i = length / 2 - 1; i > 0; i--) {
            int sum = (a[i] - '0' + b[i] - '0') + carry;
            if (sum <= 9) {
                a[i] = sum + '0';
                carry = 0;
            } else {
                a[i] = (sum % 10) + '0';
                carry = 1;
            }
        }
        // bitul de semn ramane -
    }
    puts(a);
}

int main() {
    int N;
    scanf("%d", &N);
    char a[1001], b[1001];
    char tip;  // tipul operatiei

    scanf("%s", a);  // primul vector
    int length = strlen(a);

    while (getchar() != '\n') ;
    tip = getchar();  // citim primul semn
    while (tip != '0') {
        scanf("%s", b);  // citim b-ul
        if (tip == '+') adunare(a, b, length);
        if (tip == '-') scadere(a, b, length);
        while (getchar() != '\n') ;
        tip = getchar();
    }
    return 0;
}