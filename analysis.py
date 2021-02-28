types = [1,2,3]

strings = [str(i)+"_"+str(j) for i in types for j in types]

print(strings)

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

    for game in res:
        if game: # game is not empty string
            game = game.split(" ")
            wins[game[-1][-1]]+=1
            lens[game[-1][-1]]+=len(game)-1
    
    print("Number of wins:")
    print(wins)

    print("Number of steps taken:")
    print(lens)

