# Калькулятор:
#   добавить на стек i32 - 0 n
#   напечатать и удалить вершину стека - 1
#   сложить последние два элемента стека - 2
.section .bss
my_stack:
    .space 1000

.section .data
jumptable:
    .long stack_push # jumptable + 0 * 4 == adr(stack_push)
    .long stack_pop # jumptable + 1 * 4 == adr(stack_pop)
    .long stack_sum # jumptable + 2 * 4 == adr(stack_sum)

printf_format:
    .string "%d\n"

scanf_format:
    .string "%d"

.section .text
.global main
main:
    xorl %ebx, %ebx

_loop:
    subl $4, %esp # резервируем память на стеке под перемнную, куда будем читать
    pushl %esp # кладем адрес зарезервираванной памяти
    pushl $scanf_format
    call scanf
    test %eax, %eax
    jz _finish

    mov 8(%esp), %eax

    # Выбираем нужную функцию (либо 3 if'а; либо таблица функций)

    # Считаем адрес, где лежит нужная функция
    leal jumptable(, %eax, 4), %eax # %eax = jumptable + 4 * %eax

    # Перекладываем адрес функции в регистр
    movl (%eax), %eax

    # Вызываем нужную функцию
    pushl %ebx
    call *%eax

    addl $16, %esp

    addl %eax, %ebx

    jmp _loop

_finish:
    addl $12, %esp
    xorl %eax, %eax
    ret

stack_push: # int stack_push(int stack_size)
    push %ebp
    mov %esp, %ebp

    call readi32
    movl 8(%ebp), %ecx # Перекладываем первый агрумнет функции stack_push в %ecx
    movl %eax, my_stack(, %ecx, 4) # добавляем новый элемент на стек

    mov %ebp, %esp
    pop %ebp

    movl $1, %eax # Пишем на сколько изменился размер стека

    ret

stack_pop: # int stack_pop(int stack_size)
    movl 4(%esp), %ecx # Перекладываем первый аргуент функции
    decl %ecx
    movl my_stack(, %ecx, 4), %eax # берем вершину стека

    # печатаем с помощью printf("%d\n", number)
    pushl %eax
    pushl $printf_format
    call printf

    addl $8, %esp

    movl $-1, %eax # Пишем на сколько изменился размер стека

    ret

stack_sum: # int stack_sum(int stack_size)
    push %ebp
    mov %esp, %ebp
    pushl %ebx

    movl 8(%ebp), %ecx # Перекладываем первый аргумент
    decl %ecx
    movl my_stack(, %ecx, 4), %eax # Берем значение первого элемента
    decl %ecx
    movl my_stack(, %ecx, 4), %ebx # Берем значение второго элемента

    addl %ebx, %eax
    movl %eax, my_stack(, %ecx, 4) # На месте второго элемента пишем сумму первого и второго

    popl %ebx
    mov %ebp, %esp
    pop %ebp

    movl $-1, %eax # Пишем на сколько изменился размер стека

    ret
