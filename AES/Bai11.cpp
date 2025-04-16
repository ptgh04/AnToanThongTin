#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept> // For exception handling

// Define types for clarity
typedef unsigned char byte;
typedef std::vector<byte> ByteArray;
typedef std::vector<std::vector<byte>> StateMatrix;

// --- Constants ---

// S-box (Substitution Box)
const byte sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

// Rcon (Round Constant) - only values for first 10 rounds needed for AES-128
const byte Rcon[11] = {
    0x00, // Rcon[0] is not used
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

// Number of rounds for AES-128
const int Nr = 10;
// Block size in bytes (128 bits)
const int Nb = 4; // Number of columns (32-bit words) comprising the State
// Key length in bytes (128 bits)
const int Nk = 4; // Number of 32-bit words comprising the Cipher Key

// --- Helper Functions ---

// Convert a hex string to a byte array
ByteArray hexStringToBytes(const std::string& hex) {
    if (hex.length() % 2 != 0) {
        throw std::invalid_argument("Hex string must have an even number of characters");
    }
    ByteArray bytes;
    bytes.reserve(hex.length() / 2);
    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        byte b = (byte)strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(b);
    }
    return bytes;
}

// Convert a byte array to a hex string
std::string bytesToHexString(const ByteArray& bytes) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (byte b : bytes) {
        ss << std::setw(2) << static_cast<int>(b);
    }
    return ss.str();
}

// Print a byte array (for debugging)
void printBytes(const ByteArray& bytes, const std::string& label = "") {
    if (!label.empty()) {
        std::cout << label << ": ";
    }
    std::cout << bytesToHexString(bytes) << std::endl;
}

// Convert 16-byte array to 4x4 State Matrix (column major)
StateMatrix bytesToState(const ByteArray& bytes) {
    StateMatrix state(4, std::vector<byte>(Nb));
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < Nb; ++c) {
            state[r][c] = bytes[r + 4 * c];
        }
    }
    return state;
}

// Convert 4x4 State Matrix back to 16-byte array (column major)
ByteArray stateToBytes(const StateMatrix& state) {
    ByteArray bytes(16);
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < Nb; ++c) {
            bytes[r + 4 * c] = state[r][c];
        }
    }
    return bytes;
}

// --- AES Core Functions ---

// Substitute bytes using S-box
void SubBytes(StateMatrix& state) {
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < Nb; ++c) {
            state[r][c] = sbox[state[r][c]];
        }
    }
}

// Shift rows of the state
void ShiftRows(StateMatrix& state) {
    byte temp;
    // Row 1: shift left by 1
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    // Row 2: shift left by 2
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    // Row 3: shift left by 3
    temp = state[3][0];
    state[3][0] = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = temp;
}

// Galois Field (GF(2^8)) multiplication
byte gmul(byte a, byte b) {
    byte p = 0;
    byte counter;
    byte hi_bit_set;
    for (counter = 0; counter < 8; counter++) {
        if ((b & 1) != 0) {
            p ^= a;
        }
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set != 0) {
            a ^= 0x1b; // irreducible polynomial x^8 + x^4 + x^3 + x + 1 (0x11B)
        }
        b >>= 1;
    }
    return p;
}

// Mix columns transformation
void MixColumns(StateMatrix& state) {
    StateMatrix temp_state = state; // Work on a copy
    for (int c = 0; c < Nb; ++c) {
        state[0][c] = gmul(0x02, temp_state[0][c]) ^ gmul(0x03, temp_state[1][c]) ^ temp_state[2][c] ^ temp_state[3][c];
        state[1][c] = temp_state[0][c] ^ gmul(0x02, temp_state[1][c]) ^ gmul(0x03, temp_state[2][c]) ^ temp_state[3][c];
        state[2][c] = temp_state[0][c] ^ temp_state[1][c] ^ gmul(0x02, temp_state[2][c]) ^ gmul(0x03, temp_state[3][c]);
        state[3][c] = gmul(0x03, temp_state[0][c]) ^ temp_state[1][c] ^ temp_state[2][c] ^ gmul(0x02, temp_state[3][c]);
    }
}

// Add round key to state (XOR operation)
void AddRoundKey(StateMatrix& state, const ByteArray& roundKey) {
    // roundKey is 16 bytes (4 words)
    for (int c = 0; c < Nb; ++c) {
        for (int r = 0; r < 4; ++r) {
            // Key schedule word corresponds to state column
            state[r][c] ^= roundKey[c * 4 + r];
        }
    }
}

// Key Expansion function
ByteArray KeyExpansion(const ByteArray& key) {
    ByteArray expandedKey(Nb * (Nr + 1) * 4); // 4 bytes/word * Nb words/state * (Nr+1) states
    std::vector<byte> temp(4);
    int i = 0;

    // Copy the original key as the first part of the expanded key
    while (i < Nk * 4) {
        expandedKey[i] = key[i];
        i++;
    }

    i = Nk * 4; // Start generating rest of the key schedule
    while (i < Nb * (Nr + 1) * 4) {
        // Copy the previous word into temp
        for(int k=0; k<4; ++k) {
            temp[k] = expandedKey[i - 4 + k];
        }

        // Perform transformations every Nk*4 bytes (i.e., start of each Nk-word block)
        if (i % (Nk * 4) == 0) {
            // RotWord: Circular left shift
            byte holder = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = holder;

            // SubWord: Apply S-box to each byte
            for(int k=0; k<4; ++k) {
                temp[k] = sbox[temp[k]];
            }

            // XOR with Rcon
            temp[0] ^= Rcon[i / (Nk * 4)];
        }
        // For AES-256 (Nk=8), an extra SubWord step is needed here for i % (Nk*4) == 16
        // Not needed for AES-128 (Nk=4)

        // XOR temp with the word Nk positions before
        for(int k=0; k<4; ++k) {
            expandedKey[i+k] = expandedKey[i - Nk * 4 + k] ^ temp[k];
        }
        i += 4; // Move to the next word
    }

    return expandedKey;
}

// --- AES Encryption ---
ByteArray AESEncrypt(const ByteArray& plaintext, const ByteArray& key) {
    if (plaintext.size() != 16 || key.size() != 16) {
        throw std::invalid_argument("Plaintext and Key must be 16 bytes (128 bits) long");
    }

    // 1. Key Expansion
    ByteArray expandedKey = KeyExpansion(key);

    // 2. Initial State
    StateMatrix state = bytesToState(plaintext);

    // 3. Initial Round Key Addition
    ByteArray initialRoundKey(expandedKey.begin(), expandedKey.begin() + Nb*4);
    AddRoundKey(state, initialRoundKey);

    // 4. Main Rounds (Rounds 1 to Nr-1)
    for (int round = 1; round < Nr; ++round) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        // Extract round key for this round
        ByteArray currentRoundKey(expandedKey.begin() + round * Nb * 4, expandedKey.begin() + (round + 1) * Nb * 4);
        AddRoundKey(state, currentRoundKey);
    }

    // 5. Final Round (Round Nr) - No MixColumns
    SubBytes(state);
    ShiftRows(state);
    // Extract final round key
    ByteArray finalRoundKey(expandedKey.begin() + Nr * Nb * 4, expandedKey.begin() + (Nr + 1) * Nb * 4);
    AddRoundKey(state, finalRoundKey);

    // 6. Convert final state back to byte array
    return stateToBytes(state);
}

// --- Main Function ---
int main() {
    std::string M_hex = "4AEB5D62EC3B55DBF5D5A87708E2FF1E";
    std::string K_hex = "6704C20E086B3F537AE5721F486DC559";

    try {
        ByteArray plaintext = hexStringToBytes(M_hex);
        ByteArray key = hexStringToBytes(K_hex);

        std::cout << "AES-128 (10 Rounds) Encryption" << std::endl;
        printBytes(plaintext, "Plaintext (M)");
        printBytes(key,       "Key       (K)");

        ByteArray ciphertext = AESEncrypt(plaintext, key);

        printBytes(ciphertext,"Ciphertext   ");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}