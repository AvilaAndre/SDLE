import matplotlib.pyplot as plt
import numpy as np



if __name__ == "__main__":
    file1 = open('edges_needed.txt', 'r')
    Lines = file1.readlines()
    
    graph = dict()

    count = 0
    # Strips the newline character
    for line in Lines:
        count += 1

        y, x = line.removesuffix("\n").split(" ")

        graph[int(y)] = int(x)
        
    xpoints = np.array([1, 8])
    ypoints = np.array([3, 10])

    plt.plot(graph.keys(), graph.values())
    plt.show()