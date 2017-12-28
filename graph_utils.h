/************************************************************************* 
# File Name: graph_utils.h
# Author: 
# Mail: @.com
# Created Time: Tue 05 Dec 2017 06:33:13 PM CST
 ************************************************************************/
#ifndef GRAPHUTILS_H
#define GRAPHUTILS_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <limits.h>

namespace Graph {

template <class T> struct sNode {
    T* value;
    int begin;
    int end;    
    std::vector<sNode*> children;
    
    sNode (int begin, int end) {
        this->begin = begin;
        this->end = end;
        this->value = NULL;
    }
};



/*
* special graph traverse for current mark_query
* assume that the nodes index are continuous, the first start index should 0
*/
template <class T> bool GeneratePaths (
    const std::vector<sNode<T>>& nodes,
    std::vector<std::vector<const sNode<T>*>>& paths) {
    std::unordered_map<int, std::vector<const sNode<T>*>> begin2node;
    int eos = -1;
    for (const auto& node : nodes) {
        begin2node[node.begin].push_back(&node);
        eos = (eos < node.end ? node.end : eos);
    }
    // the node and its path, (the index in the paths)
    std::queue<std::pair<const sNode<T>*, size_t>> queue;
    int begin = 0;
    auto iter = begin2node.find(begin);
    if (iter == begin2node.end()) {
        return false;
    }
    // push the head nodes into queue
    for (const auto& node_ptr : iter->second) {
        std::vector<const sNode<T>*> path;
        paths.emplace_back(path);
        queue.emplace(std::pair<const sNode<T>*, size_t>(node_ptr, paths.size() - 1));
    }

    // use BFS to generate the node list
    while (!queue.empty()) {
        auto front = queue.front();
        queue.pop();

        auto iter = begin2node.find(front.first->end);    // the index should be continous
        // insert the current node into current path        
        paths[front.second].emplace_back(front.first);
        if (iter == begin2node.end() || iter->second.empty()) {
            continue;
        }

        // copy the current path for each children
        queue.emplace(std::pair<const sNode<T>*, size_t>(iter->second[0], front.second));
        for (size_t i = 1; i < iter->second.size(); ++i) {
            std::vector<const sNode<T>*> path(paths[front.second].begin(), paths[front.second].end());
            paths.emplace_back(path);
            queue.emplace(std::pair<const sNode<T>*, size_t>(iter->second[i], paths.size() - 1));
        }
    }

    // remove the invalid cases
    auto iter1 = std::remove_if (paths.begin (), paths.end (), 
                    [&eos] (std::vector<const sNode<T>*>& path) {
                        return path.back ()->end != eos;
                    }
                );
    paths.erase (iter1, paths.end ());
    
    return true;
}


}
#endif
