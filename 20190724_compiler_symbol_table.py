# coding:utf-8
"""
grammar:

statlist -> vec_dec+
var_dec -> type id (= expr)? ;
expr -> primary (+ primary)*
primary -> id
    | num
    | ( expr )
id -> [a-zA-Z]\w*
num -> [0-9]+
type -> float int
"""
import dataclasses
import enum
import unittest
from typing import List


class TokenType(str, enum.Enum):
    EOF = ''
    NUM = 'num'
    ID = 'id'
    MUL = 'mul'
    ADD = 'add'
    DOT = 'dot'
    COMMA = 'comma'
    VEC = 'vec'
    LBRACK = 'LRBACK'
    RBRACK = 'RRBACK'
    EQ = 'eq'
    PRINT = 'print'
    SEMI = 'semicolon'
    TYPE = 'type'


@dataclasses.dataclass()
class Token:
    type: str
    text: str
    line: int = dataclasses.field(default=0)


TYPE_TOKEN = {'float', 'int'}

TOKEN_MAP = {
    '+': TokenType.ADD,
    '*': TokenType.MUL,
    '(': TokenType.LBRACK,
    ')': TokenType.RBRACK,
    '.': TokenType.DOT,
    ',': TokenType.COMMA,
    '=': TokenType.EQ,
    ';': TokenType.SEMI,
}


# OP_TOKEN = {op: Token(type, op) for op, type in TOKEN_MAP.items()}


# noinspection PyShadowingBuiltins
class Lexer:
    def __init__(self, input: str):
        self.input = input
        self.p = -1
        self.c = ''
        self.consume()
        self.line = 1

    def consume(self):
        self.p += 1
        if self.p >= len(self.input):
            self.c = TokenType.EOF
        else:
            self.c = self.input[self.p]

    def match(self, target):
        if self.c != target:
            raise TypeError(f'Expecting {target}, found {self.c}')
        self.consume()

    def next_token(self):
        while self.c.isspace():
            if self.c == '\n':
                self.line += 1
            self.consume()
        if self.c == TokenType.EOF:
            return Token(TokenType.EOF, '', self.line)

        if self.c in TOKEN_MAP:
            token = Token(TOKEN_MAP[self.c], self.c, self.line)
            self.consume()
            return token

        if self.c.isdigit():
            return self.match_num()

        if self.c.isalpha():
            token = self.match_id()
            if token.text in TYPE_TOKEN:
                return Token(TokenType.TYPE, token.text, self.line)
            return token
        raise TypeError(f'Un expected char <{self.c}>')

    def match_id(self):
        id = []
        while self.c.isalnum():
            id.append(self.c)
            self.consume()
        return Token(TokenType.ID, ''.join(id), self.line)

    def match_num(self):
        num = []
        while self.c.isdigit():
            num.append(self.c)
            self.consume()
        return Token(TokenType.NUM, ''.join(num), self.line)


@dataclasses.dataclass()
class Node:
    token: Token

    def walk(self):
        pass


@dataclasses.dataclass()
class IntNode(Node):

    def walk(self):
        print(self.token.text, end='')


@dataclasses.dataclass()
class IdNode(Node):

    def walk(self):
        print(self.token.text, end='')


@dataclasses.dataclass()
class AddNode(Node):
    left: Node
    right: Node

    def walk(self):
        self.left.walk()
        self.right.walk()
        print(self.token.text, end='')


@dataclasses.dataclass()
class MulNode(Node):
    left: Node
    right: Node

    def walk(self):
        self.left.walk()
        self.right.walk()
        print(self.token.text, end='')


@dataclasses.dataclass()
class VecNode(Node):
    children: List[Node]

    def walk(self):
        print('[ ', end='')
        for child in self.children:
            child.walk()
            print(', ', end='')
        print('] ', end='')


@dataclasses.dataclass()
class DotNode(Node):
    left: Node
    right: Node

    def walk(self):
        self.left.walk()
        print(self.token.text, end='')
        self.right.walk()


@dataclasses.dataclass()
class EqNode(Node):
    left: Node
    right: Node

    def walk(self):
        self.left.walk()
        print(self.token.text, end='')
        self.right.walk()


@dataclasses.dataclass()
class PrintNode(Node):
    expr: Node

    def walk(self):
        print('print ', end='')
        self.expr.walk()


@dataclasses.dataclass(repr=False)
class Symbol:
    """
    Symbol 里面的符号，一般用来保存一些类型信息之类的
    """
    name: str
    type: str = dataclasses.field(default=None)

    def __repr__(self):
        return f'<{self.name}:{self.type}>' if self.type else self.name

    # def __str__(self):
    #     return self.__repr__()

class VariableSymbol(Symbol):
    """变量的 symbol"""


class BuiltInTypeSymbol(Symbol):
    """内置类型"""


class Scope:
    """作用域接口类"""

    def __init__(self):
        self.symbols = {}
        self._init_type_system()

    def _init_type_system(self):
        self.define(BuiltInTypeSymbol('int'))
        self.define(BuiltInTypeSymbol('float'))

    def get_scope_name(self):
        return 'global'

    def get_enclosing_scopy(self):
        return None

    def define(self, symbol: Symbol):
        self.symbols[symbol.name] = symbol

    def revolve(self, name: str):
        return self.symbols.get(name)


class Parser:
    def __init__(self, input: Lexer, size: int):
        self.input = input
        self.size = size
        self.p = 0
        self.lookahead: List[Token] = [None] * self.size

        for i in range(size):
            self.lookahead[i] = self.input.next_token()

    def consume(self):
        self.lookahead[self.p] = self.input.next_token()
        self.p = (self.p + 1) % self.size

    def LL(self, k: int):
        return self.lookahead[(self.p + k - 1) % self.size]

    def match(self, target: str):
        if self.LL(1).type != target:
            raise TypeError(f'Expecting {target}, found {self.LL(1).type}')

        self.consume()

    def statlist(self):
        self.scope = Scope()
        self.vec_dec()
        while self.LL(1).type == TokenType.TYPE:
            self.vec_dec()
        print(self.scope.symbols)

    def vec_dec(self):
        type = self.LL(1).text
        self.type()
        print(f'line {self.LL(1).line}: def {self.LL(1).text}')
        self.scope.define(Symbol(self.LL(1).text, type))
        self.id()
        if self.LL(1).type == TokenType.EQ:
            self.match(TokenType.EQ)
            self.expr()
        self.match(TokenType.SEMI)

    def expr(self):
        self.primary()
        while self.LL(1).type == TokenType.ADD:
            self.match(TokenType.ADD)
            self.primary()

    def primary(self):
        if self.LL(1).type == TokenType.NUM:
            return self.num()

        if self.LL(1).type == TokenType.ID:
            revolve = self.scope.revolve(self.LL(1).text)
            print(f'line {self.LL(1).line}: ref to {revolve}')
            return self.id()

        if self.LL(1).type == TokenType.LBRACK:
            self.match(TokenType.LBRACK)
            self.expr()
            self.match(TokenType.RBRACK)

    def num(self):
        token = IntNode(self.LL(1))
        self.match(TokenType.NUM)
        return token

    def id(self):
        self.match(TokenType.ID)

    def type(self):
        print(f'line {self.LL(1).line}: ref {self.LL(1).text}')
        self.match(TokenType.TYPE)


class Test(unittest.TestCase):
    def test(self):
        lexer = Lexer(
            """int i = 9;
            float j;
            int k = i + 2;
            """)
        token = lexer.next_token()
        while token.type != TokenType.EOF:
            print(token)
            token = lexer.next_token()
        print(token)

    def test_parser(self):
        lexer = Lexer("""int i = 9;
        float j;
        int k = i + 2;
        """)
        parser = Parser(lexer, 10)
        parser.statlist()
