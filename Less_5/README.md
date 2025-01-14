# Домашнее задание к занятию «Упаковка приложения в контейнер»

Выполнив это задание, вы сможете запускать контейнеры Docker и упаковывать свои приложения в контейнеры.

### Цель задания

1. Сделать свой контейнер.
2. Научиться создавать контейнеры.
3. Научиться упаковывать приложения в контейнеры.

------

### [Задание 1](Task_1)

#### Установка Docker

1. Установите Docker для вашей операционной системы.
2. Проверьте работу, установив дистрибутив Ubuntu 16.04, с компиляторов gcc и любым текстовым редактором.
3. Соберите консольное приложение «Hello world».

 <h2 align="center">Сборка образа</h2>

```docker build -t h_w:v1 .```

<h2 align="center">Запуск контейнера</h2>

```docker run --name h_w -it h_w:v1```

### [Задание 2](Task_2)

#### Работа с образами

1. Упакуйте в контейнер любой проект из выполненных вами ранее домашних заданий для различных компиляторов — gcc и clang.
2. Проверьте их работу.

### Для сборки с компилятором gcc команды выполнять из папки /src_gcc

<h2 align="center">Сборка образа</h2>

```docker build -t fig_side:v1 .```

<h2 align="center">Запуск контейнера</h2>

```docker run --name fig_side -it fig_side:v1```

### Для сборки с компилятором clang команды выполнять из папки /src_clang

<h2 align="center">Сборка образа</h2>

```docker build -t fig_side_clang:v1 .```

<h2 align="center">Запуск контейнера</h2>

```docker run --name fig_side_clang -it fig_side:v1```
