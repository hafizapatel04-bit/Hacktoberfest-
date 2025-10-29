#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// This function simulates the transmission of frames using a sliding window protocol
void transmission(int &i, int &N, int &tf, int &it) {
    while (i <= tf) {
        bool timeout_occurred = false;
        int frames_sent_in_window = 0;

        cout << "Sending Window starting from Frame " << i << "..." << endl;
        
        for (int k = i; k < i + N && k <= tf; k++) {
            cout << "Sending Frame " << k << "..." << endl;
            frames_sent_in_window++;
            it++;
        }

        // Simulate acknowledgment for each frame in the window
        cout << "Waiting for acknowledgments..." << endl;
        for (int k = i; k < i + N && k <= tf; k++) {
            int r = rand() % 2; // Generate a random number (0 or 1)
            
            if (r == 0) {
                // Acknowledgment received (no error)
                cout << "Acknowledgment for Frame " << k << " received." << endl;
            } else {
                // Timeout occurred (frame not received or ACK lost)
                cout << "Timeout!! Frame " << k << " was not acknowledged." << endl;
                timeout_occurred = true;
                break; // Exit the loop and retransmit the entire window
            }
        }

        if (timeout_occurred) {
            cout << "Retransmitting the entire window from Frame " << i << "..." << endl;
        } else {
            // Move the window forward by the number of frames acknowledged (which is N if no timeout)
            i += frames_sent_in_window;
        }
        cout << endl;
    }
}

int main() {
    int tf; // Total number of frames
    int N;  // Window size
    int i = 1; // Current frame number (window start)
    int it = 0; // Total number of frames sent and re-sent

    srand(time(NULL)); // Seed the random number generator

    cout << "Enter the Total number of frames: ";
    cin >> tf;
    
    cout << "Enter the Window Size: ";
    cin >> N;

    transmission(i, N, tf, it);

    cout << "Total number of frames which were sent and re-sent are: " << it << endl;

    return 0;
}
