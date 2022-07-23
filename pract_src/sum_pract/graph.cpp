#include "graph.h"

graph::graph(long long n)
{
    g.resize(n, std::vector<long long>(n, 0));
    used.resize(n, 0);
    this->n = n;
}
void graph::print(std::ostream& out, std::string com)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = i; j < n; j++)
        {
            if(g[i][j] > 0)
            {
                out << i << " " << j << " " << g[i][j] << " " << com << std::endl;
            }
        }
    }
}
long long graph::get_edge(long long i)
{
    return g[i/n][i%n];
}
void graph::add_edge(long long from, long long to)
{
    from--;
    to--;
    g[from][to] = 1;
    g[to][from] = 1;
}
void graph::add_edge(long long i)
{
    g[i/n][i%n] = 1;
    g[i%n][i/n] = 1;
}
void graph::rm_edge(long long i)
{
    g[i/n][i%n] = 2;
    g[i%n][i/n] = 2;
}

bool graph::dest(long long from, long long to)
{
    std::fill(used.begin(), used.end(), 0);
    from--;
    to--;
    dfs(from);
    return used[to];
}
void graph::dfs(long long v)
{
    used[v] = 1;
    for(int i = 0; i < g.size(); i++)
    {
        if(g[v][i] == 1 && !used[i])
        {
            dfs(i);
        }
    }
}


std::string task(graph& g, long long start, long long end)
{
    long long n = g.n;

    std::string ans = "NoSol";
    long long stop = 0;
    for(int i = 0; i < n*n; i++)
    {
        if(g.get_edge(i) == 1)
        {
            g.rm_edge(i);
            for(int j = 0; j < n*n; j++)
            {
                if(g.get_edge(j) == 1)
                {
                    g.rm_edge(j);
                    for(int z = 0; z < n*n; z++)
                    {
                        if(g.get_edge(z) == 1)
                        {
                            g.rm_edge(z);
                            if(g.dest(start, end))
                            {
                                g.add_edge(z);
                            }else{
                                ans = "Sol";
                                stop = 1;
                                break;
                            }
                        }
                    }
                    if(stop)
                        break;
                    else
                        g.add_edge(j);
                }
                
                    
            }
            if(stop)
                break;
            else
                g.add_edge(i);
        }
        
    }
    
    return ans;
}
