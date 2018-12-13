# 用两个 stack 模拟 queue
# 这里的关键点在于：
# dequeue 时
# 1. 如果 stack2 不为空，因为 stack2 的元素全部来自于 stack1 的 push，所以 stack2 中的元素一定比 stack1 的中早 enqeue 进来所以此时直接 pop stack2 的栈顶元素即可
# 2. 如果 stack2 为空，则依序 pop stack1 中的元素并 push 到 stack2 中，此时 stack2 中的栈顶正好就是 stack1 最早进去的元素。
# 取 top 时同理
# 注意事项：
# dequee 和取 top 时斗仙判断 queue 是否为空
class EmptyError(Exception):
    pass

class Queue:
    def __init__(self):
        self._stack1 = []
        self._stack2 = []

    def enqueue(self, value):
        self._stack1.append(value)

    def dequeue(self):
        if self.is_empty():
            raise EmptyError('queue is empty, cant dequeue')
        if self._stack2:
            return self._stack2.pop()
        while self._stack1:
            self._stack2.append(self._stack1.pop())
        return self._stack2.pop()

    def top(self):
        if self.is_empty():
            raise EmptyError('queue is empty, cant top')
        if self._stack2:
            return self._stack2[-1]
        return self._stack1[0]

    def is_empty(self):
        return not self._stack1 and not self._stack2

    def get_size(self):
        return len(self._stack1) + len(self._stack2)

def test_queue():
    q = Queue()
    assert q.is_empty()

    try:
        q.top()
        assert False
    except EmptyError:
        pass

    q.enqueue('a')
    q.enqueue('b')
    q.enqueue('c')

    assert q.get_size() == 3
    assert q.top() == 'a'

    assert q.dequeue() == 'a'
    assert q.get_size() == 2
    assert q.top() == 'b'

    assert q.dequeue() == 'b'
    assert q.get_size() == 1
    assert q.top() == 'c'

    q.enqueue('d')
    assert q.get_size() == 2
    assert q.top() == 'c'

    assert q.dequeue() == 'c'
    assert q.get_size() == 1
    assert q.top() == 'd'

    assert q.dequeue() == 'd'
    assert q.get_size() == 0

test_queue()
