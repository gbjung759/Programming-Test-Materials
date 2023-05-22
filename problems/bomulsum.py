class Queue(object):
    QUEUE_IS_EMPTY = -1

    def __init__(self):
        self.queue = []

    def push(self, elem):
        self.queue.append(elem)

    def pop(self):
        if len(self.queue) == 0:
            return Queue.QUEUE_IS_EMPTY
        return self.queue.pop(0)

    def empty(self):
        return len(self.queue) == 0


class MapStatusConst:
    LAND = "L"
    WATER = "W"


class DirectionConst:
    NORTH = 0
    WEST = 1
    SOUTH = 2
    EAST = 3
    COUNT = EAST + 1


class Element:
    def __init__(self, x, y, distance):
        self.x = x
        self.y = y
        self.distance = distance


class Bomulsum:
    def __init__(self, N, M, bomul_sum):
        self.N = N
        self.M = M
        self.bomul_sum = bomul_sum
        self.is_visited = [[False] * M for _ in range(N)]

    @staticmethod
    def get_position(x, y, direction):
        if DirectionConst.NORTH == direction:
            return x - 1, y
        elif DirectionConst.WEST == direction:
            return x, y - 1
        elif DirectionConst.SOUTH == direction:
            return x + 1, y
        elif DirectionConst.EAST == direction:
            return x, y + 1

    def check_valid_position(self, x, y):
        return 0 <= x < self.N and 0 <= y < self.M

    def check_valid_land(self, x, y):
        return self.check_valid_position(x, y) and self.bomul_sum[x][y] == MapStatusConst.LAND

    def init_visit_map(self):
        for x in range(self.N):
            for y in range(self.N):
                self.is_visited[x][y] = False

    def check_is_possible_answer(self, x, y):
        north_x, north_y = Bomulsum.get_position(x, y, DirectionConst.NORTH)
        south_x, south_y = Bomulsum.get_position(x, y, DirectionConst.SOUTH)
        if self.check_valid_land(north_x, north_y) and self.check_valid_land(south_x, south_y):
            return False

        west_x, west_y = Bomulsum.get_position(x, y, DirectionConst.WEST)
        east_x, east_y = Bomulsum.get_position(x, y, DirectionConst.EAST)
        if self.check_valid_land(west_x, west_y) and self.check_valid_land(east_x, east_y):
            return False
        return True

    def search_bomul(self):
        longest_shortcut = 0
        for x in range(self.N):
            for y in range(self.N):
                if MapStatusConst.LAND == self.bomul_sum[x][y] and self.check_is_possible_answer(x, y):
                    self.init_visit_map()
                    longest_shortcut = max(longest_shortcut, self.get_longest_shortcut(x, y))
        return longest_shortcut

    def get_longest_shortcut(self, x, y):
        longest_shortcut = 0
        q = Queue()
        q.push(Element(x, y, 0))
        while not q.empty():
            current_position = q.pop()
            self.is_visited[current_position.x][current_position.y] = True
            longest_shortcut = max(longest_shortcut, current_position.distance)
            for direction in range(DirectionConst.COUNT):
                next_x, next_y = Bomulsum.get_position(current_position.x, current_position.y, direction)
                if self.check_valid_land(next_x, next_y) and not self.is_visited[next_x][next_y]:
                    q.push(Element(next_x, next_y, current_position.distance + 1))
        return longest_shortcut


def init_inputs():
    first_line = input()
    N = int(first_line.split()[0])
    M = int(first_line.split()[0])
    bomul_sum = [[""] * M for _ in range(N)]
    for r in range(N):
        line = input()
        for c in range(M):
            bomul_sum[r][c] = line[c]
    return Bomulsum(N, M, bomul_sum)


if __name__ == '__main__':
    bomul_sum = init_inputs()
    longest_shortcut = bomul_sum.search_bomul()
    print(longest_shortcut, end='')
