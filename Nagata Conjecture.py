def diff(a):
    return a * a - a


def diffn(a, dim):
    return ((dim - 1) * a - 2) * (a - 1)


def degree_condition1(a, d, g, dim):
    return 0 < a <= d - 1 and diff(a) <= (diffn(d, dim) - 2 * g)


def degree_condition2(arr, d, dim):
    sum_elements = sum(arr[:dim + 1])  # 只取前dim+1个元素
    return sum_elements <= (dim - 1) * d


def find_solutions(solution, index, M, N, d, dim, g, prev_q, results):
    # 创建前dim+1个元素的扩展数组（不足补0）
    extended = solution[:dim + 1] + [0] * (dim + 1 - len(solution))

    # 检查第一个元素的条件（如果数组不为空）
    if len(solution) >= 1 and not degree_condition1(solution[0], d, g, dim):
        return

    # 检查数组和条件
    if not degree_condition2(extended, d, dim):
        return

    # 终止条件：所有元素已填充
    if index == len(solution):
        if M == 0 and N == 0:
            results.append(solution.copy())
        return

    # 确定当前元素的范围
    max_value = min(prev_q, N)  # 不能超过剩余N和prev_q
    max_value = min(max_value, int((1 + (1 + 4 * M) ** 0.5) / 2))  # 根据diff(a)<=M推导的最大a值

    # 遍历所有可能的值（从0到max_value）
    for a in range(max_value, -1, -1):  # 逆序尝试更大的值优先
        current_diff = diff(a)
        if current_diff > M or a > N:
            continue

        solution[index] = a
        find_solutions(solution, index + 1, M - current_diff, N - a, d, dim, g, a, results)
        solution[index] = 0  # 回溯


def solution(n, k, g, dim):
    results = []
    for d in range(2, 101):  # 原始代码中的range=100
        M_total = diffn(d, dim) - 2 * g
        N_total = 2 * g - 2 + n + (dim + 1) * d

        # 初始化数组并设置第一个元素
        arr = [0] * k
        arr[0] = max(n + 2, d // (dim + 1))

        # 计算初始余量
        initial_M = M_total - diff(arr[0])
        initial_N = N_total - arr[0]

        # 剪枝：如果初始值已经不满足条件
        if initial_M < 0 or initial_N < 0:
            continue

        current_results = []
        find_solutions(arr, 1, initial_M, initial_N, d, dim, g, arr[0], current_results)

        if current_results:
            print(f"\nDegree {d} solutions:")
            for sol in current_results:
                print(f"  {sol}")


if __name__ == "__main__":
    n = 0  # 负交数
    g = 1  # 曲线亏格
    dim = 2  # 维度
    k = 9 + n + g  # 爆破点数

    print(f"Dimension: {dim}")
    print(f"Negative intersections: {n}")
    print(f"Genus: {g}")
    print(f"Blow-up points: {k}\n")

    solution(n, k, g, dim)