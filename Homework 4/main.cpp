#include "bowling_frame.h"
#include <random>
#include <cstdlib>
#include <iostream>

using namespace std;

std::random_device dev_main;
std::mt19937 rng_main(dev_main());

int current_game_total(Bowling_Frame * first_frame)
{
        Bowling_Frame * temp = first_frame;
        int game_total = 0;
        int temp_total = 0;
        while(temp){
			game_total += temp->frame_score();
			temp = temp->next_frame();
        }
        return game_total;
}

int main(int argc, char* argv[]){
		//Checks if there is a command line argument
        if (argc < 2){
			cout << "Usage: " << argv[0] << " <num_players>" << endl;
			return 1;
        }

        //Converts command line string argument to integer
        int num_play = std::atoi(argv[1]);

		cout << "Player count is: " << num_play << endl;

        //create array of each players frames for score
        const int NUM_FRAMES = 10;
        Bowling_Frame* players[num_play][NUM_FRAMES];
 //make frames and link frames together
        for(int p = 0; p < num_play; ++p){
			for(int f = 0; f < NUM_FRAMES; ++f){
				players[p][f] = new Bowling_Frame(f+1);
				if (f > 0) {
					players[p][f - 1]->next_frame(players[p][f]);
					players[p][f]->prev_frame(players[p][f - 1]);
				}
			}
		}

        //Simulate the games
        for (int p = 0; p < num_play; ++p){
			for (int f = 0; f < NUM_FRAMES; ++f){
				players[p][f]->update_scores(); //roll 1
				players[p][f]->update_scores(); // roll 2
				players[p][f]->update_scores(); // roll 3 (possible)
			}
        }

		// calculate the scores
        for (int p = 0; p < num_play; ++p){
			for (int f = 0; f < NUM_FRAMES; ++f){
				players[p][f]->calculate_score();
				
			}
        }

        //Displays scores per player
        for(int p = 0; p < num_play; ++p){
			cout << "Player " << p + 1 << endl;
			for (int f = 0; f < NUM_FRAMES; ++f){
				Bowling_Frame* frame = players[p][f];
				cout << "Frame " << frame->frame_num() << ":" << endl;
				cout << "Score 1: " << frame->score1() << endl;
				cout << "Score 2: " << frame->score2() << endl;
				if (frame->frame_num() == 10 && (frame->strike() || frame->spare())){
					cout << "Score 3: " << frame->score3() << endl;
				}
			}
			int cumulative = current_game_total(players[p][0]);
			cout << "Player " << p + 1 << "'s total: " << cumulative << endl << endl;
		}
        //Delete memory allocated on the heap to prevent memory leak
        for (int p = 0; p < num_play; ++p){
			for (int f = 0; f < NUM_FRAMES; ++f){
				delete players[p][f];
			}
		}
        return 0;
}
