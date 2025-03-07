#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Island
{
    double x, y;
};

struct Edge
{
    int island1, island2;
    double cost;

    bool operator<(const Edge &other) const
    {
        return cost < other.cost;
    }
};

struct DSU
{
    vector<int> parent, rank;

    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    // Find root
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Find which tree is deeper and attach new tree to the deeper tree.
    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int main()
{
    int nrcases, nrislands;
    cin >> nrcases;

    // Fetch input
    for (int i = 0; i < nrcases; i++)
    {

        cin >> nrislands;

        vector<Island> islands;
        vector<Edge> edges;

        // Get all island coordinates
        for (int j = 0; j < nrislands; j++)
        {
            double xcoord, ycoord;
            cin >> xcoord >> ycoord;
            Island is = {xcoord, ycoord};
            islands.push_back(is);
        }

        // Compute all edges
        for (int n = 0; n < nrislands; n++)
        {
            Island island1 = islands[n];
            for (int m = n + 1; m < nrislands; m++)
            {
                Island island2 = islands[m];
                double edgecost = sqrt((pow((island2.x - island1.x), 2) + pow((island2.y - island1.y), 2)));
                Edge edge = {n, m, edgecost};
                edges.push_back(edge);
            }
        }
        // Sort edges by cost in ascending order
        sort(edges.begin(), edges.end());

        // Initialize nodes and values
        DSU dsu(nrislands);
        double result = 0.0;
        int edgesUsed = 0;

        for (const auto &edge : edges)
        {
            // If islands do not share roots, unite and add the cost
            if (dsu.find(edge.island1) != dsu.find(edge.island2))
            {
                dsu.unite(edge.island1, edge.island2);
                result += edge.cost;
                edgesUsed++;

                // If MST is formed, break
                if (edgesUsed == nrislands - 1)
                {
                    break;
                }
            }
        }

        cout << fixed << setprecision(9) << result << endl;
    }

    return 0;
}
