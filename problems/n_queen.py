def check_answer(next_col):
    global queen_cols
    for level_diff, col in enumerate(reversed(queen_cols), start=1):
        if col == next_col or abs(col - next_col) == level_diff:
            return False
    return True


def dfs(n_queen, col):
    global answer
    global N
    if n_queen == N:
        answer += 1
        return
    queen_cols.append(col)
    for next_col in range(N):
        if col != next_col and check_answer(next_col):
            dfs(n_queen + 1, next_col)
    queen_cols.pop()


if __name__ == '__main__':
    N = int(input().rstrip())
    queen_cols = []
    answer = 0
    for col in range(N):
        dfs(1, col)
    print(answer, end='')
