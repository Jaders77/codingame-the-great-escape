#define CPP11
#define SIMU

// cout, cin
#include <iostream>
// string
#include <string>
// vector
#include <vector>
// list
#include <list>
#include <queue>
// setw
#include <iomanip>
// shared_ptr
#include <memory>

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
		, mVWallVect(mWidth * mHeight)
		, mHWallVect(mWidth * mHeight)
		, mVSimuWallVect(mWidth * mHeight)
		, mHSimuWallVect(mWidth * mHeight)
	{
		fill(mVWallVect.begin(), mVWallVect.end(), 0);
		fill(mHWallVect.begin(), mHWallVect.end(), 0);
		clearSimuWall();
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
	mutable PathfindingVect mPathfindingVect;
	typedef queue<pair<int, int> > PosQueue;
	mutable shared_ptr<PosQueue> mCurrentPosListPtr;
	mutable shared_ptr<PosQueue> mNewPosListPtr;

public:
	Player(int aWidth, int aHeight, Wall* apWall, EDirection aStartPos)
		: mWidth(aWidth)
		, mHeight(aHeight)
		, mpWall(apWall)
		, mStartPos(aStartPos)
		, mCurrentPosX(-1)
		, mCurrentPosY(-1)
		, mPathfindingVect(aWidth * aHeight)
		, mCurrentPosListPtr(new PosQueue())
		, mNewPosListPtr(new PosQueue())
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

	void findBestDirection(StepList& aStepList, bool abDump = false) const
	{
		int lBestValue = -1;
		int lBestX = -1;
		int lBestY = -1;
		computePathfinding(mPathfindingVect, lBestValue, lBestX, lBestY);
		//cerr << "Best destination [" << lBestX << "; " << lBestY << "] in " << lBestValue << " steps" << endl;
		while (lBestValue > 0) {
			lBestValue--;
			if (mpWall->isLeftValid(lBestX, lBestY) && (get(mPathfindingVect, lBestX - 1, lBestY) == lBestValue)) {
				lBestX--;
				aStepList.push_front(eRight);
			} else if (mpWall->isRightValid(lBestX, lBestY) && (get(mPathfindingVect, lBestX + 1, lBestY) == lBestValue)) {
				lBestX++;
				aStepList.push_front(eLeft);
			} else if (mpWall->isUpValid(lBestX, lBestY) && (get(mPathfindingVect, lBestX, lBestY - 1) == lBestValue)) {
				lBestY--;
				aStepList.push_front(eDown);
			} else if (mpWall->isDownValid(lBestX, lBestY) && (get(mPathfindingVect, lBestX, lBestY + 1) == lBestValue)) {
				lBestY++;
				aStepList.push_front(eUp);
			}
		}
		if (abDump) {
			dump(mPathfindingVect);
		}
	}

	void findBestStep(int& aBestValue, bool abDump = false) const
	{
		int lBestX = -1;
		int lBestY = -1;
		computePathfinding(mPathfindingVect, aBestValue, lBestX, lBestY);
		if (abDump) {
			dump(mPathfindingVect);
		}
	}

	void findBestNextStep(int& aBestValue, int& aBestX, int& aBestY, bool abDump = false) const
	{
		int lBestValue = -1;
		computePathfinding(mPathfindingVect, lBestValue, aBestX, aBestY);
		aBestValue = lBestValue;
		while (lBestValue > 1) {
			lBestValue--;
			if (mpWall->isLeftValid(aBestX, aBestY) && (get(mPathfindingVect, aBestX - 1, aBestY) == lBestValue)) {
				aBestX--;
			} else if (mpWall->isRightValid(aBestX, aBestY) && (get(mPathfindingVect, aBestX + 1, aBestY) == lBestValue)) {
				aBestX++;
			} else if (mpWall->isUpValid(aBestX, aBestY) && (get(mPathfindingVect, aBestX, aBestY - 1) == lBestValue)) {
				aBestY--;
			} else if (mpWall->isDownValid(aBestX, aBestY) && (get(mPathfindingVect, aBestX, aBestY + 1) == lBestValue)) {
				aBestY++;
			}
		}
		if (abDump) {
			dump(mPathfindingVect);
		}
	}

private:
	void computePathfinding(PathfindingVect& aPathfindingVect, int& aBestValue, int& aBestX, int& aBestY) const
	{
		aBestValue = -1;
		aBestX = -1;
		aBestY = -1;
		int lCurrentStep = 0;
		fill(aPathfindingVect.begin(), aPathfindingVect.end(), -1);
		mCurrentPosListPtr->push(make_pair(mCurrentPosX, mCurrentPosY));
		bool lIsLoopDone = mCurrentPosListPtr->empty();
		while (!lIsLoopDone) {
			while (!lIsLoopDone && !mCurrentPosListPtr->empty()) {
				int lCurrentX = mCurrentPosListPtr->front().first;
				int lCurrentY = mCurrentPosListPtr->front().second;
				if (get(aPathfindingVect, lCurrentX, lCurrentY) < 0) {
					aPathfindingVect[lCurrentY*mWidth + lCurrentX] = lCurrentStep;
					switch (mStartPos) {
					case eLeft:
						lIsLoopDone = (lCurrentX >= (mWidth - 1));
						break;
					case eRight:
						lIsLoopDone = (lCurrentX <= 0);
						break;
					case eUp:
						lIsLoopDone = (lCurrentY >= (mHeight - 1));
						break;
					case eDown:
						lIsLoopDone = (lCurrentY <= 0);
						break;
					}
					if (lIsLoopDone) {
						aBestValue = lCurrentStep;
						aBestX = lCurrentX;
						aBestY = lCurrentY;
					} else {
						if (mpWall->isLeftValid(lCurrentX, lCurrentY))
							mNewPosListPtr->push(make_pair(lCurrentX - 1, lCurrentY));
						if (mpWall->isRightValid(lCurrentX, lCurrentY))
							mNewPosListPtr->push(make_pair(lCurrentX + 1, lCurrentY));
						if (mpWall->isUpValid(lCurrentX, lCurrentY))
							mNewPosListPtr->push(make_pair(lCurrentX, lCurrentY - 1));
						if (mpWall->isDownValid(lCurrentX, lCurrentY))
							mNewPosListPtr->push(make_pair(lCurrentX, lCurrentY + 1));
					}
				}
				mCurrentPosListPtr->pop();
			}
			mCurrentPosListPtr.swap(mNewPosListPtr);
			lCurrentStep++;
			lIsLoopDone |= mCurrentPosListPtr->empty();
		}
		while (!mCurrentPosListPtr->empty()) {
			mCurrentPosListPtr->pop();
		}
		while (!mNewPosListPtr->empty()) {
			mNewPosListPtr->pop();
		}
	}

	inline int get(const PathfindingVect& aPathfindingVect, int aX, int aY) const
	{
		return aPathfindingVect[aY*mWidth + aX];
	}

	void dump(const PathfindingVect& aPathfindingVect) const
	{
		for (int lY = 0; lY < mHeight; lY++) {
			for (int lX = 0; lX < mWidth; lX++) {
				cerr << setw(2) << get(aPathfindingVect, lX, lY) << " ";
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
};

class Scenario
{
public:
	Scenario(int aWidth, int aHeight, int aPlayerCount, int aMyId)
		: mWidth(aWidth)
		, mHeight(aHeight)
		, mPlayerCount(aPlayerCount)
		, mMyId(aMyId)
		, mOpenDoorCount((aPlayerCount == 2) ? 3 : 0)
		, mMyWallLeft(0)
		, mEnnemyWallLeft(0)
		, mWall(aWidth, aHeight)
		, mPlayerVect(aPlayerCount)
	{
		for (int i = 0; i < mPlayerCount; i++) {
			Player::Ptr PlayerPtr(new Player(aWidth, aHeight, &mWall, (EDirection)i));
			mPlayerVect[i] = PlayerPtr;
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
		//applyPatternScoredSelection();
		applyPatternBrutForce();
#ifdef CPP11
		lTimeEnd = high_resolution_clock::now();
		long long lElapsedMilli = duration_cast<milliseconds>(lTimeEnd - lTimeStart).count();
		cerr << "ExecTime: " << lElapsedMilli << "ms" << endl;
#endif
	}

private:
	void applyPatternScoredSelection(void)
	{
		int lMyScore = 0;
		int lBaddestEnemyScore = numeric_limits<int>::max();
		int lBaddestEnemyId = -1;
		for (int i = 0; i < mPlayerCount; i++) {
			Player::Ptr lPlayerPtr = mPlayerVect[i];
			if (lPlayerPtr->currentX() >= 0) {
				int lBestValue = -1;
				lPlayerPtr->findBestStep(lBestValue);
				if (lBestValue <= 0) {
					break;
				} else if (i == mMyId) {
					cerr << "My position: [" << lPlayerPtr->currentX() << "; " << lPlayerPtr->currentY() << "] Score: " << lBestValue << endl;
					lMyScore = lBestValue;
				} else {
					cerr << "Enemy position: [" << lPlayerPtr->currentX() << "; " << lPlayerPtr->currentY() << "] Score: " << lBestValue << endl;
					if (lBestValue < lBaddestEnemyScore) {
						lBaddestEnemyScore = lBestValue;
						lBaddestEnemyId = i;
					}
				}
			}
		}

		int lCurrentScore = (1000 / lMyScore) - (1000 / lBaddestEnemyScore);
		int lBestScore = lCurrentScore;
		int lBestScoreX = -1;
		int lBestScoreY = -1;
		char lBestScoreH = '?';
		for (int lY = 0; lY < mHeight; lY++) {
			for (int lX = 0; lX < mWidth; lX++) {
				for (int lH = 0; lH < 2; lH++) {
					if (mWall.isWallValid(lX, lY, lH ? 'H' : 'V')) {
						mWall.addSimuWall(lX, lY, lH ? 'H' : 'V');
						int lScore = 0;
						for (int i = 0; i < mPlayerCount; i++) {
							Player::Ptr lPlayerPtr = mPlayerVect[i];
							if (lPlayerPtr->currentX() >= 0) {
								int lBestValue = -1;
								lPlayerPtr->findBestStep(lBestValue);
								if (lBestValue <= 0) {
									lScore = numeric_limits<int>::min();;
									break;
								} else if (i == mMyId) {
									lScore += 1000 / lBestValue;
								} else if (i == lBaddestEnemyId) {
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
							Player::Ptr lPlayerPtr = mPlayerVect[lBaddestEnemyId];
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
		bool lIsReponse = false;
		if (!lIsReponse && (lBestScore > (lCurrentScore + ((mPlayerCount == 2) ? 50 : 200)))) {
			lIsReponse = applyPatternWall(lBestScoreX, lBestScoreY, lBestScoreH);
		}
		if (!lIsReponse && (lMyScore == 2)) {
			lIsReponse = applyPatternOpenDoor();
		}
		if (!lIsReponse) {
			lIsReponse = applyPatternMove();
		}
	}

	void applyPatternBrutForce(void)
	{
		int lMyScore = 0;
		int lBaddestEnemyScore = numeric_limits<int>::max();
		int lBaddestEnemyId = -1;
		for (int i = 0; i < mPlayerCount; i++) {
			Player::Ptr lPlayerPtr = mPlayerVect[i];
			if (lPlayerPtr->currentX() >= 0) {
				int lBestValue = -1;
				lPlayerPtr->findBestStep(lBestValue);
				if (lBestValue <= 0) {
					break;
				} else if (i == mMyId) {
					cerr << "My position: [" << lPlayerPtr->currentX() << "; " << lPlayerPtr->currentY() << "] Score: " << lBestValue << endl;
					lMyScore = lBestValue;
				} else {
					cerr << "Enemy position: [" << lPlayerPtr->currentX() << "; " << lPlayerPtr->currentY() << "] Score: " << lBestValue << endl;
					if (lBestValue < lBaddestEnemyScore) {
						lBaddestEnemyScore = lBestValue;
						lBaddestEnemyId = i;
					}
				}
			}
		}

		int lCurrentScore = (1000 / lMyScore) - (1000 / lBaddestEnemyScore);
		int lBestScore = lCurrentScore;
		bool lIsValidWay = false;
		long long lRecurseCount = 0;
		recursePatternBrutForce(mPlayerVect, min(mMyWallLeft, 2), lBestScore, lRecurseCount);
		cerr << "recursePatternBrutForce count: " << lRecurseCount << endl;

		bool lIsReponse = false;
		if (!lIsReponse && lIsValidWay && (lBestScore > (lCurrentScore + ((mPlayerCount == 2) ? 50 : 200)))) {
			//lIsReponse = applyPatternWall(lBestScoreX, lBestScoreY, lBestScoreH);
		}
		if (!lIsReponse && (lMyScore == 2)) {
			lIsReponse = applyPatternOpenDoor();
		}
		if (!lIsReponse) {
			lIsReponse = applyPatternMove();
		}
	}

	bool recursePatternBrutForce(vector<Player::Ptr>& aPlayerVect, int aNbWallLeft, int& aBestScore, long long& aRecurseCount)
	{
		bool lIsValidWay = false;
		aRecurseCount++;
		//cerr << "recursePatternBrutForce : " << aRecurseCount << endl;
		vector<Player::Ptr> lPlayerCopyVect(mPlayerCount);
		for (int i = 0; i < mPlayerCount; i++) {
			Player::Ptr PlayerPtr(new Player(*aPlayerVect[i]));
			lPlayerCopyVect[i] = PlayerPtr;
		}
		/*int lBestScoreX = -1;
		int lBestScoreY = -1;
		char lBestScoreH = '?';*/
		for (int lY = 0; lY < mHeight; lY++) {
			for (int lX = 0; lX < mWidth; lX++) {
				for (int lH = 0; lH < 2; lH++) {
					if (mWall.isWallValid(lX, lY, lH ? 'H' : 'V')) {
						mWall.addSimuWall(lX, lY, lH ? 'H' : 'V');
						bool lIsValidNewWay = true;
						int lScore = 0;
						for (int i = 0; lIsValidNewWay && (i < mPlayerCount); i++) {
							Player::Ptr lPlayerPtr = aPlayerVect[i];
							if (lPlayerPtr->currentX() >= 0) {
								int lBestValue = -1;
								int lBestX = -1;
								int lBestY = -1;
								lPlayerPtr->findBestNextStep(lBestValue, lBestX, lBestY);
								if (lBestValue <= 0) {
									lIsValidNewWay = false;
								} else if (i == mMyId) {
									lScore += 1000 / lBestValue;
								} else {
									lScore -= 1000 / lBestValue;
								}
								lPlayerCopyVect[i]->setCurrentPosition(lBestX, lBestY);
							}
						}
						if (lIsValidNewWay)
						{
							if (lScore > aBestScore) {
								aBestScore = lScore;
								lIsValidWay = true;
								/*lBestScoreX = lX;
								lBestScoreY = lY;
								lBestScoreH = lH ? 'H' : 'V';*/
							}
							if (aNbWallLeft > 0) {
/*#ifdef CPP11
								time_point<high_resolution_clock> lTimeStart, lTimeEnd;
								lTimeStart = high_resolution_clock::now();
#endif*/
								if (recursePatternBrutForce(lPlayerCopyVect, aNbWallLeft - 1, lScore, aRecurseCount)) {
									if (lScore > aBestScore) {
										aBestScore = lScore;
										lIsValidWay = true;
										/*lBestScoreX = lX;
										lBestScoreY = lY;
										lBestScoreH = lH ? 'H' : 'V';*/
									}
								}
/*#ifdef CPP11
								lTimeEnd = high_resolution_clock::now();
								long long lElapsedMilli = duration_cast<milliseconds>(lTimeEnd - lTimeStart).count();
								cerr << "recursePatternBrutForce ExecTime: " << lElapsedMilli << "ms" << endl;
#endif*/
							}
						}
						mWall.removeSimuWall(lX, lY, lH ? 'H' : 'V');
					}
				}
			}
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

	bool applyPatternOpenDoor(void)
	{
		bool lIsReponse = false;
		if ((mOpenDoorCount > 0) && (mMyWallLeft > 0)) {
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
		lScenario.updatePlayerData(0, 0, 3, 6);
		lScenario.updatePlayerData(1, 8, 4, 6);
		//lScenario.updatePlayerData(2, 3, 0, 6);
#endif
		lScenario.runIteration();
	}
}