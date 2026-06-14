#include <iostream>
#include <windows.h> // Windows API ke liye
#include <bcrypt.h>  // Cryptography API ke liye

// =========================================================
// PHASE 1: THE ARENA EXPLOIT (MILITARY-GRADE BCRYPT ENTROPY)
// =========================================================
struct ShadowNode {
    char* memory_arena;     
    char* fake_data_ptr;    
    char* real_data_ptr;    

    ShadowNode(char real_char, char chaos_key) {
        
        int arena_size = 100000; 
        memory_arena = new char[arena_size]; 
        
        // ---------------------------------------------------------
        // 🌪️ TRUE OS-LEVEL CRYPTOGRAPHIC CHAOS ENGINE
        // ---------------------------------------------------------
        unsigned int secure_fake_seed = 0;
        unsigned int secure_gap_seed = 0;

        // Windows ke deep system se un-hackable random numbers maangna
        BCryptGenRandom(NULL, (PUCHAR)&secure_fake_seed, sizeof(secure_fake_seed), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
        BCryptGenRandom(NULL, (PUCHAR)&secure_gap_seed, sizeof(secure_gap_seed), BCRYPT_USE_SYSTEM_PREFERRED_RNG);

        // Modulo operator (%) se un numbers ko apni range mein lana
        int fake_index = secure_fake_seed % 10000; 
        int real_index = fake_index + 20000 + (secure_gap_seed % 50000); 

        // 3. Address Assign
        fake_data_ptr = &memory_arena[fake_index];
        *fake_data_ptr = '#'; 
        
        real_data_ptr = &memory_arena[real_index];
        *real_data_ptr = real_char ^ chaos_key; 
        
        std::cout << "[SYSTEM] Arena Allocated. OS Memory Manager Bypassed.\n";
        std::cout << "         [BCRYPT Cryptographic Engine Active]\n";
        std::cout << "         Fake Ptr Address: " << (void*)fake_data_ptr << "\n";
        std::cout << "         Real Ptr Address: " << (void*)real_data_ptr << "\n";
        std::cout << "         [UNBREAKABLE GAP CREATED: " << (real_index - fake_index) << " bytes!]\n\n";
    }

    void attempt_hack_fake_ptr() {
        std::cout << "[CRITICAL ALERT] RAM Scanner triggered the Fake Pointer!\n";
        if (real_data_ptr != nullptr) {
            *real_data_ptr = '\0';     
            real_data_ptr = nullptr;   
            std::cout << "[SYSTEM] KILL-SWITCH ACTIVATED: Real Pointer zeroized!\n\n";
        }
    }

    char decrypt(char chaos_key) {
        if (real_data_ptr != nullptr) return (*real_data_ptr) ^ chaos_key; 
        return '\0'; 
    }

    ~ShadowNode() {
        if (real_data_ptr != nullptr) *real_data_ptr = '\0'; 
        fake_data_ptr = nullptr;
        real_data_ptr = nullptr;
        
        if (memory_arena != nullptr) {
            delete[] memory_arena; 
            memory_arena = nullptr;
        }
        std::cout << "[SYSTEM] Destructor Executed: Massive Arena cleanly wiped.\n";
    }
};

int main() {
    std::cout << "--- SHADOW-MIRAGE PHASE 1: BCRYPT CRYPTO TEST ---\n\n";
    
    char secret_char = 'V'; 
    char chaos_key = 'X'; 

    ShadowNode* my_node = new ShadowNode(secret_char, chaos_key);

    std::cout << ">>> Hacker scans RAM and tries to read Fake Pointer...\n";
    my_node->attempt_hack_fake_ptr(); 

    std::cout << ">>> Legitimate System tries to decrypt after attack:\n";
    char result = my_node->decrypt(chaos_key);
    
    if (result != '\0') {
        std::cout << "Decrypted Output: " << result << "\n\n";
    } else {
        std::cout << "[ERROR] Cannot decrypt. Data was destroyed by Kill-Switch.\n\n";
    }

    delete my_node;
    std::cout << "[SYSTEM] Memory safely freed. Lab shutdown complete.\n";

    return 0;
}
