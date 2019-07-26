# coding:utf-8
"""
grammar:

statlist -> (assign|vec_dec|call_func|func_dec|block)+
func_dec -> type id '(' (type id)* ')' block
call_func -> id '(' (type id)* ')' block
block -> { statlist ('return' primary;)? }
assign -> id = expr;
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
    CLASS = 'class'
    RETURN = 'return'
    LCURLY = 'LCURLY'
    RCURLY = 'RCURLY'


@dataclasses.dataclass()
class Token:
    type: str
    text: str
    line: int = dataclasses.field(default=0)


TYPE_TOKEN = {'float', 'int', 'void'}

TOKEN_MAP = {
    '+': TokenType.ADD,
    '*': TokenType.MUL,
    '(': TokenType.LBRACK,
    ')': TokenType.RBRACK,
    '{': TokenType.LCURLY,
    '}': TokenType.RCURLY,
    '.': TokenType.DOT,
    ',': TokenType.COMMA,
    '=': TokenType.EQ,
    ';': TokenType.SEMI,
}

KEYWORDS_MAP = {
    'print': TokenType.PRINT,
    'return': TokenType.RETURN,
    'class': TokenType.CLASS,
    'float': TokenType.TYPE,
    'int': TokenType.TYPE,
    'void': TokenType.TYPE,
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
            if token.text in KEYWORDS_MAP:
                return Token(KEYWORDS_MAP[token.text], token.text, self.line)
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


class VariableSymbol(Symbol):
    """变量的 symbol"""


class Type:
    pass


class BuiltInTypeSymbol(Type, Symbol):
    """内置类型"""


class Scope:
    """作用域接口类"""

    def __init__(self, prev: 'BaseScope' = None):
        self.symbols = {}
        self.prev = prev

    def get_scope_name(self):
        return 'global'

    def get_enclosing_scopy(self) -> 'BaseScope':
        return self.prev

    def define(self, symbol: Symbol):
        self.symbols[symbol.name] = symbol

    def resolve(self, name: str) -> Symbol:
        env = self
        while env is not None:
            if name in env.symbols:
                return env.symbols[name]
            env = env.get_enclosing_scopy()
        return None


class MethodSymbol(Scope, Symbol):
    """方法类型
    作为 Scope 是为函数参数存在。
    不过函数参数为什么需要一个特殊的 scope 而不是跟 Local Scope 一起
    """

    def __init__(self, name=None, type=None, prev: 'BaseScope' = None):
        self.name = name
        self.type = type
        super().__init__(prev)


class BaseScope(Scope):
    pass


class GlobalScope(BaseScope):
    def __init__(self, *args, **kwarg):
        super().__init__(*args, **kwarg)
        self.init_type_system()

    def init_type_system(self):
        for type in TYPE_TOKEN:
            self.define(BuiltInTypeSymbol(type))


class LocalScope(BaseScope):
    pass


class Parser:
    def __init__(self, input: Lexer, size: int):
        self.input = input
        self.size = size
        self.p = 0
        self.lookahead: List[Token] = [None] * self.size
        self.indent = 0

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

    def program(self):
        self.current_scope = GlobalScope(prev=None)
        self.statlist()
        self.print(self.current_scope.symbols)

    def statlist(self):
        while True:
            if self.LL(1).type == TokenType.TYPE:
                if self.LL(3).type == TokenType.LBRACK:
                    self.func_dec()
                else:
                    self.var_dec()
            elif self.LL(1).type == TokenType.LCURLY:
                self.block()
            elif self.LL(1).type == TokenType.ID:
                if self.LL(2).type == TokenType.LBRACK:
                    self.call_func()
                else:
                    self.assign()
            else:
                break

    def assign(self):
        self.id()
        self.match(TokenType.EQ)
        self.expr()
        self.match(TokenType.SEMI)

    def block(self):
        self.indent += 5
        self.print('Enter block')
        self.current_scope = LocalScope(prev=self.current_scope)
        self.match(TokenType.LCURLY)
        self.statlist()
        if self.LL(1).text == 'return':
            self.match(TokenType.RETURN)
            self.primary()
            self.match(TokenType.SEMI)
        self.match(TokenType.RCURLY)
        self.print('Exit block, block symbols: %s' % self.current_scope.symbols)
        self.indent -= 5
        self.current_scope = self.current_scope.get_enclosing_scopy()


    def func_dec(self):
        type = self.LL(1).text
        self.type()
        method_symbol = MethodSymbol(name=self.LL(1).text, type=type,
                                     prev=self.current_scope)
        self.current_scope.define(method_symbol)
        self.current_scope = method_symbol
        self.id()
        self.match(TokenType.LBRACK)
        while self.LL(1).type == TokenType.TYPE:
            type = self.LL(1).text
            self.type()
            self.current_scope.define(Symbol(self.LL(1).text, type))
            self.id()
            if not self.LL(1).type == TokenType.RBRACK:
                self.match(TokenType.COMMA)
        self.match(TokenType.RBRACK)
        self.block()
        self.current_scope = method_symbol.get_enclosing_scopy()

    def call_func(self):
        self.print(f'line {self.LL(1).line}: ref to func {self.LL(1).text}')
        self.id()
        self.match(TokenType.LBRACK)
        while self.LL(1).type in {
            TokenType.ID,
            TokenType.NUM,
            TokenType.LBRACK,
        }:
            self.primary()
            if not self.LL(1).type == TokenType.RBRACK:
                self.match(TokenType.COMMA)
        self.match(TokenType.RBRACK)
        self.match(TokenType.SEMI)

    def var_dec(self):
        type = self.LL(1).text
        self.type()
        self.print(f'line {self.LL(1).line}: def {self.LL(1).text}')
        self.current_scope.define(Symbol(self.LL(1).text, type))
        self.id()
        if self.LL(1).type == TokenType.EQ:
            self.match(TokenType.EQ)
            self.expr()
        self.match(TokenType.SEMI)

    def print(self, msg):
        print(' ' * self.indent, end='')
        print(msg)

    def expr(self):
        self.primary()
        while self.LL(1).type == TokenType.ADD:
            self.match(TokenType.ADD)
            self.primary()

    def primary(self):
        if self.LL(1).type == TokenType.NUM:
            return self.num()

        if self.LL(1).type == TokenType.ID:
            revolve = self.current_scope.resolve(self.LL(1).text)
            self.print(f'line {self.LL(1).line}: ref to {revolve}')
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
        self.print(f'line {self.LL(1).line}: ref {self.LL(1).text}')
        self.match(TokenType.TYPE)


class Test(unittest.TestCase):
    def test(self):
        lexer = Lexer(
            """int i = 9;
            float f(int x, float y)
            {
                float i;
                { float z = x+y; i = z; }
                { float z = i+1; i = z; }
                return i;
            }
            void g()
            {
                f(i, 2)
            }
            """)
        token = lexer.next_token()
        while token.type != TokenType.EOF:
            print(token)
            token = lexer.next_token()
        print(token)

    def test_parser(self):
        lexer = Lexer(
            """int i = 9;
            float f(int x, float y)
            {
                float i;
                { float z = x+y; i = z; }
                { float z = i+1; i = z; }
                return i;
            }
            void g()
            {
                f(i, 2);
            }
            """)
        parser = Parser(lexer, 10)
        parser.program()
