#ifndef POSITIONSTAT_H
#define POSITIONSTAT_H

struct PositionStat
{
private:
    int _whiteWinsCount;
    int _blackWinsCount;
    int _drawnsCount;

public:
    PositionStat(int whiteWinsCount, int blackWinsCount,
                 int drawnsCount) : _whiteWinsCount(whiteWinsCount),
        _blackWinsCount(blackWinsCount), _drawnsCount(drawnsCount)
    {

    }

    int getAllPartiesCount() const
    {
        return _whiteWinsCount + _blackWinsCount + _drawnsCount;
    }

    int getWhiteWinsCount() const
    {
        return _whiteWinsCount;
    }

    int getBlackWinsCount() const
    {
        return _blackWinsCount;
    }

    int getDrawnsCount() const
    {
        return _drawnsCount;
    }

    double getWhiteWinsPercent() const
    {
        double result = (double)_whiteWinsCount /
                (double)getAllPartiesCount() * 100;
        return result;
    }

    double getBlackWinsPercent() const
    {
        double result = (double)_blackWinsCount /
                (double)getAllPartiesCount() * 100;
        return result;
    }

    double getDrawnsPercent() const
    {
        double result = (double)_drawnsCount /
                (double)getAllPartiesCount() * 100;
        return result;
    }
};


#endif // POSITIONSTAT_H
