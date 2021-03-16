import os

# types = [0,1,3,5,7,8,9,10,11]
types = range(12)

strings = [str(i)+"_"+str(j) for i in types for j in types]

# f = open("test", "w")
# f.write("1000 {} {}".format(1, 3))
# f.close()

# os.system('./a.out < test')

for i in types:
    for j in types:
        f = open("test", "w")
        f.write("1000 {} {}".format(i, j))
        f.close()

        os.system('./a.out < test')

# print(strings)

for name in strings:
    print("Checking for "+name)
    res = open("rawData/"+name)
    res = res.read()

    # print(type(res))
    res = res.split("\n")
    # print(res)
    lens = {
        'x': 0,
        'o': 0,
        '*': 0
    }

    wins = {
        'x': 0,
        'o': 0,
        '*': 0
    }
    avg_lengths = {
         'x': 0,
         'o': 0,
         '*': 0
    }

    x_count = 0
    x_length = 0
    o_count = 0
    o_length = 0
    d_count = 0
    d_length = 0

    for game in res:
        if game: # game is not empty string
            game = game.split(" ")
            wins[game[-1][-1]]+=1
            lens[game[-1][-1]]+=len(game)-1
            if game[-1][-1] == 'x':
                x_count += 1
                x_length += len(game) - 1
            elif game[-1][-1] == 'o':
                o_count += 1
                o_length += len(game) - 1
            elif game[-1][-1] == '*':
                d_count += 1
                d_length += len(game) - 1

    avg_lengths['x'] = x_length / x_count
    avg_lengths['o'] = o_length / o_count
    avg_lengths['*'] = d_length / d_count
    
    print("Number of wins:")
    print(wins)

    print("Number of steps taken:")
    print(lens)

    print(" Average game lengths to win:")
    print(avg_lengths)

