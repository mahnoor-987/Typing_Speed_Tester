#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

// Simple function to check how accurate the typing was
double checkTypingAccuracy(const string& original_text, const string& user_input) {
    int matches = 0;
    int shorter_length = min(original_text.size(), user_input.size());
    
    // Go through each character and see if they match
    for (int i = 0; i < shorter_length; i++) {
        if (original_text[i] == user_input[i]) {
            matches++;
        }
    }
    
    // Calculate percentage - dividing by original text length
    double accuracy_percent = (double)matches / original_text.size() * 100.0;
    return accuracy_percent;
}

int main() {
    // I picked some random sentences for the typing test
    vector<string> test_sentences = {
        "The quick brown fox jumps over the lazy dog.",
        "Typing speed tests improve your accuracy.",
        "C plus plus is a powerful programming language.", 
        "Never give up because great things take time.",
        "Data Structures and Algorithms sharpen your brain."
    };

    srand(time(0));  // seed random number generator
    string sentence_to_type = test_sentences[rand() % test_sentences.size()];

    // Print the header - maybe a bit over the top but looks nice
    cout << "==============================" << endl;
    cout << "     Typing Speed Tester       " << endl;
    cout << "==============================" << endl;
    cout << "\nType the following sentence:\n" << endl;
    cout << "\"" << sentence_to_type << "\"" << endl;

    // Record start time
    time_t start_time = time(0);

    cin.ignore(); // clear any leftover input buffer stuff
    string what_user_typed;
    getline(cin, what_user_typed);

    // Record end time  
    time_t end_time = time(0);

    double time_elapsed = difftime(end_time, start_time); // this gives us seconds
    double typing_accuracy = checkTypingAccuracy(sentence_to_type, what_user_typed);

    // Let's count words manually - just count spaces plus 1
    int word_count = 0;
    for (int i = 0; i < sentence_to_type.size(); i++) {
        if (sentence_to_type[i] == ' ' || i == sentence_to_type.size()-1) {
            word_count++;
        }
    }

    // Calculate words per minute 
    double words_per_minute = (word_count / time_elapsed) * 60.0;

    // Show the results
    cout << "\n===== Results =====" << endl;
    cout << "Time Taken: " << time_elapsed << " seconds" << endl;
    cout << "Speed: " << fixed << setprecision(2) << words_per_minute << " WPM" << endl;
    cout << "Accuracy: " << fixed << setprecision(2) << typing_accuracy << "%" << endl;

    // Save results to file - appending mode so we don't overwrite previous results
    ofstream results_file("leaderboard.txt", ios::app);
    if (results_file.is_open()) {  // Good practice to check if file opened successfully
        results_file << "Sentence: " << sentence_to_type << endl;
        results_file << "Typed: " << what_user_typed << endl;
        results_file << "WPM: " << words_per_minute << ", Accuracy: " << typing_accuracy << "%, Time: " << time_elapsed << "s" << endl;
        results_file << "------------------------------------" << endl;
        results_file.close();
        
        cout << "\nYour result has been saved in leaderboard.txt" << endl;
    } else {
        cout << "\nCouldn't save to file - but your results are shown above!" << endl;  // Just in case file writing fails
    }

    return 0;
}
