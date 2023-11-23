

import random


class Graph:
    def __init__(self, nodes):
        self.nodes = nodes
        self.edges = []

        self.possible_edges = []

        for i in self.nodes:
            for j in self.nodes:
                if j <= i:
                    continue
                self.possible_edges.append( (i, j) )


    def is_connected(self) -> bool:
        roll = random.choice([True, False])

        groups = dict()
        group_counter = 1

        for e1, e2 in self.edges:
            found = False
            for group_key in groups.keys():
                if (e1 in groups[group_key]) or (e2 in groups[group_key]):
                    groups[group_key].add(e1)
                    groups[group_key].add(e2)
                    found = True
                    break
            if found:
                continue
            else:
                groups[group_counter] = set([e1, e2])
                group_counter = group_counter + 1

        for group_key in groups.keys():
            if group_key == 1: continue
            intersection = groups[1].intersection(groups[group_key])

            if len(intersection):
                groups[1] = groups[1].union(groups[group_key])


        if (len(groups.keys()) and len(groups[1]) == len(self.nodes)):
            return True
        else:
            return False
    
    def add_random_edge(self):
        roll = random.choice(self.possible_edges)

        self.edges.append(roll)

        self.possible_edges.remove(roll)

        return roll


if __name__ == "__main__":
    f = open("edges_needed.txt", "w")
    for i in range(3, 250):
        nodes = []

        for j in range(1, i+1):
            nodes.append(j)

        graph = Graph(nodes)

        while not graph.is_connected():
            added_edge = graph.add_random_edge()
        
        f.write(f"{i} {len(graph.edges)}\n")
        print(f"connected {i} node graph with {len(graph.edges)} edges")

        
    f.close()