import tkinter as tk
import networkx as nx
import numpy as np
import pylab

#迪杰斯特拉算法
def dijk(graph, n, src):
    dis = [0] * n
    flag = [False] * n
    pre = [0] * n
    flag[src] = True
    k = src
    #初始化距离
    for i in range(n):
        dis[i] = graph[src][i]
    for j in range(n - 1):
        mini = np.inf
        for i in range(n):
            if dis[i] < mini and not flag[i]:
                mini = dis[i]
                k = i
        flag[k] = True
        for i in range(n):
            if dis[i] > dis[k] + graph[k][i]:
                dis[i] = dis[k] + graph[k][i]
                pre[i] = k
    return dis, pre



def draw_net(e_edge):
    global node_cnt
    global node
    global mp
    global G
    node_cnt = int(var_cnt.get())
    s = e_edge.get("0.0", 'end')

    node = np.arange(0, node_cnt, 1)

    G = nx.DiGraph()
    for i in range(0, np.size(node)):
        G.add_node(i)

    # 构建邻接矩阵
    mp = np.zeros((node_cnt, node_cnt))
    i = 0
    j = 0
    for x in s.split():
        mp[i, j] = int(x)
        if i < j and (mp[i, j] != 0 and mp[i, j] != -1):
            G.add_weighted_edges_from([(i, j, mp[i, j])])
        if mp[i, j] == -1 or mp[i,j]==0 and i!=j:
            mp[i, j] = np.inf
        j += 1
        if j == node_cnt:
            j = 0
            i += 1
    G = G.to_undirected()
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, node_color='red', edge_color='black', node_size=400, alpha=0.8)
    pylab.title('Self_Define Net', fontsize=15)
    pylab.show()
    return


def draw_dij(e_ans):

    dis, pre = dijk(mp, node_cnt, 0)
    src = int(e_src.get())
    tar = int(e_tar.get())
    if src<0 or src>=node_cnt or tar<0 or tar>=node_cnt:
        e_ans.delete(0, 'end')
        e_ans.insert(0, "请输入正确的顶点格式")
        return;
    print(dis)
    print(pre)
    path = nx.dijkstra_path(G, source=src, target=tar)
    distance = nx.dijkstra_path_length(G, source=src, target=tar)

    e_ans.delete(0, 'end')
    e_ans.insert(0, distance)
    G1 = nx.Graph()
    for i in range(path.__len__() - 1):
        G1.add_edge(path[i], path[i + 1], weight=20)
    i = 0
    j = 0
    while i < node_cnt:
        j = 0
        while j < node_cnt:
            if i < j and mp[i, j] != 0 and mp[i, j] != np.inf and not (G1.has_edge(i, j) or G1.has_edge(j, i)):
                G1.add_edge(i, j, weight=1)
            j += 1
        i += 1
    elarge = [(u, v) for (u, v, d) in G1.edges(data=True) if d['weight'] > 1]
    esmall = [(u, v) for (u, v, d) in G1.edges(data=True) if d['weight'] <= 1]

    pos = nx.spring_layout(G)
    # 首先画出节点位置
    nx.draw_networkx_nodes(G, pos, node_size=700)
    # 根据权重，实线为权值大的边，虚线为权值小的边
    nx.draw_networkx_edges(G, pos, edgelist=elarge,
                           width=6)
    nx.draw_networkx_edges(G, pos, edgelist=esmall,
                           width=6, alpha=0.5, edge_color='b', style='dashed')
    nx.draw(G, pos, font_size=20,with_labels=True, font_family='sans-serif')
    pylab.show()
    return


window = tk.Tk()
window.title('ospf算法')
window.geometry('500x500')
tk.Label(window, text='ospf最短路径路由算法-dijkstra').pack()

frm = tk.Frame(window)
frm.pack()
frm_l = tk.Frame(frm, )
frm_r = tk.Frame(frm)
frm_l.pack(side='left')
frm_r.pack(side='right')
var_cnt = tk.StringVar()
tk.Label(frm_l, text='图的顶点数').pack()
e_cnt = tk.Entry(frm_l, textvariable=var_cnt)
e_cnt.pack()

tk.Label(frm_l, text='起点').pack()
var_src = tk.StringVar()
e_src = tk.Entry(frm_l, textvariable=var_src)
e_src.pack()
tk.Label(frm_l, text='终点').pack()
var_tar = tk.StringVar()
e_tar = tk.Entry(frm_l, textvariable=var_tar)
e_tar.pack()
tk.Label(frm_l, text="\n\n\n\n最短路长度").pack()
e_ans = tk.Entry(frm_l)
e_ans.pack()

tk.Label(frm_r, text='请以邻接矩阵格式输入图的边：').pack()
e_edge = tk.Text(frm_r)
e_edge.pack()
tk.Label(frm_r, text='          ').pack(side='left')
tk.Label(frm_r, text='          ').pack(side='right')
b_net = tk.Button(frm_r, text='生成网络图', command=lambda: draw_net(e_edge))
b_net.pack(side='left')
b_dij = tk.Button(frm_r, text='最短路径', command=lambda: draw_dij(e_ans))
b_dij.pack(side='right')
tk.Label(frm_l,text='\n\n先点击生成网络图按钮，\n'
                    '获得整个网络的示意图，\n'
                    '再点击最短路径，\n'
                    '得到起点到终点的最短路径\n'
                    '在图中用黑色实线表示\n'
                    '最短路径长度输出在上方。').pack()
window.mainloop()


'''
0 1 0 0 5 0
1 0 1 0 1 0
0 1 0 1 0 0
0 0 1 0 1 1
5 1 0 1 0 0
0 0 0 1 0 0
'''
