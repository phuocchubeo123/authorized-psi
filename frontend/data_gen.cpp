#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <algorithm>
#include "cryptoTools/Common/CLP.h"

int main(int argc, char** argv) {
    /*
    Read the command line arguments:
    argv[1]: sender_file
    argv[2]: sender_size
    argv[3]: receiver_file
    argv[4]: receiver_size
    argv[5]: intersection_size
    */

   std::cout << "Starting...\n";

   if (argc != 6) {
       std::cout << "Usage: " << argv[0] << " <sender_file> <sender_size> <receiver_file> <receiver_size> <intersection_size>\n";
       return 1;
   }

    std::ofstream sender_file(argv[1]);
    std::ofstream receiver_file(argv[3]);

    oc::u64 sender_size = std::stoull(argv[2]);
    std::cout << "Sender size: " << sender_size << "\n";
    oc::u64 receiver_size = std::stoull(argv[4]);
    std::cout << "Receiver size: " << receiver_size << "\n";
    oc::u64 intersection_size = std::stoull(argv[5]);

    // for (oc::u64 i = 0; i < num_elements; ++i)
    //     // Write 32 byte random hex strings to the file
    //     file << oc::block(oc::sysRandomSeed()) << "\n";

    // Create an array of random intersection_size elements
    std::vector<oc::block> intersection(intersection_size);
    for (oc::u64 i = 0; i < intersection_size; ++i) {
        intersection[i] = oc::block(oc::sysRandomSeed());
    }

    // Create an array of random sender_size elements, which the first intersection_size elements are the same as the intersection array
    std::cout << "Creating sender array of size " << sender_size << "...\n";
    std::vector<oc::block> sender(sender_size);
    for (oc::u64 i = 0; i < sender_size; ++i) {
        if (i < intersection_size) {
            sender[i] = intersection[i];
        } else {
            sender[i] = oc::block(oc::sysRandomSeed());
        }
    }

    // Create similar array for the receiver
    std::cout << "Creating receiver array of size " << receiver_size << "...\n";
    std::vector<oc::block> receiver(receiver_size);
    for (oc::u64 i = 0; i < receiver_size; ++i) {
        if (i < intersection_size) {
            receiver[i] = intersection[i];
        } else {
            receiver[i] = oc::block(oc::sysRandomSeed());
        }
    }

    // Shuffle the sender and receiver arrays
    std::cout << "Shuffling sender and receiver array...\n";

    auto rng = std::default_random_engine {};
    std::shuffle(sender.begin(), sender.end(), rng);
    std::shuffle(receiver.begin(), receiver.end(), rng);

    // Write the sender and receiver arrays to the files
    std::cout << "Writing sender and receiver arrays to files...\n";
    for (oc::u64 i = 0; i < sender_size; ++i) {
        sender_file << sender[i] << "\n";
    }
    for (oc::u64 i = 0; i < receiver_size; ++i) {
        receiver_file << receiver[i] << "\n";
    }

    return 0;
}