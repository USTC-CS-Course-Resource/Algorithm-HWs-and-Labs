if __name__ == '__main__':
    n = int(input())
    for _ in range(n):
        sub = input()
        full = input()
        counter = 0
        while True:
            idx = full.find(sub)
            if idx >= 0:
                full = full[idx + 1:]
                counter += 1
            else:
                break
        print(counter)
