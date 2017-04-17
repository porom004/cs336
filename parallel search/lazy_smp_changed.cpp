void getBestMoveAtDepth(Board *b, MoveList *legalMoves, int depth, int alpha,
int beta, int *bestMoveIndex, int *bestScore, unsigned int startMove,
int threadID, SearchPV *pvLine) {
// SearchParameters *searchParams = &(searchParamsArray[threadID]);
SearchStatistics *searchStats = &(searchStatsArray[threadID]);
SearchPV line;
int color = b->getPlayerToMove();
int tempMove = -1;
int score = -MATE_SCORE;
*bestScore = -INFTY;
SearchStackInfo *ssi = &(ssInfo[threadID][1]);

// Push current position to two fold stack
twoFoldPositions[threadID].push(b->getZobristKey());

// Helps prevent stalls when using more threads than physical cores,
// presumably by preventing this function from completing before the thread
// is able to detach.
std::this_thread::yield();

for (unsigned int i = startMove; i < legalMoves->size(); i++) {
// Output current move info to the GUI. Only do so if 5 seconds of
// search have elapsed to avoid clutter
uint64_t timeSoFar = getTimeElapsed(searchParamsArray[0].startTime);
uint64_t nps = 1000 * getNodes() / timeSoFar;
if (threadID == 0 && timeSoFar > 5 * ONE_SECOND)
cout << "info depth " << depth << " currmove " << moveToString(legalMoves->get(i))
<< " currmovenumber " << i+1 << " nodes " << getNodes() << " nps " << nps << endl; Board copy = b->staticCopy();
copy.doMove(legalMoves->get(i), color);
searchStats->nodes++;

int startSq = getStartSq(legalMoves->get(i));
int endSq = getEndSq(legalMoves->get(i));
int pieceID = b->getPieceOnSquare(color, startSq);
ssi->counterMoveHistory = searchParamsArray[threadID].counterMoveHistory[pieceID][endSq];

if (i != 0) {
score = -PVS(copy, depth-1, -alpha-1, -alpha, threadID, true, ssi, &line);
if (alpha < score && score < beta) { line.pvLength = 0; score = -PVS(copy, depth-1, -beta, -alpha, threadID, false, ssi, &line); } } else { score = -PVS(copy, depth-1, -beta, -alpha, threadID, false, ssi, &line); } // Stop condition. If stopping, return search results from incomplete // search, if any. if (isStop || stopSignal) break; if (score > *bestScore) {
*bestScore = score;
if (score > alpha) {
alpha = score;
tempMove = (int) i;
changePV(legalMoves->get(i), pvLine, &line);
}
// To get a PV if failing low
else if (i == 0)
changePV(legalMoves->get(i), pvLine, &line);
}

if (score >= beta)
break;
}

twoFoldPositions[threadID].pop();

*bestMoveIndex = tempMove;

// This thread is finished running.
threadsRunningMutex.lock();
threadsRunning--;
threadsRunningMutex.unlock();
}
