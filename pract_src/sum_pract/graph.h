#pragma once
#include <iostream>
#include <vector>

class graph
{
public:
    graph(long long n);
    friend std::string task(graph& g, long long start, long long end);
    void print(std::ostream& out, std::string com);
    long long get_edge(long long i);
    void add_edge(long long from, long long to);
    void add_edge(long long i);
    void rm_edge(long long i);

    bool dest(long long from, long long to);
    void dfs(long long v);
    std::vector<bool>used;
    std::vector<std::vector<long long>>g;
    long long n; 
};

