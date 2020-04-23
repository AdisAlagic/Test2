﻿# Работа с программой


## Команда `print`
**Описание:** 
Выводит на экран текущую схему сотрудников

**Синтаксис:**
```bash
> print
```

## Команда `add`
**Описание:**
Добавляет в схему новое подразделение или сотрудника, если подразделение уже выбрано.
В случае, если зарплата будет указана не в цифре, она выставиться на 0
Чтобы отменить действие, нужно написать `!c`

**Синтаксис:**
Добавление нового подразделения
```bash
>add [Название подразделения]
```
Добавление сотрудника
```bash
> add
surname> [Фамилия]
name> [Имя]
middleName> [Отчество]
function> [Название специализации]
salary> [Зарплата в рублях]
```
## Команда `get`
**Описание:**
Выбирает подразделение или сотрудника. Индекс не может быть меньше 1 и соответствует цифре, которую отображает команда `print`

**Синтаксис:**
Выбор подразделения
```bash
> get [Индекс]
```
Выбор сотрудника
```bash
> get [Индекс подразделения] [Индекс сотрудника]
```

## Команда `edit`
**Описание:**
Позволяет редактировать подразделение или сотрудника по заданному параметру.
Для использования необходимо выбрать подразделение или сотрудника с помощью команды `get`
Для подразделения доступно только изменение `name`
Для сотрудника доступны следующие аргументы:
* name - Имя
* surname - Фамилия
* middleName - Отчество
* function - Специализация
* salary - Зарплата в рублях

Чтобы отменить действие, нужно написать `!c`

**Синтаксис:**
Редактирование подразделения
```bash
> edit name
name> [Новое имя]
```
Редактирование имени сотрудника
```bash
> edit name
name> [Новое имя]
```
## Команда `delete`
**Описание:**
Удаляет выбранный элемент или подразделение по индексу. Команда может быть сокращена до `del`

**Синтаксис:**
Удаление выбранного элемента
```bash
> delete
```
Удаление подразделения по индексу
```bash
> delete [Индекс]
```

## Команда `clear`
**Описание:**
Очищает консоль

**Синтаксис:**
```bash
> clear
```

## Команда `exit`
**Описание:**
Завершает выполнение программы

**Синтаксис:**
```bash
> exit
```

## Команда `undo`
**Описание:**
Отменяет последнее изменение

**Синтаксис:**
```bash
> undo
```

## Команда `redo`
**Описание:**
Возвращает последнее изменение

**Синтаксис:**

```bash
> redo
```

## Команда `drop`
**Описание:**
Сбрасывает выделение с выбранного элемента, если присутствует.

**Синтаксис:**

```bash
> drop
```
## Команда `show`
**Описание:**
Показывает текущий выбранный элемент

**Синтаксис:**
```bash
> show
```

## Команда `average`
**Описание:**
В зависимости от выбранного элемента показывает зарплату. Если это подразделение, то показывает среднюю зарплату подразделения, если выбран сотрудник, то показывает его зарплату.

**Синтаксис:**

```bash
> average
```
