#include <stdio.h>
#include <time.h>

unsigned long long int keys[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

int IPbox[] = {
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
};

int Ebox[] = {
        32,1,2,3,4,5,
        4,5,6,7,8,9,
        8,9,10,11,12,13,
        12,13,14,15,16,17,
        16,17,18,19,20,21,
        20,21,22,23,24,25,
        24,25,26,27,28,29,
        28,29,30,31,32,1
};

int SBoxes[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },

    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },

    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },

    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },

    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },

    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },

    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },

    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

int PBox[] = {
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25
};

int FPbox[] = {
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25
};

int permuted_choice_1[] = {
    57,49,41,33,25,17,9,1,
    58,50,42,34,26,18,10,2,
    59,51,43,35,27,19,11,3,
    60,52,44,36,63,55,47,39,
    31,23,15,7,62,54,46,38,
    30,22,14,6,61,53,45,37,
    29,21,13,5,28,20,12,4
};

int permuted_choice_2[] = {
    14,17,11,24,1,5,3,28,
    15,6,21,10,23,19,12,4,
    26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,
    51,45,33,48,44,49,39,56,
    34,53,46,42,50,36,29,32
};

int right_shifts[] = { 0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

int left_shifts[] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

// works
unsigned long long int initial_permuation(unsigned long long int plain) {
    unsigned long long int result = 0;

    for (int i = 0; i < 64; i++) {
        result |= ((plain >> 64 - IPbox[i]) & 1) << 63 - i;
    }

    return result;
}

// works
unsigned long long int expansion(unsigned long long int plain) {
    unsigned long long int result = 0;

    for (int i = 0; i < 48; i++) {
        result |= ((plain >> 32 - Ebox[i]) & 1) << 47 - i;
    }

    return result;
}

// works
int row_calculation(int input) {
    input = input & 0x21;
    int row = ((input >> 4) & 2) + (input & 1);
    return row;
}

// works
int column_calculation(int input) {
    input = input & 0x1E;
    int column = (input >> 1) & 0xF;
    return column;
}

// works
unsigned int sbox(unsigned int input, int box) {
    int row = row_calculation(input);
    int column = column_calculation(input);

    return SBoxes[box][row][column];
}

// works
unsigned int pbox(unsigned int input) {
    unsigned int result = 0;

    for (int i = 0; i < 32; i++) {
        result |= ((input >> 32 - PBox[i]) & 1) << 31 - i;
    }

    return result;
}

// works
unsigned int f_function(unsigned int plain, int round) {
    unsigned int result = 0;
    unsigned long long int expanded = expansion(plain);
    expanded = expanded ^ keys[round];

    for (int i = 0; i < 8; i++) {
        unsigned int input = (expanded >> 42 - 6 * i) & 0x3F;
        result |= sbox(input, i) << 28 - 4 * i;
    }

    return pbox(result);
}

// works
unsigned long long int final_permutation(unsigned int left, unsigned long long int right) {
    unsigned long long int result = 0;
    unsigned long long int temp = 0;

    temp |= right << 32;
    temp |= left;

    for (int i = 0; i < 64; i++) {
        result |= ((temp >> 64 - FPbox[i]) & 1) << 63 - i;
    }

    return result;
}

// works
unsigned long long int key_permuted_choice_1(unsigned long long int key) {
    unsigned long long int result = 0;

    for (int i = 0; i < 56; i++) {
        result |= ((key >> 64 - permuted_choice_1[i]) & 1) << 55 - i;
    }

    return result;
}

// works
unsigned int leftshift(unsigned int key, int round) {
    unsigned int temp = 0;

    if (left_shifts[round] == 2) {
        temp |= ((key << left_shifts[round]) & 0xFFFFFFC);
        temp |= key >> 26;
    }
    else {
        temp |= ((key << left_shifts[round]) & 0xFFFFFFE);
        temp |= key >> 27;
    }

    return temp;
}

// works
unsigned long int rightshift(unsigned int site, int round) {
    unsigned int temp = 0;

    if (right_shifts[round] == 0) {
        return site;
    }
    else if (right_shifts[round] == 1) {
        temp |= (site >> 1) & 0x7FFFFFF;
        temp |= (site << 27) & 0x8000000;
    }
    else {
        temp |= (site >> 2) & 0x3FFFFFF;
        temp |= (site << 26) & 0xC000000;
    }
    return temp;
}

// works
void key_permuted_choice_2(unsigned long long int* array, unsigned long long int left, unsigned int right, int round) {
    unsigned long long int result = 0;
    unsigned long long int temp = 0 | left << 28;
    temp |= right;

    for (int i = 0; i < 48; i++) {
        result |= ((temp >> 56 - permuted_choice_2[i]) & 1) << 47 - i;
    }
    array[round] = result;
}

// works
void encryption_key_schedule(unsigned long long int key) {
    unsigned long long int permuted_key = key_permuted_choice_1(key);

    unsigned int left = 0 | permuted_key >> 28;
    unsigned int right = 0 | (permuted_key & 0xFFFFFFF);

    unsigned long long int result = 0;
    for (int i = 0; i < 16; i++) {
        left = leftshift(left, i);
        right = leftshift(right, i);
        key_permuted_choice_2(keys, left, right, i);
    }
}

// works
void decryption_key_schedule(unsigned long long int key) {
    unsigned long long int permuted_key = key_permuted_choice_1(key);

    unsigned int left = 0 | permuted_key >> 28;
    unsigned int right = 0 | (permuted_key & 0xFFFFFFF);


    for (int i = 0; i < 16; i++) {
        left = rightshift(left, i);
        right = rightshift(right, i);
        key_permuted_choice_2(keys, left, right, i);
    }
}

// works
void encrypt() {
    unsigned long long int plain = ; // add 64 bit plaintext
    unsigned long long int key = ; // add 64 bit key

    // generates roundkeys
    encryption_key_schedule(key);

    // initial permutation
    plain = initial_permuation(plain);

    // splitting into halfes
    unsigned int left_site = plain >> 32;
    unsigned int right_site = plain;

    for (int i = 0; i < 16; i++) {
        unsigned int temp_right_site = f_function(right_site, i);
        unsigned int temp_left_site = left_site ^ temp_right_site;

        left_site = right_site;
        right_site = temp_left_site;
    }

    printf("%llu\n", final_permutation(left_site, right_site));
}

// works
void decrypt() {
    unsigned long long int encrypted = ; // add 64 bit encrypted
    unsigned long long int key = ; // add 64 bit key

    decryption_key_schedule(key);

    encrypted = initial_permuation(encrypted);

    unsigned int left_site = encrypted >> 32;
    unsigned int right_site = encrypted;

    for (int i = 0; i < 16; i++) {
        unsigned int temp_right_site = f_function(right_site, i);
        unsigned int temp_left_site = left_site ^ temp_right_site;

        left_site = right_site;
        right_site = temp_left_site;
    }

    printf("%llu\n", final_permutation(left_site, right_site));
}

int main() {
    encrypt(); // whatever you want
    decrypt(); // whatever you want
    return 0;
}
