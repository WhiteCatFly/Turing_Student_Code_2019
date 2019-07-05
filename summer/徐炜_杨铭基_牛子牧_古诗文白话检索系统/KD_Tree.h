#ifndef KD_TREE_INCLUDED
#define KD_TREE_INCLUDED

#include <ctime>
#include <cmath>
#include <cstdlib>

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

struct Answer
{
    int id;
    double dist;
    Answer(){}
    Answer(int _id, double _dist): id(_id), dist(_dist){}
    bool operator < (const Answer &rhs) const
    {
        return dist < rhs.dist;
    }
};

class KD_Tree
{
private:
    static const int MAX_K = 105;
    static const int NUM_OF_ANSWERS = 3;
    static int compare_id;
    
    int id;
    double pos[MAX_K], mn[MAX_K], mx[MAX_K];
    KD_Tree *lson, *rson;

    static bool cmp(const std::vector<double> &a, const std::vector<double> &b)
    {
        return a[compare_id] < b[compare_id];
    }

    static double sqr(double x)
    {
        return x * x;
    }

    double min_dist(std::vector<double> &target)
    {
        double res = 0;
        for (int i = 0; i < K; ++i)
        {
            res += sqr(std::max((double)0, std::max(target[i] - mx[i], mn[i] - target[i])));
        }
        return res;
    }
    
    void update(KD_Tree *son)
    {
        for (int i = 0; i < K; ++i)
        {
            mx[i] = std::max(mx[i], son -> mx[i]);
            mn[i] = std::min(mn[i], son -> mn[i]);
        }
    }

    void recursive_query(std::vector<double> &target, std::priority_queue<Answer> &answers) const
    {
        double dist = 0;
        for (int i = 0; i < K; ++i)
        {
            dist += sqr(target[i] - pos[i]);
        }
        answers.push(Answer(id, dist));
        if (answers.size() > NUM_OF_ANSWERS)
        {
            answers.pop();
        }
        double lson_min_dist, rson_min_dist;
        if (lson != nullptr)
        {
            lson_min_dist = lson -> min_dist(target);
        }
        if (rson != nullptr)
        {
            rson_min_dist = rson -> min_dist(target);
        }
        bool vis_lson = false, vis_rson = false;
        if (lson != nullptr && (rson == nullptr || lson_min_dist < rson_min_dist))
        {
            vis_lson = true;
            if (answers.size() < NUM_OF_ANSWERS || lson_min_dist < answers.top().dist)
            {
                lson -> recursive_query(target, answers);
            }
        }
        if (rson != nullptr && (lson == nullptr || rson_min_dist < lson_min_dist))
        {
            vis_rson = true;
            if (answers.size() < NUM_OF_ANSWERS || rson_min_dist < answers.top().dist)
            {
                rson -> recursive_query(target, answers);
            }
        }
        if (lson != nullptr && !vis_lson && (answers.size() < NUM_OF_ANSWERS || lson_min_dist < answers.top().dist))
        {
            lson -> recursive_query(target, answers);
        }
        if (rson != nullptr && !vis_rson && (answers.size() < NUM_OF_ANSWERS || rson_min_dist < answers.top().dist))
        {
            rson -> recursive_query(target, answers);
        }
    }

public:
    static int K;

    KD_Tree(){}
    KD_Tree(std::vector<std::vector<double> > &arr, int L, int R)
    {
        int mid = (L + R) >> 1;
        compare_id = rand() % K + 1;
        std::nth_element(arr.begin() + L, arr.begin() + mid, arr.begin() + R + 1, cmp);
        id = arr[mid][0];
        for (int i = 0; i < K; ++i)
        {
            mn[i] = mx[i] = pos[i] = arr[mid][i+1];
        }
        if (L < mid)
        {
            lson = new KD_Tree(arr, L, mid - 1);
            update(lson);
        }
        if (R > mid)
        {
            rson = new KD_Tree(arr, mid + 1, R);
            update(rson);
        }
    }
    KD_Tree(std::vector<std::vector<double> >&arr):
        KD_Tree(arr, 0, arr.size() - 1){}
    
    ~KD_Tree()
    {
        delete lson;
        delete rson;
    }

    std::vector<int> query(std::vector<double> target) const
    {
        std::priority_queue<Answer> answers;
        recursive_query(target, answers);
        std::vector<int> ret;
        for (int i = 0; i < NUM_OF_ANSWERS; ++i)
        {
            if(answers.empty()) break;
            ret.push_back(answers.top().id);
            answers.pop();
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

int KD_Tree::compare_id = 0;
int KD_Tree::K = 0;

int n = 4;
double dat[][2] =
{
    {0, 0},
    {1, 0},
    {0, 1},
    {-1, -1}
};

#endif