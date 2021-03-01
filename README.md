# Routing Algorithms implemented in C

Implementation and simulation of the following routing algorithm in C -

-   Distance Vector Routing - using Bellman Ford Algorithm
-   Link State Routing - using Dijkstra's Algorithm

## Prerequisite

To run this program, you need the following -

-   `gcc` - The GNU Compiler Collection
-   `make` - The make utility (optional)

## Usage

To run the program, firstly clone this repository and change the directory to it -

```
$ git clone https://github.com/aneeshsharma/RoutingAlgorithms
$ cd RoutingAlgorithms
```

Now, compile the program using -

```
$ make
```

You can run each of the programs using `./dvr.o` and `./lsr.o`.

### Input Format

For each of the programs, the input format is -

```
n m
u1 v1 w1
.
.
.
um vm wm
```

-   `n` - the number of vertices/routers in the network
-   `m` - the nunber of edges/links in the network
-   `ui vi wi` - i'th edge/link in the network
    -   `ui` - the source vertex/router
    -   `vi` - the destination vertex/router
    -   `wi` - the weight of the edge/link

### Example Inputs

There are 2 example inputs included in the `example_inputs/` directory. You can use the inputs to test the program as -

```
$ ./lsr.o < example_inputs/in1.txt
$ ./dvr.o < example_inputs/in1.txt
```
