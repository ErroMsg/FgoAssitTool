#ifndef CVMATCHHELPER_H
#define CVMATCHHELPER_H
#include "cvinclude.h"
#include <QString>
#include <vector>
using namespace std;
struct cvResult
{
    float prob;
    Rect resultRect;
    cvResult()
    {
        prob = -1.0;
    }
};

class CvMatchHelper
{
public:
    CvMatchHelper();

    cvResult MatchTemplate(QString srcfile,QString templatefile);
private:
    vector<float> Match(const Mat& src, const Mat& obj, vector<Rect>& rect, int type, int num = 1);
    cvResult getBestResult(vector<float> &pros,vector<Rect>& rects);
};

#endif // CVMATCHHELPER_H
