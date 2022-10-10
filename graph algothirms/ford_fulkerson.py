import sys
sys.stdin=open('t.inp','r')
sys.stdout=open('t.out','w')

def dfs(u, sink):
    # đánh dấu u đã được thăm
    visited[u] = True

    # duyệt hết các đỉnh v có thể đến được từ u hay thỏa mãn điều kiện c[u][v] - f[u][v] > 0
    for( v in VertecesCanComeFromU ):
        if not visited[v]:
            trace[v] = u

def find_augment_from_to(int source, int sink):
    """
        brief: hàm này sẽ tìm một đường tăng luồng từ source đến sink
        return: 
            - Nếu có một đường tăng luồng trả về True
            - Nếu không có đường tăng luồng nào trả về False
    """
    # khởi tạo mảng đánh dấu visited ( false nếu chưa thăm, true nếu đã thăm)
    fill(all(visited), False)
    # dùng thuật toán dfs tìm đường tăng luồng
    dfs(source, sink)
    return visited[sink]

def increase_flow(int minCapacity, int source, int sink)
    """
        brief: thủ tục tăng luồng lên một giá trị minCapacity theo đường tăng luồng từ source đên sink
    """
    # khởi tạo minCapacity vô cùng lớn
    minCapacity = inf

    # lấy khả năng thông qua nhỏ nhất trên đường tăng luồng để tăng luồng
    u = sink
    while u != source:
        previousVertex = trace[u]
        minCapacity = min(minCapacity, c[previousVertex][u]-f[previousVertex][u])
        u = previousVertex

    # tăng luồng
    while sink != source:
        previousVertex = trace[sink]
        f[previousVertex][sink] += minCapacity
        f[sink][previousVertex] -= minCapacity
        sink = previousVertex

# Trong khi vẫn tồn tại đường tăng luồng
while find_augment_from_to(s,t):
    # tăng luồng
    increase_flow(s, t)
