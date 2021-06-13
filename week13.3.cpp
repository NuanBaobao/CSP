// 巡回演唱会
#include <iostream>
#include <queue>
#include <cstring>
#include <string>
#include <memory>
using namespace std;

#define INF 0x3f3f3f3f    //用来表示无穷大
const int MAXN = 2e5 + 5; //顶点最大个数
int vis[MAXN], dis[MAXN], cnt[MAXN], n, m, d[MAXN];

//图的信息使用链式向前星
struct Edge //表示边的信息
{
    int u, v, w, next;   //u起点,v终点，w权重，next指向下一条边
} Edges[MAXN];           //存储边的数组
int head[MAXN],res[MAXN], tot = 0,t = 1; //head[u]代表从u射出边的编号,tot是Edges的下标，指向边



void find_min_res(int a[], int now)
{
    int temp = INF;
    for( int i = 1;i <= n;i++)
        temp = min(temp,2 * a[i] + d[i-1]);
    
    res[now] = temp;
}

void addEdge(int u, int v, int w) //添加边信息
{
    Edges[tot].u = u;
    Edges[tot].v = v;
    Edges[tot].w = w;
    Edges[tot].next = head[u];
    head[u] = tot++;
}

bool flag = false; //标记是否存在负环
bool SPFA(int s)
{
    flag = false;
    for (int i = 1; i <= n; i++)
        vis[i] = 0, dis[i] = INF, cnt[i] = 0; //初始化
    dis[s] = 0;
    vis[s] = 1; //到自己的距离为0
    //建立队列
    queue<int> que;
    que.push(s);         //将该顶点压入队列
    while (!que.empty()) //队列不空
    {
        int now = que.front();
        que.pop();                                          //弹出队列中的第一个元素
        for (int i = head[now]; i != -1; i = Edges[i].next) //遍历当前顶点的所有邻接顶点
        {
            if (dis[Edges[i].v] > dis[now] + Edges[i].w) //松弛迭代
            {
                dis[Edges[i].v] = dis[now] + Edges[i].w; //更新该顶点的最短路径
                cnt[Edges[i].v] = cnt[now] + 1;
                if (cnt[Edges[i].v] >= n) //存在负环
                {
                    flag = true; //标记
                    break;
                }
                if (!vis[Edges[i].v]) //如果该点不在队列中
                {
                    vis[Edges[i].v] = 1;  //标记
                    que.push(Edges[i].v); //入队
                }
            }
        }
        vis[now] = 0; //取消标记
        if (flag)
            break;
    }
    return flag;
}
int main(void)
{

    cin >> n >> m; //输入
    //初始化
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++)
    {
        int s, e, t;
        cin >> s >> e >> t;
        addEdge(s, e, t); //添加双向边
        addEdge(e, s, t);
    }
    for (int i = 0; i < n; i++)
        cin >> d[i];

    for (int i = 1; i <= n; i++)
    {
        SPFA(i);
        find_min_res(dis, i);  
    }
    for(int i = 1;i <= n;i++) printf("%d ",res[i]);
    printf("\n");
    
    return 0;
}

/*
4 4
1 2 3
2 3 4
3 4 5
1 4 6
10 20 30 10
*/
