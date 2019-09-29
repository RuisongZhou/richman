# richman
Project of Software Engineering at seedclass2017

* build
```bash
cd richman
make clean
make
```
if you want to add background music, first you should compile music part.
```bash
cd auplay
make clear
make
```
then change `initialize.c` and compile
```bash
    if (!IS_DEBUG){
        pthread_create(&(game_pointer->music), NULL, (void *)&playMusic, NULL);
        pthread_detach(game_pointer->music);
    } // remove explanatory note
```
* run
```bash
./rich.ext
```

## Author
Yu Peng, Zhiyu Zhang, Ruisong Zhou, Shusheng Yang, Zhaochuan Peng, Yixing Guo, Ziqing Pan.