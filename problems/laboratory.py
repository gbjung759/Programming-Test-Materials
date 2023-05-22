# �ㅽ뻾�쒓컙 : 50媛쒖쓽 �뚯뒪�� 耳��댁뒪瑜� �⑹퀜�� C / C++ / JAVA�� 寃쎌슦 3珥�
# �뚯씠�ъ쓽 寃쎌슦 15珥�
# 硫붾え由� : Heap, Global, Stack �깆쓣 紐⑤몢 �⑺빐 理쒕� 256 MB 源뚯� �ъ슜媛���(��, �ㅽ깮�� 理쒕� 1MB源뚯� �ъ슜 媛���)
# 泥レ㎏ 以꾩뿉 吏��꾩쓽 �몃줈 �ш린 N 媛�濡� �ш린 M
# �섏㎏ 以� 吏���
# 0�� 鍮덉뭏, 1�� 踰�, 2�� 諛붿씠�ъ뒪
# 鍮덉뭏 理쒖냼 3, 踰� 3媛� �몄슫 �� 吏꾪뻾

DEBUG = False

BLANK = 0
WALL = 1
VIRUS = 2
# 紐⑺몴 : �덉쟾 �곸뿭�� �ш린瑜� 理쒕�
# 留듭쓣 �뚯븘媛�硫� 踰� �ㅼ튂 -> �대떦 留듭뿉�� 諛붿씠�ъ뒪 �쇳듃由ш린 -> �덉쟾 �곸뿭 媛쒖닔 李얘린


class Position:
    def __init__(self, x, y):
        self.x = x
        self.y = y


def virus_find():
    # 諛붿씠�ъ뒪 �쇳듃由� 留� 蹂듭궗
    for i in range(n):
        for j in range(m):
            copy_research_map[i][j] = research_map[i][j]
    # 諛붿씠�ъ뒪 李얘린
    for i in range(n):
        for j in range(m):
            if research_map[i][j] == VIRUS:
                copy_research_map[i][j] = BLANK
                virus_spread(i, j)
    # �덉쟾�곸뿭 �� 李얘린 �⑥닔
    return count_safety_zone()


def virus_spread(x, y):
    if 0 <= x < n and 0 <= y < m and copy_research_map[x][y] == BLANK:
        copy_research_map[x][y] = VIRUS
        virus_spread(x + 1, y)
        virus_spread(x, y + 1)
        virus_spread(x - 1, y)
        virus_spread(x, y - 1)


def count_safety_zone():
    cnt = 0
    for i in range(n):
        for j in range(m):
            if copy_research_map[i][j] == BLANK:
                cnt += 1
    return cnt


n, m = map(int, input().split())
research_map = []
for _ in range(n):
    research_map.append(list(map(int, input().split())))

copy_research_map = [[0 for i in range(m)] for _ in range(n)]

result = 0

blacks = list()
for i in range(n):
    for j in range(m):
        if research_map[i][j] == BLANK:
            blacks.append(Position(i, j))

for i in range(len(blacks)):
    for j in range(i+1, len(blacks)):
        for k in range(j+1, len(blacks)):
            research_map[blacks[i].x][blacks[i].y] = WALL
            research_map[blacks[j].x][blacks[j].y] = WALL
            research_map[blacks[k].x][blacks[k].y] = WALL

            result = max(result, virus_find())

            research_map[blacks[i].x][blacks[i].y] = BLANK
            research_map[blacks[j].x][blacks[j].y] = BLANK
            research_map[blacks[k].x][blacks[k].y] = BLANK

print(result)
