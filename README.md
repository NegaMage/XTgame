# XTgame
XT is expanded tic tac toe, played on a 9x9 grid.

We're looking at naive strategies for tic tac toe. Assuming that both players have no idea how to play this game, their only inputs will be similar to random inputs, so we can simulate a large number of naive games by looking at rng inputs to a game state. 

We then generate possible strategies, perhaps it'll be easier to win if we aggressively go for corners, then middles, then edges. Or something similar. Then we look at the average game length, and deduce backwards that certain strategies may have certain advantages.

We can also aggressively test strategies, still with RNG. By pure RNG, each option is equally likely. Instead we can make the edge pieces the top priority, or have different players with different schemes. 

There's lots of things to try out. 