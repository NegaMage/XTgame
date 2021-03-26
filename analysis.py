import os
import pandas as pd

# types = [0,1,3,5,7,8,9,10,11]
types = [0,1,2,3,4,5,6,7]

strings = [str(i)+"_"+str(j) for i in types for j in types]

# f = open("test", "w")
# f.write("1000 {} {}".format(1, 3))
# f.close()

# os.system('./a.out < test')

n_collisions = 0
n_same_file_collisions = 0
n_diff_file_collisions = 0
game_dict = dict()



for i in types:
    for j in types:
        f = open("test", "w")
        f.write("1000 {} {}".format(i, j))
        f.close()

        os.system('./a.out < test')

#print(strings)
data_t1 = {}
data_t2 = {}
data_t3 = {}
for i in types:
    data_t1[str(i)] = []
    data_t2[str(i)] = []
    data_t3[str(i)] = []

for name in strings:
    print("Checking for "+name)
    res = open("rawData/"+name)
    res = res.read()

    # print(type(res))
    res = res.split("\n")
    #print(res)
    '''
    lens = {
        'x': 0,
        'o': 0,
        '*': 0
    }
    '''

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
    print(res[0])
    for game in res:
        if game in game_dict.keys():
            if game_dict[game] == name:
                num = res.count(game)
                n_collisions += num
                n_same_file_collisions += num
                res.remove(game)
                res.append(game)
            else:
                res.remove(game)
                other_file = open('rawData/' + game_dict[game])
                other_file = other_file.read()
                other_file = other_file.split("\n")
                num = other_file.count(game)
                n_collisions += num
                n_diff_file_collisions += num
                other_file.remove(game)

        game_temp = game
        if game: # game is not empty string
            game = game.split(" ")
            wins[game[-1][-1]]+=1
            #lens[game[-1][-1]]+=len(game)-1
            if game[-1][-1] == 'x':
                x_count += 1
                x_length += len(game) - 1
            elif game[-1][-1] == 'o':
                o_count += 1
                o_length += len(game) - 1
            elif game[-1][-1] == '*':
                d_count += 1
                d_length += len(game) - 1
        game_dict[game_temp] = name

    avg_lengths['x'] = x_length / x_count
    avg_lengths['o'] = o_length / o_count
    avg_lengths['*'] = d_length / d_count
    
    print("Number of wins:")
    print(wins)

    #print("Number of steps taken:")
    #print(lens)

    print(" Average game lengths to win:")
    print(avg_lengths)
    x_perc_win = round((wins['x']/(wins['x'] + wins['o'])) * 100.0 , 1)
    o_perc_win = round((wins['o']/(wins['x'] + wins['o'])) * 100.0 , 1)
    draw_perc = round((wins['*']/(wins['x'] + wins['o'] + wins['*'])) * 100.0,1)

    cur_t1 = str(x_perc_win) + '% , ' + str(o_perc_win) + '%'
    cur_t2 = str(round(avg_lengths['x'],1)) + ' ,' + str(round(avg_lengths['o'],1))
    cur_t3 = str(draw_perc) + '% , ' + str(round(avg_lengths['*'],1))
    
    data_t1[name[2]].append(cur_t1)
    data_t2[name[2]].append(cur_t2)
    data_t3[name[2]].append(cur_t3)

df_t1 = pd.DataFrame.from_dict(data_t1)
df_t2 = pd.DataFrame.from_dict(data_t2)
df_t3 = pd.DataFrame.from_dict(data_t3)
df_t1.to_csv('df_t1.csv')
df_t2.to_csv('df_t2.csv')
df_t3.to_csv('df_t3.csv')
print(df_t1.to_latex())
print(df_t2.to_latex())
print(df_t3.to_latex())
print('Number of collisions: ' + str(n_collisions))
print('Number of same file collisions: ' + str(n_same_file_collisions))
print('Number of different file collisions: ' + str(n_diff_file_collisions))

    