//https://contest.yandex.ru/contest/29188/problems/B/

#include "funcs.h"
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

void parseVect(std::istream & input,
               std::vector<int> & v,
               int & len){
    input>>len;
    v.resize(len);
    std::copy_n(std::istream_iterator<int>(input),len,v.begin());
}

/*! @brief Index of first element, that returns true for given func
 *
 * @tparam Func function pointer, lambda, on given vector should have
 * that form: "___---"
 * @tparam T type of values stored in vector
 * @param v vector to search in, sorted
 * @param func function pointer, lambda, that should accept int as input
 * @param left First index, default 0
 * @param right Last index, default -1 means length of given vector
 * @return index,that you should check again
 */
template<typename Func, typename T>
int indexOfFirst(const std::vector<T> & v, Func func, int left, int right){
    while (left<right){
        int middle = (left+right)/2;
        if(func(v[middle])){
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    return left;
}

/*! @brief Index of last element, that returns true for given func
 *
 * @tparam Func function pointer, lambda, on given vector should have
 * that form: "---____"
 * @tparam T type of values stored in vector
 * @param v vector to search in, sorted
 * @param func function pointer, lambda, that should accept int as input
 * @param left First index, default 0
 * @param right Last index, default -1 means length of given vector
 * @return index,that you should check again
 */
template<typename Func, typename T>
int indexOfLast(const std::vector<T> & v, Func func, int left, int right){
    while (left<right){
        int middle = (left+right+1)/2;
        if(func(v[middle])){
            left = middle;
        } else {
            right = middle -1;
        }
    }
    return left;
}

std::pair<int,int> getFirstAndLastIndexes(const std::vector<int> & v, int iVMax, int val){
    std::pair<int,int> ans(0,0);
    int iMin = indexOfFirst(v,[&val](int a){return a>=val;},0,iVMax);
    if(v[iMin]!=val)
        return ans;
    ans.first = ans.second = iMin+1;
    if(iMin == iVMax)
        return ans;
    int iMax = indexOfLast(v,[&val](int a){return a<=val;},ans.first,iVMax);
    if(v[iMax]==val)
        ans.second=iMax+1;
    return ans;
}

void parseFile(std::istream & input, std::ostream & output){

    int lenV, lenAns;
    std::vector<int>v;
    parseVect(input,v,lenV);

    input >> lenAns;
    std::vector<std::pair<int,int>>ans(lenAns);
    int val, iVMax=lenV-1;
    for(auto & a : ans){
        input>>val;
        a = getFirstAndLastIndexes(v,iVMax,val);
    }

    for(auto & a : ans){
        output<<a.first<<' '<<a.second<<'\n';
    }
}
