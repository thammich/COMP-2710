#include "bowling_frame.h"
#include <random>

std::random_device dev;
std::mt19937 rng(dev());

Bowling_Frame::Bowling_Frame(int fnum)
{
	score1_ = 0;
	score2_ = 0;
	score3_ = 0;
	strike_ = false;
	spare_ = false;
	roll_one_ = false;
	roll_two_ = false;
	roll_three_ = false;
	frame_num_ = fnum;
	frame_score_ = 0;

	next_frame_ = NULL;
	prev_frame_ = NULL;

}

Bowling_Frame::~Bowling_Frame()
{
	// handled in main
}

Bowling_Frame* Bowling_Frame::next_frame() { return next_frame_; }
void Bowling_Frame::next_frame( Bowling_Frame * new_frame ) { next_frame_ = new_frame; }

Bowling_Frame* Bowling_Frame::prev_frame() { return prev_frame_; }
void Bowling_Frame::prev_frame( Bowling_Frame * new_frame ) { prev_frame_ = new_frame; }

int Bowling_Frame::score1()				{ return score1_; }
void Bowling_Frame::score1( int score )	{ score1_ = score; }

int Bowling_Frame::score2()				{ return score2_; }
void Bowling_Frame::score2( int score )	{ score2_ = score; }

int Bowling_Frame::score3()				{ return score3_; }
void Bowling_Frame::score3( int score ) { score3_ = score; }

bool Bowling_Frame::strike() 			{ return strike_; }
void Bowling_Frame::strike(bool value )	{ strike_ = value; }

bool Bowling_Frame::spare() 			{ return spare_; }
void Bowling_Frame::spare(bool value )	{ spare_ = value; }

int Bowling_Frame::frame_num()
{
	return frame_num_;
}

int Bowling_Frame::frame_score()
{
	return frame_score_; 
}

void Bowling_Frame::update_scores()
{
	std::uniform_int_distribution<std::mt19937::result_type> dist10(0, 10);
	// returns are used to exit, recursion removed because of loop in main

	// Roll One
	if (!roll_one_)
	{
		score1_ = dist10(rng);
		roll_one_ = true;

		if(score1_ == 10) strike_ = true; 
		return; 
	}

	// Roll Two
	else if (!roll_two_ )
	{
		// If Frame 10 and Roll 1 was a strike allow Roll 2 to be played
		if (frame_num_ == 10 && strike_)
		{
			score2_ = dist10(rng);
			roll_two_ = true;
			return;
		}
		// else if Roll 1 was not a strike do Roll 2
		else if (!strike_)
		{
			std::uniform_int_distribution<std::mt19937::result_type> distX(0,10 - score1_);
			score2_ = distX(rng); 
			roll_two_ = true;

			if ((score1_ + score2_) == 10) spare_ = true;
			return;
		}

		// else if roll 1 was a strike then skip roll 2 and move on
		else if (strike_)
		{
			roll_two_ = true;	
			return;
		}
	}

	// Roll Three (frame 10)
	else if (!roll_three_ && frame_num_ == 10 && (strike_ || spare_))
	{
		// Roll 1 was strike and Roll 2 was also a strike we Roll Score 3 with dist10(rng)
		if (strike_ && score2_ == 10)
		{
			score3_ = dist10(rng);
		}

		// Roll 1 was a strike and Roll 2 was only 5 OR Roll 1 and Roll 2 ended with a spare
		else
		{
			std::uniform_int_distribution<std::mt19937::result_type> distX(0,10 - score2_);
			score3_ = distX(rng);
		}

		roll_three_ = true;
		return;
	}
}

void Bowling_Frame::calculate_score()
{
	// Calculate Scores for each Frame
	// Frame 10
	if (frame_num_ == 10)
	{
		frame_score_ = score1_ + score2_ + score3_;
	}

	// frame is a strike so we add the next 2 rolls
	else if (strike_)
	{
		frame_score_ = 10;
		if (next_frame_)
		{
			frame_score_ += next_frame_->score1();

			// frame 9 special case
			if (frame_num_ == 9)
			{
				frame_score_ += next_frame_->score2();
			}

			// if next frame/roll is also a strike we go to the next next frame
			else if (next_frame_->strike() && next_frame_->next_frame())
			{
				frame_score_ += next_frame_->next_frame()->score1();
			}

			// else we add the two rolls in the next frame
			else
			{
				frame_score_ += next_frame_->score2();
			}
		}
	}

	// frame is a spare so we add the next roll
	else if (spare_)
	{
		frame_score_ = 10;
		if (next_frame_)
		{
			frame_score_ += next_frame_->score1();
		}
	}

	// no strike or spare so for example 8 points in this frame
	else
	{
		frame_score_ = score1_ + score2_;
	}
}