direction = {0 : "북", 1: "동", 2: "남", 3: "서"}
DEBUG = False


class RoomConditionConst:
    ROOM = 0
    WALL = 1


class DirectionConst:
    NORTH = 0
    EAST = 1
    SOUTH = 2
    WEST = 3


class Robot:
    def __init__(self, x, y, d):
        self.x = x
        self.y = y
        self.d = d
        self.n_cleaned_room = 0

    def rotate(self):
        if DirectionConst.NORTH == self.d:
            self.d = DirectionConst.WEST
        elif DirectionConst.WEST == self.d:
            self.d = DirectionConst.SOUTH
        elif self.d == DirectionConst.SOUTH:
            self.d = DirectionConst.EAST
        elif self.d == DirectionConst.EAST:
            self.d = DirectionConst.NORTH
        if DEBUG:
            print(f'd: {direction[self.d]}')

    def clean(self, is_room_cleaned):
        assert is_room_cleaned[self.x][self.y] is False
        is_room_cleaned[self.x][self.y] = True
        self.n_cleaned_room += 1
        if DEBUG:
            print(f'n: {robot.n_cleaned_room}')

    def get_forward_position(self):
        if DirectionConst.NORTH == self.d:
            return (self.x - 1), self.y
        elif DirectionConst.WEST == self.d:
            return self.x, (self.y - 1)
        elif DirectionConst.SOUTH == self.d:
            return (self.x + 1), self.y
        elif DirectionConst.EAST == self.d:
            return self.x, (self.y + 1)

    def get_backward_position(self):
        if DirectionConst.NORTH == self.d:
            return (self.x + 1), self.y
        elif DirectionConst.WEST == self.d:
            return self.x, (self.y + 1)
        elif DirectionConst.SOUTH == self.d:
            return (self.x - 1), self.y
        elif DirectionConst.EAST == self.d:
            return self.x, (self.y - 1)

    def move(self, next_x, next_y):
        self.x = next_x
        self.y = next_y
        if DEBUG:
            print(f'(x: {robot.x}, y: {robot.y}, d: {direction[self.d]})')


class Room:
    def __init__(self, N, M):
        self.N = N
        self.M = M
        self.condition = [[0] * M for i in range(N)]
        self.is_cleaned = [[False] * M for i in range(N)]

    def check_position_is_not_clean(self, x, y):
        return (self.condition[x][y] == RoomConditionConst.ROOM) and (not self.is_cleaned[x][y])

    def check_room_to_be_cleaned_exist_around_position(self, x, y):
        room_exist = False
        # 북
        if self.check_position_is_not_clean(x - 1, y):
            room_exist = True
        # 서
        if self.check_position_is_not_clean(x, y - 1):
            room_exist = True
        # 남
        if self.check_position_is_not_clean(x + 1, y):
            room_exist = True
        # 동
        if self.check_position_is_not_clean(x, y + 1):
            room_exist = True
        return room_exist


def debug_print(robot, room):
    """
    보실 필요 없음
    """
    if DEBUG:
        print('')
        for r in range(len(room.condition)):
            for c in range(len(room.condition[r])):
                if r == robot.x and c == robot.y:
                    content = '*'
                elif room.is_cleaned[r][c]:
                    content = '#'
                else:
                    content = room.condition[r][c]
                if c == len(room.condition[r]) - 1:
                    print(content)
                else:
                    print(content, end=' ')
        print('')


def init_inputs():
    first_line = input()
    N = int(first_line.split()[0])
    M = int(first_line.split()[1])

    second_line = input()
    x = int(second_line.split()[0])
    y = int(second_line.split()[1])
    d = int(second_line.split()[2])

    robot = Robot(x, y, d)
    room = Room(N, M)

    n_room = 0
    for r in range(N):
        line = input()
        for c in range(M):
            room.condition[r][c] = int(line.split()[c])
            if room.condition[r][c] == RoomConditionConst.ROOM:
                n_room += 1
    if DEBUG:
        print(f'n_room: {n_room}')
    return robot, room


def clean(robot, room):
    while True:
        debug_print(robot, room)
        if room.check_position_is_not_clean(robot.x, robot.y):
            robot.clean(room.is_cleaned)
        # 조건 3
        if room.check_room_to_be_cleaned_exist_around_position(robot.x, robot.y):
            robot.rotate()
            next_x, next_y = robot.get_forward_position()
            if room.check_position_is_not_clean(next_x, next_y):
                robot.move(next_x, next_y)
        # 조건 2
        else:
            next_x, next_y = robot.get_backward_position()
            if room.condition[next_x][next_y] == RoomConditionConst.ROOM:
                robot.move(next_x, next_y)
            elif room.condition[next_x][next_y] == RoomConditionConst.WALL:
                break


if __name__ == "__main__":
        robot, room = init_inputs()
        clean(robot, room)
        print(robot.n_cleaned_room)