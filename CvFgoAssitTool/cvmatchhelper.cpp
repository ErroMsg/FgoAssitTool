#include "cvmatchhelper.h"
#include <QDebug>

CvMatchHelper::CvMatchHelper()
{

}

vector<float> CvMatchHelper::Match(const Mat &src, const Mat &obj,
                                   vector<Rect> &rect, int type, int num)
{
    Mat dst;
    //SQDIFF method:the smaller the better;
    //CV_TM_CCORR_NORMED:the bigger the better;
    matchTemplate(src, obj, dst, CV_TM_CCORR_NORMED);
    normalize(dst, dst, 0, 255, NORM_MINMAX);
    vector<float> pro;
    rect.clear();
    double mx = 0;
    double mi = 0;
    Point maxloc,minloc, pre(-1, -1);
    for (int i = 0; i < num;)
    {
        //compare minloc or maxloc depend on
        //matchTemplate's calculate method(CV_TM_CCORR_NORMED/CV_TM_SQDIFF...)
        minMaxLoc(dst, &mi, &mx, &minloc, &maxloc);
        qDebug()<<"min = "<<mi<<",max = "<<mx;
        if (abs(maxloc.x - pre.x) > 10 && abs(maxloc.y - pre.y) > 10)
        {
            rect.push_back(Rect(maxloc.x, maxloc.y, obj.cols, obj.rows));
            pro.push_back(mx/255.0); pre = maxloc; ++i;
        }
        dst.at<float>(maxloc.y, maxloc.x) = 0; mx = 0;
    }
    return pro;
}

cvResult CvMatchHelper::getBestResult(vector<float> &pros, vector<Rect> &rects)
{
    cvResult rslt;
    if(pros.size() != rects.size())
        return rslt;
    auto biggest = std::max_element(pros.begin(), pros.end());
    auto pos = std::distance(pros.begin(), biggest);
    rslt.prob = *biggest;
    rslt.resultRect = rects[pos];

    return rslt;
}

cvResult CvMatchHelper::MatchTemplate(QString srcfile, QString templatefile)
{
    Mat src = imread(srcfile.toStdString());
    Mat roiImg = imread(templatefile.toStdString());
    int type = 0, num = 1;
    vector<Rect> rect;
    vector<float> probs = Match(src,roiImg,rect,type,num);
    return getBestResult(probs,rect);
}

