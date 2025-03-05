# poolday
Thread pool simulation written in C++26

## Build

```bash
xmake build poolday
```

Note: For different number of threads or log options, you have to
modify the main.cpp file (line 10). Default is 8 and INFO.

## Run

```bash
xmake run poolday number_of_tasks task_1_arrive_time task_1_exe_time ...
```
### Runing Tests (in linux)

```bash
xargs -I {} bash -c "{}" < in/1.txt
# ...
xargs -I {} bash -c "{}" < in/2.txt
# ...
xargs -I {} bash -c "{}" < in/3.txt
# ...
```
