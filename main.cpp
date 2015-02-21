#define CPP11
#define BRUTFORCE_DEEP_MAX 1

#ifdef _WIN32
#define SIMU
#endif

// cout, cin
#include <iostream>
// string
#include <string>
// vector
#include <vector>
// list
#include <list>
// queue
#include <queue>
// greater
#include <functional>
// setw
#include <iomanip>
// shared_ptr
#include <memory>
// numeric_limits
#include <limits>

using namespace std;
#ifdef CPP11
#include <chrono>
using namespace std::chrono;
#else
using namespace std::tr1;
#endif

enum EDirection
{
	eLeft = 0,
	eRight = 1,
	eUp = 2,
	eDown
};

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/
class Wall
{
public:
	Wall(int aWidth, int aHeight)
		: mWidth(aWidth)
		, mHeight(aHeight)
		, mVWallVect(mWidth * mHeight, 0)
		, mHWallVect(mWidth * mHeight, 0)
		, mVSimuWallVect(mWidth * mHeight, 0)
		, mHSimuWallVect(mWidth * mHeight, 0)
	{
	}

	~Wall(void)
	{
	}

	void addWall(int aWallX, int aWallY, char aWallOrientation)
	{
		int lWallPos = aWallY*mWidth + aWallX;
		if (aWallOrientation == 'H') {
			int lWallPos2 = lWallPos + 1;
			mHWallVect[lWallPos] = 1;
			mHWallVect[lWallPos2] = 2;
		} else {
			int lWallPos2 = lWallPos + mWidth;
			mVWallVect[lWallPos] = 1;
			mVWallVect[lWallPos2] = 2;
		}
	}

	void clearSimuWall(void)
	{
		fill(mVSimuWallVect.begin(), mVSimuWallVect.end(), 0);
		fill(mHSimuWallVect.begin(), mHSimuWallVect.end(), 0);
	}

	void addSimuWall(int aWallX, int aWallY, char aWallOrientation)
	{
		int lWallPos = aWallY*mWidth + aWallX;
		if (aWallOrientation == 'H') {
			int lWallPos2 = lWallPos + 1;
			mHSimuWallVect[lWallPos] = 1;
			mHSimuWallVect[lWallPos2] = 2;
		} else {
			int lWallPos2 = lWallPos + mWidth;
			mVSimuWallVect[lWallPos] = 1;
			mVSimuWallVect[lWallPos2] = 2;
		}
	}

	void removeSimuWall(int aWallX, int aWallY, char aWallOrientation)
	{
		int lWallPos = aWallY*mWidth + aWallX;
		if (aWallOrientation == 'H') {
			int lWallPos2 = lWallPos + 1;
			mHSimuWallVect[lWallPos] = 0;
			mHSimuWallVect[lWallPos2] = 0;
		} else {
			int lWallPos2 = lWallPos + mWidth;
			mVSimuWallVect[lWallPos] = 0;
			mVSimuWallVect[lWallPos2] = 0;
		}
	}

	bool isWallValid(int aWallX, int aWallY, char aWallOrientation) const
	{
		bool lIsResult = false;
		int lWallPos = aWallY*mWidth + aWallX;
		if (aWallOrientation == 'H') {
			lIsResult = (0 <= aWallX) && (aWallX < (mWidth - 1)) && (0 < aWallY) && (aWallY < mHeight);
			if (lIsResult) {
				int lWallPos2 = lWallPos + 1;
				lIsResult = (0 >= mHWallVect[lWallPos]) && (0 >= mHSimuWallVect[lWallPos]);
				lIsResult &= (0 >= mHWallVect[lWallPos2]) && (0 >= mHSimuWallVect[lWallPos2]);
				lIsResult &= (1 >= mVWallVect[lWallPos2]) && (1 >= mVSimuWallVect[lWallPos2]);
			}
		} else {
			lIsResult = (0 < aWallX) && (aWallX < mWidth) && (0 <= aWallY) && (aWallY < (mHeight - 1));
			if (lIsResult) {
				int lWallPos2 = lWallPos + mWidth;
				lIsResult = (0 >= mVWallVect[lWallPos]) && (0 >= mVSimuWallVect[lWallPos]);
				lIsResult &= (0 >= mVWallVect[lWallPos2]) && (0 >= mVSimuWallVect[lWallPos2]);
				lIsResult &= (1 >= mHWallVect[lWallPos2]) && (1 >= mHSimuWallVect[lWallPos2]);
			}
		}
		return lIsResult;
	}

	bool isWallContiguous(int aWallX, int aWallY, char aWallOrientation) const
	{
		bool lIsResult = false;
		int lWallPos = aWallY*mWidth + aWallX;
		if (aWallOrientation == 'H') {
			lIsResult = ((0 >= aWallX) || (aWallX >= (mWidth - 2))
				|| (0 < mVWallVect[lWallPos]) || (0 < mVSimuWallVect[lWallPos])
				|| (0 < mVWallVect[lWallPos + 1]) || (0 < mVSimuWallVect[lWallPos + 1])
				|| (0 < mVWallVect[lWallPos + 2]) || (0 < mVSimuWallVect[lWallPos + 2])
				|| (0 < mVWallVect[lWallPos - mWidth]) || (0 < mVSimuWallVect[lWallPos - mWidth])
				|| (0 < mVWallVect[lWallPos + 1 - mWidth]) || (0 < mVSimuWallVect[lWallPos + 1 - mWidth])
				|| (0 < mVWallVect[lWallPos + 2 - mWidth]) || (0 < mVSimuWallVect[lWallPos + 2 - mWidth])
				|| (0 < mHWallVect[lWallPos - 1]) || (0 < mHSimuWallVect[lWallPos - 1])
				|| (0 < mHWallVect[lWallPos + 2]) || (0 < mHSimuWallVect[lWallPos + 2]));
		} else {
			int lWallOffset2 = mWidth * 2;
			lIsResult = ((0 >= aWallY) || (aWallY >= (mHeight - 2))
				|| (0 < mHWallVect[lWallPos]) || (0 < mHSimuWallVect[lWallPos])
				|| (0 < mHWallVect[lWallPos + mWidth]) || (0 < mHSimuWallVect[lWallPos + mWidth])
				|| (0 < mHWallVect[lWallPos + lWallOffset2]) || (0 < mHSimuWallVect[lWallPos + lWallOffset2])
				|| (0 < mHWallVect[lWallPos - 1]) || (0 < mHSimuWallVect[lWallPos - 1])
				|| (0 < mHWallVect[lWallPos + mWidth - 1]) || (0 < mHSimuWallVect[lWallPos + mWidth - 1])
				|| (0 < mHWallVect[lWallPos + lWallOffset2 - 1]) || (0 < mHSimuWallVect[lWallPos + lWallOffset2 - 1])
				|| (0 < mVWallVect[lWallPos - mWidth]) || (0 < mVSimuWallVect[lWallPos - mWidth])
				|| (0 < mVWallVect[lWallPos + lWallOffset2]) || (0 < mVSimuWallVect[lWallPos + lWallOffset2]));
		}
		return lIsResult;
	}

	bool isLeftValid(int aX, int aY) const
	{
		bool lIsResult = (0 < aX) && (aX < mWidth) && (0 <= aY) && (aY < mHeight);
		if (lIsResult) {
			int lWallPos = aY*mWidth + aX;
			lIsResult = (0 >= mVWallVect[lWallPos]) && (0 >= mVSimuWallVect[lWallPos]);
		}
		return lIsResult;
	}

	bool isUpValid(int aX, int aY) const
	{
		bool lIsResult = (0 <= aX) && (aX < mWidth) && (0 < aY) && (aY < mHeight);
		if (lIsResult) {
			int lWallPos = aY*mWidth + aX;
			lIsResult = (0 >= mHWallVect[lWallPos]) && (0 >= mHSimuWallVect[lWallPos]);
		}
		return lIsResult;
	}

	bool isRightValid(int aX, int aY) const
	{
		aX++;
		bool lIsResult = (0 < aX) && (aX < mWidth) && (0 <= aY) && (aY < mHeight);
		if (lIsResult) {
			int lWallPos = aY*mWidth + aX;
			lIsResult = (0 >= mVWallVect[lWallPos]) && (0 >= mVSimuWallVect[lWallPos]);
		}
		return lIsResult;
	}

	bool isDownValid(int aX, int aY) const
	{
		aY++;
		bool lIsResult = (0 <= aX) && (aX < mWidth) && (0 < aY) && (aY < mHeight);
		if (lIsResult) {
			int lWallPos = aY*mWidth + aX;
			lIsResult = (0 >= mHWallVect[lWallPos]) && (0 >= mHSimuWallVect[lWallPos]);
		}
		return lIsResult;
	}
	void dumpWalls(void) const
	{
		cerr << "Walls" << endl;
		for (int lY = 0; lY < mHeight; lY++) {
			cerr << "#";
			for (int lX = 0; lX < mWidth; lX++) {
				int lWallPos = lY*mWidth + lX;
				bool lIsHValid = (0 < mHWallVect[lWallPos]) || (0 < mHSimuWallVect[lWallPos]);
				bool lIsVValid = (0 < mVWallVect[lWallPos]) || (0 < mVSimuWallVect[lWallPos]);
				if (lIsHValid && lIsVValid) {
					cerr << "+ ";
				} else if (lIsHValid) {
					cerr << "- ";
				} else if (lIsVValid) {
					cerr << "| ";
				} else {
					cerr << "  ";
				}
			}
			cerr << "#" << endl;
		}
	}
	void dumpContiguousWalls(void) const
	{
		cerr << "Contiguous walls" << endl;
		for (int lY = 0; lY < mHeight; lY++) {
			for (int lX = 0; lX < mWidth; lX++) {
				if (isWallValid(lX, lY, 'H')) {
					cerr << (isWallContiguous(lX, lY, 'H') ? "H" : "-");
				} else {
					cerr << "-";
				}
				if (isWallValid(lX, lY, 'V')) {
					cerr << (isWallContiguous(lX, lY, 'V') ? "V" : "-");
				} else {
					cerr << "-";
				}
				cerr << " ";
			}
			cerr << endl;
		}
	}

private:
	int mWidth;
	int mHeight;
	vector<int> mVWallVect;
	vector<int> mHWallVect;
	vector<int> mVSimuWallVect;
	vector<int> mHSimuWallVect;
};

class Player
{
public:
	typedef shared_ptr<Player> Ptr;
	typedef list<EDirection> StepList;
	typedef vector<int> PathfindingVect;
	typedef pair<int, pair<int, int> > PathfindingElem;
	typedef priority_queue<PathfindingElem, vector<PathfindingElem>, greater<PathfindingElem> > PathfindingQueue;

public:
	Player(int aWidth, int aHeight, Wall* apWall, EDirection aStartPos)
		: mWidth(aWidth)
		, mHeight(aHeight)
		, mpWall(apWall)
		, mStartPos(aStartPos)
		, mCurrentPosX(-1)
		, mCurrentPosY(-1)
		, mPathfindingVect(aWidth * aHeight, -1)
		, mPathQueue()
	{
	}

	~Player(void)
	{
	}

	void setCurrentPosition(int aCurrentX, int aCurrentY)
	{
		mCurrentPosX = aCurrentX;
		mCurrentPosY = aCurrentY;
	}

	inline int currentX(void) const
	{
		return mCurrentPosX;
	}

	inline int currentY(void) const
	{
		return mCurrentPosY;
	}

	void findBestDirection(StepList& aStepList, bool abDump = false)
	{
		int lBestValue = -1;
		int lBestX = -1;
		int lBestY = -1;
		computePathfinding(lBestValue, lBestX, lBestY);
		cerr << "Best destination [" << lBestX << "; " << lBestY << "] in " << lBestValue << " steps" << endl;
		while (lBestValue > 0) {
			lBestValue--;
			if (mpWall->isLeftValid(lBestX, lBestY) && (get(lBestX - 1, lBestY) == lBestValue)) {
				lBestX--;
				aStepList.push_front(eRight);
			} else if (mpWall->isRightValid(lBestX, lBestY) && (get(lBestX + 1, lBestY) == lBestValue)) {
				lBestX++;
				aStepList.push_front(eLeft);
			} else if (mpWall->isUpValid(lBestX, lBestY) && (get(lBestX, lBestY - 1) == lBestValue)) {
				lBestY--;
				aStepList.push_front(eDown);
			} else if (mpWall->isDownValid(lBestX, lBestY) && (get(lBestX, lBestY + 1) == lBestValue)) {
				lBestY++;
				aStepList.push_front(eUp);
			}
		}
		if (abDump) {
			dumpPath();
		}
	}

	void findBestStep(int& aBestValue, bool abDump = false)
	{
		int lBestX = -1;
		int lBestY = -1;
		computePathfinding(aBestValue, lBestX, lBestY);
		if (abDump) {
			dumpPath();
		}
	}

	void findBestNextStep(int& aBestValue, int& aBestX, int& aBestY, bool abDump = false)
	{
		int lBestValue = -1;
		computePathfinding(lBestValue, aBestX, aBestY);
		aBestValue = lBestValue;
		while (lBestValue > 1) {
			lBestValue--;
			if (mpWall->isLeftValid(aBestX, aBestY) && (get(aBestX - 1, aBestY) == lBestValue)) {
				aBestX--;
			} else if (mpWall->isRightValid(aBestX, aBestY) && (get(aBestX + 1, aBestY) == lBestValue)) {
				aBestX++;
			} else if (mpWall->isUpValid(aBestX, aBestY) && (get(aBestX, aBestY - 1) == lBestValue)) {
				aBestY--;
			} else if (mpWall->isDownValid(aBestX, aBestY) && (get(aBestX, aBestY + 1) == lBestValue)) {
				aBestY++;
			}
		}
		if (abDump) {
			dumpPath();
		}
	}

private:
	void computePathfinding(int& aBestValue, int& aBestX, int& aBestY)
	{
		aBestValue = -1;
		aBestX = -1;
		aBestY = -1;
		int lCurrentStep = 0;
		fill(mPathfindingVect.begin(), mPathfindingVect.end(), -1);
		switch (mStartPos) {
		case eLeft:
			lCurrentStep += mWidth - mCurrentPosX - 1;
			break;
		case eRight:
			lCurrentStep += mCurrentPosX;
			break;
		case eUp:
			lCurrentStep += mHeight - mCurrentPosY - 1;
			break;
		case eDown:
			lCurrentStep += mCurrentPosY;
			break;
		}
		mPathQueue.push(make_pair(lCurrentStep, make_pair(mCurrentPosX, mCurrentPosY)));
		bool lIsLoopDone = mPathQueue.empty();
		while (!lIsLoopDone) {
			lCurrentStep = mPathQueue.top().first;
			int lCurrentX = mPathQueue.top().second.first;
			int lCurrentY = mPathQueue.top().second.second;
			mPathQueue.pop();
			if (get(lCurrentX, lCurrentY) < 0) {
				// Reverse heuristic
				switch (mStartPos) {
				case eLeft:
					lCurrentStep -= mWidth - lCurrentX - 1;
					lIsLoopDone = (lCurrentX >= (mWidth - 1));
					break;
				case eRight:
					lCurrentStep -= lCurrentX;
					lIsLoopDone = (lCurrentX <= 0);
					break;
				case eUp:
					lCurrentStep -= mHeight - lCurrentY - 1;
					lIsLoopDone = (lCurrentY >= (mHeight - 1));
					break;
				case eDown:
					lCurrentStep -= lCurrentY;
					lIsLoopDone = (lCurrentY <= 0);
					break;
				}
				mPathfindingVect[lCurrentY*mWidth + lCurrentX] = lCurrentStep;
				if (lIsLoopDone) {
					aBestValue = lCurrentStep;
					aBestX = lCurrentX;
					aBestY = lCurrentY;
				} else {
					lCurrentStep++;
					for (int lDirection = eLeft; lDirection <= eDown; lDirection++) {
						int lIsValid = false;
						int lNewX = lCurrentX;
						int lNewY = lCurrentY;
						int lNewStep = lCurrentStep;
						// Reverse heuristic
						switch (lDirection) {
						case eLeft:
							lIsValid = mpWall->isLeftValid(lCurrentX, lCurrentY);
							lNewX--;
							break;
						case eRight:
							lIsValid = mpWall->isRightValid(lCurrentX, lCurrentY);
							lNewX++;
							break;
						case eUp:
							lIsValid = mpWall->isUpValid(lCurrentX, lCurrentY);
							lNewY--;
							break;
						case eDown:
							lIsValid = mpWall->isDownValid(lCurrentX, lCurrentY);
							lNewY++;
							break;
						}
						// Heuristic
						switch (mStartPos) {
						case eLeft:
							lNewStep += mWidth - lNewX - 1;
							break;
						case eRight:
							lNewStep += lNewX;
							break;
						case eUp:
							lNewStep += mHeight - lNewY - 1;
							break;
						case eDown:
							lNewStep += lNewY;
							break;
						}
						if (lIsValid) {
							mPathQueue.push(make_pair(lNewStep, make_pair(lNewX, lNewY)));
						}
					}
				}
			}
			lIsLoopDone |= mPathQueue.empty();
		}
		while (!mPathQueue.empty()) {
			mPathQueue.pop();
		}
	}

	inline int get(int aX, int aY) const
	{
		return mPathfindingVect[aY*mWidth + aX];
	}

	void dumpPath(void) const
	{
		for (int lY = 0; lY < mHeight; lY++) {
			for (int lX = 0; lX < mWidth; lX++) {
				cerr << setw(2) << get(lX, lY) << " ";
			}
			cerr << endl;
		}
	}

private:
	int mWidth;
	int mHeight;
	Wall* mpWall;
	EDirection mStartPos;
	int mCurrentPosX;
	int mCurrentPosY;
	PathfindingVect mPathfindingVect;
	PathfindingQueue mPathQueue;
};

class Scenario
{
public:
	Scenario(int aWidth, int aHeight, int aPlayerCount, int aMyId)
		: mWidth(aWidth)
		, mHeight(aHeight)
		, mPlayerCount(aPlayerCount)
		, mMyId(aMyId)
		, mOpenDoorCount((aPlayerCount == 2) ? 0 : 0)
		, mMyWallLeft(0)
		, mEnnemyWallLeft(0)
		, mWall(aWidth, aHeight)
		, mPlayerVect()
	{
		mPlayerVect.reserve(aPlayerCount);
		for (int lId = 0; lId < mPlayerCount; lId++) {
			mPlayerVect.push_back(Player::Ptr(new Player(aWidth, aHeight, &mWall, (EDirection)lId)));
		}
	}

	~Scenario(void)
	{
	}

	void initIteration(void)
	{
		mMyWallLeft = 0;
		mEnnemyWallLeft = 0;
	}

	void updatePlayerData(int aId, int aCurrentX, int aCurrentY, int aWallsLeft)
	{
		mPlayerVect[aId]->setCurrentPosition(aCurrentX, aCurrentY);
		if (aId == mMyId) {
			mMyWallLeft = aWallsLeft;
		} else {
			mEnnemyWallLeft += aWallsLeft;
		}
	}

	void updateWallData(int aWallX, int aWallY, char aWallOrientation)
	{
		mWall.addWall(aWallX, aWallY, aWallOrientation);
	}

	void runIteration(void)
	{
#ifdef CPP11
		time_point<high_resolution_clock> lTimeStart, lTimeEnd;
		lTimeStart = high_resolution_clock::now();
#endif
		if (mEnnemyWallLeft <= 0) {
			mOpenDoorCount = 0;
		}

		int lMyScore = 0;
		int lBaddestEnemyScore = numeric_limits<int>::max();
		int lBaddestEnemyId = -1;
		for (int lId = 0; lId < mPlayerCount; lId++) {
			Player::Ptr lPlayerPtr = mPlayerVect[lId];
			if (lPlayerPtr->currentX() >= 0) {
				int lBestValue = -1;
				lPlayerPtr->findBestStep(lBestValue, false);
				if (lBestValue <= 0) {
					break;
				} else if (lId == mMyId) {
					//cerr << "My position: [" << lPlayerPtr->currentX() << "; " << lPlayerPtr->currentY() << "] Score: " << lBestValue << endl;
					lMyScore = lBestValue;
				} else {
					//cerr << "Enemy position: [" << lPlayerPtr->currentX() << "; " << lPlayerPtr->currentY() << "] Score: " << lBestValue << endl;
					if (lBestValue < lBaddestEnemyScore) {
						lBaddestEnemyScore = lBestValue;
						lBaddestEnemyId = lId;
					}
				}
			}
		}
		//mWall.dumpWalls();

		bool lIsReponse = false;
		if (!lIsReponse) {
			if (mPlayerCount == 2) {
				lIsReponse = applyPatternBrutForce(lMyScore, lBaddestEnemyScore, lBaddestEnemyId);
			} else {
				lIsReponse = applyPatternScoredSelection(lMyScore, lBaddestEnemyScore, lBaddestEnemyId);
			}
		}
		if (!lIsReponse) {
			lIsReponse = applyPatternOpenDoor(lMyScore);
		}
		if (!lIsReponse) {
			lIsReponse = applyPatternMove();
		}
#ifdef CPP11
		lTimeEnd = high_resolution_clock::now();
		long long lElapsedMilli = duration_cast<milliseconds>(lTimeEnd - lTimeStart).count();
		cerr << "ExecTime: " << lElapsedMilli << "ms" << endl;
#endif
	}

private:
	bool applyPatternScoredSelection(int aMyScore, int aBaddestEnemyScore, int aBaddestEnemyId)
	{
		bool lIsReponse = (mMyWallLeft > mOpenDoorCount);
		int lBestScoreX = -1;
		int lBestScoreY = -1;
		char lBestScoreH = '?';
		if (lIsReponse) {
			int lCurrentScore = (1000 / aMyScore) - (1000 / aBaddestEnemyScore);
			int lBestScore = lCurrentScore;
			for (int lY = 0; lY < mHeight; lY++) {
				for (int lX = 0; lX < mWidth; lX++) {
					for (int lH = 0; lH < 2; lH++) {
						if (mWall.isWallValid(lX, lY, lH ? 'H' : 'V')) {
							mWall.addSimuWall(lX, lY, lH ? 'H' : 'V');
							int lScore = 0;
							for (int lId = 0; lId < mPlayerCount; lId++) {
								Player::Ptr lPlayerPtr = mPlayerVect[lId];
								if (lPlayerPtr->currentX() >= 0) {
									int lBestValue = -1;
									lPlayerPtr->findBestStep(lBestValue);
									if (lBestValue <= 0) {
										lScore = numeric_limits<int>::min();
										break;
									} else if (lId == mMyId) {
										lScore += 1000 / lBestValue;
									} else if (lId == aBaddestEnemyId) {
										lScore -= 1000 / lBestValue;
									}
								}
							}
							if (lScore > lBestScore) {
								//cerr << "BestScore: [" << lX << "; " << lY << "] Score: " << lScore << endl;
								lBestScore = lScore;
								lBestScoreX = lX;
								lBestScoreY = lY;
								lBestScoreH = lH ? 'H' : 'V';
							} else if (lScore == lBestScore) {
								Player::Ptr lPlayerPtr = mPlayerVect[aBaddestEnemyId];
								int lBestDistX = (lPlayerPtr->currentX() - lBestScoreX);
								lBestDistX *= lBestDistX;
								int lBestDistY = (lPlayerPtr->currentY() - lBestScoreY);
								lBestDistY *= lBestDistY;
								int lBestDist = lBestDistX + lBestDistY;
								int lCurrentDistX = (lPlayerPtr->currentX() - lX);
								lCurrentDistX *= lCurrentDistX;
								int lCurrentDistY = (lPlayerPtr->currentY() - lY);
								lCurrentDistY *= lCurrentDistY;
								int lCurrentDist = lCurrentDistX + lCurrentDistY;
								if (lCurrentDist > lBestDist) {
									//cerr << "BestScore: [" << lX << "; " << lY << "] Score: " << lScore << endl;
									lBestScore = lScore;
									lBestScoreX = lX;
									lBestScoreY = lY;
									lBestScoreH = lH ? 'H' : 'V';
								}
							}
							mWall.clearSimuWall();
						}
					}
				}
			}
			lIsReponse = (lBestScore > (lCurrentScore + ((mPlayerCount == 2) ? 50 : 200)));
		}
		if (lIsReponse) {
			lIsReponse = applyPatternWall(lBestScoreX, lBestScoreY, lBestScoreH);
		}
		return lIsReponse;
	}

	bool applyPatternBrutForce(int aMyScore, int aBaddestEnemyScore, int aBaddestEnemyId)
	{
		bool lIsReponse = (mMyWallLeft > mOpenDoorCount);
		int lBestScoreX = -1;
		int lBestScoreY = -1;
		char lBestScoreH = '?';
		int lBadScoreX = -1;
		int lBadScoreY = -1;
		char lBadScoreH = '?';
		if (lIsReponse) {
			int lCurrentScore = (1000 / aMyScore) - (1000 / aBaddestEnemyScore);
			int lBestScore = lCurrentScore;
			int lBadScore = lCurrentScore;
			long long lRecurseCount = 0;
			bool lIsValidWay = recursePatternBrutForce(aBaddestEnemyId, min(mMyWallLeft - mOpenDoorCount, BRUTFORCE_DEEP_MAX), lBestScore, lBestScoreX, lBestScoreY, lBestScoreH, lBadScore, lBadScoreX, lBadScoreY, lBadScoreH, lRecurseCount);
			lBestScore -= lCurrentScore;
			lBadScore -= lCurrentScore;
			lBestScore /= mPlayerCount - 1;
			lBadScore /= mPlayerCount - 1;
			cerr << "BrutForce RecurceCount: " << lRecurseCount << " CurrentScore: " << lCurrentScore << " BestScore: " << lBestScore << " BadScore: " << lBadScore << endl;
			if (mPlayerCount == 2) {
				lIsReponse = (lBadScore <= -50) && (-lBadScore >= lBestScore);
			} else {
				lIsReponse = (lBadScore <= -100) && (-lBadScore >= lBestScore);
			}
			if (lIsReponse) {
				cerr << "Blocker" << endl;
				lIsReponse = applyPatternBlocker(aBaddestEnemyId, lBadScoreX, lBadScoreY, lBadScoreH, lBestScoreX, lBestScoreY, lBestScoreH);
			}
			if (!lIsReponse) {
				if (mPlayerCount == 2) {
					lIsReponse = lIsValidWay && (lBestScore >= 10) && ((lCurrentScore < 0) || (lBestScore >= 50));
				} else {
					lIsReponse = lIsValidWay && (lBestScore >= 100);
				}
			}
		}
		if (lIsReponse) {
			lIsReponse = applyPatternWall(lBestScoreX, lBestScoreY, lBestScoreH);
		}
		return lIsReponse;
	}

	bool applyPatternBlocker(int aBaddestEnemyId, int aWallX, int aWallY, char aWallOrientation, int& aBestScoreX, int& aBestScoreY, char& aBestScoreH)
	{
		bool lIsReponse = false;
		int BestScore = numeric_limits<int>::min();;
		for (int lY = 0; lY < mHeight; lY++) {
			for (int lX = 0; lX < mWidth; lX++) {
				for (int lH = 0; lH < 2; lH++) {
					if (mWall.isWallValid(lX, lY, lH ? 'H' : 'V')) {
						mWall.addSimuWall(lX, lY, lH ? 'H' : 'V');
						if (!mWall.isWallValid(aWallX, aWallY, aWallOrientation)) {
							bool lIsValidNewWay = true;
							int lScore = 0;
							for (int lId = 0; lIsValidNewWay && (lId < mPlayerCount); lId++) {
								Player::Ptr lPlayerPtr = mPlayerVect[lId];
								if (lPlayerPtr->currentX() >= 0) {
									int lBestValue = -1;
									int lBestX = -1;
									int lBestY = -1;
									lPlayerPtr->findBestNextStep(lBestValue, lBestX, lBestY);
									if (lBestValue <= 0) {
										lIsValidNewWay = false;
									} else if (lId == mMyId) {
										lScore += 1000 / lBestValue;
									} else if (lId == aBaddestEnemyId) {
										lScore -= 1000 / lBestValue;
									}
								}
							}
							if (lIsValidNewWay) {
								if (lScore > BestScore) {
									BestScore = lScore;
									aBestScoreX = lX;
									aBestScoreY = lY;
									aBestScoreH = lH ? 'H' : 'V';
									lIsReponse = true;
								}
							}
						}
						mWall.removeSimuWall(lX, lY, lH ? 'H' : 'V');
					}
				}
			}
		}
		return lIsReponse;
	}

	bool recursePatternBrutForce(int aBaddestEnemyId, int aNbWallLeft, int& aBestScore, int& aBestScoreX, int& aBestScoreY, char& aBestScoreH, int& aBadScore, int& aBadScoreX, int& aBadScoreY, char& aBadScoreH, long long& aRecurseCount)
	{
		bool lIsValidWay = false;
		aNbWallLeft--;
		aRecurseCount++;
		pair<int, int> lPlayerPositionBackupVect[3];
		for (int lId = 0; lId < mPlayerCount; lId++) {
			Player::Ptr lPlayerPtr = mPlayerVect[lId];
			lPlayerPositionBackupVect[lId].first = lPlayerPtr->currentX();
			lPlayerPositionBackupVect[lId].second = lPlayerPtr->currentY();
		}
		//cerr << "recursePatternBrutForce : " << aRecurseCount << endl;
		for (int lY = 0; lY < mHeight; lY++) {
			for (int lX = 0; lX < mWidth; lX++) {
				for (int lH = 0; lH < 2; lH++) {
					if (mWall.isWallValid(lX, lY, lH ? 'H' : 'V') && ((aRecurseCount <= 1) || mWall.isWallContiguous(lX, lY, lH ? 'H' : 'V'))) {
						mWall.addSimuWall(lX, lY, lH ? 'H' : 'V');
						bool lIsValidNewWay = true;
						int lScore = 0;
						int lScoreX = -1;
						int lScoreY = -1;
						char lScoreH = '?';
						int lBScore = 0;
						int lBScoreX = -1;
						int lBScoreY = -1;
						char lBScoreH = '?';
						for (int lId = 0; lIsValidNewWay && (lId < mPlayerCount); lId++) {
							Player::Ptr lPlayerPtr = mPlayerVect[lId];
							lPlayerPtr->setCurrentPosition(lPlayerPositionBackupVect[lId].first, lPlayerPositionBackupVect[lId].second);
							if (lPlayerPtr->currentX() >= 0) {
								int lBestValue = -1;
								int lBestX = -1;
								int lBestY = -1;
								lPlayerPtr->findBestNextStep(lBestValue, lBestX, lBestY);
								if (lBestValue <= 0) {
									lIsValidNewWay = false;
								} else if (lId == mMyId) {
									lScore += 1000 / lBestValue;
								} else if (lId == aBaddestEnemyId) {
									lScore -= 1000 / lBestValue;
								}
								lPlayerPtr->setCurrentPosition(lBestX, lBestY);
							}
						}
						if (lIsValidNewWay) {
							if (lScore > aBestScore) {
								aBestScore = lScore;
								aBestScoreX = lX;
								aBestScoreY = lY;
								aBestScoreH = lH ? 'H' : 'V';
								lIsValidWay = true;
							} else if (lScore == aBestScore) {
								Player::Ptr lPlayerPtr = mPlayerVect[aBaddestEnemyId];
								int lBestDistX = (lPlayerPtr->currentX() - aBestScoreX);
								lBestDistX *= lBestDistX;
								int lBestDistY = (lPlayerPtr->currentY() - aBestScoreY);
								lBestDistY *= lBestDistY;
								int lBestDist = lBestDistX + lBestDistY;
								int lCurrentDistX = (lPlayerPtr->currentX() - lX);
								lCurrentDistX *= lCurrentDistX;
								int lCurrentDistY = (lPlayerPtr->currentY() - lY);
								lCurrentDistY *= lCurrentDistY;
								int lCurrentDist = lCurrentDistX + lCurrentDistY;
								if (lCurrentDist > lBestDist) {
									//cerr << "BestScore: [" << lX << "; " << lY << "] Score: " << lScore << endl;
									aBestScore = lScore;
									aBestScoreX = lX;
									aBestScoreY = lY;
									aBestScoreH = lH ? 'H' : 'V';
									lIsValidWay = true;
								}
							}
							if (lScore < aBadScore) {
								aBadScore = lScore;
								aBadScoreX = lX;
								aBadScoreY = lY;
								aBadScoreH = lH ? 'H' : 'V';
							}
							if (aNbWallLeft > 0) {
								if (recursePatternBrutForce(aBaddestEnemyId, aNbWallLeft, lScore, lScoreX, lScoreY, lScoreH, lBScore, lBScoreX, lBScoreY, lBScoreH, aRecurseCount)) {
									if (lScore > aBestScore) {
										aBestScore = lScore;
										aBestScoreX = lX;
										aBestScoreY = lY;
										aBestScoreH = lH ? 'H' : 'V';
										lIsValidWay = true;
									} else if (lScore == aBestScore) {
										Player::Ptr lPlayerPtr = mPlayerVect[aBaddestEnemyId];
										int lBestDistX = (lPlayerPtr->currentX() - aBestScoreX);
										lBestDistX *= lBestDistX;
										int lBestDistY = (lPlayerPtr->currentY() - aBestScoreY);
										lBestDistY *= lBestDistY;
										int lBestDist = lBestDistX + lBestDistY;
										int lCurrentDistX = (lPlayerPtr->currentX() - lX);
										lCurrentDistX *= lCurrentDistX;
										int lCurrentDistY = (lPlayerPtr->currentY() - lY);
										lCurrentDistY *= lCurrentDistY;
										int lCurrentDist = lCurrentDistX + lCurrentDistY;
										if (lCurrentDist > lBestDist) {
											//cerr << "BestScore: [" << lX << "; " << lY << "] Score: " << lScore << endl;
											aBestScore = lScore;
											aBestScoreX = lX;
											aBestScoreY = lY;
											aBestScoreH = lH ? 'H' : 'V';
											lIsValidWay = true;
										}
									}
								}
							}
						}
						mWall.removeSimuWall(lX, lY, lH ? 'H' : 'V');
					}
				}
			}
		}
		for (int lId = 0; lId < mPlayerCount; lId++) {
			mPlayerVect[lId]->setCurrentPosition(lPlayerPositionBackupVect[lId].first, lPlayerPositionBackupVect[lId].second);
		}
		return lIsValidWay;
	}

	bool applyPatternWall(int aWallX, int aWallY, char aWallOrientation)
	{
		bool lIsReponse = (mMyWallLeft > mOpenDoorCount);
		if (lIsReponse) {
			cout << aWallX << " " << aWallY << " " << aWallOrientation << " Eat this!" << endl;
		}
		return lIsReponse;
	}

	bool applyPatternOpenDoor(int aMyScore)
	{
		bool lIsReponse = false;
		if ((mOpenDoorCount > 0) && (mMyWallLeft > 0) && (aMyScore == 2)) {
			Player::Ptr lPlayerPtr = mPlayerVect[mMyId];
			switch (mMyId) {
			case eLeft:
				if (lPlayerPtr->currentX() == (mWidth - 3)) {
					if (mWall.isWallValid(lPlayerPtr->currentX(), lPlayerPtr->currentY(), 'V')) {
						cout << lPlayerPtr->currentX() << " " << lPlayerPtr->currentY() << " " << 'V' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX(), lPlayerPtr->currentY() - 1, 'V')) {
						cout << lPlayerPtr->currentX() << " " << lPlayerPtr->currentY() - 1 << " " << 'V' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX(), lPlayerPtr->currentY(), 'H')) {
						cout << lPlayerPtr->currentX() << " " << lPlayerPtr->currentY() << " " << 'H' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX(), lPlayerPtr->currentY() + 1, 'H')) {
						cout << lPlayerPtr->currentX() << " " << lPlayerPtr->currentY() + 1 << " " << 'H' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX() + 1, lPlayerPtr->currentY(), 'H')) {
						cout << lPlayerPtr->currentX() + 1 << " " << lPlayerPtr->currentY() << " " << 'H' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX() + 1, lPlayerPtr->currentY() + 1, 'H')) {
						cout << lPlayerPtr->currentX() + 1 << " " << lPlayerPtr->currentY() + 1 << " " << 'H' << " Open door" << endl;
						lIsReponse = true;
					}
				}
				break;
			case eRight:
				if (lPlayerPtr->currentX() == 3) {
					if (mWall.isWallValid(lPlayerPtr->currentX() + 1, lPlayerPtr->currentY(), 'V')) {
						cout << lPlayerPtr->currentX() + 1 << " " << lPlayerPtr->currentY() << " " << 'V' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX() + 1, lPlayerPtr->currentY() - 1, 'V')) {
						cout << lPlayerPtr->currentX() + 1 << " " << lPlayerPtr->currentY() - 1 << " " << 'V' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX() - 1, lPlayerPtr->currentY(), 'H')) {
						cout << lPlayerPtr->currentX() - 1 << " " << lPlayerPtr->currentY() << " " << 'H' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX() - 1, lPlayerPtr->currentY() + 1, 'H')) {
						cout << lPlayerPtr->currentX() - 1 << " " << lPlayerPtr->currentY() + 1 << " " << 'H' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX() - 2, lPlayerPtr->currentY(), 'H')) {
						cout << lPlayerPtr->currentX() - 2 << " " << lPlayerPtr->currentY() << " " << 'H' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX() - 2, lPlayerPtr->currentY() + 1, 'H')) {
						cout << lPlayerPtr->currentX() - 2 << " " << lPlayerPtr->currentY() + 1 << " " << 'H' << " Open door" << endl;
						lIsReponse = true;
					}
				}
				break;
			case eUp:
				if (lPlayerPtr->currentY() == (mHeight - 3)) {
					if (mWall.isWallValid(lPlayerPtr->currentX(), lPlayerPtr->currentY(), 'H')) {
						cout << lPlayerPtr->currentX() << " " << lPlayerPtr->currentY() << " " << 'H' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX() - 1, lPlayerPtr->currentY(), 'H')) {
						cout << lPlayerPtr->currentX() - 1 << " " << lPlayerPtr->currentY() << " " << 'H' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX(), lPlayerPtr->currentY(), 'V')) {
						cout << lPlayerPtr->currentX() << " " << lPlayerPtr->currentY() << " " << 'V' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX() + 1, lPlayerPtr->currentY(), 'V')) {
						cout << lPlayerPtr->currentX() + 1 << " " << lPlayerPtr->currentY() << " " << 'V' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX(), lPlayerPtr->currentY() + 1, 'V')) {
						cout << lPlayerPtr->currentX() << " " << lPlayerPtr->currentY() + 1 << " " << 'V' << " Open door" << endl;
						lIsReponse = true;
					} else if (mWall.isWallValid(lPlayerPtr->currentX() + 1, lPlayerPtr->currentY() + 1, 'V')) {
						cout << lPlayerPtr->currentX() + 1 << " " << lPlayerPtr->currentY() + 1 << " " << 'V' << " Open door" << endl;
						lIsReponse = true;
					}
				}
				break;
			}
			if (lIsReponse) {
				mOpenDoorCount--;
			}
		}
		return lIsReponse;
	}

	bool applyPatternMove(void)
	{
		Player::StepList lMyStepList;
		Player::Ptr lPlayerPtr = mPlayerVect[mMyId];
		if (lPlayerPtr->currentX() >= 0) {
			lPlayerPtr->findBestDirection(lMyStepList);
			switch (lMyStepList.front()) {
			case eLeft:
				cout << "LEFT" << endl;
				break;
			case eRight:
				cout << "RIGHT" << endl;
				break;
			case eUp:
				cout << "UP" << endl;
				break;
			case eDown:
				cout << "DOWN" << endl;
				break;
			}
		}
		return true;
	}

private:
	int mWidth;
	int mHeight;
	int mPlayerCount;
	int mMyId;
	int mOpenDoorCount;
	int mMyWallLeft;
	int mEnnemyWallLeft;
	Wall mWall;
	vector<Player::Ptr> mPlayerVect;
};

int main()
{
#ifndef SIMU
	int w; // width of the board
	int h; // height of the board
	int playerCount; // number of players (2 or 3)
	int myId; // id of my player (0 = 1st player, 1 = 2nd player, ...)
	cin >> w >> h >> playerCount >> myId; cin.ignore();
	Scenario lScenario(w, h, playerCount, myId);
#else
	Scenario lScenario(9, 9, 2, 0);
#endif
	// game loop
	while (1) {
		lScenario.initIteration();
#ifndef SIMU
		for (int i = 0; i < playerCount; i++) {
			int x; // x-coordinate of the player
			int y; // y-coordinate of the player
			int wallsLeft; // number of walls available for the player
			cin >> x >> y >> wallsLeft; cin.ignore();
			lScenario.updatePlayerData(i, x, y, wallsLeft);
		}
		int wallCount; // number of walls on the board
		cin >> wallCount; cin.ignore();
		for (int i = 0; i < wallCount; i++) {
			int wallX; // x-coordinate of the wall
			int wallY; // y-coordinate of the wall
			string wallOrientation; // wall orientation ('H' or 'V')
			cin >> wallX >> wallY >> wallOrientation; cin.ignore();
			lScenario.updateWallData(wallX, wallY, wallOrientation[0]);
		}
#else
		lScenario.updatePlayerData(0, 0, 3, 10);
		lScenario.updatePlayerData(1, 8, 2, 10);
		//lScenario.updatePlayerData(2, 3, 0, 6);
#endif
		lScenario.runIteration();
	}
}
