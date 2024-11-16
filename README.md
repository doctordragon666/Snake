# Snake Game [中文文档点这里](README_ZH.md)

The snake game is based on C++11 and system APIs, and it runs on the console.

There are two unresolved issues in this project:

1. Food may be generated on the snake's body.
2. The moving speed is inconsistent when moving up and down due to characters.

### Running Example

You can download the program by clicking on the release package. Here is the result of running it in the shell.

```shell
$ g++.\Snake.cpp -o Snake
$.\Snake.exe
00000000000000000000000000000000000
0                                 0
0                                 0
0                                 0
0                                 0
0   Y                             0
0                                 0
0                                 0
0                                 0
0                                 0
0                                 0
0         D                       0
0         D                       0
0         D                       0
00000000000000000000000000000000000


Game over! You get 0 scores.
```

### Flow Chart

```mermaid
flowchart LR
	Initialization --> PrintMap --> GetKey --> Process --> A{"Judge Game Result"}
	A --> |Yes| End
	A -->|No| PrintMap
```

### Key Algorithms

Regarding how to update the position of the snake, a bidirectional queue in the C++ Standard Template Library (STL) is used to update the snake's position.

```mermaid
flowchart LR
	init("Initialize the coordinates of three snake positions and add them to the queue") --> getkey("Get keyboard messages") -->|Game hotkeys| c1
	getkey -->|ESC key| e(Exit)
	del("Delete the tail node")
	isfood("Is it food?") -->|Yes| push
	isfood -->|No| del
	c1{"Is the direction opposite to the snake's moving direction?"} -->|Yes| movea("The snake moves according to the previous direction") --> isfood
	push("Update the coordinates of the head node and add it to the front of the queue") --- getkey
	del --> push
	c1 -->|No| moveb("The snake moves according to the currently specified direction") --> isfood
```

### License

Since there is no license, it cannot be distributed casually by default. 