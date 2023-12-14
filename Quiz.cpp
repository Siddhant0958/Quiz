#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<stdlib.h>
using namespace std;

struct Game {
    string questionText;
    vector<string> options;
    int answer;
};

void displayQuestion(const Game& q) {
    cout << q.questionText << endl;
    for (size_t i = 0; i < q.options.size(); ++i) {
        cout << i + 1 << ". " << q.options[i] << endl;
    }
}

int getUserAnswer() {
    int userAnswer;
    cout << "Enter your answer (1-4): ";
    cin >> userAnswer;
    return userAnswer;
}

bool isAnswerCorrect(const Game& q, int userAnswer) {
    return (userAnswer == q.answer);
}

int playQuiz(const vector<Game>& quiz) {
    int score = 0;

    for (const auto& question : quiz) {
        displayQuestion(question);
        int userAnswer = getUserAnswer();

        if (isAnswerCorrect(question, userAnswer)) {
            cout << "Correct!\n";
            score++;
        } else {
            cout << "Incorrect. The correct answer is: " << question.answer << ". " << question.options[question.answer - 1] << endl;
        }

        cout << "-----------------------------\n";
    }

    return score;
}

int main() {
    vector<Game> quiz;

    ifstream file("quiz_questions.txt");
    if (!file.is_open()) {
        cerr << "Error opening file: quiz_questions.txt" << endl;
        return 1;
    }

    // Reading questions from the file
    string line;
    while (getline(file, line)) {
        string questionText = line;
        vector<string> options;
        for (int i = 0; i < 4; ++i) {
            getline(file, line);
            options.push_back(line);
        }
        int answer;
        file >> answer;
        quiz.push_back({questionText, options, answer});
        file.ignore();
    }
    file.close();

    // Number of players
    int numPlayers;
    cout << "Enter the number of players: ";
    cin >> numPlayers;

    // Play quiz for each player
    vector<int> playerScores;
    for (int i = 1; i <= numPlayers; ++i) {
        cout << "\nPlayer " << i << ", ";
        int score = playQuiz(quiz);
        playerScores.push_back(score);
        cout << "Your score: " << score << " out of " << quiz.size() << "\n\n";
        system("CLS");
    }
int temp=0,index=0,j;
    // Display final scores
    cout << "Final Scores:\n";
    for (int i = 0; i < numPlayers; ++i) {
        cout << "Player " << i + 1 << ": " << playerScores[i] << " out of " << quiz.size() << "\n";
       for(j=i+1;j<numPlayers;j++){
        if( playerScores[i]<playerScores[j]){
            temp = playerScores[j];
            index=j;
        }
       }
    }
cout<<"Player"<<index<<" is the winner with score "<<temp<<endl;
    
    return 0;
}
